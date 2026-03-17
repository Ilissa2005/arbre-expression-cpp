main : main.cpp pile.o arbre.o noeud.o
	g++ -o main pile.o arbre.o noeud.o main.cpp

pile.o : Pile.hpp Pile.cpp
	g++ -c Pile.cpp

arbre.o : Arbre.hpp Noeud.hpp Arbre.cpp
	g++ -c Arbre.cpp

noeud.o : Noeud.hpp Noeud.cpp
	g++ -c Noeud.cpp
