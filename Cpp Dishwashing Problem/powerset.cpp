#include "powerset.hpp"
#include <iostream>
using namespace std;

subsetn* powerSet(int indexCardinality)
{
	subsetn* pSet = new subsetn[indexCardinality+1]; //Make an array of a collection of subsets, the extra is just to include the empty set
	int* original = new int[indexCardinality]; //Subset needs an original set for reference 
	for (int i = 0; i < indexCardinality; i++)
	{
		*(original + i) = i;
	} //Generate original set for makeSubset to use, values range from (0,n-1)
	for (int j = 0; j < indexCardinality + 1; j++)
	{
		pSet[j].member = makeSubset(original, indexCardinality, j); //Make each subsets member attribute equal to the collection of subsets that can be 
		//made from length j
	}
	delete[] original; //Original was only needed for generating subsets, should be deleted now at this point
	return pSet;
}

void showPset(subsetn* sets, int cardinality)
{
	for (int i = 0; i < cardinality + 1; i++)
	{
		int count = combination(cardinality, i); //Print each collection of subsets in the powerset
		printSubset(sets[i].member, count, i);
	}
}