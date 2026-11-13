
#include <iostream>
#include <string>
using namespace std;

class TableHachage {
private:

    
    struct Noeud {
        int cle;
        string valeur;
        Noeud* suivant;

        Noeud(int c, string v) {
            cle = c;
            valeur = v;
            suivant = nullptr;
        }
    };

    Noeud** table;
    int tailleTable;
    int nombreElements;

    
    int hachage(int cle) const {
        return ((cle % tailleTable) + tailleTable) % tailleTable;
    }

    
    void redimensionner() {
        int ancienneTaille = tailleTable;
        Noeud** ancienneTable = table;

        tailleTable *= 2;
        table = new Noeud*[tailleTable];

        for (int i = 0; i < tailleTable; i++) {
            table[i] = nullptr;
        }

        for (int i = 0; i < ancienneTaille; i++) {
            Noeud* courant = ancienneTable[i];

            while (courant != nullptr) {
                Noeud* suivant = courant->suivant;

                int indice = hachage(courant->cle);

                courant->suivant = table[indice];
                table[indice] = courant;

                courant = suivant;
            }
        }

        delete[] ancienneTable;
    }

public:

    
    TableHachage(int taille = 5) {
        if (taille <= 0) {
            taille = 5;
        }

        tailleTable = taille;
        nombreElements = 0;

        table = new Noeud*[tailleTable];

        for (int i = 0; i < tailleTable; i++) {
            table[i] = nullptr;
        }
    }


    void inserer(int cle, string valeur) {
        int indice = hachage(cle);

        Noeud* courant = table[indice];

        
        while (courant != nullptr) {
            if (courant->cle == cle) {
                courant->valeur = valeur;
                cout << "Valeur mise a jour." << endl;
                return;
            }

            courant = courant->suivant;
        }

        
        Noeud* nouveau = new Noeud(cle, valeur);

        nouveau->suivant = table[indice];
        table[indice] = nouveau;

        nombreElements++;

        cout << "Element insere avec succes." << endl;

        
        if (nombreElements > tailleTable * 0.75) {
            redimensionner();
        }
    }

    
    string rechercher(int cle) const {
        int indice = hachage(cle);

        Noeud* courant = table[indice];

        while (courant != nullptr) {
            if (courant->cle == cle) {
                return courant->valeur;
            }

            courant = courant->suivant;
        }

        return "Cle introuvable";
    }

    
    void supprimer(int cle) {
        int indice = hachage(cle);

        Noeud* courant = table[indice];
        Noeud* precedent = nullptr;

        while (courant != nullptr) {
            if (courant->cle == cle) {

                if (precedent == nullptr) {
                    table[indice] = courant->suivant;
                }
                else {
                    precedent->suivant = courant->suivant;
                }

                delete courant;
                nombreElements--;

                cout << "Element supprime avec succes." << endl;
                return;
            }

            precedent = courant;
            courant = courant->suivant;
        }

        cout << "Cle introuvable." << endl;
    }

    
    void afficher() const {
        cout << "\n===== TABLE DE HACHAGE =====" << endl;

        for (int i = 0; i < tailleTable; i++) {
            cout << "Case " << i << " : ";

            Noeud* courant = table[i];

            while (courant != nullptr) {
                cout << "[" << courant->cle
                     << " : " << courant->valeur << "] -> ";

                courant = courant->suivant;
            }

            cout << "nullptr" << endl;
        }
    }

    
    ~TableHachage() {
        for (int i = 0; i < tailleTable; i++) {
            Noeud* courant = table[i];

            while (courant != nullptr) {
                Noeud* temp = courant;
                courant = courant->suivant;
                delete temp;
            }
        }

        delete[] table;
    }
};


int main() {

    TableHachage table(5);

    
    table.inserer(10, "Ali");
    table.inserer(15, "Sara");
    table.inserer(20, "Imane");
    table.inserer(7, "Youssef");
    table.inserer(12, "Amine");

    
    table.afficher();

    
    cout << "\nRecherche de la cle 15 : "
         << table.rechercher(15) << endl;

    cout << "Recherche de la cle 30 : "
         << table.rechercher(30) << endl;

    
    cout << "\nSuppression de la cle 15 :" << endl;
    table.supprimer(15);

    
    table.afficher();

    return 0;
}
