//#include "Affichable.hpp"
//
//
//class Personnage : public virtual Affichable
//{
//public:
//    Personnage(const string& nom, const string& jeu);
//    virtual ~Personnage() = default;
//
//    const string& getNom() const;
//    const string& getJeu() const;
//
//    void afficher(ostream& os) const override;
//
//    void changerCouleur(const string& couleur) override;
//
//private:
//    string nom_;
//    string jeu_;
//    string couleur_ = "\033[0m";
//};