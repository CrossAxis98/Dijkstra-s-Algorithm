CPPFLAGS= -c -g -Iinc -Wall -pedantic -std=c++14

_start_: algorytm
	./algorytm

algorytm: obj2/main.o obj2/ListaSasiedztwa.o obj2/MacierzSasiedztwa.o
	g++ -Wall -pedantic -o algorytm obj2/main.o obj2/ListaSasiedztwa.o obj2/MacierzSasiedztwa.o

obj2/main.o: main.cpp ReprezentacjaGrafu.h ListaSasiedztwa.h MacierzSasiedztwa.h
	g++ ${CPPFLAGS} -o obj2/main.o main.cpp

obj2/ListaSasiedztwa.o: ListaSasiedztwa.cpp ListaSasiedztwa.h ReprezentacjaGrafu.h
	g++ ${CPPFLAGS} -o obj2/ListaSasiedztwa.o ListaSasiedztwa.cpp

obj2/MacierzSasiedztwa.o: MacierzSasiedztwa.cpp MacierzSasiedztwa.h ReprezentacjaGrafu.h
	g++ ${CPPFLAGS} -o obj2/MacierzSasiedztwa.o MacierzSasiedztwa.cpp

clean:
	rm -f obj2/*.o algorytm



	
