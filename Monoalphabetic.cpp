#include <iostream>
#include <string>   /* For C++ strings */
#include <bits/stdc++.h>
#include "Monoalphabetic.h"

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */
bool Monoalphabetic::setKey(const string& key){

    alphabet = "abcdefghijklmnopqrstuvwxyz";    //define possible letters in alphabet

    vector<bool> mark(26, false);  //vector to mark each letter as they appear
    int index;  //index for bool vector

    if (key.length() == 26) {   //key must be 26 characters long (26 letters in alphabet)

        for (int i = 0; i < key.length(); i++) {    //begin loop for checking valid characters

            if (!isalpha(key[i])) { //check for only letters of the alphabet
                return false;
            }

            else {   //if all characters are valid letters of the alphabet

                if ('A' <= key[i] && key[i] <= 'Z') {   //check uppercase characters
                    index = key[i] - 'A';   //subtract A to get index in ASCII
                    mark[index] = true;     //mark letter as existing
                }
                else if ('a' <= key[i] && key[i] <= 'z') { //check lowercase characters
                    index = key[i] - 'a';   //subtract a to get index in ASCII
                    mark[index] = true;     //mark letter as existing
                }
            }
        }   //end loop for checking valid characters
    }   

    for (int j = 0; j <= 25; j++) { //loops through vector 
        if (mark[j] == false) { //if any letters are not present key is invalid
            return false;   
        }
    }

    for (int k = 0; k < key.length(); k++) {    //change key to uppercase
        toupper(key[k]);
    }
    return true;
 }


/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Monoalphabetic::encrypt(const string& plaintext)
{
    string encryption = "";  //string to hold the ciphertext

    for (int i = 0; i < plaintext.length(); i++) {

        for (int j = 0; j < 26; j++) {  //match plaintext character with cipher alphabet

            if (plaintext[j] == alphabet[j]) {
                encryption.push_back(monoalphabeticKey[j]); //adding the resulting character to the encrypted plaintext variable
            }
        }
    }
    return encryption;  
}



/**
 * Decrypts a string of ciphertext
 * @param ciphertext - the ciphertext
 * @return - the decrypted plaintext
 */
string Monoalphabetic::decrypt(const string& ciphertext)
{
    string decryption = "";  //string to hold the plaintext

    for (int i = 0; i < ciphertext.length(); i++) { //match ciphertext character with plain alphabet
        
        for (int j = 0; j < 26; j++) {

            if (ciphertext[i] == monoalphabeticKey[j]) {
                decryption.push_back(alphabet[j]);  //adding the resulting character to the decrypted ciphertext
            }
        }
    }
    return decryption;  
}
