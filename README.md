# Brute-Force-vs-Dynamic-Programming
This repository contains files illustrating different ways to solve problems that involve finding the right combination of values from set 
(usually of size n) to maximizing one value relating to the items of the set but while also minimizing another separate category value or being constrained by that value. The most known implementation involves some thing called a knapsack algorithm which can get either that max value or which item combinations makes that max value. 

One example is fairly simple and from HackerRank, it is a dishwashing problem where each plate has a payment of p for washing it and a pay dock of d for not washing it. There are n plates but can only wash k plates (k < n). Work to maximize the pay. Simpler since combinations are just the subsets of length k from the set of length n, rather than the whole power set of set n.

Some examples are shown with comments in python and C++

The link is below:

https://www.hackerrank.com/contests/101hack41/challenges/washing-plates

A link that contains some introduction and the utility of knapsack algorithms:
http://www.es.ele.tue.nl/education/5MC10/Solutions/knapsack.pdf
