
#include <iostream>
using namespace std;


class Noeud {
public:
    int valeur;
    Noeud* suivant;

    Noeud(int v) {
        valeur = v;
        suivant = nullptr;
    }
};


class ListeChainee {
private:
    Noeud* tete;

public:
    // Constructeur
    ListeChainee() {
        tete = nullptr;
    }


    void ajouterDebut(int valeur) {
        Noeud* nouveau = new Noeud(valeur);
        nouveau->suivant = tete;
        tete = nouveau;
    }


    void ajouterFin(int valeur) {
        Noeud* nouveau = new Noeud(valeur);

        if (tete == nullptr) {
            tete = nouveau;
            return;
        }

        Noeud* courant = tete;

        while (courant->suivant != nullptr) {
            courant = courant->suivant;
        }

        courant->suivant = nouveau;
    }


    void supprimer(int valeur) {
        if (tete == nullptr) return;

        if (tete->valeur == valeur) {
            Noeud* temp = tete;
            tete = tete->suivant;
            delete temp;
            return;
        }

        Noeud* courant = tete;

        while (courant->suivant != nullptr &&
               courant->suivant->valeur != valeur) {
            courant = courant->suivant;
        }

        if (courant->suivant != nullptr) {
            Noeud* temp = courant->suivant;
            courant->suivant = temp->suivant;
            delete temp;
        }
    }

    
    void afficher() const {
        Noeud* courant = tete;

        while (courant != nullptr) {
            cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }

        cout << "nullptr" << endl;
    }

    
    int taille() const {
        int compteur = 0;
        Noeud* courant = tete;

        while (courant != nullptr) {
            compteur++;
            courant = courant->suivant;
        }

        return compteur;
    }


    ~ListeChainee() {
        Noeud* courant = tete;

        while (courant != nullptr) {
            Noeud* temp = courant;
            courant = courant->suivant;
            delete temp;
        }
    }


    class Iterateur {
    private:
        Noeud* courant;

    public:
        Iterateur(Noeud* noeud) {
            courant = noeud;
        }

        int& operator*() {
            return courant->valeur;
        }

        Iterateur& operator++() {
            courant = courant->suivant;
            return *this;
        }

        bool operator!=(const Iterateur& autre) const {
            return courant != autre.courant;
        }
    };

    Iterateur begin() {
        return Iterateur(tete);
    }

    Iterateur end() {
        return Iterateur(nullptr);
    }
};


int main() {
    ListeChainee liste;

    liste.ajouterDebut(20);
    liste.ajouterDebut(10);
    liste.ajouterFin(30);
    liste.ajouterFin(40);

    cout << "Liste initiale : ";
    liste.afficher();

    cout << "Taille : " << liste.taille() << endl;

    liste.supprimer(20);

    cout << "Apres suppression de 20 : ";
    liste.afficher();

    cout << "Parcours avec Iterateur : ";

    for (ListeChainee::Iterateur it = liste.begin();
         it != liste.end(); ++it) {
        cout << *it << " ";
    }

    cout << endl;

    return 0;
}
