main: main.cpp binaryManip.h hexManip.h chiSquared.h
	g++ -std=c++11 -c main.cpp 
	g++ -std=c++11 main.o -o mainfile.o
	./mainfile.o

1.2: FixedXOR.cpp binaryManip.h hexManip.h
	g++ -std=c++11 -c FixedXOR.cpp 
	g++ -std=c++11 FixedXOR.o -o 1.2.o
	./1.2.o

1.4: 1byte_xor_cipher.cpp hexManip.h chiSquared.h
	g++ -std=c++11 -c 1byte_xor_cipher.cpp 
	g++ -std=c++11 1byte_xor_cipher.o -o 1.4.o 
	./1.4.o 

1.5: repeating_key_xor.cpp binaryManip.h 
	g++ -std=c++11 -c repeating_key_xor.cpp 
	g++ -std=c++11 repeating_key_xor.o -o 1.5.o 
	./1.5.o

clean:
	rm *.o *.out 1.*