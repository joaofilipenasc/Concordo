.DEFAULT_GOAL := all

OBJECTS=build/sistema.o build/executor.o

build/sistema.o: src/sistema.cpp include/sistema.h
	g++ src/sistema.cpp -c -o build/sistema.o

build/executor.o: src/executor.cpp include/executor.h 
	g++ -Iinclude src/executor.cpp -c -o build/executor.o

build/usuario.o: src/usuario.cpp include/usuario.h
	g++ -Iinclude src/usuario.cpp -c -o build/usuario.o

build/mensagem.o: src/mensagem.cpp include/mensagem.h
	g++ -Iinclude src/mensagem.cpp -c -o build/mensagem.o

build/canaltexto.o: src/canalTexto.cpp include/canaltexto.h 
	g++ -Iinclude src/canaltexto.cpp -c -o build/canaltexto.o

build/servidor.o: src/servidor.cpp include/canaltexto.h
	g++ -Iinclude src/servidor.cpp -c -o build/servidor.o

objects: sistema.o executor.o usuario.o mensagem.o canaltexto.o servidor.o

concordo: objects src/concordo.cpp build/sistema.o build/executor.o build/usuario.o build/mensagem.o build/canaltexto.o build/servidor.o
	g++ -Wall -fsanitize=address -Iinclude sistema.o executor.o usuario.o mensagem.o canaltexto.o servidor.o src/concordo.cpp -o build/concordo

clean:
	rm build/*.o build/concordo

all: concordo

run:
	./build/concordo
