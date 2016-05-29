import re
import sys

label = re.compile(r'>(.*)')

with open(sys.argv[1]) as file:
    for line in file:
        dna = ''
        l = line.rstrip('\n')
        m = label.match(l)

        if m:
            print(m.group(1))

        else:
            dna += l
            print(dna)
