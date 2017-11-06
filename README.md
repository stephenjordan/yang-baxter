# yang-baxter
Code to generate all permutation-matrix solutions to the Yang-Baxter up to dimension 25 by pruned depth-first-search. Also, the solutions.

The text files contain all the permutations satisfying the Yang-Baxter
relation for n=2,3,4,5. That is, each permutation matrix M satisfies:

(M \otimes I) (I \otimes M) (M \otimes I) =
(I \otimes M) (M \otimes I) (I \otimes M)

Here M is a n^2 by n^2 matrix and I is an n by n identity matrix. Note
that, in the literature, this is one of two equations that are
sometimes referred to as the Yang-Baxter equation. Careful authors
refer to the above as the braided Yang-Baxter equation, and the other
version as the algebraic Yang-Baxter equation. M satisfies the
algebraic Yang-Baxter equation if and only if MS satisfies the braided
Yang-Baxter equation, where S is the swap gate. (Or should it be SM? I
forget.)

Let M be any n by n permutation matrix. Then, if Y is a solution to
the Yang-Baxter equation then so is: 

Y' = (M \otimes M) Y (M \otimes M)^{-1}

In this case I say that Y' is biconjugate to Y. Obviously, if A and B
are biconjugate then A and B have equivalent power as reversible
gates - they differ only by a relabelling of dit-states. Thus, it is
often more convenient to just have a list of one representative from
each biconjugacy class rather than a full list of Yang-Baxter
solutions. (Such a list is also faster to compute.)

In this directory, we have:

yb2reps.txt - biconjugacy class representatives for n=2
yb3reps.txt - biconjugacy class representatives for n=3
yb4reps.txt - biconjugacy class representatives for n=4
yb5reps.txt - biconjugacy class representatives for n=5

yb2.txt - full solution list for n=2
yb3.txt - full solution list for n=3
yb4.txt - full solution list for n=4
yb5.txt - full solution list for n=5

fillout.c - source code for a program that takes as input a list of
biconjugacy class representatives and produces the full solution list
by calculating the biconjugacy orbit of each representative

repsfast.c - source code for a program that produces the biconjugacy
class representatives for all classes of permutations satisfying
Yang-Baxter. The program works by depth-first-search. To set n, one
changes an initial #define directive in the program and
recompiles. One must also remember to change the #define directive for
nfac to be n factorial.

repspartfast.c - source code to compute some of the biconjugacy class
representatives. We need this because for n=5 the computation takes
too long and must be split into pieces which are then farmed out to a
cluster. The command line arguments to repspartfast.c are the first
three entries in the Lehmer code for a permutation. The program then
finds all permutations satisfying the Yang-Baxter relation whose
Lehmer code starts with these values. In practice, the computations
did not finish fast enough, so I had to break up some searches at a
deeper level of the search tree, i.e. specifying as many as five of
the entries of the Lehmer code.

makejobs.c - a little program to generate the repspartfast jobs on the
cluster. This and repspartfast.c can be easily modified to split the
computation into smaller jobs, as discussed above.
