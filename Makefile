main: main.cpp binaryManip.h hexManip.h decrypt_1byte_xor_cipher.h chiSquared.h
	g++ -std=c++11 -c main.cpp 
	g++ -std=c++11 main.o -o mainfile.o
	./mainfile.o

1.2: FixedXOR.cpp binaryManip.h hexManip.h
	g++ -std=c++11 -c FixedXOR.cpp 
	g++ -std=c++11 FixedXOR.o -o 1.2.o
	./1.2.o

1.4: detect_1byte_xor.cpp hexManip.h 
	g++ -std=c++11 -c detect_1byte_xor.cpp 
	g++ -std=c++11 detect_1byte_xor.o -o 1.4.o 
	./1.4.o

clean:
	rm *.o *.out 1.*