#include <iostream>
#include <string>
#include "Railfence.h"

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Railfence::setKey(const std::string& key){

    if (key.length() > 0) {     //check key for letters, key should be an integer only

        for (int i = 0; i < key.length(); i++) {

            if (isalpha(key[i])) {  //if a letter is found
                return false; //key is invalid
            }
        }

        railfenceKey = key; //set value of railfencekey to parameter key
        return true;
    }
    else {
        return false;
    }
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Railfence::encrypt(const string& plaintext) {

    /*
    refer to slide 102 in classicalciphers
    get length of ciphertext
    ciphertext / key
    (ciphertext) % (key)
    1st row = .... + (% result)
    2nd row = ....
    3rd row = ....
    */

    string encryption = ""; //string to hold the ciphertext

    int depth = stoi(railfenceKey);     //converts from string to int data type (how many rows will the railfence have?)
    int depthCounter = 0;               //iterator to determine which row to insert into
    int length = plaintext.length();    //length of plaintext

    for (int i = 0; i < depth; i++) {   
        depthCounter = depthCounter + i;

        while (depthCounter < length) {
            encryption.push_back(plaintext[depthCounter]); //add character to ciphertext
            depthCounter = depthCounter + depth;   //will append the next character after "depth" amount of spaces
        }

        depthCounter = 0; //reset the depth counter to maintain the same "distance" between each append per row

        encryption.push_back('\n'); //creates the rows, uncomment when done testing
    }
    //cout << encryption << endl;   //testing output, uncomment to check if rows outputted properly
    return encryption;
}


/**
* Decrypts a string of ciphertext
* @param ciphertext - the ciphertext
* @return - the decrypted plaintext
*/
string Railfence::decrypt(const string& ciphertext){

    /*
    refer to slide 103 in classicalciphers
    get length of ciphertext
    ciphertext / key
    (ciphertext) % (key)
    1st row = .... + (% result)
    2nd row = ....
    3rd row = ....
    */

    string decryption = "";                         //string to hold the plaintext
    int length = ciphertext.length();               //length of ciphertext parameter
    int depth = stoi(railfenceKey);                 //converts from string to int data type (how many rows does the railfence have?)

    string encryptedText = "";                      //string to store ciphertext, ciphertext currently has multiple rows
    int lengthEncrypted = encryptedText.length();   //length of ciphertext
    bool isDivisible = false;                       //bool to determine if ciphertext is divisible
    int remainder = lengthEncrypted % depth;        //remainder of length/(# of rows)

    if (remainder == 0) {       //determine whether or not ciphertext length has remainder after %
        isDivisible = true;     //no remainder, all rows will be same length
    }
    else {
        isDivisible = false;    //has remainder, 1st row will be longer than others
    }

    
    for (int i = 0; i < length; i++) {                   //populate encryptedText with parameter ciphertext without rows
        if (ciphertext[i] != '\n') {                     //ignore new line when parsing string
            encryptedText.push_back(ciphertext[i]);
        }
    }                                                    //left with ciphertext in one long row at this point
        
   
    long int columnCounter = 0;
    long int column = 0;
    if (remainder != 0) {
        column = (lengthEncrypted / depth) + 1;
    }
    else {
        column = (lengthEncrypted / depth);
    }

    if (isDivisible) {
        for (unsigned int k = 0; k < lengthEncrypted / depth; k++) {
            for (unsigned int l = 0; l < lengthEncrypted; l += (lengthEncrypted / depth)) {
                decryption.push_back(encryptedText[l + columnCounter]);
            }
            columnCounter++;
        }
    }
    else {
        while (columnCounter != column) {
            if (columnCounter == column - 1) {
                for (unsigned int m = 0; m < remainder; m++) {
                    decryption.push_back(encryptedText[columnCounter]);
                    columnCounter += (lengthEncrypted / depth) + 1;
                }
                break;
            }
            for (unsigned int n = columnCounter; n < lengthEncrypted; n++) {
                decryption.push_back(encryptedText[n]);
                if (remainder != 0) {
                    n++;
                    remainder--;
                }
                n += (lengthEncrypted / depth) - 1;
            }
            remainder = lengthEncrypted % depth;
            columnCounter++;
        }
    }
    return decryption;
}
