.DEFAULT_GOAL := all

build/usuario.o: src/usuario.cpp include/usuario.h
		g++ src/usuario.cpp -Iinclude -Wall -ansi -pedantic -std=c++11 -g -c -o build/usuario.o

build/servidor.o: src/servidor.cpp include/servidor.h
		g++ src/servidor.cpp -Iinclude -Wall -ansi -pedantic -std=c++11 -g -c -o build/servidor.o

build/canaltexto.o: src/canaltexto.cpp include/canaltexto.h
		g++ src/canaltexto.cpp -Iinclude -Wall -ansi -pedantic -std=c++11 -g -c -o build/canaltexto.o

build/sistema.o: src/sistema.cpp include/sistema.h build/usuario.o build/servidor.o build/canaltexto.o
		g++ src/sistema.cpp -Iinclude -Wall -ansi -pedantic -std=c++11 -g -c -o build/sistema.o

build/executor.o: src/executor.cpp include/executor.h build/sistema.o
		g++ src/executor.cpp -Iinclude -Wall -ansi -pedantic -std=c++11 -g -c -o build/executor.o

build/concordo.o: src/concordo.cpp build/sistema.o build/executor.o build/usuario.o build/servidor.o build/canaltexto.o
		g++ src/concordo.cpp -Iinclude -Wall -ansi -pedantic -std=c++11 -g -c -o build/concordo.o

concordo: build/concordo.o build/sistema.o build/executor.o build/usuario.o build/servidor.o build/canaltexto.o
		g++ build/*.o -Iinclude -Wall -ansi -pedantic -std=c++11 -g -o concordo

#cria a pasta objects
create_build:
		mkdir -p build

all: create_build concordo

run:
		./concordo

#remove a pasta build e o executável do projeto
clean:
		rm -rf build concordo
