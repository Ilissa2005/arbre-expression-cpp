#include "Noeud.hpp"
#include <cmath>

using namespace std;

Noeud::Noeud(char operateur, Noeud* gauche, Noeud* droite) {
    type = 'o';
    ope = operateur;
    val = 0;
    fg = gauche;
    fd = droite;
}

Noeud::Noeud(double valeur) {
    type = 'f';
    val = valeur;
    ope = '\0';
    fg = nullptr;
    fd = nullptr;
}

Noeud::Noeud(char variable, bool estVariable) {
    (void)estVariable; // juste pour distinguer ce constructeur de celui des operateurs
    type = 'v';
    ope = variable;
    val = 0;
    fg = nullptr;
    fd = nullptr;
}

void Noeud::afficher() const {
    if (type == 'o') {
        cout << "(";
        if (fg != nullptr) fg->afficher();
        cout << ope;
        if (fd != nullptr) fd->afficher();
        cout << ")";
    } else if (type == 'f') {
        cout << val;
    } else {
        cout << ope;
    }
}

Noeud* Noeud::copie() const {
    if (type == 'f') return new Noeud(val);
    if (type == 'v') return new Noeud(ope, true);
    return new Noeud(ope,
                     fg != nullptr ? fg->copie() : nullptr,
                     fd != nullptr ? fd->copie() : nullptr);
}

double Noeud::evaluer(double x, double y, double z) const {
    if (type == 'f') return val;

    if (type == 'v') {
        if (ope == 'X') return x;
        if (ope == 'Y') return y;
        if (ope == 'Z') return z;
        return 0;
    }

    double a = (fg != nullptr) ? fg->evaluer(x, y, z) : 0;
    double b = (fd != nullptr) ? fd->evaluer(x, y, z) : 0;

    if (ope == '+') return a + b;
    if (ope == '-') return a - b;
    if (ope == '*') return a * b;
    if (ope == '/') return (b != 0) ? a / b : 0;
    if (ope == '^') return pow(a, b);

    return 0;
}

Noeud* Noeud::derivee(char var) const {
    // Cas d'une constante
    if (!estVariable && gauche == nullptr && droite == nullptr) {
        return new Noeud(0.0);
    }

    // Cas d'une variable
    if (estVariable) {
        if ((char)valeur == var)
            return new Noeud(1.0);
        else
            return new Noeud(0.0);
    }

    // Cas des opérateurs
    if (valeur == '+') {
        return new Noeud('+', gauche->derivee(var), droite->derivee(var));
    }

    if (valeur == '-') {
        return new Noeud('-', gauche->derivee(var), droite->derivee(var));
    }

    if (valeur == '*') {
        return new Noeud('+',
            new Noeud('*', gauche->derivee(var), droite),
            new Noeud('*', gauche, droite->derivee(var))
        );
    }

    if (valeur == '/') {
        return new Noeud('/',
            new Noeud('-',
                new Noeud('*', gauche->derivee(var), droite),
                new Noeud('*', gauche, droite->derivee(var))
            ),
            new Noeud('^', droite, new Noeud(2.0))
        );
    }

    if (valeur == '^') {
        // Cas u^n avec n constante
        if (droite != nullptr && !droite->estVariable &&
            droite->gauche == nullptr && droite->droite == nullptr) {

            double n = droite->valeur;

            return new Noeud('*',
                new Noeud('*',
                    new Noeud(n),
                    new Noeud('^', gauche, new Noeud(n - 1))
                ),
                gauche->derivee(var)
            );
        }
    }

    return new Noeud(0.0);
}

Noeud* Noeud::simplifier() {
    // feuille
    if (gauche == nullptr && droite == nullptr)
        return this;

    // simplifier les sous-arbres
    if (gauche) gauche = gauche->simplifier();
    if (droite) droite = droite->simplifier();

    if (!estVariable) {
        // x + 0 = x, 0 + x = x
        if (valeur == '+') {
            if (gauche && !gauche->estVariable &&
                gauche->gauche == nullptr && gauche->droite == nullptr &&
                gauche->valeur == 0.0)
                return droite;

            if (droite && !droite->estVariable &&
                droite->gauche == nullptr && droite->droite == nullptr &&
                droite->valeur == 0.0)
                return gauche;
        }

        // x - 0 = x
        if (valeur == '-') {
            if (droite && !droite->estVariable &&
                droite->gauche == nullptr && droite->droite == nullptr &&
                droite->valeur == 0.0)
                return gauche;
        }

        // x * 0 = 0, 0 * x = 0, x * 1 = x, 1 * x = x
        if (valeur == '*') {
            if (gauche && !gauche->estVariable &&
                gauche->gauche == nullptr && gauche->droite == nullptr &&
                gauche->valeur == 0.0)
                return new Noeud(0.0);

            if (droite && !droite->estVariable &&
                droite->gauche == nullptr && droite->droite == nullptr &&
                droite->valeur == 0.0)
                return new Noeud(0.0);

            if (gauche && !gauche->estVariable &&
                gauche->gauche == nullptr && gauche->droite == nullptr &&
                gauche->valeur == 1.0)
                return droite;

            if (droite && !droite->estVariable &&
                droite->gauche == nullptr && droite->droite == nullptr &&
                droite->valeur == 1.0)
                return gauche;
        }
    }

    return this;
}