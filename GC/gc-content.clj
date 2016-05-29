(defn gc-count           
  [DNA]
  (reduce + (vals (select-keys (frequencies DNA) [\C \G]))))

(defn gc-percent 
  "Compute GC percent"
  [DNA]
  (float (/ (gc-count DNA) (count DNA))))
