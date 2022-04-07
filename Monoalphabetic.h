#ifndef MONOALPHABETIC_H
#define MONOALPHABETIC_H

#include <string>	/* For C++ strings */
#include "CipherInterface.h"

using namespace std;

/**
 * This class implements the Monoalphabetic cipher.
 * The class extends the abstract class
 * CipherInterface.
 */

class Monoalphabetic : public CipherInterface{

	/** The public members **/
	public:

		/**
		 * Sets the key to use
		 * @param key - the key to use
		 * @return - True if the key is valid and False otherwise
		 */
		virtual bool setKey(const string& key);

		/**
		 * Encrypts a plaintext string
		 * @param plaintext - the plaintext string
		 * @return - the encrypted ciphertext string
		 */
		virtual string encrypt(const string& plaintext);

		/**
		 * Decrypts a string of ciphertext
		 * @param ciphertext - the ciphertext
		 * @return - the plaintext
		 */
		virtual string decrypt(const string& ciphertext);


	/*protected members*/
	protected:

		string monoalphabeticKey;	//string to store monoalphabetic key

	/*the private members*/
	private:

		string alphabet;	//string to store letters of the alphabet
};

#endif
