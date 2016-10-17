gcc count.c -Wall -O2 -o a.out 
gcc read.c -Wall -O2 -o read.out
gcc readBuf.c -Wall -O2 -o readBuf.out
g++ readBufAsync.cpp -Wall  -std=c++14 -o readBufAsync.out
g++ readBufThread.cpp -Wall  -std=c++14 -o readBufThread.out
gcc fread.c -Wall -O2 -o fread.out
gcc freadzbuf.c -Wall -O2 -o freadzbuf.out
g++ count.cpp -Wall -O2 -o b.out
stack exec ghc benchmark
stack exec ./benchmark -- --output count.html
