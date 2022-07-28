#include "CSV.h" //include CSV

std::string MakeSampleName(int numSamples, int sampleNum) { //create a MakeSampleName name with numSamples and sampleNum
	std::string ret = "Sample"; //Create Sample name first

	int numChars = std::to_string(numSamples).size(); //in of numChars
	std::string num = std::to_string(sampleNum); //string num
	int diff = numChars - num.size();// difference
	for (int i = 0; i < diff; i++) { //iterate thru difference, and insert
		num.insert(num.begin(), '0');//for creation of file name
	}

	return ret+num;//return ret and num
}

SampleData::SampleData(std::string sampleName, const std::vector<int>& sample) { //create a sample name
	Sample = sampleName;//set sampleName to Sample

	PerformInsertionSort(sample); //use insertion sort function to get the value
	PerformMergeSort(sample);//use PerformMergeSort function to perform the Merge sort
	PerformQuickSort(sample);//perform quick sort
}

void SampleData::PerformInsertionSort(std::vector<int> sample) { //use this to enter the data into and get ready to print
	int numCompares = 0;//create numCompares variable
	int numAccess = 0; //create numAccess variables

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); //create a high resolution clock time point

	InsertionSort(&sample, numCompares, numAccess); //Insertion sort function with comparisons

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();//ending time point

	InsertionSortTime = std::chrono::duration<double, std::micro>(end - start).count();//get the time of insertion sort
	InsertionSortCompares = numCompares; //get the num of compares
	InsertionSortMemaccess = numAccess; //get the memory access
}

void SampleData::PerformMergeSort(std::vector<int> sample) { //Now we can move to mergesort
	int numCompares = 0;//numCompares var
	int numAccess = 0;//numAccess variable

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); //start the mergesort clokc

	MergeSort(&sample, numCompares, numAccess);//in this function

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();//get value of clock at specific point

	MergeSortTime = std::chrono::duration<double, std::micro>(end - start).count();//Give time
	MergeSortCompares = numCompares;//total compares
	MergeSortMemaccess = numAccess;//total numAccess
}

void SampleData::PerformQuickSort(std::vector<int> sample) {//now work on quicksort data
	int numCompares = 0;//num compares initialization
	int numAccess = 0;//total num of Accesses

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now(); //start clock

	QuickSort(&sample, numCompares, numAccess);//use Quicksort in it

	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now(); //get clock current time 

	QuickSortTime = std::chrono::duration<double, std::micro>(end - start).count(); //Get quicksort time
	QuickSortCompares = numCompares;//get numCompares
	QuickSortMemaccess = numAccess;//get numAccess
}

std::ostream& operator<<(std::ostream& out, const SampleData& RHS) {//formatting with Sample Data
	out << RHS.Sample << ',' << RHS.InsertionSortTime << ',' << RHS.InsertionSortCompares << ',' << //output times
		RHS.InsertionSortMemaccess << ',' << RHS.MergeSortTime << ',' << RHS.MergeSortCompares << ',' <<//output times
		RHS.MergeSortMemaccess << ',' << RHS.QuickSortTime << ',' << RHS.QuickSortCompares << ',' <<//output compares 
		RHS.QuickSortMemaccess << std::endl;//output memaccess

	return out; // return out
}

CSV::CSV(json Samples) {//create a json variable
	int numSamples = Samples["metadata"]["numSamples"];//put numSamples into numSamples

	for (int i = 1; i <= numSamples; i++) { //loop through the samples
		std::string sampleName = MakeSampleName(numSamples, i); //create the sample name
		data.emplace_back(SampleData(sampleName, Samples[sampleName]));//call sampledata constructor and add to vector of sampledata
	}
}

std::ostream& operator<<(std::ostream& out, const CSV& RHS) { //sending data out operator
	out << "Sample,InsertionSortTime,InsertionSortCompares,InsertionSortMemaccess," << //move all the data out
		"MergeSortTime,MergeSortCompares,MergeSortMemaccess,QuickSortTime," <<//continuation of last line
  		"QuickSortCompares,QuickSortMemaccess" << std::endl;//continuation of last line

	for (const SampleData& sample : RHS.data) {//put out sample loop
		out << sample; //print out each sample
	}

	return out; //finally return out
}
