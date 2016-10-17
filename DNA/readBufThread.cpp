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
  std::atomic<size_t> a;
  std::atomic<size_t> t;
  std::atomic<size_t> c;
  std::atomic<size_t> g;
  void add(size_t ia, size_t it,size_t ic, size_t ig){
       a += ia;
       t += it;
       c += ic;
       g += ig;
  }
  void zero(){
    a=t=c=g=0;
  }

};

void sumIt(char *buffer, size_t length,  
    std::atomic<size_t> &ra, std::atomic<size_t> &rt,std::atomic<size_t> &rc,std::atomic<size_t> &rg) {
  size_t i;
 
  size_t a,t,c,g;
  char ch;
  //Counts counter;
  a = t = c = g=0;

  for (i = 0; i < length; i++) {
    ch = buffer[i];
    if (ch == 'A')
      a++;
    if (ch == 'T')
      t++;
    if (ch == 'C')
      c++;
    if (ch == 'G')
      g++;
  }
  //return counter;
  ra += a;
  rt += t;
  rc += c;
  rg += g;
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
  std::vector<std::thread> results;
   std::atomic<size_t> a(0);
  std::atomic<size_t> t(0);
  std::atomic<size_t> c(0);
  std::atomic<size_t> g(0);

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
    results.push_back(std::thread(sumIt, &buffer[i * Chunk], Chunk, 
      std::ref(a),std::ref(t),std::ref(c),std::ref(g)));
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
  results.push_back(std::thread(sumIt, &buffer[fullReads * Chunk], lastRead, 
    std::ref(a),std::ref(t),std::ref(c),std::ref(g)));

  // copy the file into the buffer:
  // result = read(fd,buffer,lSize);
  //  #if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

  /* the whole file is now loaded in the memory buffer. */

  // terminate
  fclose(pFile);

  
  for (i = 0; i < results.size(); i++) {
   results[i].join();
  }

  free(buffer);
  printf("%lu %lu %lu %lu\n", a.load(), t.load(), c.load(), g.load());
  // printf("%lu %lu %lu %lu\n", 1ul, 1ul, 1ul,1ul);

  //flush(STDIO);
  return 0;
}
