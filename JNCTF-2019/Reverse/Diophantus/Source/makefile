Diophantus: Diophantus.o Base64.o AES.o
	g++ -o Diophantus Diophantus.o Base64.o AES.o

Diophantus.o: Diophantus.cpp
	g++ -c Diophantus.cpp

Base64.o: Base64.cpp Base64.h
	g++ -c Base64.cpp

AES.o: AES.cpp AES.h
	g++ -c AES.cpp

clean:
	rm Diophantus Diophantus.o Base64.o AES.o 



