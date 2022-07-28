// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include <vector> //include vector functions

void QuickSort(std::vector<int>* numbers, int& numCompares, int& numAccess); //use this vector function to use quicksort
void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& numCompares, int& numAccess); //QuickSortRecurse function
int Partition(std::vector<int>* numbers, int i, int k, int& numCompares, int& numAccess); //partition vectors and insert references to numCompares and numAccess which we got from the callstack
