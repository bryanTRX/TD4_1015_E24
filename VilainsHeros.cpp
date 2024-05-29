//#include "VilainsHeros.hpp"
//
//VilainHeros::VilainHeros(const Vilains& vilain, const Heros& heros, const string& mission) : Personnage(vilain.getNom() + "-" + heros.getNom(), vilain.getJeu() + "-" + heros.getJeu()), Heros(heros), Vilains(vilain), mission_(mission) {}
//
//const string& VilainHeros::getMission() const { return mission_; }
//
//void VilainHeros::afficher(ostream& os) const
//{
//    Personnage::afficher(os);
//    os << "Objectif : " << Vilains::getObjectif() << endl;
//    os << "Ennemi : " << Heros::getEnnemi() << "\nAlliés :" << endl;
//    for (const auto& allie : Heros::getAllies())
//    {
//        os << " " << allie << endl;
//    }
//    os << "Mission spéciale : " << mission_ << endl;
//}