#include "withvectorsandsort.hpp"
//Same as getMaxCheck but uses sort and vectors to write less code
int MaxfromSort(int n, int k, int* gains, int* losses)
{
	std::vector<int> profitVector (n, 0); 
	int deductions = 0;
	for (int i = 0; i < n; i++)
	{
		deductions += losses[i];
	}
	deductions = deductions * -1;
	for (int i = 0; i < n; i++)
	{
		profitVector[i] = gains[i] + losses[i] + deductions;
	} //same as before
	sort(profitVector.begin(), profitVector.end()); //sort vector
	int profits = 0; 
	for (int i = n - 1; i > n  - k - 1; i--) //Highest values are at last indexes
	{
		profits += profitVector[i]; //Add profits by item in profitVector k times
	}
	int adjustedprofits = profits + (-1 * deductions * (k - 1)); //Adjust and return answer
	return adjustedprofits;
}