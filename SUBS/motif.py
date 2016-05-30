import sys


def find_motif_locations(dna, motif):
    motif_locations = []

    if len(dna) < len(motif):
        raise ValueError('Motif can\'t be shorter than sequence')

    if len(motif) == len(dna) and motif != dna:
        return motif_locations

    for _ in range(len(dna) - len(motif) + 1):
        if dna[_:_ + len(motif)] == motif:
            motif_locations.append(_ + 1)

    return motif_locations

if __name__ == '__main__':
    sequences = open(sys.argv[1]).read().split()

    print(
        ' '.join(
            str(_)
            for _ in
            find_motif_locations(
                sequences[0],
                sequences[1]
            )
        )
    )
