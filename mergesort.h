// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

//TODO: Comments (essentially wherever you see "numCompares" or "numAccess" I made a change)

#include <vector>//include the vector function

void MergeSort(std::vector<int>* numbers, int& numCompares, int& numAccess); //Mergesort function that access with all given parameters
void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int& numCompares, int& numAccess);//Recurse version
void Merge(std::vector<int>* numbers, int i, int j, int k, int& numCompares, int& numAccess);//Merges all the compares together (reference to numCompares and numAccess is passed through the callstack)
