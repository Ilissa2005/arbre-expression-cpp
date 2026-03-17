#include "Pile.hpp"

PileNoeud::PileNoeud() {
    capacite = 10;
    elements = new Noeud*[capacite];
    sommet = -1;
}

PileNoeud::~PileNoeud() {
    delete[] elements;
}

void PileNoeud::agrandir() {
    int nouvelleCapacite = capacite * 2;
    Noeud** nouveau = new Noeud*[nouvelleCapacite];
    for (int i = 0; i <= sommet; i++) {
        nouveau[i] = elements[i];
    }
    delete[] elements;
    elements = nouveau;
    capacite = nouvelleCapacite;
}

void PileNoeud::empiler(Noeud* n) {
    if (sommet + 1 >= capacite) {
        agrandir();
    }
    elements[++sommet] = n;
}

Noeud* PileNoeud::depiler() {
    if (sommet < 0) return nullptr;
    return elements[sommet--];
}

bool PileNoeud::vide() const {
    return sommet == -1;
}

Noeud* PileNoeud::top() const {
    if (sommet < 0) return nullptr;
    return elements[sommet];
}
