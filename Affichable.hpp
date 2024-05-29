#pragma once

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Affichable 
{
public:
    virtual ~Affichable() = default;
    virtual void afficher(ostream& os) const = 0;
    virtual void changerCouleur(const string& couleur) = 0;
};

class Personnage : public virtual Affichable
{
public:
    Personnage(const string& nom, const string& jeu) : nom_(nom), jeu_(jeu) {}
    virtual ~Personnage() = default;

    const string& getNom() const { return nom_; }
    const string& getJeu() const { return jeu_; }

    void afficher(ostream& os) const override
    {
        os << "Nom : " << nom_ << "\nParution : " << jeu_ << endl;
    }

    void changerCouleur(const string& couleur) override
    {
        couleur_ = couleur;
        cout << couleur_;
    }

private:
    string nom_;
    string jeu_;
    string couleur_ = "\033[0m";
};

class Heros : public virtual Personnage
{
public: 
    Heros(const string& nom, const string& jeu, const string& ennemi) : Personnage(nom, jeu), ennemi_(ennemi) {}

    void ajouterAllier(const string& allie)
    {
        allies_.push_back(allie);
    }

    const string& getEnnemi() const { return ennemi_; }
    const vector<string>& getAllies() const { return allies_; }

    void afficher(ostream& os) const override
    {
        Personnage::afficher(os);
        os << "Ennemi : " << ennemi_ << "\nAlliés : " << endl;
        for (const auto& i : allies_)
        {
            os << "\t" << i << endl;
        }
    }

private: 
    string ennemi_; 
    vector<string> allies_;
};

class Vilain : public virtual Personnage
{
public:
    Vilain(const string& nom, const string& jeu, const string& objectif) : Personnage(nom, jeu), objectif_(objectif) {}

    const string& getObjectif() const { return objectif_; }
    
    void afficher(ostream& os) const override
    {
        Personnage::afficher(os);
        os << "Objectif : " << objectif_ << endl;
    }

    //friend istream& operator>>(istream& is, Vilain& vilain)
    //{
    //    string nom, jeu, objectif;
    //    is >> nom >> jeu >> objectif;
    //    vilain = Vilain(nom, jeu, objectif);
    //    return is;
    //}

private: 
    string objectif_;
};

class VilainHeros : public Vilain, public Heros
{
public:
    VilainHeros(const Vilain& vilain, const Heros& heros, const string& mission) : Personnage(vilain.getNom() + "-" + heros.getNom(),vilain.getJeu() + "-" + heros.getJeu()), Heros(heros), Vilain(vilain), mission_(mission) {}

    const string& getMission() const { return mission_; }

    void afficher(ostream& os) const override 
    {
        Personnage::afficher(os);
        os << "Objectif : " << Vilain::getObjectif() << endl;
        os << "Ennemi : " << Heros::getEnnemi() << "\nAlliés :" << endl;
        for (const auto& allie : Heros::getAllies()) 
        {
            os << " " << allie << endl;
        }
        os << "Mission spéciale : " << mission_ << endl;
    }

private:
    string mission_;
};