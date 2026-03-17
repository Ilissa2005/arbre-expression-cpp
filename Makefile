CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

main: main.o Arbre.o Noeud.o Pile.o
	$(CXX) $(CXXFLAGS) -o main main.o Arbre.o Noeud.o Pile.o

main.o: main.cpp Arbre.hpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Arbre.o: Arbre.cpp Arbre.hpp Noeud.hpp
	$(CXX) $(CXXFLAGS) -c Arbre.cpp

Noeud.o: Noeud.cpp Noeud.hpp
	$(CXX) $(CXXFLAGS) -c Noeud.cpp

Pile.o: Pile.cpp Pile.hpp Noeud.hpp
	$(CXX) $(CXXFLAGS) -c Pile.cpp

clean:
	rm -f *.o main
