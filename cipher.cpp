#include <iostream>
#include <fstream>
#include <string>
#include "CipherInterface.h"
#include "Playfair.h"
#include "Monoalphabetic.h"
#include "Railfence.h"
#include "Vigenere.h"
#include "Caesar.h"

using namespace std;

int main(int argc, char** argv)
{
	/* Create empty cipher object*/	
	CipherInterface* cipher = NULL;

	ifstream inFile;		//define input output filestream
	ofstream outFile;

	string cipherSelect = "";	//string to select a cipher
	string action = "";		//string to store choice to encrypt or decrypt
	string encrypt = "ENC";		//string to encrypt
	string decrypt = "DEC";		//string to decrypt
	string cipherKey = "";		//string to store key being passed in
	string inputText = "";		//text to be inputted
	string plainText = "";		//string to store plaintext
	string cipherText = "";		//string to store ciphertext
	string inputFile = "";		//string to store name of input file that contains text
	string outputFile = "";		//string to store name of output file containing cipherText
	
	//ciphers to choose from
	string ces = "CES";	//caesar
	string mac = "MAC";	//monoalphabetic
	string plf = "PLF";	//playfair
	string rfc = "RFC";	//railfence
	string vig = "VIG";	//vigenere

	//the arguments to be passed in
	cipherSelect = argv[1];
	cipherKey = argv[2];
	action = argv[3];
	inputFile = argv[4];
	outputFile = argv[5];


	// test command:  ./cipher <cipher name> <key> <enc/dec> <input file> <output file>
	// test example:  ./cipher CAE 3 ENC input.txt output.txt
	cout << "Cipher: " << cipherSelect << endl; 
	cout << "Key: " << cipherKey << endl;
	cout << "Action: " << action << endl;
	cout << "Input File: " << inputFile << endl;
	cout << "Output File: " << outputFile << endl;


	//call the commands, compares to inputted argvs
	if (cipherSelect.compare(ces) == 0) {
		cipher = new Caesar();
	}
	else if (cipherSelect.compare(mac) == 0) {
		cipher = new Monoalphabetic();
	}
	else if (cipherSelect.compare(plf) == 0) {
		cipher = new Playfair();
	}
	else if (cipherSelect.compare(rfc) == 0) {
		cipher = new Railfence();
	}
	else if (cipherSelect.compare(vig) == 0) {
		cipher = new Vigenere();
	}
	else {	//if input doesn't match any of the ciphers
		cout << "Invalid cipher selected.";
	}

	//if key was valid and cipher selection/argvs are valid
	inFile.open(argv[4]);		
	outFile.open(argv[5]);
	getline(inFile, inputText, '\0');	//read text from input file
	inFile.close();


	/* Error checks */
	if (!cipher) {
		fprintf(stderr, "ERROR [%s %s %d]: could not allocate memory\n",
			__FILE__, __FUNCTION__, __LINE__);
		exit(-1);
	}
	if (!cipher->setKey(cipherKey)) {
		cout << "Invalid Key inputted for the selected cipher." << endl 
			 << "Selected Cipher: " << cipherSelect << endl;
		exit(-1);
	}
	
	

	if (action.compare(encrypt) == 0) {	//action is encrypt
		cipherText = cipher->encrypt(inputText);
		outFile << cipherText;
	}
	else if (action.compare(decrypt) == 0) { //action is decrypt
		plainText = cipher->decrypt(inputText);
		outFile << plainText;
	}

	outFile.close();
	return 0;
}
