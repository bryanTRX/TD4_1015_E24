#include "lectureBinaire.hpp"
#include "Affichable.hpp"
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
    vector<Heros> vecteurHeros;
    vector<Vilain> vecteurVilain;
    vector<shared_ptr<Personnage>> vecteurPersonnages;

    // Lecture des fichiers binaires
    ifstream fichierHeros = ouvrirFichierBinaire("heros.bin");
    if (!fichierHeros) {
        cerr << "Erreur lors de l'ouverture du fichier heros.bin" << endl;
        return 1;
    }

    ifstream fichierVilain = ouvrirFichierBinaire("vilains.bin");
    if (!fichierVilain) {
        cerr << "Erreur lors de l'ouverture du fichier Vilain.bin" << endl;
        return 1;
    }

    // Lecture des héros
    size_t nombreHeros = lireUintTailleVariable(fichierHeros);
    for (size_t i = 0; i < nombreHeros; ++i) {
        string nom = lireString(fichierHeros);
        string jeu = lireString(fichierHeros);
        string ennemi = lireString(fichierHeros);
        Heros heros(nom, jeu, ennemi);

        size_t nombreAllies = lireUintTailleVariable(fichierHeros);
        for (size_t j = 0; j < nombreAllies; ++j) {
            heros.ajouterAllier(lireString(fichierHeros));
        }

        vecteurHeros.push_back(heros);
    }

    // Lecture des Vilain
    size_t nombreVilain = lireUintTailleVariable(fichierVilain);
    for (size_t i = 0; i < nombreVilain; ++i) 
    {
        string nom = lireString(fichierVilain);
        string jeu = lireString(fichierVilain);
        string objectif = lireString(fichierVilain);
        Vilain vilain(nom, jeu, objectif);

        vecteurVilain.push_back(vilain);
    }

    // ---------------------------------------------------------------- Héros ----------------------------------------------------------------

    const string traitHeros= "\n\033[93m══════════════════════════════════ Affichage des Héros ═══════════════════════════════════════ ";
    cout << traitHeros << endl;

    cout << "\033[94m";  
    for (const auto& heros : vecteurHeros) 
    {
        heros.afficher(cout);
        cout << trait << "\033[94m" << endl;
    }

    // ---------------------------------------------------------------- Vilain ----------------------------------------------------------------

    const string traitVilain = "\n\033[93m══════════════════════════════════ Affichage des Vilains ═══════════════════════════════════════ ";
    cout << traitVilain << endl; 

    const string traitRouge = "\n\033[91m═════════════════════════════════════════════════════════════════════════ ";

    cout << "\033[91m";  
    for (const auto& vilain : vecteurVilain) {
        vilain.afficher(cout);
        cout << trait << "\033[91m" << endl;
    }

    //// Remplir le vecteur de personnages
    //for (const auto& heros : vecteurHeros) {
    //    vecteurPersonnages.push_back(make_shared<Heros>(heros));
    //}
    //for (const auto& vilain : vecteurVilain) {
    //    vecteurPersonnages.push_back(make_shared<Vilain>(vilain));
    //}

    //// Affichage des personnages
    //for (const auto& personnage : vecteurPersonnages) {
    //    if (dynamic_cast<Heros*>(personnage.get())) {
    //        cout << "\033[94m";  // Bleu
    //    }
    //    else if (dynamic_cast<Vilain*>(personnage.get())) {
    //        cout << "\033[91m";  // Rouge
    //    }
    //    personnage->afficher(cout);
    //    cout << "-----------------------" << endl;
    //}

    //// Création d'un VilainHeros
    //if (!vecteurVilain.empty() && !vecteurHeros.empty()) {
    //    Vilain vilain = vecteurVilain[0];
    //    Heros heros = vecteurHeros[0];
    //    if (vilain.getNom() != heros.getEnnemi()) {
    //        VilainHeros vilainHeros(vilain, heros, "Détruire tout ce qui existe dans le monde de " + heros.getJeu());
    //        cout << "\033[95m";  // Mauve
    //        vilainHeros.afficher(cout);
    //        vecteurPersonnages.push_back(make_shared<VilainHeros>(vilainHeros));
    //    }
    //}

    //// Affichage des personnages après ajout de VilainHeros
    //for (const auto& personnage : vecteurPersonnages) {
    //    if (dynamic_cast<Heros*>(personnage.get())) {
    //        cout << "\033[94m";  // Bleu
    //    }
    //    else if (dynamic_cast<Vilain*>(personnage.get())) {
    //        cout << "\033[91m";  // Rouge
    //    }
    //    else if (dynamic_cast<VilainHeros*>(personnage.get())) {
    //        cout << "\033[95m";  // Mauve
    //    }
    //    personnage->afficher(cout);
    //    cout << "-----------------------" << endl;
    //}

    // Réinitialiser la couleur
    cout << "\033[0m";

    return 0;
}