//#include "Heros.hpp"
//
//Heros::Heros(const string& nom, const string& jeu, const string& ennemi) : Personnage(nom, jeu), ennemi_(ennemi) {}
//
//void Heros::ajouterAllier(const string& allie)
//{
//	allies_.push_back(allie);
//}
//
//const string& Heros::getEnnemi() const { return ennemi_; }
//const vector<string>& Heros::getAllies() const { return allies_; }
//
//void Heros::afficher(ostream& os) const
//{
//	Personnage::afficher(os);
//    os << "Ennemi : " << ennemi_ << "\nAlliés : " << endl;
//    for (const auto& i : allies_)
//    {
//        os << "\t" << i << endl;
//    }
//}