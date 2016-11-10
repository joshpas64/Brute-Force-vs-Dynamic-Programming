#include<iostream>
#include "subset.hpp"
#include "powerset.hpp"
#include "withvectorsandsort.hpp"
#include "alternateapproach.hpp"

using namespace std;
int main()
{
	int n = 4;
	int k = 2;
	int gains[4] = { 12, 43, 32, 22 };
	int losses[4] = { 3, 18, 8, 10 };
	int x = MaxfromSort(n, k, gains, losses);
	cout << x << endl;
	system("pause");
	return 0;
}