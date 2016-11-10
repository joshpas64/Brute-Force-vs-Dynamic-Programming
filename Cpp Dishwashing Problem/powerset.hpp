#include "subset.hpp" //Powerset function makes n calls to subset from range (0,n)
#ifndef POWERSET_HPP
#define POWERSET_HPP
struct subsetn
{
	int** member; //Basically to have an array of pointers of pointer of integers :P
};

subsetn* powerSet(int indexCardinality); 
void showPset(subsetn* sets, int cardinality);
#endif