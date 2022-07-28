// Quicksort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "quicksort.h"


void QuickSort(std::vector<int>* numbers, int& numCompares, int& numAccess) { //take numCompares and numAccess
   QuickSortRecurse(numbers, 0, numbers->size() - 1, numCompares, numAccess); //and pass them into the recurse
}

void QuickSortRecurse(std::vector<int>* numbers, int i, int k, int& numCompares, int& numAccess) { //take numCompares and numAccess
   int j = 0;
   
   /* Base case: If there are 1 or zero elements to sort,
    partition is already sorted */
   if (i >= k) {
      return;
   }
   
   /* Partition the data within the array. Value j returned
    from partitioning is location of last element in low partition. */
   j = Partition(numbers, i, k, numCompares, numAccess); //and pass them into the partition
   
   /* Recursively sort low partition (i to j) and
    high partition (j + 1 to k) */
   QuickSortRecurse(numbers, i, j, numCompares, numAccess); //call with numAccess and numCompares
   QuickSortRecurse(numbers, j + 1, k, numCompares, numAccess); //call with numAccess and numCompares
   
   return;
}

int Partition(std::vector<int>* numbers, int i, int k, int& numCompares, int& numAccess) { //function call includes references to numCompares and numAccess
   int l = 0;
   int h = 0;
   int midpoint = 0;
   int pivot = 0;
   int temp = 0;
   bool done = false;
   
   /* Pick middle element as pivot */
   midpoint = i + (k - i) / 2;
   pivot = (*numbers)[midpoint];
   numAccess += 1;
   
   l = i;
   h = k;
   
   while (!done) {
      
      /* Increment l while numbers[l] < pivot */
      while ((*numbers)[l] < pivot) {
      	numCompares += 1; //one compare
      	numAccess += 1; //and one access in the while loop
         ++l;
      }
      numCompares += 1; //final compare of while loop
      numAccess += 1; //final access of while loop
      
      /* Decrement h while pivot < numbers[h] */
      while (pivot < (*numbers)[h]) {
      	numCompares += 1; //one compare
      	numAccess += 1; //and one access in the while loop
         --h;
      }
      numCompares += 1; //final compare of while loop
      numAccess += 1; //final access of while loop
      
      /* If there are zero or one elements remaining,
       all numbers are partitioned. Return h */
      if (l >= h) {
         done = true;
      }
      else {
         /* Swap numbers[l] and numbers[h],
          update l and h */
         temp = (*numbers)[l];
         numAccess += 1; //first access of swap
         (*numbers)[l] = (*numbers)[h];
         numAccess += 2; //next two accesses of swap 
         (*numbers)[h] = temp;
         numAccess += 1; //last access of swap
         
         ++l;
         --h;
      }
   }
   
   return h;
}
