#ifndef ARBRE_HPP
#define ARBRE_HPP

#include "Noeud.hpp"
#include <string>

class Arbre {
private:
    Noeud* racine;

    void detruire(Noeud* n);
    Noeud* parseExpression(const std::string& expr, int& i);
    Noeud* parseTerm(const std::string& expr, int& i);
    Noeud* parseFactor(const std::string& expr, int& i);
    Noeud* parsePrimary(const std::string& expr, int& i);
    void sauterEspaces(const std::string& expr, int& i);

public:
    Arbre(Noeud* racine);
    Arbre(const std::string& expression);
    ~Arbre();

    void afficher() const;
    double evaluer(double x, double y, double z) const;
    Arbre* derivee(char var) const;
};

#endif
