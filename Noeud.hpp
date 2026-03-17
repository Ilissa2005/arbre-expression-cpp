#ifndef NOEUD_HPP
#define NOEUD_HPP

#include <iostream>

class Noeud {
public:
    char type;   // 'o' = operateur, 'f' = constante, 'v' = variable
    double val;  // valeur si constante
    char ope;    // operateur ou nom de variable
    Noeud* fg;   // fils gauche
    Noeud* fd;   // fils droit

    Noeud(char operateur, Noeud* gauche = nullptr, Noeud* droite = nullptr);
    Noeud(double valeur);
    Noeud(char variable, bool estVariable);

    void afficher() const;
    double evaluer(double x, double y, double z) const;
    Noeud* derivee(char var) const;
    Noeud* copie() const;
    Noeud* simplifier();
};

#endif
