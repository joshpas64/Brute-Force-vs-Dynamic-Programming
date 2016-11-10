#pragma once
#ifndef ALTERNATEAPPROACH_HPP
#define ALTERNATEAPPROACH_HPP

int compare(int x, int y);
int knapsack(int n, int W, int* items, int* constraints);
int getMax(int* profits, int currentLength, int subsize);
int getMaxCheck(int n, int k, int* gains, int* losses);

#endif