#ifndef CSV_H //header guard
#define CSV_H //header guard

#include <iostream> //include the iostream functions
#include <vector>//include vector functions
#include <chrono> //include chrono functions
#include <string> //include string functions
#include "insertionsort.h" //include insertion sort
#include "mergesort.h"//include mergesort
#include "quicksort.h"//include quicksort
#include "json.hpp" //include json hpp

using json = nlohmann::json;//rename namespace to just json

class SampleData {//create a class with sample data
public: //public part of class
	SampleData() = default;//default constructor
	SampleData(std::string sampleName, const std::vector<int>& sample); //create a sampleName given name sample
	virtual ~SampleData() = default; //default destructor

	friend std::ostream& operator<<(std::ostream& out, const SampleData& RHS); //overloading << operator to print in CSV format
private://private functions

	void PerformInsertionSort(std::vector<int> sample);//Perform insertion sort
	void PerformMergeSort(std::vector<int> sample);//Perform merge sort
	void PerformQuickSort(std::vector<int> sample);//Perform quicksort

	std::string Sample; //Sample Name
	double InsertionSortTime; //Insertion sort time
	int InsertionSortCompares; //Insertion sort compares
	int InsertionSortMemaccess; //Insertion sort memory accesses
	double MergeSortTime;//Merge sort time
	int MergeSortCompares;//number of compares in Mergesort
	int MergeSortMemaccess;//amount of mem accesses in Mergesort
	double QuickSortTime;//quicksort time access
	int QuickSortCompares; // Qicksort num compares
	int QuickSortMemaccess;//quick sort accesses
};

class CSV { //create a clas of CSV
public:
	CSV() = default;//default constructor
	explicit CSV(json Samples); //Create a CSV with json sample
	virtual ~CSV() = default;//default destructor

	friend std::ostream& operator<<(std::ostream& out, const CSV& RHS); //overloading << operator to output in CSV format
private://private functin parts
	std::vector<SampleData> data; //vector SampleData
};

#endif //header guard
