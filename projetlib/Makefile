.PHONY = build genlib install

install: genlib
	mkdir build
	mkdir build/include
	mkdir build/lib
	cp *.h ./build/include/
	cp *.a ./build/lib/

genlib: build
	ar -rsc libOperation.a Operation.o
	ar -rsc libPersonne.a Personne.o

build:
	g++ -o Operation.o -c Operation.cpp
	g++ -o Personne.o -c Personne.cpp