#include <iostream>
#include <string>
#include "Arbre.hpp"

using namespace std;

int main() {
    string expression;
    cout << "Entrez une expression arithmetique (ex: (X+Y)*Z ou X^2+3*Y): ";
    getline(cin, expression);

    Arbre arbre(expression);

    cout << "\nExpression lue : ";
    arbre.afficher();
    cout << endl;

    double x, y, z;
    cout << "Entrez la valeur de X : ";
    cin >> x;
    cout << "Entrez la valeur de Y : ";
    cin >> y;
    cout << "Entrez la valeur de Z : ";
    cin >> z;

    cout << "\nResultat = " << arbre.evaluer(x, y, z) << endl;

    char var;
    cout << "Deriver par rapport a quelle variable ? (X, Y, Z) : ";
    cin >> var;

    Arbre* d = arbre.derivee(var);
    cout << "Derivee : ";
    d->afficher();
    cout << endl;

    // Pense a liberer la memoire de l'arbre derive
    delete d;

    return 0;
}
