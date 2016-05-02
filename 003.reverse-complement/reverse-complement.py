import sys

n_map = {
    'A': 'T',
    'T': 'A',
    'G': 'C',
    'C': 'G',
}

with open(sys.argv[1]) as f:
    DNA = f.read().strip()

print(
    ''.join(
        n_map[nucleotide] for nucleotide in DNA[::-1]
    )
)
