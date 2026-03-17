#ifndef PILE_HPP
#define PILE_HPP

#include "Noeud.hpp"

class PileNoeud {
private:
    Noeud** elements;
    int capacite;
    int sommet;
    void agrandir();

public:
    PileNoeud();
    ~PileNoeud();

    void empiler(Noeud* n);
    Noeud* depiler();
    bool vide() const;
    Noeud* top() const;
};

#endif
