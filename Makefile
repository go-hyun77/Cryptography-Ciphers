all:	cipher

cipher:	cipher.o Playfair.o Railfence.o Monoalphabetic.o Vigenere.o Caesar.o
	g++ cipher.o Playfair.o Railfence.o Monoalphabetic.o Vigenere.o Caesar.o -o cipher

cipher.o: cipher.cpp
	g++ -g -c cipher.cpp 

Playfair.o:	Playfair.cpp Playfair.h CipherInterface.h
	g++ -g -c Playfair.cpp

Railfence.o: Railfence.cpp Railfence.h CipherInterface.h
	g++ -g -c Railfence.cpp

Monoalphabetic.o: Monoalphabetic.cpp Monoalphabetic.h CipherInterface.h
	g++ -g -c Monoalphabetic.cpp

Vigenere.o: Vigenere.cpp Vigenere.h CipherInterface.h
	g++ -g -c Vigenere.cpp

Caesar.o: Caesar.cpp Caesar.h CipherInterface.h
	g++ -g -c Caesar.cpp

clean:
	rm -rf *.o cipher
