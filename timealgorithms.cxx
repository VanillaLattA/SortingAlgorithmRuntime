#include <fstream> //include the fstream library
#include "CSV.h" //include the CSV header file, where the sorting algorithms are run

int main(int argc, char** argv) { //Get the arguments 

	if (argc != 2) { //checks if the arguments is right
		std::cerr << "Incorrect number of arguments" << std::endl; //error message for not enough arguments
		return 1; //return statement
	}

	std::ifstream inFS; //create ifstream for file
	inFS.open(argv[1]);//open the file
	if (!inFS.is_open()) {//check if file opened properly.
		std::cerr << "Error: cannot open file " << argv[1] << std::endl; //print file and say that you cannot open the file
		return 1; //return 1
	}
	json Samples; //create a json object called samples
	inFS >> Samples; //move file comtents to Samples
	inFS.close(); //close the file

	std::cout << CSV(Samples); //construct a CSV class with the json object and send to output stream. 

	return 0; //return 0
}
