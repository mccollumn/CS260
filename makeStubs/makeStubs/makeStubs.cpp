/** ---------------------------------------------
*
* @file		makeStubs.cpp
* @author	Nick McCollum
* @version	1.0
*
* Reads a header file and outputs a .cpp file
* containing stub functions for all of the prototypes.
*
* -------------------------------------------- */

#include <string>
#include <iostream>
#include <fstream>
#include <regex>

/**
	Reads the filename provided as a command line argument

	@param	argc	The number of command line arguments passed to main()
	@param	argv	Array of command line arguments passed to main()
	@return			The filename
*/
std::string getFilename(int argc, char* argv[]);

/**
	Opens the header file

	@param	filename	The name of the file to open
	@param	inputStream	Input stream associated with the file
	@return				True if the file was opened successfully,
						false if not
*/
bool openInputFile(std::string filename, std::ifstream& inputStream);

/**
	Opens / creates the cpp file
	Any file contents will be overwritten

	@param	filename		The name of the file to open
	@param	outputStream	Output stream associated with the file
	@return					True if the file was opened successfully,
							false if not
*/
bool openOutputFile(std::string filename, std::ofstream& outputStream);

/**
	Writes the comment block at the top of the cpp file

	@param	filename		The name of the file with no extension
	@param	outputStream	Output stream associated with the file
*/
void writeHeader(std::string filename, std::ofstream& outputStream);

/**
	Writes the header include line at the top of the cpp file

	@param	filename		The name of the header file
	@param	outputStream	Output stream associated with the file
*/
void writeInclude(std::string filename, std::ofstream& outputStream);

/**
	Writes a stub function to the cpp file

	@param	className		The name of the class
	@param	dataType		The function return data type
	@param	function		The function declaration, minus the return type
	@param	outputStream	Output stream associated with the file
*/
void writeStub(std::string className, std::string dataType, std::string function, std::ofstream& outputStream);

/**
	Returns a filename with the extension removed

	@param	filename		The name of the file with an extension
	@return					The file name with no extension
*/
std::string removeExtension(std::string filename);

/**
	Trims leading a trailing whitespace from a string

	@param	str		The string to trim
	@return			A string with whitespace trimmed
*/
std::string trimWhitespace(std::string str);

/**
	Checks a string for a class name

	@param	line		The string to check
	@param	className	Contains class name if one was found
	@return				True if a class name was found,
						false if not
*/
bool findClassName(std::string line, std::string& className);

/**
	Determines if a string is a function prototype

	@param	line	The string to check
	@return			True if the string is a function prototype,
					false if it is not
*/
bool isFunctionPrototype(std::string line);

/**
	Identifies the function's return type

	@param	line	The string to check
	@return			The return data type
*/
std::string findDataType(std::string line);

/**
	Identifies the function name, parameters,
	and any other keywords before the semicolon

	@param	line	The string to check
	@return			The function prototype
*/
std::string findFunction(std::string line);

/**
	Provides an appropriate reutrn statement for the stub function

	@param	dataType	The function return data type
	@return				A string containing a reutrn statement
*/
std::string stubBody(std::string dataType);

// ----------------------------------------------
int main(int argc, char* argv[]) {
	std::string file = getFilename(argc, argv);
	std::string filename = removeExtension(file);
	std::string className;
	std::string headerLine;
	std::ifstream inputStream;
	std::ofstream outputStream;

	openInputFile(file, inputStream);
	openOutputFile(filename, outputStream);
	writeHeader(filename, outputStream);
	writeInclude(file, outputStream);

	while (std::getline(inputStream, headerLine)) {
		std::string trimmedLine = trimWhitespace(headerLine);
		findClassName(trimmedLine, className);
		if (isFunctionPrototype(trimmedLine))	{
			std::string dataType = findDataType(trimmedLine);
			std::string function = findFunction(trimmedLine);
			writeStub(className, dataType, function, outputStream);
		}
	}

	inputStream.close();
	outputStream.close();

	return 0;
}

// ----------------------------------------------
std::string getFilename(int argc, char* argv[]) {
	std::string filename;
	if (argc == 1) {
		std::cerr << "No header filename provided.\n";
		std::cerr << "Syntax: makeStubs header.h\n";
		exit(EXIT_FAILURE);
	}
	else {
		filename = argv[1];
	}
	return filename;
}

// ----------------------------------------------
std::string removeExtension(std::string filename) {
	int dot = filename.find_last_of(".");
	return filename.substr(0, dot);
}

// ----------------------------------------------
bool openInputFile(std::string filename, std::ifstream& inputStream) {
	inputStream.open(filename);
	if (!inputStream) {
		std::cerr << "Error: Could not open file:\n";
		std::cerr << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	return true;
}

// ----------------------------------------------
bool openOutputFile(std::string filename, std::ofstream& outputStream) {
	std::string outputFile = filename + ".cpp";
	outputStream.open(outputFile);
	if (!outputStream) {
		std::cerr << "Error: Could not write file:\n";
		std::cerr << outputFile << std::endl;
		exit(EXIT_FAILURE);
	}
	return true;
}

// ----------------------------------------------
void writeHeader(std::string filename, std::ofstream& outputStream) {
	outputStream << "/** ---------------------------------------------\n";
	outputStream << "*\n";
	outputStream << "* @file\t\t\t" << filename << ".cpp" << std::endl;
	outputStream << "* @author\t\t\n";
	outputStream << "* @version\t\t1.0\n";
	outputStream << "*\n";
	outputStream << "*\n";
	outputStream << "*\n";
	outputStream << "* -------------------------------------------- */\n\n";
}

// ----------------------------------------------
void writeInclude(std::string filename, std::ofstream& outputStream) {
	outputStream << "#include \"" << filename << "\"" << std::endl;
	outputStream << std::endl;
}

// ----------------------------------------------
void writeStub(std::string className, std::string dataType, std::string function, std::ofstream& outputStream) {
	outputStream << "// ----------------------------------------------\n";
	if (dataType == "") {
		outputStream << className << "::" << function << " {" << std::endl;
	}
	else {
		outputStream << dataType << " " << className << "::" << function << " {" << std::endl;
	}
	outputStream << "\t" << stubBody(dataType) << std::endl;
	outputStream << "}" << std::endl << std::endl;
}

// ----------------------------------------------
std::string trimWhitespace(std::string str) {
	std::string trimmed;
	trimmed = std::regex_replace(str, std::regex("^\\s+"), "");
	str = trimmed;
	trimmed = std::regex_replace(str, std::regex("\\s+$"), std::string(""));
	return trimmed;
}

// ----------------------------------------------
bool findClassName(std::string line, std::string& className) {
	std::regex classExp("^class\\s(\\w+)");
	std::smatch classMatch;
	if (std::regex_search(line, classMatch, classExp)) {
		className = classMatch[1];
		return true;
	}
	return false;
}

// ----------------------------------------------
bool isFunctionPrototype(std::string line) {
	std::regex functionMatchExp(".*\\(.*\\).*;");
	return std::regex_match(line, functionMatchExp);
}

// ----------------------------------------------
std::string findDataType(std::string line) {
	std::regex dataTypeExp("^(\\w+)\\s");
	std::smatch dataTypeMatch;
	if (std::regex_search(line, dataTypeMatch, dataTypeExp)) {
		return dataTypeMatch[1];
	}
	return "";
}

// ----------------------------------------------
std::string findFunction(std::string line) {
	std::regex functionExp("^\\w+\\s([^;]+);|([^;]+);");
	std::smatch functionMatch;
	if (std::regex_search(line, functionMatch, functionExp)) {
		if (!functionMatch[1].matched) {
			return functionMatch[2];
		}
		else {
			return functionMatch[1];
		}
	}
	return "";
}

// ----------------------------------------------
std::string stubBody(std::string dataType) {
	if (dataType == "" || dataType == "void") {
		return "";
	}
	else if (dataType == "bool") {
		return "return false;";
	}
	else if (dataType == "int") {
		return "return 0;";
	}
	else if (dataType == "float" || dataType == "double") {
		return "return 0.0;";
	}
	else if (dataType == "char") {
		return "return '';";
	}
	else if (dataType == "string" || dataType == "std::string") {
		//TODO: Cannot currently match data types with a namespace
		return "return \"\";";
	}
	else {
		std::string returnValue = dataType + " stubTemp;\n\treturn stubTemp;";
		return returnValue;
	}
}