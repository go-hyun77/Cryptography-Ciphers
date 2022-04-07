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
    ciphertext / key = length of row
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

        //encryption.push_back('\n'); //creates the rows, uncomment when done testing
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
    ciphertext / key = length of row
    (ciphertext) % (key)
    1st row = .... + (% result)
    2nd row = ....
    3rd row = ....
    */

    string decryption = "";  //string to hold the plaintext

    int depth = stoi(railfenceKey);    //converts from string to int data type (how many rows does the railfence have?)
    int length = ciphertext.length();  //length of ciphertext parameter
    int remainder = length % depth;    //remainder of length/(# of rows)
    int rowLength = length / depth;    //contains number of char per row
    int column = 0;                    //length of row, used to calculate how many "spaces" to jump in ciphertext
    int columnCounter = 0;             //iterator to change columns between each decryption.pushback()
    bool isDivisible = false;          //bool to determine if ciphertext is divisible

    if (remainder == 0) {       //determine whether or not ciphertext length has remainder after %
        isDivisible = true;     //no remainder, all rows will be same length
    }
    else {
        isDivisible = false;    //has remainder, 1st row will be longer than others
    }

    if (remainder != 0) {       //if remainder exists
        column = (rowLength) + 1;
    }
    else {                      //if no remainder
        column = (rowLength);
    }

    if (isDivisible) {          //if all rows are same length
        for (int i = 0; i < rowLength; i++) {
            for (int j = 0; j < length; j += (rowLength)) {         //skip rowLength amount of spaces to add in order by column
                decryption.push_back(ciphertext[j + columnCounter]);    //add character to plaintext
            }
            columnCounter++;    //increment counter to move to the next column
        }
    }
    else {      //if row length is not the same across all rows
        while (columnCounter != column) {
                
            if (columnCounter == column - 1) {  //account for rows that are + 1 longer than the others

                for (int k = 0; k < remainder; k++) {
                    decryption.push_back(ciphertext[columnCounter]);    //add character to plaintext
                    columnCounter += (rowLength) + 1;   //skip spaces to next character 
                }
                break;
            }

            for (int l = columnCounter; l < length; l++) {  //add from beginning
                decryption.push_back(ciphertext[l]);

                if (remainder != 0) {   //if additional char exists on current row
                    l++;
                    remainder--;    //decrement to avoid moving another "space"
                }

                l += (rowLength) - 1;   //jump rowLength amount of spaces to next char to pushback in next "column"
            }
            remainder = length % depth; //check if we need to skip an additional "space" to get to next "column"
            columnCounter++;
        }
    }
    return decryption;
}
