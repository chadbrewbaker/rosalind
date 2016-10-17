#include <stdio.h>
#include <string.h>

// struct Counts {
//  size_t a;
//  size_t t;
//  size_t c;
//  size_t g;
//};

int main(int argc, char *argv[]) {

  // struct Counts counter;
  size_t a, t, c, g;
  a = t = c = g = 0;
  //  counter.a = counter.t = counter.c = counter.g =0;
  if (argc < 2)
    return 1;
  FILE *fp = fopen(argv[1], "r");

  char ch;
  while ((ch = getc(fp)) != EOF) {
    if (ch == 'A')
      a++;
    if (ch == 'T')
      t++;
    if (ch == 'C')
      c++;
    if (ch == 'G')
      g++;
  }
  fclose(fp);

  printf("%lu %lu %lu %lu\n", a, t, c, g);

  return 0;
}
