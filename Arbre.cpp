#include "Arbre.hpp"
#include <cctype>
#include <cstdlib>
#include <iostream>

using namespace std;

Arbre::Arbre(Noeud* r) {
    racine = r;
}

Arbre::Arbre(const string& expression) {
    int i = 0;
    racine = parseExpression(expression, i);
}

Arbre::~Arbre() {
    detruire(racine);
}

void Arbre::detruire(Noeud* n) {
    if (n == nullptr) return;
    detruire(n->fg);
    detruire(n->fd);
    delete n;
}

void Arbre::sauterEspaces(const string& expr, int& i) {
    while (i < (int)expr.size() && isspace((unsigned char)expr[i])) {
        i++;
    }
}

Noeud* Arbre::parsePrimary(const string& expr, int& i) {
    sauterEspaces(expr, i);

    if (i >= (int)expr.size()) return new Noeud(0.0);

    if (expr[i] == '(') {
        i++;
        Noeud* n = parseExpression(expr, i);
        sauterEspaces(expr, i);
        if (i < (int)expr.size() && expr[i] == ')') i++;
        return n;
    }

    if (expr[i] == 'X' || expr[i] == 'Y' || expr[i] == 'Z') {
        char v = expr[i++];
        return new Noeud(v, true);
    }

    if (expr[i] == '-') {
        // gère le signe moins unaire : -A devient (0-A)
        i++;
        Noeud* droite = parsePrimary(expr, i);
        return new Noeud('-', new Noeud(0.0), droite);
    }

    if (isdigit((unsigned char)expr[i]) || expr[i] == '.') {
        int debut = i;
        while (i < (int)expr.size() && (isdigit((unsigned char)expr[i]) || expr[i] == '.')) {
            i++;
        }
        double valeur = atof(expr.substr(debut, i - debut).c_str());
        return new Noeud(valeur);
    }

    // caractère non reconnu
    i++;
    return new Noeud(0.0);
}

Noeud* Arbre::parseFactor(const string& expr, int& i) {
    Noeud* gauche = parsePrimary(expr, i);
    sauterEspaces(expr, i);

    while (i < (int)expr.size() && expr[i] == '^') {
        char op = expr[i++];
        Noeud* droite = parsePrimary(expr, i);
        gauche = new Noeud(op, gauche, droite);
        sauterEspaces(expr, i);
    }
    return gauche;
}

Noeud* Arbre::parseTerm(const string& expr, int& i) {
    Noeud* gauche = parseFactor(expr, i);
    sauterEspaces(expr, i);

    while (i < (int)expr.size() && (expr[i] == '*' || expr[i] == '/')) {
        char op = expr[i++];
        Noeud* droite = parseFactor(expr, i);
        gauche = new Noeud(op, gauche, droite);
        sauterEspaces(expr, i);
    }
    return gauche;
}

Noeud* Arbre::parseExpression(const string& expr, int& i) {
    Noeud* gauche = parseTerm(expr, i);
    sauterEspaces(expr, i);

    while (i < (int)expr.size() && (expr[i] == '+' || expr[i] == '-')) {
        char op = expr[i++];
        Noeud* droite = parseTerm(expr, i);
        gauche = new Noeud(op, gauche, droite);
        sauterEspaces(expr, i);
    }
    return gauche;
}

void Arbre::afficher() const {
    if (racine != nullptr) racine->afficher();
}

double Arbre::evaluer(double x, double y, double z) const {
    if (racine == nullptr) return 0;
    return racine->evaluer(x, y, z);
}

Arbre* Arbre::derivee(char var) const {
    Noeud* d = racine->derivee(var);
    d = d->simplifier();
    return new Arbre(d);
}
