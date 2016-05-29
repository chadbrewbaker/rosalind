import sys
import string

with open(sys.argv[1]) as f:
    DNA = f.read().strip()

print(DNA.translate(string.maketrans('ATGC', 'TACG')))
