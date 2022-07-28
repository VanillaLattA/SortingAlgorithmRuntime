all: sortedverification consistentresultverification timealgorithms createdata #rule for all executables

sortedverification: sortedverification.cxx json.hpp #rule for sortedverification
	g++ -Wall -Werror sortedverification.cxx -o sortedverification #command to compile sortedverification

consistentresultverification: consistentresultverification.cxx json.hpp #rule for consistentresultverification
	g++ -Wall -Werror consistentresultverification.cxx -o consistentresultverification #command to compile consistentresultverification
	
timealgorithms: timealgorithms.cxx insertionsort.o mergesort.o quicksort.o CSV.o #rule for timealgorithms
	g++ -Wall -Werror insertionsort.o mergesort.o quicksort.o CSV.o timealgorithms.cxx -o timealgorithms #command to compile timealgorithms
	
insertionsort.o: insertionsort.h insertionsort.cpp #rule for insertionsort library
	g++ -Wall -Werror -c insertionsort.cpp -o insertionsort.o #command to generate o file for insertionsort
	
mergesort.o: mergesort.h mergesort.cpp #rule for mergesort library
	g++ -Wall -Werror -c mergesort.cpp -o mergesort.o #command to generate o file for mergesort
	
quicksort.o: quicksort.h quicksort.cpp #rule for quicksort library
	g++ -Wall -Werror -c quicksort.cpp -o quicksort.o #command to generate o file for quicksort
	
CSV.o: CSV.h CSV.cpp json.hpp #rule for CSV library
	g++ -Wall -Werror -c CSV.cpp -o CSV.o #command to generate o file for CSV library
	
createdata: createdata.cxx json.hpp #rule for createdata executable
	g++ -Wall -Werror createdata.cxx -o createdata  #command to compile createdata
	
.PHONY: clean #define clean as a phony rule
clean: #clean rule
	rm -rf sortedverification consistentresultverification timealgorithms createdata *.json *.o #command to remove all generated and data files
