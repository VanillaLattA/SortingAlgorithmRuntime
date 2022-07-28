#include <iostream> //import iostream
#include <fstream> //import fstream
#include <vector> //import vector functions
#include <string> //import string functions
#include <cmath> //import cmath functions
#include "json.hpp" //include the json.hpp file which helps us work on the jsons

using json = nlohmann::json; //rename namespace to json instead of nlohmann::json

std::vector<std::vector<int>> FindInversions(const std::vector<int>& sample){ //double vector for storing and Finding inversions
	std::vector<std::vector<int>> found; //double vector for found inversions 

	int sampleSize = sample.size() - 1; //entire sample size
	for (int i = 0; i < sampleSize; i++) { //iterate thru sample size
		std::vector<int> inversion; //inversions vector
		if (sample[i] > sample[i+1]) { //check if there is an inversion
			inversion.push_back(sample[i]); //if inversion true pushback first element
			inversion.push_back(sample[i+1]); //push back the second element
		}
		found.push_back(inversion);//add the inversion to the double vector
	}

	return found; //return the found vector
};

std::string MakeSampleName(int numSamples, int sampleNum) { //Make the sample name
	std::string ret = "Sample";//ret= Sample

	int numChars = std::to_string(numSamples).size(); //get numChars
	std::string num = std::to_string(sampleNum);//get num as string
	int diff = numChars - num.size();//difference between num chars
	for (int i = 0; i < diff; i++) { //for loop to get difference
		num.insert(num.begin(), '0');//begin 0's
	}

	return ret+num;//return string combined
}

int main(int argc, char** argv) { //take command line arguments

	if (argc != 2) { //check for incorrect arguments
		std::cerr << "Incorrect number of arguments" << std::endl; //print error message
		return 1;//return 1 after
	}

	std::ifstream inFS; //file opening line
	inFS.open(argv[1]);//open the file
	if (!inFS.is_open()) { //check if the file is open if not print an error
		std::cerr << "Error: cannot open file " << argv[1] << std::endl; //print this error and say taht file doenst work
		return 1;//return 1 after
	}
	json Sample; //create object called Sample
	json Output; //create object called Output where we will store the outputs
	inFS >> Sample; //move all the json data to sample
	inFS.close();//Close the file

	int numSamples = Sample["metadata"]["numSamples"]; //access the JSON numSamples and enter it into num samples
	int numInvertedSamples = 0; //counter for numInvertedSamples

	for (int i = 1; i <= numSamples; i++) { //Go through the loop of data points
		std::string sampleName = MakeSampleName(numSamples, i); //creates a sample name to access the json
		std::vector<std::vector<int>> inversions = FindInversions(Sample[sampleName]); //vector to store inversions
		int  numInversions = 0; //counter for numInversions
		std::vector<int> inversionIndex; //vector to store indices of inversions
		for (int j = inversions.size() - 1; j >= 0; j--) { //iterating through inversions
			if (!(inversions[j].empty())) {//check if inversions vec not empty
				numInversions += 1;//increment one
				inversionIndex.insert(inversionIndex.begin(), j); //add to inversionIndex
			} else {
				inversions.erase(inversions.begin()+j);//erase empty element.
			}
		}
		if (!numInversions) continue;//continue
		else numInvertedSamples += 1;//if not numInversions increase numInvertedSamples
		for (int j = 0; j < numInversions; j++) {//go through inversions
			std::string numString = std::to_string(inversionIndex[j]); //conv to string
			Output[sampleName]["ConsecutiveInversions"][numString] = inversions[j];//add inversion to output json
		}
		Output[sampleName]["sample"] = Sample[sampleName]; //specify sample name
	}

	Output["metadata"]["arraySize"] = Sample["metadata"]["arraySize"]; //put data in arraySize
	Output["metadata"]["file"] = argv[1]; //put file name in output
	Output["metadata"]["numSamples"] = Sample["metadata"]["numSamples"]; //put numSamples in output
	Output["metadata"]["samplesWithInversions"] = numInvertedSamples; //put numInvertedSamples into # of inversions

	std::cout << Output.dump(2) << std::endl; //output json with dump

	return 0; //return statement
}
