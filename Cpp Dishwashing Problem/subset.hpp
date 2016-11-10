#ifndef SUBSET_HPP
#define SUBSET_HPP
//For the continue next fn. nextSet contains the new subset and an int that determines if there are more subsets to find.
struct nextSet
{
	int* set; // The new subset
	int hasNext; //A flag to determine if there are more sets to find, this value is meant to be relevant to outside functions 
};
//Function explanations are in subset.cpp
int** makeSubset(int* original, int originalSize, int subsize);
nextSet determineNext(int* original, int originalSize, int* current, int subsize);
int factorial(int n);
int combination(int n, int r);
void printSubset(int** subSet, int length, int subsize);
void inputAssign(int* inpts, int length);
#endif
