#include <iostream>
#include <string>   /* For C++ strings */
#include "Caesar.h"

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Caesar::setKey(const string& key){ 

    if (key.length() > 0) { //if not an empty input, key is valid
        for (int i = 0; i < key.length(); i++) {    //loop through parameter string key, key could be more than one digit
            caesarKey = caesarKey + key[i];         
        }
        return true; 
    }

    else {  //empty input, key is invalid
        cout << "Key is empty." << endl;
        return false;
    }
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Caesar::encrypt(const string& plaintext){

    /*
    refer to slide 54 in classicalciphers
    encryption: ciphertext = encrypt(plaintext) = (plaintext + key) mod 26
    */
    int encryptionOffset = stoi(caesarKey) % 26; //convert string stored in caesarKey to int to get the offset
    string encryption = ""; //string to hold the ciphertext
    char currentChar; //variable to hold current character in the plaintext 

    /*
    ASCII A = 65, Z = 90, a = 97, z = 122
    */

    for (int i = 0; i < plaintext.length(); i++) {  //loop through plaintext char by char

        char currentChar = plaintext[i];   //set current char to first char in plaintext string

        if (currentChar >= 'a' && currentChar <= 'z') { //if character is between a and z
            currentChar += 'A' - 'a';
        }

        currentChar = currentChar + encryptionOffset; //adding the offset to the character

        if (currentChar > 'Z') {    //account for ASCII values between 91 - 96
            currentChar = 'A' + (currentChar - 'Z' - 1);
        }
   
        encryption.push_back(currentChar);  //adding the resulting character to the encrypted plaintext variable

    }
    return encryption;
}


/**
 * Decrypts a string of ciphertext
 * @param ciphertext - the ciphertext
 * @return - the decrypted plaintext
 */
string Caesar::decrypt(const string& ciphertext){

    /*
    refer to slide 54 in classicalciphers
    decryption: plaintext = decrypt(ciphertext) = (26 + (ciphertext – key)) mod 26
    */
    int offsetDecryption = stoi(caesarKey) % 26; //convert string stored in caesarKey to int to get the offset
    string decryption = ""; //string to hold the plaintext
    char currentChar; //variable to hold current character in the ciphertext 
    
    /*
    ASCII A = 65, Z = 90, a = 97, z = 122
    */

    for (int i = 0; i < ciphertext.length(); i++) { //loop through ciphertext char by char

        char currentChar = ciphertext[i];   //set current char to first char in ciphertext string 

        currentChar = currentChar - offsetDecryption;    //subtracting the offset

        if (currentChar < 'A') {    //account for ASCII values less than 65
            currentChar = 'Z' - ('A' - currentChar - 1); 
        }

        decryption.push_back(currentChar);  //adding the resulting character to the decrypted ciphertext

    }
    return decryption;
}

