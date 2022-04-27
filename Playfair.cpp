#include <iostream>
#include <iterator>
#include <string>
#include "Playfair.h"

using namespace std;


//helper function to get the characters for the matrix given the coordinates*/
char Playfair::getCharacter(int x, int y)
{
	return playfairMatrix[(y + 5) % 5][(x + 5) % 5];	//return character 
}

/*the other helper function to get the coordinates of the matrix given the characters*/
bool Playfair::getCoordinates(char a, int& x, int& y)
{
	for (int i = 0; i < 5; i++) {	//traverse x axis

		for (int j = 0; j < 5; j++) {	//traverse y axis

			if (playfairMatrix[i][j] == a) {	//if match found
				x = j;
				y = i;
				return true;
			}
		}
	}
	return false;
}

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Playfair::setKey(const string& key)
{
	if (key.length() > 0) {		//if key exists
		playfairKey = key;	//set key
		return true; 
	}
	return false; 
}


/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Playfair::encrypt(const string& plaintext)
{
	string encryption = "";				//string to hold the ciphertext

	string playfairMatrixValues = "";	//string to hold matrix values, will be used to populate actual 5x5 matrix later
	string originalText = plaintext;	//string to hold plaintext to perform indexing on
	int length = originalText.length(); //get length of plaintext 
	string pairs = "";					//string to hold letters in blocks of two

	int x1, x2, y1, y2;		//variables to hold coordinates for the intersections in the matrix
	
	playfairKey = playfairKey + "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //append alphabet to key to create basis for matrix

	
	for (string::iterator iterator = playfairKey.begin(); iterator != playfairKey.end(); iterator++) {	//iterate through parameter and append values to playfairMatrixValues

		*iterator = toupper(*iterator);	//changes to uppercase

		if ((*iterator < 65) || (*iterator > 90)) {	//if character is valid uppercase letter, move to next character 
			continue;		
		}

		if (*iterator == 'I') {	//if I detected, matches to J 
			*iterator = 'J';
		}

		if (playfairMatrixValues.find(*iterator) == -1) {	//if character that is not yet added to originalText is found, append 
			playfairMatrixValues += *iterator;
		}
	}

	copy(playfairMatrixValues.begin(), playfairMatrixValues.end(), &playfairMatrix[0][0]);	//copy values into playfairMatrix

	for (string::iterator iterator = originalText.begin(); iterator != originalText.end(); iterator++) {	//iterate through plaintext, remove I when J is encountered

		*iterator = toupper(*iterator);

		if ((*iterator < 65) || (*iterator > 90)) {	//if character is valid uppercase letter, move to next character
			continue;
		}

		if (*iterator == 'I') {	//if I detected, matches to J
			*iterator = 'J';
		}
	}

	for (int i = 0; i < length; i += 2) {	//iterate by twos, and add X to duplicate characters

		pairs += originalText[i];	//append values to pairs for indexing

		if (i + 1 < length) {	//while not end of plaintext

			if (originalText[i] == originalText[i + 1]) {	//compare current and next character and check for match
				pairs += 'X';	//append X if pair detected
			}

			pairs += originalText[i + 1]; //move to next "pair"
		}
	}

	if (pairs.length() % 2 == 1) {	//check for odd number of letters
		pairs += 'X';	//appends X
	}

	for (string::iterator iterator = pairs.begin(); iterator != pairs.end(); iterator++) {	//iterate through plaintext, now in pairs

		if (getCoordinates(*iterator++, x1, y1)) {	//get coordinates of first character in pair

			if (getCoordinates(*iterator, x2, y2)) {	//get coordinates of second character in pair

				if (x1 == x2) { //if same row, append next character in the same row for both
					encryption += getCharacter(x1, y1 + 1);
					encryption += getCharacter(x2, y2 + 1);
				}
				else if (y1 == y2) { //if same column, append next character in same column for both
					encryption += getCharacter(x1 + 1, y1);
					encryption += getCharacter(x2 + 1, y2);
				}
				else {	//normal, append intersection between row/column of the two characters
					encryption += getCharacter(x2, y1);
					encryption += getCharacter(x1, y2);
				}
			}
		}
	}
	return encryption;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText) 
{
	string decryption = "";	//string to hold decrypted text

	string playfairMatrixValues = "";		//string to hold matrix values, will be used to populate actual 5x5 matrix later
	string encryptedText = cipherText;		//string to hold ciphertext to perform indexing on
	int length = encryptedText.length();	//get length of ciphertext
	string pairs = "";						//string to hold letters in blocks of two

	int x1, x2, y1, y2;		//variables to hold coordinates for the intersections in the matrix

	playfairKey = playfairKey + "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //append alphabet to key to create basis for matrix


	for (string::iterator iterator = playfairKey.begin(); iterator != playfairKey.end(); iterator++) {	//iterate through parameter and append values to playfairMatrixValues

		*iterator = toupper(*iterator);	
		
		if (*iterator == 'I') {		//if I detected, matches to J 
			*iterator = 'J';
		}

		if (playfairMatrixValues.find(*iterator) == -1) {	//if character that is not yet added to originalText is found, append 
			playfairMatrixValues += *iterator;
		}
	}

	copy(playfairMatrixValues.begin(), playfairMatrixValues.end(), &playfairMatrix[0][0]); //populate matrix

	cout << "Matrix" << endl;
	for (int i = 0; i < 5; i++) {		//print matrix to check 

		for (int j = 0; j < 5; j++) {
			cout << playfairMatrix[i][j];
		}
		cout << '\n';
	}

	
	for (string::iterator iterator = encryptedText.begin(); iterator != encryptedText.end(); iterator++) {	//iterate through ciphertext, replace I with J 

		*iterator = toupper(*iterator);	

		if ((*iterator < 65) || (*iterator > 90)) {	//if character is valid, go next
			continue;
		}
		
		if (*iterator == 'I') {	//if I is found, set to J
			*iterator = 'J';
		}
	}

	
	for (int i = 0; i < length; i += 2) {	//iterate by twos, and add X to duplicate characters

		pairs += encryptedText[i];	//append values to pairs for indexing

		if (i + 1 < length) {	//while not at end of encrypted text

			if (encryptedText[i] == encryptedText[i + 1]) {	//if pair detected
				pairs += 'X';
			}
			pairs += encryptedText[i + 1];
		}
	}

	if (pairs.length() % 2 == 1) {	//check for odd numbers
		pairs += 'X';	//append X
	}

	
	for (string::iterator iterator = pairs.begin(); iterator != pairs.end(); iterator++) {	//iterate through plaintext, now in pairs

		if (getCoordinates(*iterator++, x1, y1)) {	//get coordinates of first character in pair

			if (getCoordinates(*iterator, x2, y2)) {	//get coordinates of second character in pair

				if (x1 == x2) {	//if same row, append next character in the same row for both
					decryption += getCharacter(x1, y1 - 1);
					decryption += getCharacter(x2, y2 - 1);
				}
				else if (y1 == y2) {	//if same column, append next character in same column for both
					decryption += getCharacter(x1 - 1, y1);
					decryption += getCharacter(x2 - 1, y2);
				}
				else {	//normal, append intersection between row/column of the two characters
					decryption += getCharacter(x2, y1);
					decryption += getCharacter(x1, y2);
				}
			}
		}
	}
	return decryption;
}
