/** ---------------------------------------------
*
* @file		hash.cpp
* @author	Nick McCollum
* @version	1.0
*
* CS-260-02 - Assignment 6 - Hashing
* Generates a hash from strings, then outputs the collisions
*
* -------------------------------------------- */

#include <string>
#include <iostream>
#include <fstream>

const std::string INPUT_FILENAME = "words.txt";
const std::string OUTPUT_FILENAME = "hashresults.csv";
const int NUM_WORDS = 45402;

/**
	Generates a hash from a string

	@param	data	The string to be hashed
	@return			The hash value
*/
unsigned long long hash(std::string data);

/**
	Reads the next word from words.txt

	@param	inputStream		The input stream to read from
	@return					The next word from the file
*/
std::string getWord(std::ifstream& inputStream);

/**
	Converts the provided string to lower case

	@param	data	The string to be converted
	@return			The string converted to all lower case
*/
std::string convertToLower(std::string data);

/**
	Calculates the collision rate

	@param	indexes		Array containing hash buckets
	@return				The percentage of collisions
*/
float getCollisionRate(int indexes[]);

/**
	Print output to the console

	@param	indexes		Array containing hash buckets
*/
void print(int indexes[]);

/**
	Writes hash indexes to CSV file

	@param	indexes		Array containing hash buckets
	@return				True if file was written successfully,
						False if not
*/
bool output(int indexes[]);

int main() {
	int indexes[NUM_WORDS] = { 0 };
	unsigned long long hashVal;
	std::string word;

	// Open the file
	std::ifstream inputStream;
	inputStream.open(INPUT_FILENAME);
	if (!inputStream) {
		std::cerr << "Error: Could not open file:\n";
		std::cerr << INPUT_FILENAME << std::endl;
		return 1;
	}

	// Read each line and generate a hash
	while (inputStream) {
		hashVal = hash(getWord(inputStream));
		indexes[hashVal % NUM_WORDS]++;
	}
	inputStream.close();

	// Output to console and file
	print(indexes);
	output(indexes);

	return 0;
}

// ----------------------------------------------
std::string getWord(std::ifstream& inputStream) {
	std::string word;
	std::getline(inputStream, word);
	return convertToLower(word);
}

// ----------------------------------------------
std::string convertToLower(std::string data) {
	int strLength = data.length();
	std::string lower = "";
	for (int i = 0; i < strLength; i++) {
		lower += tolower(data[i]);
	}
	return lower;
}

// ----------------------------------------------
float getCollisionRate(int indexes[]) {
	int collisions = 0;
	for (int i = 0; i < NUM_WORDS; i++) {
		if (indexes[i] > 1) {
			collisions += indexes[i] - 1;
		}
	}
	return (static_cast<float> (collisions) / NUM_WORDS) * 100;
}

// ----------------------------------------------
void print(int indexes[]) {
	std::cout << "CS 260: A6 hashing,Nick McCollum," << getCollisionRate(indexes) << std::endl;
}

// ----------------------------------------------
bool output(int indexes[]) {
	std::ofstream outputStream;
	outputStream.open(OUTPUT_FILENAME);
	if (!outputStream) {
		std::cerr << "Error: Could not write to file:\n";
		std::cerr << OUTPUT_FILENAME << std::endl;
		return false;
	}
	for (int i = 0; i < NUM_WORDS; i++) {
		outputStream << indexes[i] << std::endl;
	}
	outputStream.close();
	return true;
}

// ----------------------------------------------
unsigned long long hash(std::string data) {
/*
	Algorithm:
	 -divide ascii value of each character by position in string
	 -multiply by 100K
	 -divide by a prime number
	 -sum the values
*/
	const int prime[30] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107 };
	int strLength = data.length();
	double asciiPosition;
	unsigned long long hash = 0;
	for (int i = 0; i < strLength; i++) {
		asciiPosition = (data[i] - 0) / (i + 1.0);
		hash += static_cast<int> (asciiPosition * 100000) / prime[i];
	}
	return hash;
}