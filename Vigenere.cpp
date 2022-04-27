#include "Vigenere.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Vigenere::setKey(const string& key)
{
    if (key.length() > 0) {     //if key exists
        for (int i = 0; i < key.length(); i++) {
            if (!isalpha(key[i])) {    //if non-alphabet character detected, throw error
                return false;
            }
            if (key[i] >= 'a' && key[i] <= 'z') {	//check for lowercase
                vigenereKey += key[i] + 'A' - 'a';  //change to uppercase 
            }
            else if (key[i] >= 'A' && key[i] <= 'Z') {  //if letter is valid
                vigenereKey += key[i];
            }
        }
        return true;
    }
    return false;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Vigenere::encrypt(const string& plainText)
{
    string encryption = ""; //string to hold the ciphertext

    for (int x = 0, y = 0; x < plainText.length(); x++) {
        
        char currentChar = plainText[x];

        if (currentChar >= 'a' && currentChar <= 'z') { //if current character is between a and z
            currentChar += 'A' - 'a';   //add current character to "difference" between vigenere table length
        }
        else if (currentChar < 'A' || currentChar > 'Z') { //if uppercase caught, skip current iteration of loop and continue
            continue;
        }

        encryption += (currentChar + vigenereKey[y] - 2 * 'A') % 26 + 'A'; //append current character to encryption,
                                                                           //add value of A to bring back in ASCII range of A-Z

        y = (y + 1) % vigenereKey.length(); 
    }
    return encryption;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Vigenere::decrypt(const string& cipherText)
{
    string decryption = ""; //string to hold the plaintext

    for (int x = 0, y = 0; x < ciphertext.length(); x++) {

        char currentChar = ciphertext[x];

        if (currentChar >= 'a' && currentChar <= 'z') { //if current character is between a and z
            currentChar += 'A' - 'a';   //add current character 
        }
        else if (currentChar < 'A' || currentChar > 'Z') {
            continue;
        }
        decryption += (currentChar - vigenereKey[y] + 26) % 26 + 'A';   //append current character to encryption,
                                                                        //add value of A to bring back in ASCII range of A-Z
        y = (y + 1) % vigenereKey.length();
    }
    return decryption;
}

