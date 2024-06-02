#pragma once

#include <iostream>
#include "Couleur.hpp"

class Affichable 
{
public:
    virtual void afficher(ostream& os, Couleur couleur) const = 0;
    virtual void changerCouleur(Couleur couleur) = 0;
    virtual ~Affichable() = default;
};