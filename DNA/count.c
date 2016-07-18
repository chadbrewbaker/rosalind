#include <stdio.h>
#include <string.h>

struct Counts {
  size_t a;
  size_t t;
  size_t c;
  size_t g;
};

int main(int argc, char *argv[]) {

  struct Counts counter;

  if (argc < 2)
    return 1;
  FILE *fp = fopen(argv[1], "r");

  char c;
  while ((c = getc(fp)) != EOF) {
    if (c == 'A')
      counter.a++;
    if (c == 'T')
      counter.t++;
    if (c == 'C')
      counter.c++;
    if (c == 'G')
      counter.g++;
  }
  fclose(fp);

  printf("%lu %lu %lu %lu\n", counter.a, counter.t, counter.c, counter.g);

  return 0;
}
