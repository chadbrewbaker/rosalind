import System.Process
import Criterion.Main

main = defaultMain [
     bench "wc baseline" $ nfIO (readProcess "wc" ["rosalind_dna.txt"] []),
     bench "read" $ nfIO (readProcess "./read.out" ["rosalind_dna.txt"][]),
     bench "readBuf" $ nfIO (readProcess "./readBuf.out" ["rosalind_dna.txt"][]),
     bench "readBufAsync" $ nfIO (readProcess "./readBufAsync.out" ["rosalind_dna.txt"][]),
     bench "readBufThread" $ nfIO (readProcess "./readBufThread.out" ["rosalind_dna.txt"][]),
     bench "fread" $ nfIO (readProcess "./fread.out" ["rosalind_dna.txt"][]),
     bench "freadzbuf" $ nfIO (readProcess "./freadzbuf.out" ["rosalind_dna.txt"][]),
     bench "Python version" $ nfIO (readProcess "python" ["count.py", "rosalind_dna.txt"][]),
     bench "C version" $ nfIO (readProcess "./a.out" ["rosalind_dna.txt"][]),
     bench "C++ version" $ nfIO (readProcess "./b.out" ["rosalind_dna.txt"][]),
     bench "Awk version" $ nfIO (readProcess "awk" ["-f",  "count.awk",  "rosalind_dna.txt"][]) ,
     bench "sort " $ nfIO (readProcess "sort" ["rosalind_dna.txt"][]),
     bench "uniq " $ nfIO (readProcess "uniq" ["rosalind_dna.txt"][])
  ]
