import sys

with open(sys.argv[1]) as file:
    for dna in file:
        print ' '.join([str(dna.count(c)) for c in 'ACGT'])
