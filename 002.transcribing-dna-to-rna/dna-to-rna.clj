(print (clojure.string/replace 
  (slurp 
    (first *command-line-args*)) "T" "U"))
