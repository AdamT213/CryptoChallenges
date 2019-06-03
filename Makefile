1.2: FixedXOR.cpp binaryManip.h hexManip.h
	g++ -std=c++11 -c FixedXOR.cpp 
	g++ -std=c++11 FixedXOR.o -o 1.2.o
	./1.2.o

1.4: 1byte_xor_cipher.cpp hexManip.h decrypt_1byte_xor_cipher.h
	g++ -std=c++11 -c 1byte_xor_cipher.cpp 
	g++ -std=c++11 1byte_xor_cipher.o -o 1.4.o 
	./1.4.o 

1.5: repeating_key_xor.cpp binaryManip.h repeating_key_xor.h
	g++ -std=c++11 -c repeating_key_xor.cpp 
	g++ -std=c++11 repeating_key_xor.o -o 1.5.o 
	./1.5.o 

1.6: break_vigenere_cipher.cpp binaryManip.h informationTheory.h
	g++ -std=c++11 -c break_vigenere_cipher.cpp
	g++ -std=c++11 break_vigenere_cipher.o -o 1.6.o 
	./1.6.o 

1.7: decrypt_AES_in_ECBmode.cpp  binaryManip.h
	g++ -Wall -std=c++11 -c decrypt_AES_in_ECBmode.cpp
	g++ -Wall -std=c++11 decrypt_AES_in_ECBmode.o -o  1.7.o -lcrypto
	./1.7.o

1.8: detect_AES_in_ECBmode.cpp  
	g++ -Wall -std=c++11 -c detect_AES_in_ECBmode.cpp
	g++ -Wall -std=c++11 detect_AES_in_ECBmode.cpp -o  1.8.o -lcrypto
	./1.8.o

2.9: PKCS7.cpp 
	g++ -Wall -std=c++11 -c PKCS7.cpp
	g++ -Wall -std=c++11 PKCS7.cpp -o  2.9.o 
	./2.9.o

2.10: CBC_by_hand.cpp
	g++ -Wall -std=c++11 -c CBC_by_hand.cpp
	g++ -Wall -std=c++11 CBC_by_hand.o -o  2.10.o -lcrypto
	./2.10.o
	
clean:
	rm *.o *.out 1.* 2.*
