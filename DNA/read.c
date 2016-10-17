/* fread example: read an entire file */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  FILE *pFile;
  long lSize;
  char *buffer;
  size_t result;

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

  // copy the file into the buffer:
  result = read(fd, buffer, lSize);
  if (result != lSize) {
    fputs("Reading error", stderr);
    exit(3);
  }

  /* the whole file is now loaded in the memory buffer. */

  // terminate
  fclose(pFile);
  free(buffer);
  printf("%lu %lu %lu %lu\n", 1ul, 1ul, 1ul, 1ul);

  return 0;
}
