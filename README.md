# mast - 
|project project implemented in 2020| (n^2 solution)

Implementation of an algorithm that reads a set of n rooted trees in the [NEWICK](https://evolution.gs.washington.edu/phylip/newicktree.html "NEWICK") format, then for each of n(n-1)/2 pairs of trees calculates the minimum number of leaves whose removal from both trees will make them isomorphic.
In IT this problem is known as [Maximum agreement subtree problem.](https://en.wikipedia.org/wiki/Maximum_agreement_subtree_problem "Maximum agreement subtree problem.")

Input
The value of n denotes the size of the set of n rooted trees.
n rooted trees in NEWICK format.
Output
n(n-1)/2 comparisons of input trees (each with each). The order of comparison: 1-2, 1-3, ..., 1-n, 2-3, 2-4, ..., 2-n, ..., (n-1) -n.

Example:
Input
4
(1,5,(10,6,3),(2,(8,7)),(9,4));
((7,(3,(4,9,(1,2)))),8,(5,(10,6)));
(7,((6,(9,5),(8,3)),(1,(2,10,4))));
(7,(8,3,4,6,1),(9,5,10),2);

Output
5
7
6
6
6
6
