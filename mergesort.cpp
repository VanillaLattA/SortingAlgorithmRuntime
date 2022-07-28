// Merge Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "mergesort.h" //Include the header for declaration

void MergeSort(std::vector<int>* numbers, int& numCompares, int& numAccess) { //pass references through this function
   MergeSortRecurse(numbers, 0, numbers->size() - 1, numCompares, numAccess); //to this function
}


void MergeSortRecurse(std::vector<int>* numbers, int i, int k, int& numCompares, int& numAccess) { //pass references from this function to the merge function
   int j = 0;
   
   if (i < k) {
      j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
      MergeSortRecurse(numbers, i, j, numCompares, numAccess); //call with numCompares and numAccess
      MergeSortRecurse(numbers, j + 1, k, numCompares, numAccess); //call with numCompares and numAccess
      
      // Merge left and right partition in sorted order
      Merge(numbers, i, j, k, numCompares, numAccess); //call with numCompares and numAccess
   }
}

void Merge(std::vector<int>* numbers, int i, int j, int k, int& numCompares, int& numAccess) {
   int mergedSize = k - i + 1;                // Size of merged partition
   int mergePos = 0;                          // Position to insert merged number
   int leftPos = 0;                           // Position of elements in left partition
   int rightPos = 0;                          // Position of elements in right partition
   std::vector<int> mergedNumbers;
   mergedNumbers.resize(mergedSize);          // Dynamically allocates temporary array
                                              // for merged numbers
   
   leftPos = i;                               // Initialize left partition position
   rightPos = j + 1;                          // Initialize right partition position
   
   // Add smallest element from left or right partition to merged numbers
   while (leftPos <= j && rightPos <= k) {
      if ((*numbers)[leftPos] < (*numbers)[rightPos]) {
         mergedNumbers[mergePos] = (*numbers)[leftPos];
         numAccess += 2; //two accesses in the line above
         ++leftPos;
      }
      else {
         mergedNumbers[mergePos] = (*numbers)[rightPos];
         numAccess += 2; //two accesses in the line above
         ++rightPos;
         
      }
      numCompares += 1; //one compare in the if statement
      numAccess += 2; //two accesses in the if statement
      ++mergePos;
   }
   
   // If left partition is not empty, add remaining elements to merged numbers
   while (leftPos <= j) {
      mergedNumbers[mergePos] = (*numbers)[leftPos];
      numAccess += 2; //two accesses in the line above
      ++leftPos;
      ++mergePos;
   }
   
   // If right partition is not empty, add remaining elements to merged numbers
   while (rightPos <= k) {
      mergedNumbers[mergePos] = (*numbers)[rightPos];
      numAccess += 2; //two accesses in the line above
      ++rightPos;
      ++mergePos;
   }
   
   // Copy merge number back to numbers
   for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
      (*numbers)[i + mergePos] = mergedNumbers[mergePos];
      numAccess += 2; //two accesses in the line above
   }
}
