#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
#include <sstream>
using namespace std;

//--------------------Initialization of functions to be used in this program--------------------
int userNumber(int& usNum);	//Outputs the same message of different options the user can choose from and retuns choice value
void choicesZ(ifstream& currFS, int usNum, ofstream& coutFS); //Uses user choice to complete specific tasks
void choice1(ifstream& currFS);	//Counts the number of words in a .txt file
void choice2(ifstream& currFS);	//Outputs the longest word that appears alphabetically in .txt file
void choice3(ifstream& currFS);	//Replace non alphanumeric characters with blank spaces ' '
void choice4(ifstream& currFS, ofstream& coutFS);	//Group words based on their lengths and sort them in ascending order alphabetically, then output to sorted.txt

//--------------------Main body of the program: main()--------------------
int main() {
	string fileName;	//Name of .txt file
	cin >> fileName;	//Stores name of .txt file from user input
	int usrChoice = 1;	//User choice, set as 1 initially to not stop the program
	ifstream inFS(fileName);	//Opens file chosen by user
	ofstream outFS("sorted.txt");	//Creates sorted.txt for output storage

	if (!inFS.is_open()) {	//If file is not open
		cout << "File not found!" << endl;	//Display error message
		return 1;	//Return 1 and exit program
	}

	while (usrChoice != 0) {	//While the user does not type 0
		userNumber(usrChoice);	//Displays options and returns user choice
		choicesZ(inFS, usrChoice, outFS);	//Displays information related to user choice
	}

	inFS.close(); //Closes input .txt file
	outFS.close();	//Closes output .txt file
	return 0;	//Returns 0 if everything ran successfully
}

//--------------------Definition of functions to be used in this program--------------------
int userNumber(int& usNum) {	//Outputs the same message of different options the user can choose from and retuns choice value
	cout << setfill('-') << setw(62) << "" << endl;	//Displays line for better visualization
	cout << "Please make your choice:" << endl;
	cout << " 0 - Exit" << endl;
	cout << " 1 - Word count" << endl;
	cout << " 2 - Find the longest word that appears the last alphabetically" << endl;
	cout << " 3 - Replace all none alphabetical characters with whitespaces and output the new text on screen" << endl;
	cout << " 4 - Output all words in order of their lengths and alphabetically" << endl;
	cout << setfill('-') << setw(62) << "" << endl;	//Displays line for better visualization
	cin >> usNum;	//Collects input choice from the user

	return usNum;	//Returns user choice
}

void choicesZ(ifstream& currFS, int usNum, ofstream& coutFS) { //Completes certain tasks depending on usNum
	if (usNum == 0) {	//If usNum = 0, do nothing as it will exit the while loop
	}

	else if (usNum == 1) {	//If usNum = 1
		choice1(currFS);	//Execute choice1 function
	}

	else if (usNum == 2) {	//If usNum = 2
		choice2(currFS);	//Execute choice2 function
	}

	else if (usNum == 3) {	//If usNum = 3
		choice3(currFS);	//Execute choice3 function
	}

	else if(usNum == 4) {	//If usNum = 4
		choice4(currFS, coutFS);	//Execute choice4 function
	}
	else {
		cout << "Please only enter 0, 1, 2, 3, or 4!" << endl; //Out of range message
	}
}

void choice1(ifstream& currFS) {	//Counts the number of words in a .txt file
	string cWord;	//Current word stored
	int wordCount = 0;	//Number of words counter
	while (currFS >> cWord) {	//Main loop that inputs sections from .txt file to cWord
		for (int i = 0; i < cWord.size(); ++i) {	//For loop that looks through each string in search for a letter
			if (isalpha(cWord[i])) {	//Checks if an alphabet letter is present
				++wordCount;	//If alphabet letter is present, increase word counter by 1
				break;	//IF alphabet letter is present, break the loop and move to next input string
			}
		}
	}

	cout << "The number of words in the text is " << wordCount << endl;	//Outputs the number in wordCount
	currFS.clear();	//Clears .txt input
	currFS.seekg(0,currFS.beg);	//Goes back to the beginning of .txt file for next task
}

void choice2(ifstream& currFS) {	//Outputs the longest word that appears alphabetically in .txt file
	string lWord = "A";	//Longest word stored
	string longestWords[100];	//Array to store largest words
	string cWord;	//Current word stored
	int wordCounter = 0;	//Counter to keep track of how many larger words have been stored
	while (currFS >> cWord) {	//Loop that parses through the entire .txt file for inputs
		if (!isalpha(cWord.at(cWord.size() - 1)) && (cWord.size() > 1)) {	//Checks if punctuation mark is at the end of an input string
			cWord.resize(cWord.size() - 1);	//If punctuation mark is present, this removes it
		}
		
			if ((cWord[0] >= lWord[0]) && (cWord.size() >= lWord.size())) {	//If statement to collect the largest words which is greater in the alphabet than the previous lWord
					lWord = cWord;	//If cWord > lWord, lWord = cWord; stores the last largest word that fits the previous criteria
					longestWords[wordCounter] = cWord;	//Stores increasingly large words
					++wordCounter;	//Increases the count to keep track of how many words have been stored
			}
	}

	for (int i = 0; i < wordCounter-1; ++i) {	//For loop to compare all the largest words; since last word stored is already lWord, wordCounter - 1 is used
		if (longestWords[i].at(0) == lWord.at(0)) {	//Since the first letter in lWord already is in the last group of the alphabet found in the .txt file, only compare other words that start with the same letter
			for (int j = 0; j < longestWords[i].size(); ++j) {	//For loop goes through each char  in the current word as well as lWord
				if (longestWords[i].at(j) > lWord.at(j)) {	//If the first different letter is greater than the char at lWord
					lWord = longestWords[i];	//lWord becomes the current word
					break; //Skips to the next word; ++i
				}
				else if (longestWords[i].at(j) != lWord.at(j)) { //If current char in new word is not greater or equal to current char in lWord
					break;	//Skips to the next word; ++i
				}
			}
		}
	}

	cout << "The longest word that appears the last alphabetically is " << lWord << endl;	//Outputs lWord
	currFS.clear();	//Clears .txt input
	currFS.seekg(0, currFS.beg);	//Goes back to the beginning of .txt file for next task
}

void choice3(ifstream& currFS) {	//Replace non alphanumeric characters with blank spaces ' '
	string cLine;	//Current line stored
	string cWord;	//Current word stored
	string outVec;	//Output line

	while (getline(currFS, cLine)) {	//While loop that gets each line from the .txt file
		outVec = "";	//Clears out current output line
		istringstream temp(cLine);	//istringstream variable that will allow being able to extract each word from each line
		while (temp >> cWord) {	//While loop that extracts each word from the istringstream line
			string tempW = " ";	//Creates and clears out current temporary word variable
			if (!isalpha(cWord.at(0)) && (cWord.size() > 1)) {	//Checks if punctuation mark is at the beginning of input
				for (int i = 0; i < cWord.size(); ++i) {	//Parses through whole world if punctuation mark is at the beginning of input
					if (isalpha(cWord.at(i))) {	//If it is part of the alphabet
						tempW += cWord.at(i);	//Store char in temp string
					}
				}
				cWord = tempW;	//Temporary variable becomes part of main variables
			}

			if (!isalpha(cWord.at(cWord.size() - 1)) && (cWord.size() > 1)) {	//Checks if punctuation mark is at the end of an input string
				cWord.resize(cWord.size() - 1);	//If punctuation mark is present, this removes it
				cWord += " ";	//Adds a space at the end of the word to replace the non alphabet char
			}

			if (!isalpha(cWord.at(0))) {	//If curret word is a single char and it is not in the alphabet
				cWord = ' ';	//Current word becomes a space
			}

			outVec += cWord;	//Output line gets the current analyzed word
			outVec += " ";	//Add a space to the end of the word
		}
		if (!currFS.eof()) {	//If the file is not at its ending point
			cout << outVec << endl;	//Output the line with the extra space at the end
		}
		else {	
			outVec.resize(outVec.size() - 1);	//Remove the extra space at the end of the line
			cout << outVec << endl;	//Output the new line
		}
	}

	currFS.clear();	//Clears .txt input
	currFS.seekg(0, currFS.beg);	//Goes back to the beginning of .txt file for next task
}

void choice4(ifstream& currFS, ofstream& coutFS) {	//Group words based on their lengths and sort them in ascending order alphabetically, then output to sorted.txt
	string cWord = "";	//Stores the current word in the input
	string sortedArr[100];	//Stores unsorted array
	string unsortedArr[100];	//Stores unsorted array
	int wordCount = 0;	//Counts how many words are stored
	int arrCount = 0;	//Keeps track of how big the array is
	int wordSize = 0;	//Keeps track of word sizes
	int maxSize = 0;	//Stores the size of the largest word
	string temp = "";	//Stores temporary words to be switched

	while (currFS >> cWord) {	//While loop to collect and sort every word form .txt file
		//--------------------Removes any punctuation marks from words within the .txt file (taken from choice2)--------------------
		if (!isalpha(cWord.at(cWord.size() - 1)) && (cWord.size() > 1)) {	//Checks if punctuation mark is at the end of an input string
			cWord.resize(cWord.size() - 1);	//If punctuation mark is present, this removes it
		}

		if (!isalpha(cWord.at(0)) && (cWord.size() > 1)) {	//Checks if punctuation mark is at the beginning of input
			temp = "";
			for (int i = 0; i < cWord.size(); ++i) {	//Parses through whole world if punctuation mark is at the beginning of input
				if (isalpha(cWord.at(i))) {	//If it is part of the alphabet
					temp += cWord.at(i);	//Store char in temp string
				}
			}
			cout << temp << endl;
			cWord = temp;	//Temporary variable becomes part of main variables
		}

		wordSize = cWord.size();	//Get size of the current word
		if (wordSize > maxSize) {	//If current size is bigger than previous biggest size stored
			maxSize = wordSize;	//Biggest size becomes the new maxSize
		}
		unsortedArr[wordCount] = cWord;	//Current word gets added to unsorted array
		++wordCount;	//Adds 1 to the array size counter
	}

	//--------------------Organizes each word per ascending ASCII value--------------------
	for (int i = 1; i < wordCount; ++i) {	//For loop that parses through each word (wordCount used as constraint)
		for (int j = 1; j < wordCount;++j) {	//For loop that parses through each word (wordCount used as constraint)
			if (unsortedArr[j - 1] > unsortedArr[j]) {	//If ASCII value of word[j-1] > ASCII value of word[j]
				temp = unsortedArr[j - 1];	//temp becomes word[j-1]
				unsortedArr[j - 1] = unsortedArr[j];	//word[j-1] swaps with word[j]
				unsortedArr[j] = temp;	//word[j] swaps with word[j-1] through temp
			}
		}
	}

	//--------------------Organizes each word per ascending size--------------------
	for (int i = 0; i <= maxSize; ++i) {	//For loop that goes through each possible word size
		for (int j = 0; j < wordCount; ++j) {	//For loopthat goes through each word
			if (unsortedArr[j].size() == i) {	//If current word matches current size
				sortedArr[arrCount] = unsortedArr[j];	//Word gets added to next spot in sorted array
				++arrCount;	//Sorted array spot moves to the next number
			}
		}
	}

	//--------------------Makes sure that each output is alphanumerical (taken from choice1)--------------------
	for (int i = 0; i < wordCount; ++i) {	//For loop that goes through each word
		for (int j = 0; j < sortedArr[i].size(); ++j) {	//For loop that looks through each string in search for a letter
			if (isalpha(sortedArr[i].at(j))) {	//Checks if an alphabet letter is present
				coutFS << sortedArr[i] << endl;	//Outputs the current word to sorted.txt
				break;	//IF alphabet letter is present, break the loop and move to next input string
			}
		}
	}
}