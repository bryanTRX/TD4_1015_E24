// Programme contenant le projet du TD4.
// file		main.cpp
// author	Iliass Khider et Bryan Alexandre Tavares
// date		27 mai 2024
// Créé le	3 juin 2024

#include "lectureBinaire.hpp"
#include "VilainsHeros.hpp"
#include <fstream>
#include <sstream>
#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "bibliotheque_cours.hpp"

using namespace std;

ifstream ouvrirFichierBinaire(const string& nomFichier)
{
    ifstream fichier(nomFichier, ios::binary);
    fichier.exceptions(ios::failbit);
    return fichier;
}

void testsPourCouvertureLectureBinaire()
{
    istringstream iss("\xA0\x12\xA1\x21\x43\xA2\x98\xBA\xDC\xFE");
    assert(lireUintTailleVariable(iss) == 0x12);
    assert(lireUintTailleVariable(iss) == 0x4321);
    assert(lireUintTailleVariable(iss) == 0xFEDCBA98);
}

int main()
{
#pragma region "Bibliothèque du cours"
    // Permet sous Windows les "ANSI escape code" pour changer de couleur
    // https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
    // les supportent normalement par défaut.
    bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

    testsPourCouvertureLectureBinaire();

    const string trait = "\n\033[0m═════════════════════════════════════════════════════════════════════════";

    // Ici on fait la lecture de notre fichier heros.bin et l'initialisation de notre vecteur Heros.
    vector<Heros> vecteurHeros;
    ifstream fichierHeros = ouvrirFichierBinaire("heros.bin");
    if (!fichierHeros)
    {
        cerr << "Erreur lors de l'ouverture du fichier heros.bin" << endl;
        return 1;
    }

    // Dans cette section on fait simplement remplir notre vecteur des heros qu'on a lu dans le fichier heros.bin.
    size_t nombreHeros = lireUintTailleVariable(fichierHeros);
    for (size_t i = 0; i < nombreHeros; ++i)
    {
        string nom    = lireString(fichierHeros);
        string jeu    = lireString(fichierHeros);
        string ennemi = lireString(fichierHeros);
        Heros heros(nom, jeu, ennemi);

        // Dans cette section on fait simplement la lecture du nombre d'alliés qu'un héros possède.
        size_t nombreAllies = lireUintTailleVariable(fichierHeros);
        for (size_t j = 0; j < nombreAllies; ++j)
        {
            heros.ajouterAllier(lireString(fichierHeros));
        }

        vecteurHeros.push_back(heros);
    }

    // Ici on fait la lecture de notre fichier vilains.bin et l'initialisation de notre vecteur Vilain.
    vector<Vilain> vecteurVilain;
    ifstream fichierVilain = ouvrirFichierBinaire("vilains.bin");
    if (!fichierVilain)
    {
        cerr << "Erreur lors de l'ouverture du fichier Vilain.bin" << endl;
        return 1;
    }

    // Dans cette section on fait simplement remplir notre vecteur des vilains qu'on a lu dans le fichier vilains.bin.
    size_t nombreVilain = lireUintTailleVariable(fichierVilain);
    for (size_t i = 0; i < nombreVilain; ++i)
    {
        string nom      = lireString(fichierVilain);
        string jeu      = lireString(fichierVilain);
        string objectif = lireString(fichierVilain);
        Vilain vilain(nom, jeu, objectif);

        vecteurVilain.push_back(vilain);
    }

    // ---------------------------------------------------------------- Héros ----------------------------------------------------------------

    const string traitHeros = "\n\033[33m══════════════════════════════════ Affichage des Héros ═══════════════════════════════════════ ";
    cout << traitHeros << endl;

    // Affichage des héros avec la couleur bleue.
    for (const auto& heros : vecteurHeros)
    {
        heros.afficher(cout, Couleur::Bleu);
        cout << trait << endl;
    }

    // ---------------------------------------------------------------- Vilain ----------------------------------------------------------------

    const string traitVilain = "\n\033[33m══════════════════════════════════ Affichage des Vilains ═══════════════════════════════════════ ";
    cout << traitVilain << endl;

    // Affichage des vilains avec la couleur rouge.
    for (const auto& vilain : vecteurVilain)
    {
        vilain.afficher(cout, Couleur::Rouge);
        cout << trait << endl;
    }

    // ---------------------------------------------------------------- Personnages ----------------------------------------------------------------

    const string traitPersonnage = "\n\033[33m══════════════════════════════ Affichage des Personnages ═══════════════════════════════════ ";
    cout << traitPersonnage << endl;

    // Fusion des héros et vilains dans un vecteur de personnages.
    vector<shared_ptr<Personnage>> vecteurPersonnages;

    for (const auto& heros : vecteurHeros)
    {
        vecteurPersonnages.push_back(make_shared<Heros>(heros));
    }

    for (const auto& vilain : vecteurVilain)
    {
        vecteurPersonnages.push_back(make_shared<Vilain>(vilain));
    }

    // Affichage des personnages avec les couleurs correspondantes.
    for (const auto& personnage : vecteurPersonnages)
    {
        if (dynamic_cast<Heros*>(personnage.get()))
        {
            personnage->changerCouleur(Couleur::Bleu);
        }
        
        else if (dynamic_cast<Vilain*>(personnage.get()))
        {
            personnage->changerCouleur(Couleur::Rouge);
        }
        personnage->afficher(cout, personnage->getCouleur());
        cout << trait << endl;
    }

    // ---------------------------------------------------------------- Vilain/Heros ----------------------------------------------------------------

    const string traitVilainHero = "\n\033[33m══════════════════════════════ Affichage du Vilain/Hero ══════════════════════════════════ ";
    cout << traitVilainHero << endl;

    // Création et affichage d'un personnage hybride Vilain/Héros si les vecteurs ne sont pas vides.
    if (!vecteurVilain.empty() && !vecteurHeros.empty())
    {
        Vilain vilain = vecteurVilain[2];
        Heros heros = vecteurHeros[0];

        VilainHeros vilainHeros(vilain, heros);
        vilainHeros.afficher(cout, Couleur::Mauve);
        vecteurPersonnages.push_back(make_shared<VilainHeros>(vilainHeros));
    }
    cout << trait << endl;

    // ---------------------------------------------------------------- Affichage du vecteur personnage à la fin ----------------------------------------------------------------

    const string traitFinal = "\n\033[33m══════════════════════════════ Affichage du vecteur Personnage après l'ajout du Vilain/Hero ═══════════════════════════════════ ";
    cout << traitFinal << endl;

    // Affichage final des personnages après l'ajout du Vilain/Héros avec les couleurs correspondantes.
    for (const auto& personnage : vecteurPersonnages)
    {
        if (dynamic_cast<VilainHeros*>(personnage.get()))
        {
            personnage->changerCouleur(Couleur::Mauve);
        }
        
        else if (dynamic_cast<Heros*>(personnage.get()))
        {
            personnage->changerCouleur(Couleur::Bleu);
        }

        else if (dynamic_cast<Vilain*>(personnage.get()))
        {
            personnage->changerCouleur(Couleur::Rouge);
        }
        personnage->afficher(cout, personnage->getCouleur());
        cout << trait << endl;
    }

    cout << couleurToString(Couleur::Blanc) << endl;

    return 0;
}