#include "subset.hpp"
#include <iostream>
using namespace std;
//above are stated just for the print subset function

int factorial(int n) //Iterative factorial fn; i.e 5! = 5 * 4 * ... * 2 *1
{
	if (n == 1 || n == 0)
		return 1;
	else if (n < 0)
		return 0;
	else
	{
		int product = n;
		int i = n - 1;
		while (i > 1)
		{
			product = product * i;
			i--;
		}
		return product;
	}
}

int combination(int n, int r) //Gives combinations to determine the amount of subsets of length r from a base set of length n
/*
n! / ((n - r)!r!)
*/
{
	int temp = factorial(r) * factorial(n - r);
	int result = factorial(n) / temp;
	return result;
}

int** makeSubset(int* original, int originalSize, int subsize) //Returns an array of arrays of integers that denote the ways you can order a 
//subset of length k from base set of length n where usually (n > k) the integers in each subset represent the indexes of the base set so each index from 
// a subset could be used to map to an array of persay, objects, and make a combination of those
// Also note in this example it is assumed that order DOESNT MATTER and there is NO REPETITION ALLOWED
{
	// ORiginal Example: [1,2,3,4]
	//5 4 3 2 
	//Ex Size 3
	//Answer [[1,2,3],[1,3,4],[2,3,4]]
	if (subsize == 0)
	{
		int** totalSet = new int*[1]; //To keep type compatibility
		totalSet[0] = {}; // Empty set
		return totalSet;
	}
	else if (originalSize == subsize)
	{
		int** totalSet = new int*[1];
		int* ocopy = new int[originalSize];
		for (int i = 0; i < originalSize; i++)
		{
			ocopy[i] = i;
		}
		totalSet[0] = ocopy; //Make a copy of the original array and return it just in case you need
		// to add it to a powerset
		return totalSet;
	}
	else
	{
	int totalSize = combination(originalSize, subsize); //Get subsets length
	int** totalSet = new int*[totalSize]; //Initialize the totalSet
	int* starter = new int[subsize]; // Make the first subset
	int* nextptr = new int[subsize]; //Have a pointer to the nextset, (which hasnt yet been created) to be used to determine the next subset
	int index = 1; //Next index to go to 
	int terminate = 1; // Stands for true in determineNext
	for (int i = 0; i < subsize; i++)
		{
		*(starter + i) = *(original + i);
		}
	*(totalSet) = starter; //make starter
	nextptr = starter; // use this to start the while loop that will make the next subsets
	do //The do while is the cleaner implementation, just catch the exception cases k = 0,n in if statements
		{
		nextSet next = determineNext(original, originalSize, nextptr, subsize); //Get the nextset and determine if there are more subsets to find
		int* nextset = next.set; //Get the subset
		terminate = next.hasNext; //Determine if there are more subsets to find
		*(totalSet + index) = nextset; //Add to totalset
		nextptr = nextset; //Have the newpointer point to the new subset so it could be used in the next determineNext fn. call without any read or
		//memory access violations
		index++; // Move to next index in totalset so it can be given another subset to add
		} while (terminate); //Continue until there are no more unique subsets left to find
	delete nextptr; //No longer needed so delete pointer but not contents
	return totalSet;
	}
}

nextSet determineNext(int* original, int originalSize, int* current, int subsize)
//Use the original set, its size, the subset length, and the current subset you are in the sequence of subsets of to find the next subset
//and determine if there are anymore left to find
{
	//Example orginal: [1,2,3,4] size = 4
	//Example subsize 3
	// Example current: [1,3,4] or [1,2,3]
	// Correct Result of this is a nextSet whose
	//nextset.set = [2,3,4]
	//nextset.hasnext = 0;
	//second ex result
	// nextset.set = [1,3,4]
	// nextset.hasnext = 1;
	nextSet nextset;
	nextset.set = new int[subsize];
	if (current[0] == (originalSize - subsize)) //Since order is irrelevant and no repetition the first element of the last subset would be 
	// kth-to-the-last index of the original set i.e. for k = 2 and n = 5 the first element of the last subset of length 2 would be the fourth index
	// but because of 0 based indexing it would originalset[3] :)
	{
		for (int i = 0; i < subsize; i++)
		{
			*(nextset.set + i) = *(current + i);
		} //Make nextset's set attribute to current
		nextset.hasNext = 0; //Set continue flag to false now
		return nextset;
	}
	else
	{
		int marker = subsize - 1; //last index of current
		int bound = originalSize - 1; //last index of original
		if (current[marker] < original[originalSize - 1]) 
		/*
		The purpose of this is to check where (which index) in the current subset to apply changes to make the new subset
		IF the last element of current is less than original's last element pass this statement and go to the for loop since the 
		last index of the current subset is the easiest one to make a change to and create a new subset
		i.e. k = 2 n = 4 current : [0,1,2] original: [0,1,2,3] since current[2] < original[3] we can just make a change at index 2
		making the new subset [0,1,3] 
		
		*/
		{
			;
		}
		else
		/*
		If it fails first move the index to the second to last index of current
		*/
		{
			marker--;
			while (current[marker] >= original[bound - 1])
			/*
			Keep comparing moving down the arrays of both to find the starting index to make changes for the new subset
			NOTE: IT IS ASSUMED THAT BOTH current and original are sorted beforehand
			*/
			{
				marker--;
				bound--;
			}
		}
		for (int i = 0; i < subsize; i++)
		{
			if (i < marker) //If the index is below marker just copy it to the new subset's corresponding index
			{
				*(nextset.set + i) = *(current + i);
			}
			else if (i == marker) //If the index is equal to the marker increment it and make it the value for the subset's corresponding index
			{
				int increment = *(current + i) + 1;
				*(nextset.set + i) = increment;
			}
			else //To keep the rest of the subset ordered and all the following subsets ordered as well, make the next index of the new subset
				// to the incremented value of the previous index
			{
				int newVal = *(nextset.set + i - 1) + 1;
				*(nextset.set + i) = newVal;
			}
		}
		nextset.hasNext = 1; //Set continue flag to true, there are still more subsets left to find
		return nextset;
	}
}

void printSubset(int** subSet, int length, int subsize) //With all the subsets of length k from base length n found, lets print them
{
	for (int i = 0; i < length; i++)
	{
		cout << "{ "; //To denote this an individual combination of length subsize
		for (int j = 0; j < subsize; j++)
		{
			if (j == subsize - 1)
				cout << subSet[i][j]; //If last value just output
			else
				cout << subSet[i][j] << ", "; //If not last value, output and output comma
		}
		cout << " }" << endl;
	}
}
void inputAssign(int* inpts, int length) //Generate a dyanmic alloc array with val from range(0,length - 1)
{
	for (int i = 0; i < length; i++)
		*(inpts + i) = i;
}