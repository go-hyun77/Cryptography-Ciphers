#include "Playfair.h"
#include <iostream>
#include <string>
using namespace std;



/**
 * Sets the key to use
 * @param key - the key to use
 * @return - True if the key is valid and False otherwise
 */

string playfairKey = "";
char playfairMatrix [5][5] = {0};
string alphabet = "abcdefghiklmnopqrstuvwxyz";
string temp = "";
bool isDuplicate = false;
string newPlaintext = "";

bool Playfair::setKey(const string& key)
{
    playfairKey = key;
    
    //check to make sure the key is all letters
    for (int i = 0; i < playfairKey.length(); i++)
    {
        if (!isalpha(playfairKey[i])) {
            cout << "error in key" << endl;
            return false;
        }
    }
    cout << "The key is " << playfairKey << "." << endl;
    return true;
}

//find row and column postions for each letter
void Playfair::findPositionInMatrix(char letter, int &row, int &col)
{
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (letter == playfairMatrix[i][j])
            {
                row = i;
                col = j;
                return;
            }
        }
    }
}

/**	
 * Encrypts a plaintext string
 * @param plaintext - the plaintext string
 * @return - the encrypted ciphertext string
 */
string Playfair::encrypt(const string& plaintext)
{
    //adding alphabet to our key
    temp = playfairKey + alphabet;
    cout << "this is temp: " << temp << "\n";
    
    //we want to make sure playfairKey has no duplicates
    //flayfairKey = securityabcdefghijklmnopqrstuvwxyz
    
    for (int i = 0; i < playfairKey.length(); i++)
    {
        for (int j = i + 1; j < temp.length(); j++)
        {
            if (playfairKey[i] == temp[j])  //go into this lock if the same letters appears more than once
            {
                cout << "Duplicate found: " << temp[j] << "\n";
                //erase duplicate letter
                temp.erase(j, 1);
                break;
            }
        }
    }
    playfairKey = temp;
    cout << "This is the key without duplicates: " << playfairKey << "\n";
    
    //so now let's insert key into our 5x5 matrix
    //so matrix will look like: secur ityab dfghk lmnop qvwxz
    //UPPERCASE LETTERS ARE IGNORED FOR NOW
    
    for (int i = 0; i < playfairKey.length(); i++)
    {
        (playfairMatrix[0][i] = playfairKey[i]);
        //cout << playfairMatrix[0][i] << " | ";
    }
    cout << "\n";
    
   /* //print out matrix--not really needed, cause i have it up above
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << playfairMatrix[i][j] << " | ";
        }
    }
    cout << endl; */
    

    //print matrix in 5x5 table format
    int rows = 5;
    int columns = 5;
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            cout << " " << playfairMatrix[i][j] << " | ";   //prints matrix out
        }
        cout << "\n";
    }
    cout << "\n";
     
 
    //split up key into digrams
    //plaintext: "hello world" is passed in
    //first we want to make sure there are no 2 letters that are the same next to each other
    
    string withX = "";
    int size = plaintext.length();
    
    for (int i = 1; i < size; ++i)
    {
        if (!isspace(plaintext[i-1]))
        {
            withX += plaintext[i-1];
        }
        if (plaintext[i-1] == plaintext[i])
            withX += 'x';
    }
    
    //now reading in the last letter and seeing if there is an odd number of letters in the key
    withX += plaintext[size - 1];
   // if (withX.length() % 2 == 1)
    if ((withX.length() & 1) == 1)
    {
        withX += 'x';
    }
    cout << "this is withX: " << withX << "\n";
    
    
    
    
    //HERE
    
    
    //find position in matrix
    //we will encrypt 2 letters at a time
    string encryptedString = "";
    int row1;
    int column1;
    int row2;
    int column2;
    
    for(int pos = 0; pos < size; pos += 2)
    {
        
        findPositionInMatrix(plaintext[pos], row1, column1);
        findPositionInMatrix(plaintext[pos+1], row2, column2);
        
        //implementing encryption rules
        //1. If the two letter pair is in the same row, move each letter one space to the right
        
        if (row1 == row2)
        {
            //output += playfairMatrix[row1][mod(column1+1, 5)];
            //row values stay the same
            
            int mod1 = (column1 + 1 % 5);
            int mod2 = (column2 + 1 % 5);
            encryptedString += playfairMatrix[row1][mod1];
            encryptedString += playfairMatrix[row2][mod2];
            //cout << "row == row " << ": " << encryptedString << "\n";
            
        }
        else if (column1 == column2)
        {
            int mod3 = (row1 + 1 % 5);
            int mod4 = (row2 + 1 % 5);
            encryptedString += playfairMatrix[mod3][column1];
            encryptedString += playfairMatrix[mod4][column2];
            
            //cout << "output is " << encryptedString << "\n";
        }
        else
        {
            
            encryptedString += playfairMatrix[row1][column2];
            encryptedString += playfairMatrix[row2][column1];
            
            //cout << "regular encryption" << ": " << encryptedString << "\n";
            
        }
    }
    cout << "THE FINAL ENCRYPTED STRING IS: " << encryptedString << "\n";
	return encryptedString;
}

/**
 * Decrypts a string of ciphertext
 * @param cipherText - the ciphertext
 * @return - the plaintext
 */
string Playfair::decrypt(const string& cipherText) 
{
    //no need to remove the X's
    string decryptedString = "";
    int row1, column1, row2, column2;
    int size = cipherText.length();
    
    for(int pos = 0; pos < size; pos += 2)
    {
        findPositionInMatrix(cipherText[pos], row1, column1);
        findPositionInMatrix(cipherText[pos+1], row2, column2);
        
        //implementing encryption rules
        //1. If the two letter pair is in the same row, move each letter one space to the right
        
        if (row1 == row2)
        {
            int mod1 = (column1 - 1 % 5);
            int mod2 = (column2 - 1 % 5);
            decryptedString += playfairMatrix[row1][mod1];
            decryptedString += playfairMatrix[row2][mod2];
            //cout << "row == row " << ": " << decryptedString << "\n";
        }
        
        //move each letter down one
        else if (column1 == column2)
        {
            int mod3 = (row1 - 1 % 5);
            int mod4 = (row2 - 1 % 5);
            decryptedString += playfairMatrix[mod3][column1];
            decryptedString += playfairMatrix[mod4][column2];
            
           // cout << "output is " << decryptedString << "\n";
            
        }
        else
        {
            decryptedString += playfairMatrix[row1][column2];
            decryptedString += playfairMatrix[row2][column1];
            
            //cout << "regular encryption" << ": " << decryptedString << "\n";
        }
}
    cout << "THE FINAL DECRYPTED STRING IS: " << decryptedString << "\n";
    return decryptedString; }


/*

string Playfair::encrypt(const string& plaintext)
{
    //adding alphabet to our key
    playfairKey += alphabet;
    
    //we want to make sure playfairKey has no duplicates
    //flayfairKey = securityabcdefghijklmnopqrstuvwxyz
    
    for (int i = 0; i < playfairKey.length(); i++)
    {
        for (int j = i + 1; j < playfairKey.length(); j++)
        {
            if (playfairKey[i] == playfairKey[j])  //go into this lock if the same letters appears more than once
            {
                cout << "Duplicate found: " << playfairKey[j] << "\n";
                //erase duplicate letter
                playfairKey.erase(j, 1);
                break;
            }
        }
    }
    cout << "This is the key without duplicates: " << playfairKey << "\n\n";
    
    //so now let's insert key into our 5x5 matrix
    //so matrix will look like: secur ityab dfghk lmnop qvwxz
    //UPPERCASE LETTERS ARE IGNORED FOR NOW
    
    for (int i = 0; i < playfairKey.length(); i++)
    {
        (playfairMatrix[0][i] = playfairKey[i]);
        cout << playfairMatrix[0][i] << " | ";
    }
    cout << "\n" << "\n";
*/
