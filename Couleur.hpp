#pragma once

#include <string>

using namespace std;

enum class Couleur
{
    Rouge,
    Bleu,
    Mauve,
    Blanc,
};

string couleurToString(Couleur couleur)
{
    switch (couleur)
    {
        case Couleur::Rouge: return "\033[91m";
        case Couleur::Bleu: return "\033[94m";
        case Couleur::Mauve: return "\033[95m";
        case Couleur::Blanc: return "\033[0m";
        default: return "\033[0m";
    }
}
