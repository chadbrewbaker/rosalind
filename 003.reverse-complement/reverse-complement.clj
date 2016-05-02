; Ran with lein exec

(def nmap {\A \T, \G \C})

(def nucleotide-map
  (merge 
    nmap 
    (clojure.set/map-invert nmap))) ; Entirely unnecessary

(defn get-sequence 
  "Get DNA sequence from a file"
  [name-of-file]
  (slurp name-of-file))

(defn reverse-complement
  "Find the reverse complement"
  [DNA]
  (clojure.string/join "" (map nucleotide-map (reverse (seq DNA))))) ; Beautiful!

(println (reverse-complement (get-sequence (second *command-line-args*))))
