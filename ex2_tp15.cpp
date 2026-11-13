
#include <iostream>
#include <stdexcept>
using namespace std;

class File {
private:
    int* tableau;
    int capacite;
    int debut;
    int fin;
    int nombre;

public:
    
    File(int cap = 5) {
        if (cap <= 0) {
            throw invalid_argument("Capacite invalide !");
        }

        capacite = cap;
        tableau = new int[capacite];
        debut = 0;
        fin = -1;
        nombre = 0;
    }

    
    bool estVide() const {
        return nombre == 0;
    }


    bool estPleine() const {
        return nombre == capacite;
    }

    
    void enfiler(int valeur) {
        if (estPleine()) {
            cout << "Erreur : la file est pleine !" << endl;
            return;
        }

        fin = (fin + 1) % capacite;
        tableau[fin] = valeur;
        nombre++;

        cout << valeur << " ajoute a la file." << endl;
    }

    
    int defiler() {
        if (estVide()) {
            throw underflow_error("Impossible : la file est vide !");
        }

        int valeur = tableau[debut];
        debut = (debut + 1) % capacite;
        nombre--;

        return valeur;
    }

    
    void afficher() const {
        if (estVide()) {
            cout << "La file est vide." << endl;
            return;
        }

        cout << "File : ";

        for (int i = 0; i < nombre; i++) {
            cout << tableau[(debut + i) % capacite] << " ";
        }

        cout << endl;
    }

    
    ~File() {
        delete[] tableau;
    }
};


int main() {
    int capacite;
    int choix;
    int valeur;

    cout << "Donner la capacite de la file : ";
    cin >> capacite;

    try {
        File file(capacite);

        do {
            cout << "\n===== MENU FILE FIFO =====" << endl;
            cout << "1. Enfiler un element" << endl;
            cout << "2. Defiler un element" << endl;
            cout << "3. Afficher la file" << endl;
            cout << "4. Verifier si la file est vide" << endl;
            cout << "5. Verifier si la file est pleine" << endl;
            cout << "0. Quitter" << endl;

            cout << "Votre choix : ";
            cin >> choix;

            try {
                switch (choix) {

                    case 1:
                        cout << "Donner une valeur : ";
                        cin >> valeur;
                        file.enfiler(valeur);
                        break;

                    case 2:
                        cout << "Element retire : "
                             << file.defiler() << endl;
                        break;

                    case 3:
                        file.afficher();
                        break;

                    case 4:
                        if (file.estVide())
                            cout << "La file est vide." << endl;
                        else
                            cout << "La file n'est pas vide." << endl;
                        break;

                    case 5:
                        if (file.estPleine())
                            cout << "La file est pleine." << endl;
                        else
                            cout << "La file n'est pas pleine." << endl;
                        break;

                    case 0:
                        cout << "Fin du programme." << endl;
                        break;

                    default:
                        cout << "Choix invalide !" << endl;
                }
            }
            catch (const underflow_error& e) {
                cout << "Exception : " << e.what() << endl;
            }

        } while (choix != 0);

    }
    catch (const exception& e) {
        cout << "Erreur : " << e.what() << endl;
    }

    return 0;
}
