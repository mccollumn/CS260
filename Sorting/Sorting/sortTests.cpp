/** ---------------------------------------------
*
* @file		sortTests.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 8 - Sorting
* Performs bubble, selection, and insertion sorts
* on various datasets.
* Outputs results to file.
*
* -------------------------------------------- */

#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

const int ARRAY_SIZE = 1000000;
const int SEED = 42;
const std::string FILENAME = "sort_results.csv";
const std::string ORDER_STRINGS[] = { "In Order", "Reverse Order", "Random" };
const std::string TYPE_STRINGS[] = { "Bubble", "Selection", "Insertion" };

/**
	Initializes the test array with values based on SEED

	@param	testValues	The array being initialized
	@param	method		The method/order to initialize the data
*/
void initArray(int testValues[], std::string method);

/**
	Swaps two array values in place

	@param	array	Array containing the values to swap
	@param	index1	The index of the first value
	@param	index2	The index of the second value
*/
void swap(int array[], int index1, int index2);

/**
	Appends the provided string to the specified file

	@param	filename	The file to write to
	@param	value		The string to write to the file
	@return				True if the write was successful,
						false if not
*/
bool writeToFile(std::string filename, std::string value);

/**
	Performs a bubble sort

	@param	array	The array to be sorted
	@param	length	The number of elements to sort
*/
void bubbleSort(int array[], int length);

/**
	Performs a selection sort

	@param	array	The array to be sorted
	@param	length	The number of elements to sort
*/
void selectionSort(int array[], int length);

/**
	Performs an insertion sort

	@param	array	The array to be sorted
	@param	length	The number of elements to sort
*/
void insertionSort(int array[], int length);

/**
	Initializes the data and sorts it

	@param	sortType	Pointer to the sort function
	@param	method		The method/order to initialize the data
	@param	size		The number of elements to sort
	@param	testValules	Array to be sorted
*/
void sort(void(*sortType)(int[], int), std::string method, int size, int testValues[]);

int main() {
	static int testValues[ARRAY_SIZE];
	void(*sortTypes[])(int[], int) = { bubbleSort, selectionSort, insertionSort };

	for (int type = 0; type < (sizeof(TYPE_STRINGS) / sizeof(TYPE_STRINGS[0])); type++) {
		writeToFile(FILENAME, TYPE_STRINGS[type]);
		writeToFile(FILENAME, ",100,1000,10000,100000,1000000\n");
		for (int order = 0; order < (sizeof(ORDER_STRINGS) / sizeof(ORDER_STRINGS[0])); order++) {
			writeToFile(FILENAME, ORDER_STRINGS[order]);
			for (int size = 100; size <= ARRAY_SIZE; size *= 10) {
				sort(sortTypes[type], ORDER_STRINGS[order], size, testValues);
			}
			writeToFile(FILENAME, "\n");
		}
		writeToFile(FILENAME, "\n\n");
	}

	return 0;
}

// ----------------------------------------------
void initArray(int testValues[], std::string method) {
	if (method == "In Order") {
		for (int i = 0; i < ARRAY_SIZE; i++) {
			testValues[i] = i + 1;
		}
	}
	else if (method == "Reverse Order") {
		int value = ARRAY_SIZE;
		for (int i = 0; i < ARRAY_SIZE; i++) {
			testValues[i] = value--;
		}
	}
	else {
		srand(SEED);
		for (int i = 0; i < ARRAY_SIZE; i++) {
			testValues[i] = rand();
		}
	}
}

// ----------------------------------------------
void swap(int array[], int index1, int index2) {
	int temp = array[index1];
	array[index1] = array[index2];
	array[index2] = temp;
}

// ----------------------------------------------
bool writeToFile(std::string filename, std::string value) {
	std::ofstream output;
	output.open(filename, std::ios_base::app);
	if (!output) {
		std::cerr << "File " << filename << " could not be opened.\n";
		return false;
	}
	output << value;
	output.close();
	return true;
}

// ----------------------------------------------
void bubbleSort(int array[], int length) {
	while (length > 1) {
		int newLength = 0;
		for (int i = 1; i < length; i++) {
			if (array[i - 1] > array[i]) {
				swap(array, i - 1, i);
				newLength = i;
			}
		}
		length = newLength;
	}
}

// ----------------------------------------------
void selectionSort(int array[], int length) {
	int sortedIndex;
	int unsortedIndex;
	for (sortedIndex = 0; sortedIndex < length - 1; sortedIndex++) {
		int minValue = sortedIndex;
		for (unsortedIndex = sortedIndex + 1; unsortedIndex < length; unsortedIndex++) {
			if (array[unsortedIndex] < array[minValue]) {
				minValue = unsortedIndex;
			}
		}
		if (minValue != sortedIndex) {
			swap(array, sortedIndex, minValue);
		}
	}
}

// ----------------------------------------------
void insertionSort(int array[], int length) {
	for (int currentIndex = 0; currentIndex < length; currentIndex++) {
		int insertIndex = currentIndex;
		while (insertIndex > 0 && array[insertIndex - 1] > array[insertIndex]) {
			swap(array, insertIndex, insertIndex - 1);
			insertIndex--;
		}
	}
}

// ----------------------------------------------
void sort(void(*sortType)(int[], int), std::string method, int size, int testValues[]) {
	initArray(testValues, method);
	int startTick = clock();
	(*sortType)(testValues, size);
	float elapsedSeconds = (float)(clock() - startTick) / CLOCKS_PER_SEC;
	writeToFile(FILENAME, "," + std::to_string(elapsedSeconds));
}