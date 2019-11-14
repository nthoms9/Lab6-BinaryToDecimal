/*
Nick Thoms
C++ 2019 
Due: 11/14/2019
Lab 6 Binary to Decimal
Description: This program inputs binary numbers from a file, then outputs the number and its decimal 
             equivalent, centered beneath appropriate headings.
*/

#include<iostream> // Includes a basic library for c++.
#include<istream>  // Allows for the use of get and ignore.
#include<iomanip>  // Allows for the use of setw.
#include<fstream>  // Allows for the use of the fstream variable type.
#include<cassert>  // Allows for the assert function.

using namespace std;

void openInFile(ifstream& inFile, ifstream& inFile2);
// Preconditions:  The flow of control is valid.
// Postconditions: Two different ifstreams are opened, if the stream is invalid the program will close

void fileRead(ifstream& inFile, char& input);
// Preconditions:  The flow of control is valid and the ifstream is valid.
// Postconditions: A new value is stored in the char "input". The flow f control continues.

void binaryIn( char, ifstream& inFile, unsigned int& decVal, int& binarySize, bool& valid);
// Preconditions:  The flow of control is valid, and the ifstream is valid
// Postconditions: A base value is set for each of the variables, then a new value is calculated, As each
//                 character is read in through the file using a while loop for the 1st ifstream. A value is
//                 assigned to "decVal" according to the number of 0s and 1s in the input. A value is 
//                 assigned to "binarySize" according to the number of iterations of a while loop within the
//                 function. "valid" is either true or false depending on the characters inputted. The marker
//                 in the first ifstream will be at a new line character. The flow of control continues.

void binaryOut(char, int, bool, ifstream& inFile2);
// Preconditions:  The flow of control has passed on from "binaryIn" and the ifstream is valid.
// Postconditions: A new variable for the width of the binary number is declared. The value for this variable
//                 is then calculated using the value of "binarySize" from the previous function. Spaces
//                 are outputted to the screen then the binary number is outputted using the second ifstream.
//                 The binary number is then followed by more spaces. If the  value for "valid" from the 
//                 previous function was false, an error would be outputted to the screen instead. The marker
//                 in the second ifstream is at a new line character. The flow of control continues.

void decOut(unsigned int);
// preconditions:  The flow of control has passed on from "binaryOut", the ifstream is valid, and the value
//                 for the variable 'valid' is true.
// Postconditions: A new variable for the width is declared. The value for this variable is calculated using
//                 the value of "decVal". Spaces are outputted to the screen, then the decimal number is 
//                 outputted to the screen and the flow of control continues.

int main() // The heading of the main function.
{
	ifstream inFile;        // Two ifstream variables are declared to allow for access of data from the file.
	ifstream inFile2;
	char input;             // Data from the file will be stored in the character "input"
	unsigned int decVal;    // "decVal" will store the value of the calculated decimal number.
	int binarySize;         // "binarySize" will store the value of the amount of spaces of the binary input.
	bool valid;             // The validity of the binary number is stored in "valid".

	openInFile(inFile, inFile2);    // "openInFile is called. 

	cout << "          Binary Number              Decimal Equivalent" << endl; // The heading is displayed.

	fileRead(inFile, input);  //"fileRead" is called for the priming read of "inFile"

	while (inFile) // A while loop is run until the end of the file is reached.
	{
		binaryIn(input, inFile, decVal, binarySize, valid);  // "binaryIn" is called.
		binaryOut(input, binarySize, valid, inFile2);        // "binaryOut" is called.

		if (valid)
			decOut(decVal);  // If the binary number input was valid "decOut" is called.
	
		fileRead(inFile, input);    // This will read the first character of each newline.
	}
	return 0; // The program is exited.
}

// "openInFile" opens the input file into two different ifstreams using reference parameters.
void openInFile(ifstream& inFile, ifstream& inFile2)
{
	string BinaryIn = "C:/Users/THOMS4/Documents/C++ Projects/Lab6/BinaryIn.dat";
	inFile.open(BinaryIn);  // The first ifstream is opened.
	if (!inFile)
	{
		cout << "Cannot read the file: ";
		assert(inFile); // Assert checks for errors in the file name.
	}
	inFile2.open(BinaryIn); // The second ifstream is opened.

}

// "file read"  reads in the first character of each new line, but skips over blanks spaces and zeros.
// This function uses value parameters.
void fileRead(ifstream& inFile, char& input)
{
	inFile >> input;   // The first character is read in.
	while (inFile && input != '1' && input == ' ' || input == '0')
	{
		inFile.get(input);    // Characters are read in until the stream reaches a 1 or an invalid 
	}                         // character.
}

// "binaryIn" will read all of the characters on a line and determine whether the input was a valid binary
// number, and it will calculate the decimal equivalent of the  binary number. Lastly this module
// will count the total amount of characters of the binary number. The char "input" is a value 
// parameter and the rest are reference parameters. (The values will be needed in later functions.)
void binaryIn(char input, ifstream& inFile, unsigned int& decVal, int& binarySize, bool& valid)
{
	decVal = 0;          // Each of the variablse are set to a base value, so that each iteration of the
	binarySize = 0;      // end of file loop in the main function will be consistent
	valid = true;

	while (inFile && input != '\n')  // This while loop limits the program to reading one line at a time.
	{                                // The loop will exit if it hits the end of the file.
		switch (input)
		{                                             // A switch statement is used to determine the 
		case '0': decVal = (decVal * 2) + 0; break;   // the calculation for the decimal number. It also
		case '1': decVal = (decVal * 2) + 1; break;   // checks the input for bad digits. If there is a 
		default:  valid = false;                      // bad digit, the bool "valid" becomes false.
		}

		binarySize++;   // For each iteration of the loop the size of the number increases by 1 character

		inFile.get(input);  // The next character in the line is read.
	}
}

// "binaryOut" takes the information from binary in and detrmines and output. If the binary number was valid.
// A calculation is made to determine how many spaces will be outputted before the binary number to center 
// it. Then the line is read in through the second ifstream and the binary number is outputted if it was
// valid. If it was invalid an error message is displayed. This function primarily takes data in so it uses
// mostly value parameters. The ifstream must be a reference parameter.
void binaryOut(char input, int binarySize, bool valid, ifstream& inFile2)
{
	int binaryW;    // The variable that stores the width of the binary number is declared.

	if (binarySize % 2 == 0)                       // The width is calculated based on the size of
		binaryW = ((binarySize) / -2) + 18;        // binary number. There is a calculation for even sizes
	else                                           // and odd sizes.
		binaryW = ((binarySize) / -2) + 17;

	if (valid)
		cout << setw(binaryW);            // The width is outputted

	inFile2.ignore(200, '1');             // The program will ignore anything that it isn't the first
	input = '1';                          // digit of the binary number

	while (inFile2 && input != '\n')      // This while loop will output one binary number at a time.
	{                                     // A new line character seperates each binary number.
		if (valid)                        // It will stop if it reaches the end of the file.
			cout << input;
		                                  // Each character is read and outputted to the screen one at a 
		inFile2.get(input);               // time. (If invalid the character will only be read)
	}

	if (valid)
	{
		cout << setw(binaryW);            // The space after the binary number is outputted.
		cout << "\t";
	}
	else
		cout << "        bad digit on input" << endl; // If the binary number was invalid a message is
}                                                     // displayed.

//"decOut" calculates the amount of spaces that should be outputted for each decimal number, then it displays
// both the spaces and the number to the screeen. This function only brings in the data for the decimal
// number, so there is only one value parameter.
void decOut(unsigned int decVal)
{
	int decSize;          // "decSize' is the amoount of characters of the decimal number.
	int decW;             // "decW" is the amount of characters to be ouputted before the decimal number.
	unsigned int decVal2; // "decVal2" is a copy of "decVal".

	decSize = 0;          // A base value is set to "decval".

	decVal2 = decVal;     // The copy of decVal is made.
	while (decVal2 >= 1)
	{
		decVal2 /= 10;    // "decSize" is calculated
		decSize++;
	}

	if (decSize % 2 == 0)                 // The width is calculated based on the size of the decimal
		decW = ((decSize) / -2) + 6;      // numbers. There is a calculation for even sizes and for odd
	else                                  // sizes.
		decW = ((decSize) / -2) + 5;
	
	for (decW; decW > 0; decW--)
	{                                     // The correct amounts of spaces are outputted to the screen
		cout << " ";
	}

	cout << decVal << endl;               // The decimal number is outputted to the screen
}
