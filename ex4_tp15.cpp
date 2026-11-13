
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

template <typename T>
class Pile {
private:

    // Structure d'un noeud
    struct Noeud {
        T element;
        Noeud* suivant;

        Noeud(T valeur) {
            element = valeur;
            suivant = nullptr;
        }
    };

    Noeud* sommetPile;

public:

    // Constructeur
    Pile() {
        sommetPile = nullptr;
    }

    // Verifier si la pile est vide
    bool estVide() const {
        return sommetPile == nullptr;
    }

    // Empiler un element
    void empiler(T element) {
        Noeud* nouveau = new Noeud(element);

        nouveau->suivant = sommetPile;
        sommetPile = nouveau;
    }

    // Depiler un element
    T depiler() {
        if (estVide()) {
            throw underflow_error("La pile est vide !");
        }

        Noeud* temp = sommetPile;
        T valeur = temp->element;

        sommetPile = sommetPile->suivant;

        delete temp;

        return valeur;
    }

    // Retourner le sommet sans supprimer
    T sommet() const {
        if (estVide()) {
            throw underflow_error("La pile est vide !");
        }

        return sommetPile->element;
    }

    // Inverser la pile
    void inverser() {
        Noeud* precedent = nullptr;
        Noeud* courant = sommetPile;
        Noeud* suivant = nullptr;

        while (courant != nullptr) {
            suivant = courant->suivant;
            courant->suivant = precedent;
            precedent = courant;
            courant = suivant;
        }

        sommetPile = precedent;
    }

    // Afficher la pile
    void afficher() const {
        Noeud* courant = sommetPile;

        cout << "Sommet -> ";

        while (courant != nullptr) {
            cout << courant->element << " -> ";
            courant = courant->suivant;
        }

        cout << "nullptr" << endl;
    }

    // Destructeur
    ~Pile() {
        while (!estVide()) {
            Noeud* temp = sommetPile;
            sommetPile = sommetPile->suivant;
            delete temp;
        }
    }
};

// Programme principal
int main() {

    // Test avec int
    cout << "===== PILE INT =====" << endl;

    Pile<int> p1;

    p1.empiler(10);
    p1.empiler(20);
    p1.empiler(30);

    p1.afficher();

    cout << "Sommet : " << p1.sommet() << endl;
    cout << "Element depile : " << p1.depiler() << endl;

    p1.afficher();

    p1.inverser();

    cout << "Apres inversion : ";
    p1.afficher();


    // Test avec string
    cout << "\n===== PILE STRING =====" << endl;

    Pile<string> p2;

    p2.empiler("Java");
    p2.empiler("C++");
    p2.empiler("Python");

    p2.afficher();

    cout << "Sommet : " << p2.sommet() << endl;

    p2.inverser();

    cout << "Apres inversion : ";
    p2.afficher();


    // Test avec double
    cout << "\n===== PILE DOUBLE =====" << endl;

    Pile<double> p3;

    p3.empiler(10.5);
    p3.empiler(20.5);
    p3.empiler(30.5);

    p3.afficher();

    cout << "Element depile : " << p3.depiler() << endl;

    p3.afficher();


    // Test de l'exception
    cout << "\n===== TEST EXCEPTION =====" << endl;

    Pile<int> p4;

    try {
        p4.depiler();
    }
    catch (const underflow_error& e) {
        cout << "Exception : " << e.what() << endl;
    }

    return 0;
}
