// Insertion Sort
// 
// Author: Rob Gysel
// ECS60, UC Davis
// Adapted from: Lysecky & Vahid "Data Structures Essentials", zyBooks

#include "insertionsort.h"//include the original insertion sort file

void InsertionSort(std::vector<int>* numbers, int& numCompares, int& numAccess) { //with additional parameters for numCompares and numAccess
   int i = 0;//var i
   int j = 0;//var j
   int temp = 0;  // Temporary variable for swap
   
   for (i = 1; i < (int)numbers->size(); ++i) {
      j = i;
      // Insert numbers[i] into sorted part
      // stopping once numbers[i] in correct position
      while (j > 0 && (*numbers)[j] < (*numbers)[j - 1]) {
      	numCompares += 1; //one compare inside while loop
      	numAccess += 2; //two accesses inside while loop
         
         // Swap numbers[j] and numbers[j - 1]
         temp = (*numbers)[j];
         numAccess += 1; //one access
         (*numbers)[j] = (*numbers)[j - 1];
         numAccess += 2; //two accesses
         (*numbers)[j - 1] = temp;
         numAccess += 1; //one access
         --j;
      }
      numCompares += 1; //final compare of while loop
      numAccess += 2; //final two accessess of while loop
      if (j <= 0) { //If while loop terminated on this argument
		 numCompares -= 1; //Decriment the just incremented numCompares
		 numAccess -= 2; //Decriment the just incremented numAccess
      }
   }

   return;
}
