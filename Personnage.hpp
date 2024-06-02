#pragma once

#include "Affichable.hpp"

class Personnage : public virtual Affichable
{
public:
    // Constructeurs ------------------------------------------------------------------------------------------

    Personnage(const string& nom, const string& jeu) : nom_(nom), jeu_(jeu), couleur_(Couleur::Blanc) {}
    virtual ~Personnage() = default;

    // Méthodes -----------------------------------------------------------------------------------------------

    const string& getNom() const { return nom_; }
    const string& getJeu() const { return jeu_; }
    const Couleur getCouleur() const { return couleur_; }

    void afficher(ostream& os, Couleur couleur) const override
    {
        os << couleurToString(couleur) << "Nom : " << nom_ << "\nParution : " << jeu_ << "\033[0m" << endl;
    }

    void changerCouleur(Couleur couleur) override
    {
        couleur_ = couleur;
    }

private:
    string nom_;
    string jeu_;
    Couleur couleur_;
};