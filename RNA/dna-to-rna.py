import sys

with open(sys.argv[1]) as f:
    DNA = f.read()

print(DNA.replace('T', 'U'))
