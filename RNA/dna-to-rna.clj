(print (clojure.string/replace 
  (slurp 
    (second *command-line-args*)) "T" "U"))
