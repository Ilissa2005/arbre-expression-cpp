# Arbre d'Expressions en C++

## Description

Ce projet a été réalisé dans le cadre d’un **projet universitaire en C++**.

Il consiste à implémenter un système complet de **manipulation d'expressions arithmétiques** en utilisant des **arbres binaires**.

L’objectif est de modéliser une expression mathématique, de l’évaluer et de calculer sa **dérivée symbolique**.

---

## Fonctionnalités

* 🔹 Lecture d’une expression arithmétique (ex : `(X+Y)*Z`)
* 🔹 Construction d’un **arbre binaire d’expression**
* 🔹 Affichage de l’expression (forme infixée)
* 🔹 Évaluation avec des variables (`X`, `Y`, `Z`)
* 🔹 Dérivation symbolique
* 🔹 Gestion des opérateurs : `+`, `-`, `*`, `/`, `^`

---

## Compilation

```bash id="c1"
g++ main.cpp Arbre.cpp Noeud.cpp Pile.cpp -o main
```

---

## Exécution

```bash id="c2"
./main
```

---

## Exemple d'utilisation

### Entrée

```id="c3"
(X+2)*3
```

### Valeurs

```id="c4"
X = 1
Y = 0
Z = 0
```

### Résultat

```id="c5"
9
```

### Dérivée

```id="c6"
(((1+0)*3)+((X+2)*0))
```

---

## Limites

* La dérivation symbolique est correcte mais **non simplifiée automatiquement**
* Certaines expressions peuvent produire des formes développées

---

## Concepts abordés

* Arbres binaires
* Structures de données (pile implémentée manuellement)
* Parsing d’expressions
* Dérivation symbolique
* Programmation orientée objet en C++

---

## Structure du projet

```id="c7"
main.cpp
Arbre.cpp / Arbre.hpp
Noeud.cpp / Noeud.hpp
Pile.cpp / Pile.hpp
Makefile
```

---

## Contexte

Projet réalisé dans le cadre d’un **enseignement universitaire en informatique (C++)**.
Il répond à un cahier des charges incluant la manipulation d’expressions, leur évaluation et leur dérivation.

---

## Améliorations possibles

* Simplification automatique des expressions
* Ajout de fonctions mathématiques (sin, cos, log...)
* Interface utilisateur plus avancée

---

## Auteur

**Ilissa**
Étudiant(e) en informatique

---
