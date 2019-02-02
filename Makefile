FixedXor.o: FixedXOR.cpp binaryManip.h hexManip.h
	g++ -std=c++11 -c FixedXOR.cpp 
	g++ -std=c++11 FixedXOR.o -o 1.2
	./1.2

decrypt_1byte_xor_cipher.o: decrypt_1byte_xor_cipher.cpp hexManip.h
	g++ -std=c++11 -c decrypt_1byte_xor_cipher.cpp 
	g++ -std=c++11 decrypt_1byte_xor_cipher.o -o 1.3
	./1.3
clean:
	rm *.o *.out 1.*