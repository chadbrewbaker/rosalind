/* fread example: read an entire file */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define Chunk (16384)

struct Counts {
  size_t a;
  size_t t;
  size_t c;
  size_t g;
};

int main(int argc, char *argv[]) {
  FILE *pFile;
  struct Counts counter;
  long lSize;
  char *buffer;
  size_t result;
  char c;
  int i, j;
  if (argc < 2)
    return 1;

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
  int lastRead = lSize % Chunk;
  for (i = 0; i < fullReads; i++) {
    result = read(fd, &buffer[i * Chunk], Chunk);

    for (j = 0; j < Chunk; j++) {
      c = buffer[i * Chunk + j];
      if (c == 'A')
        counter.a++;
      if (c == 'T')
        counter.t++;
      if (c == 'C')
        counter.c++;
      if (c == 'G')
        counter.g++;
    }
  }
  result = read(fd, &buffer[fullReads * Chunk], lastRead);
  for (j = 0; j < lastRead; j++) {
    c = buffer[fullReads * Chunk + j];
    if (c == 'A')
      counter.a++;
    if (c == 'T')
      counter.t++;
    if (c == 'C')
      counter.c++;
    if (c == 'G')
      counter.g++;
  }

  // copy the file into the buffer:
  // result = read(fd,buffer,lSize);
  //  #if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

  /* the whole file is now loaded in the memory buffer. */

  // terminate
  fclose(pFile);
  free(buffer);
  printf("%lu %lu %lu %lu\n", counter.a, counter.t, counter.c, counter.g);
  // printf("%lu %lu %lu %lu\n", 1ul, 1ul, 1ul,1ul);

  return 0;
}
