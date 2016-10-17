/* fread example: read an entire file */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <thread>
#include <future>
#include <vector>

#define Chunk (16384)

struct Counts {
  size_t a;
  size_t t;
  size_t c;
  size_t g;
};

Counts sumIt(char *buffer, size_t length) {
  size_t i;
  char c;
  Counts counter;
  counter.a = counter.t = counter.c = counter.g=0;

  for (i = 0; i < length; i++) {
    c = buffer[i];
    if (c == 'A')
      counter.a++;
    if (c == 'T')
      counter.t++;
    if (c == 'C')
      counter.c++;
    if (c == 'G')
      counter.g++;
  }
  return counter;
}

int main(int argc, char *argv[]) {
  FILE *pFile;
  //struct Counts counter;
  long lSize;
  char *buffer;
  size_t result;
 // char c;
  int i;//, j;
  if (argc < 2)
    return 1;
  std::vector<std::future<Counts>> results;

  //Counts *cArr;

  pFile = fopen(argv[1], "rb");

  if (pFile == NULL) {
    fputs("File error", stderr);
    exit(1);
  }

  int fd = fileno(pFile);

  // obtain file size:
  fseek(pFile, 0, SEEK_END);
  lSize = ftell(pFile);
  rewind(pFile);

  // setbuf ( pFile, NULL );

  // allocate memory to contain the whole file:
  buffer = (char *)malloc(sizeof(char) * lSize);
  if (buffer == NULL) {
    fputs("Memory error", stderr);
    exit(2);
  }

  int fullReads = lSize / Chunk;
  // cArr = (Counts *)malloc(sizeof(Counts)*(fullReads+1));
  int lastRead = lSize % Chunk;
  results.reserve(fullReads+1);
  for (i = 0; i < fullReads; i++) {
    result = read(fd, &buffer[i * Chunk], Chunk);
    results.push_back(std::async(sumIt, &buffer[i * Chunk], Chunk));
    /* for (j = 0; j < Chunk; j++) {
       c = buffer[i * Chunk + j];
       if (c == 'A')
         counter.a++;
       if (c == 'T')
         counter.t++;
       if (c == 'C')
         counter.c++;
       if (c == 'G')
         counter.g++;
     }*/
  }
  result = read(fd, &buffer[fullReads * Chunk], lastRead);
  results.push_back(std::async(sumIt, &buffer[fullReads * Chunk], lastRead));

  // copy the file into the buffer:
  // result = read(fd,buffer,lSize);
  //  #if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

  /* the whole file is now loaded in the memory buffer. */

  // terminate
  fclose(pFile);
  Counts total;
  total.a = total.t = total.c = total.g = 0;
  for (i = 0; i < results.size(); i++) {
    Counts next = results[i].get();
   // printf("%lu %lu %lu %lu\n", next.a, next.t, next.c, next.g);
    total.a += next.a;
    total.t += next.t;
    total.c += next.c;
    total.g += next.g;
  }

  free(buffer);
  printf("%lu %lu %lu %lu\n", total.a, total.t, total.c, total.g);
  // printf("%lu %lu %lu %lu\n", 1ul, 1ul, 1ul,1ul);

  //flush(STDIO);
  return 0;
}
