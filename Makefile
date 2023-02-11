all: compile

compile:
	g++ -pthread -o server.out -std=c++11 Server/*.cpp Server/*.h Server/CLI/*.h Server/CLI/*.cpp Server/Command/*.h Server/Command/*.cpp Server/Distances/*.h Server/Distances/*.cpp Server/IO/*.h Server/IO/*.cpp
	g++ -pthread -o client.out -std=c++11 Client/*.cpp Client/*.h

clean:
	rm *.out
