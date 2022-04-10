#include "Vigenere.h"
#include <iostream>
#include <string>

using namespace std;

/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */

string vigenereKey = "";
//string xAxis = "abcdefghijklmnopqrstuvwxyz";
//string yAxis = "abcdefghijklmnopqrstuvwxyz";
string temp = "";


bool Vigenere::setKey(const string& key)
{
    vigenereKey = key;
    char value;
    
    for (int i = 0; i < vigenereKey.length(); i++)
    {
        if (!isalpha(vigenereKey[i])) {
            cout << "Key can only contain letters." << "\n";
        }
    }
    cout << "The key is " << vigenereKey << "." << "\n";
    
    return true;
}

/**
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */


string Vigenere::encrypt(const string& plainText)
{
    string encryptedText = "";
    char charOne;
    int count = 0;
    int index = 0;
    int temp;
    char newChar;
 
    
   while (encryptedText.length() < plainText.length())
   {
       for (int i = 0; i < vigenereKey.length(); i++)
       {
            temp = (int(vigenereKey[i]) - 65 ) + (int(plainText[index]) );

            // setting ascii range
                   if (temp > 90)
                   {
                       temp = temp - 90 + 64;
                   }
                   if (temp > 64 && temp < 91)
                   {
                       newChar = char(temp);
                       encryptedText = encryptedText + newChar;
                   }

                   index++;
               }
           }
          
    
    /*//create table
    int table[26][26] = {};
    for (int i = 0; i < 26; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            int temporary = 0;
            if((i+65)+j > 90)
            {
                temporary = ((i+65)+j) - 26;
                table[i][j] = temporary;  //adds letter to the correct table position
            }
            else
            {
                temporary = (i+65)+j;
                table[i][j] = temporary;   //adds letter to the correct table position
            }
        }
    } */
    
    cout << "the encrypted text is: " << encryptedText << endl;
    return encryptedText;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */


string Vigenere::decrypt(const string& cipherText)
{
    string decryptedText ="";
    int keySize = vigenereKey.length();
    int index = 0;
    int temp;
    char newChar;

    while (decryptedText.length() < cipherText.length() )
    {
        for (int i = 0; i<vigenereKey.length(); i++)
        {
            temp = ( int(cipherText[index]) - (int(vigenereKey[i]) - 65 )  );

            // put the value into A-Z ASCII range, 65-90
            if ( 65 > temp )
            {
                temp = 91 - (65 - temp);
            }

            if (64 < temp  && 91 > temp)
            {
                newChar = char(temp);
                decryptedText = decryptedText + newChar;
            }

            index++;
        }
    }
    cout << "the decrypted text is: " << decryptedText << endl;
    return decryptedText;
}