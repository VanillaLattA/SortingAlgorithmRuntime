#include <iostream> //Include iostream functions
#include <fstream> //Include file manipulation
#include <vector> //Include vectors
#include <string> //Include strings
#include <utility> //For pairs
#include "json.hpp" //Include json

using json = nlohmann::json; //rename the namespace to json

std::vector<std::pair<int, std::vector<int>>> FindMismatches(const std::vector<int>& sample1, const std::vector<int>& sample2) { //Find mismatches function with vectors
	int sampleSize = sample1.size(); //find sampleSize
	std::vector<std::pair<int, std::vector<int>>> mismatches; //vector pair with mismatches and index of mismatch

	for (int i = 0; i < sampleSize; i++) { //iterating sampleSize
		std::vector<int> mismatch; //create vector for a mismatch
		if (sample1[i] != sample2[i]) { //check if sample1[i]!=sample2[i]
			mismatch.push_back(sample1[i]);//if true push back first element of mismatch
			mismatch.push_back(sample2[i]);//if true push back second element of mismatch
		}
		std::pair<int, std::vector<int>> misPair; //pair of index of mismatch and mismatch
		misPair.first = i;//set index
		misPair.second = mismatch; //set vector
		mismatches.push_back(misPair);//pushback mismatch pair
	}

	return mismatches; //return the mismatched vectors
}

std::string MakeSampleName(int numSamples, int sampleNum) {//function to create sample name
	std::string ret = "Sample";//start function that we will use to return sample name

	int numChars = std::to_string(numSamples).size();//number of characters in sample
	std::string num = std::to_string(sampleNum);//gets num
	int diff = numChars - num.size();//difference in char and size
	for (int i = 0; i < diff; i++) {//for loop for diff
		num.insert(num.begin(), '0');//insert nums
	}

	return ret+num;//returns name
}

int main(int argc, char** argv) { //main function plus arguments

	if (argc != 3) {//checks for argument number
		std::cerr << "Incorrect number of arguments" << std::endl;//error message for incorrect argument number
		return 1;//return statement
	}

	std::ifstream file1;//ifstream for file 1
	std::ifstream file2;//ifstream for file 2
	file1.open(argv[1]);//open file 1
	if (!file1.is_open()) {//check if file1 open exists
		std::cerr << "Error: cannot open file " << argv[1] << std::endl; //error message if it doesnt open
		return 1;//return statement
	}
	file2.open(argv[2]); //open file 2
	if (!file1.is_open()) {//check if file open
		std::cerr << "Error: cannot open file " << argv[2] << std::endl; //error statement for file 2
		file1.close();//close file1
		return 1;//return 1
	}
	json Sample1;//create object of type json in sample 1
	file1 >> Sample1; //put data in Sample 1
	file1.close(); //close file 1
	json Sample2;//Sample2 into json format
	file2 >> Sample2;//move data to Sample2
	file2.close();//close file 2

	json Output;//create object Output for Json

	int numSamples = Sample1["metadata"]["numSamples"];//put numSamples in Sample1
	int numMismatchedSamples = 0;//initialize numMismatchedSamples

	for (int i = 1; i <= numSamples; i++) { //iterate through numSamples
		std::string sampleName = MakeSampleName(numSamples, i);//create sample name and use name function to make name
		std::vector<std::pair<int, std::vector<int>>> mismatches = FindMismatches(Sample1[sampleName], Sample2[sampleName]);//find mismatches using function

		int numMismatches = 0;//initialize numMismatches
		for (int j = mismatches.size() - 1; j >= 0; j--) {//get mismatch size
			if (!(mismatches[j].second.empty())) {//get second empty one 
				numMismatches += 1;//iterate numMismatches
			} else {
				mismatches.erase(mismatches.begin() + j);//erase the mismatches
			}
		}

		if (!numMismatches) continue;//check numMismatches
		else numMismatchedSamples += 1; //if there is a mismatch, add one

		Output[sampleName][argv[2]] = Sample2[sampleName]; //put the second sample into the json
		for (int j = 0; j < numMismatches; j++) { //iterate through numMismatches
			std::string numString = std::to_string(mismatches[j].first);//index of the mismatch is the json key
			Output[sampleName]["Mismatches"][numString] = mismatches[j].second;//put the mismatch into the json.
		}
		Output[sampleName][argv[1]] = Sample1[sampleName]; //put the first sample into the json
	}

	Output["metadata"]["File1"]["arraySize"] = Sample1["metadata"]["arraySize"]; //Set File1 array Size
	Output["metadata"]["File1"]["name"] = argv[1];//set File1 name
	Output["metadata"]["File1"]["numSamples"] = Sample1["metadata"]["numSamples"];//set Numsamples in Sample1
	Output["metadata"]["File2"]["arraySize"] = Sample2["metadata"]["arraySize"]; //set arraySize Sample2
	Output["metadata"]["File2"]["name"] = argv[2]; //File 2 name set in File2 JSON
	Output["metadata"]["File2"]["numSamples"] = Sample2["metadata"]["numSamples"];//Set numSamples to Sample2 (samples)
	Output["metadata"]["samplesWithConflictingResults"] = numMismatchedSamples; //set samplesWithConflictingResults to mismathced

	std::cout << Output.dump(2) << std::endl; //print output with dump

	return 0; //return 0
}
