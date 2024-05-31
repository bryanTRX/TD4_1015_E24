#pragma once

#include "Vilains.hpp"
#include "Heros.hpp"

class VilainHeros : public Vilain, public Heros
{
public:
    VilainHeros(const Vilain& vilain, const Heros& heros) : Personnage(vilain.getNom() + " - " + heros.getNom(), vilain.getJeu() + " - " + heros.getJeu()), Vilain(vilain), Heros(heros), mission_(vilain.getObjectif() + " dans le monde de " + heros.getJeu()) {}

    const string& getMission() const { return mission_; }

    void afficher(ostream& os, Couleur couleur) const override 
    {
        Personnage::afficher(os, couleur);
        os << couleurToString(couleur) << "Objectif : " << Vilain::getObjectif() << endl;
        os << "Ennemi : " << Heros::getEnnemi() << "\nAlli�s :" << endl;
        for (const auto& allie : Heros::getAllies()) 
        {
            os << "\t" << allie << endl;
        }
        os << "Mission sp�ciale : " << mission_ << "\033[0m" << endl;
    }

private:
    string mission_;
};