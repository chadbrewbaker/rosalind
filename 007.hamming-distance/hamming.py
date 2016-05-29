import sys


def compute_hamming_distance(sequences):
    '''Computes the Hamming Distance of an array of two sequences
    of the same length.
    '''

    if len(sequences[0]) != len(sequences[1]):
        raise ValueError('Sequences must be of the same length')

    return sum(_ != __ for _, __ in zip(sequences[0], sequences[1]))


if __name__ == '__main__':
    print(
        compute_hamming_distance(
            open(sys.argv[1]).read().split()
        )
    )
