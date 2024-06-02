#pragma once

#include "Personnage.hpp"
#include <vector>

class Heros : public virtual Personnage
{
public:
    // Constructeurs -----------------------------------------------------------------------------------------------

    Heros(const string& nom, const string& jeu, const string& ennemi) : Personnage(nom, jeu), ennemi_(ennemi) {}

    // Méthodes ----------------------------------------------------------------------------------------------------

    const string& getEnnemi() const { return ennemi_; }
    const vector<string>& getAllies() const { return allies_; }
    size_t getNombreAllies() const { return allies_.size(); }

    void afficher(ostream& os, Couleur couleur) const override
    {
        Personnage::afficher(os, couleur);
        os << couleurToString(couleur) << "Ennemi : " << ennemi_ << "\nNombre d'alliés : " << getNombreAllies() << "\nAlliés :" << endl;
        for (const auto& allie : allies_) 
        {
            os << "\t" << allie << endl;
        }
        os << "\033[0m";
    }

    void ajouterAllier(const string& allie)
    {
        allies_.push_back(allie);
    }

private:
    string ennemi_;
    vector<string> allies_;
};