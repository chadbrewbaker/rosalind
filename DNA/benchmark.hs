import System.Process
import Criterion.Main

main = defaultMain [
     bench "wc baseline" $ nfIO (readProcess "wc" ["rosalind_dna.txt"] []),
     bench "Python version" $ nfIO (readProcess "python" ["count.py", "rosalind_dna.txt"][]), 
     bench "C version" $ nfIO (readProcess "./a.out" ["rosalind_dna.txt"][]),
     bench "C++ version" $ nfIO (readProcess "./b.out" ["rosalind_dna.txt"][]),
     bench "Awk version" $ nfIO (readProcess "awk" ["-f",  "count.awk",  "rosalind_dna.txt"][]) 
  ]

