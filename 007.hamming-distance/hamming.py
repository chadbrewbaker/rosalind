import sys


def compute_hamming_distance(sequences):
    '''Computes the Hamming Distance of an array of two sequences
    of the same length.
    '''

    if len(sequences[0]) != len(sequences[1]):
        raise ValueError('Sequences must be of the same length')

    # Will generate a huge list of tuples for large sequences...
    # return len(
    #     [
    #         (sequences[0][_], sequences[1][_])
    #         for _
    #         in range(len(sequences[0]))
    #         if sequences[0][_] != sequences[1][_]
    #     ]
    # )

    hamming_distance = 0

    for _ in range(len(sequences[0])):
        if sequences[0][_] != sequences[1][_]:
            hamming_distance += 1

    return hamming_distance


if __name__ == '__main__':
    print(
        compute_hamming_distance(
            open(sys.argv[1]).read().split()
        )
    )
