.DEFAULT_GOAL := all

OBJECTS=sistema.o executor.o

sistema.o: src/sistema.cpp include/sistema.h
	g++ src/sistema.cpp -c -o sistema.o

executor.o: src/executor.cpp include/executor.h 
	g++ -Iinclude src/executor.cpp -c -o executor.o

usuario.o: src/usuario.cpp include/usuario.h
	g++ -Iinclude src/usuario.cpp -c -o usuario.o

mensagem.o: src/mensagem.cpp include/mensagem.h
	g++ -Iinclude src/mensagem.cpp -c -o mensagem.o

canaltexto.o: src/canalTexto.cpp canaltexto.o
	g++ -Iinclude src/canaltexto.cpp -c -o canaltexto.o

servidor.o: src/servidor.cpp mensagem.o canaltexto.o include/servidor.h include/canaltexto.h
	g++ -Iinclude src/servidor.cpp -c -o servidor.o

objects: sistema.o executor.o usuario.o mensagem.o canaltexto.o servidor.o

concordo: objects src/concordo.cpp
	g++ -Wall -fsanitize=address -Iinclude sistema.o executor.o usuario.o mensagem.o canaltexto.o servidor.o src/concordo.cpp -o concordo

clean:
	rm *.o concordo

all: concordo

run:
	./concordo
