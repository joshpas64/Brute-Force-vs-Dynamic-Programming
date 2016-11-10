#include "alternateapproach.hpp"


int compare(int x, int y) //Simple compare function in this case we want to get the max value, for min just switch operators
{
	if (x >= y)
		return x;
	return y;
}

int knapsack(int n, int W, int* items, int* constraints)
//Link is .py files
// Takes a powerset problem, which has 2^n time complexity and uses a memory table to reduce the time complexity to
// n * W (Upgrades from exponential to polynomial), BUT what if very large W??? or a large range of W constraint value
// Perhaps iterative would be better??? Dont know
// In explanation link from uni range went to 10 and n was 4
// So t = 40 vs t = 16
// The brute force would still be messier since after generating the subsets (16 - 1)[not including the empty subset]
// Each would have to weights its weight and values calculated, but still could work something like this?
/*
Im assuming the subsets generated would be representations of indexes in the args list i.e. {0,3} would reference the 
third and first item in the value and constraints arrays

so loop would look like this
currentMax = 0

for(int i=0; 2**n; i++)
{
	int* subset = findinPset(index);
	int vals = 0
	int weights = 0
	for_each(int i:subset)
	{
		vals += items[i]
		weights += constraints[i]
	}
	if(weights <= W && vals >= currentMax)
		currentMax = vals
}
return currentMax
*/
/*
So this is how the problem works you have n items each with a value v that is good that you want to maximize and another value
that acts as a constraint w that you have to keep at a limit W
You must figure out which items to pick to have the highest v possible but have your w be less than or equal to W
The powerset implementation has too high a time complexity to be used consistently
The key is to use a 2D table V with rows from (0,n) and columns (0,W)
and set the values of the coordinates([i][j]) of the table recursively from either the previous row's value at the corresponding column
or the sum of the value of the current rows value in the original value array and the value from the coordinate in the table V from the previous
row but where the column is equal to (the current column j - the value of the index j in the constraint table constraints[j]) to account for incrementing your
total constraint value by that constraint value, constraint[j]

The way it is logically looked at is this
way I start 0 items
I can EITHER:
Not take the item, not increasing my constraint in hopes for a better next option
OR
Take the item, increasing my total value, but increasing my constraint value
One thing to note is with the table approach doing range (0,W) eliminates all combinations whose total constraint values w would be higher than W
Eliminating need to check and filter
Also some combinations are skipped because if its value is less than what is considered the best value so far (V[i-1][j]) it is just set to that value

A way to look at it is that the table shows the values that could be made to less than or equal to constraint w (actual accuracy of this statement may be a bit iffy)
Where W would have the highest value since the more combinations can be made to fit netweights <= W than maybe netweights <= (W-5)
*/
{
	int* V = new int[(n + 1) * (W + 1)]; //Makes a 2D table but since each index is an int, for the sake of making the memory more local and reducing the chance
	// of it being spread out and hence slower to access make a 1D table that is n*W large
	// The plus ones are to account for the zeroing that occurs at the beginning
	for (int i = 0; i < W + 1; i++) //Make first row all 0's because if no item is picked then the net value gained is zero
	{
		V[i] = 0;
	}
	for (int i = 1; i < n + 1; i++) // for the rest of the rows
	{
		for (int j = 0; j < W + 1; j++) //For all columns in each row
		{
			if (constraints[i - 1] <= j) //if the columns value in the corresponding constraints index is less than the j,
				//which represents a possible constraint value 
				//Basically if the weight of the item is less than the column j a combination with that item cannot be possible, make it something else
				V[(i * (W + 1)) + j] = compare(V[((i - 1)*(W + 1)) + j], items[i - 1] + V[((i - 1) * (W + 1)) + j - constraints[i - 1]]);
			// i * (W+1) is offset the row
			// Set index in table to the max of: (the last Value than can be made of constraint j OR the corresponding sum associated of adding the value of the iten
			// and the value at V[((i - 1) * (W + 1)) + j - constraints[i - 1]]
			// Since adding an item means add its constraint val, lets just for an example weight w and limit W
			//If you add it, it means you W - w, room left for more items to add or even lower if there were items there already to begin with
			//With taking max and using to (j - constraints[i]) you are saying look for column(constraint j) that can be made with item i,
			//If you want to add subtract that j from the constraints[i-1] of the actual item and see what values you can get that have weight j-constraint[i-1]
			// but dont have the current item, the max part of each iteration eliminates the need for a search and just references one value V[((i - 1) * (W + 1)) + j - constraints[i - 1]]
			else
				V[(i * (W + 1)) + j] = V[((i - 1)*(W + 1)) + j]; //Make it equal to value of the scenario where the item is not included
		}
	}

	int result = V[((n + 1) * (W + 1)) - 1]; //Get last item in V, always the MAX 
	delete[] V; //Now that the MAX is found V can be deallocated
	return result;
}

int getMax(int* profits, int currentLength, int subsize) // Has a complexity of n * k 
//This could be an iterative version of a knapsack algorithm with no table the optimization
//in this case is much easier
// Now how to get the indexes (which plates to wash)
{
	int currentMax = 0;
	int count = 0;
	int temp2 = 0;
	while (count < subsize) //Iterate subsize times
	{
		int temp1 = 0;
		for (int i = 0; i < currentLength; i++)
		{
			if (profits[i] >= temp1 && (profits[i] < temp2 || temp2 == 0)) //Find the max value of the list
				// Once you are past the first while loop iteration, the next max Value cant be the same as the last or greater than it 
			{
				temp1 = profits[i];
			}
		}
		currentMax += temp1; //Add it to currentMax
		temp2 = temp1; //Set the new Max limit
		count++; //Start a new iteration
	} 
	return currentMax;
}

int getMaxCheck(int n, int k, int* gains, int* losses)
{
	int* profitlist = new int[n]; //Make a list containing gains and losses for each item
	int deductions = 0;
	for (int i = 0; i < n; i++)
	{
		deductions += losses[i];
	}
	deductions = deductions * -1; //The most you could be docked is if you washed 0 plates
	for (int i = 0; i < n; i++)
	{
		profitlist[i] = gains[i] + losses[i] + deductions; //For washing just 1 item, you get a gain,gains[i], but also get its losses[i], it loss value
		// deducted from your total deductions, the sum of all deductions
	}
	int profits = getMax(profitlist, n, k); //Find the first k profitable plates in profitlist
	int adjustedProfits = profits + (-1 * deductions * (k - 1)); //This is an adjustment to get correct value, since each value from profitlisr is the scenario
	// where only 1 plate is washed
	delete[] profitlist; //Answer found can deallocate profitlist
	return adjustedProfits;
}
