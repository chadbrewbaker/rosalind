#! /usr/bin/env awk -f

# DISCLAIMER - If you are interested in the Rosalind Project, please solve
# this problem on your own before reading my solution.

# This counts the number of nucleotides in DNA sequence.
BEGIN {
	  symbols["A"] = 0
	    symbols["C"] = 0
	      symbols["G"] = 0
	        symbols["T"] = 0
	}

	{
		  chars = length($0)
		    for(i = 1; i <= chars; i++) {
			        char = substr($0, i, 1)
				    symbols[char]++
					     }
			    }

			    END {
				      print symbols["A"], symbols["C"], symbols["G"], symbols["T"]
			      }
