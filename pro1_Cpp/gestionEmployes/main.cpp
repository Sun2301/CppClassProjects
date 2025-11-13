#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;


class Employe {
    // Attributs privés
    int matricule;
    string nom;
    string prenom;
    float salaire;

public:
    // Déclarations des constructeurs et méthodes
    Employe();                                    // constructeur par défaut
    Employe(int, string, string, float);         // constructeur avec paramètres
    void afficher();                             // méthode d'affichage

    // Méthodes d'accès (getters) car les attributs sont privés
    int getMatricule();
    string getNom();
    string getPrenom();
    float getSalaire();

    // Méthodes de modification (setters)
    void setMatricule(int);
    void setNom(string);
    void setPrenom(string);
    void setSalaire(float);
};

// Définitions des méthodes
Employe::Employe() {
    matricule = 0;
    salaire = 0.0;
}

Employe::Employe(int mat, string n, string p, float sal) {
    matricule = mat;
    nom = n;
    prenom = p;
    salaire = sal;
}

void Employe::afficher() {
    cout << "  Matricule: " << matricule << "\n";
    cout << "  Nom: " << nom << "\n";
    cout << "  Prenom: " << prenom << "\n";
    cout << "  Salaire: " << salaire << " FCFA\n";
}

int Employe::getMatricule() {
    return matricule;
}

string Employe::getNom() {
    return nom;
}

string Employe::getPrenom() {
    return prenom;
}

float Employe::getSalaire() {
    return salaire;
}

void Employe::setMatricule(int mat) {
    matricule = mat;
}

void Employe::setNom(string n) {
    nom = n;
}

void Employe::setPrenom(string p) {
    prenom = p;
}

void Employe::setSalaire(float sal) {
    salaire = sal;
}

// ========================================
// Classe GestionEmployes
// ========================================
class GestionEmployes {
    vector<Employe> employes;

    // Méthodes privées
    void viderBuffer();
    bool matriculeExiste(int);

public:
    // Déclarations des méthodes publiques
    GestionEmployes();                    // constructeur
    void ajouterEmploye();
    void afficherTous();
    void rechercherParSeuil();
    void supprimerEmploye();
    void trierParSalaire();
    void sauvegarder();
    void charger();
    void afficherMenu();
    void executer();
};

// Définitions des méthodes EN DEHORS de la classe
GestionEmployes::GestionEmployes() {
    // Constructeur : on pourrait charger automatiquement le fichier ici
    // mais on le laisse vide pour l'instant
}

void GestionEmployes::viderBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}

bool GestionEmployes::matriculeExiste(int mat) {
    int i;
    for (i = 0; i < employes.size(); i++) {
        if (employes[i].getMatricule() == mat) {
            return true;
        }
    }
    return false;
}

void GestionEmployes::ajouterEmploye() {
    int matricule;
    string nom, prenom;
    float salaire;

    cout << "\n--- Nouvel employe ---\n";

    cout << "Matricule : ";
    cin >> matricule;

    if (matricule <= 0) {
        cout << "Matricule invalide\n";
        return;
    }

    if (matriculeExiste(matricule)) {
        cout << "Ce matricule existe deja !\n";
        return;
    }

    cout << "Nom : ";
    cin >> nom;

    cout << "Prenom : ";
    cin >> prenom;

    cout << "Salaire : ";
    cin >> salaire;

    if (salaire < 0) {
        cout << "Salaire invalide\n";
        return;
    }

    // Utilisation du constructeur avec paramètres !
    Employe nouveauEmploye(matricule, nom, prenom, salaire);
    employes.push_back(nouveauEmploye);

    cout << "Employe ajoute avec succes !\n";
}

void GestionEmployes::afficherTous() {
    int i;

    if (employes.size() == 0) {
        cout << "\nAucun employe enregistre\n";
        return;
    }

    cout << "\n--- Liste des employes ---\n";
    cout << "Total : " << employes.size() << "\n";

    for (i = 0; i < employes.size(); i++) {
        cout << "\nEmploye " << (i + 1) << ":\n";
        employes[i].afficher();
    }
}

void GestionEmployes::rechercherParSeuil() {
    float seuil;
    int i, compteur;

    if (employes.size() == 0) {
        cout << "\nAucun employe dans la liste\n";
        return;
    }

    cout << "\nSeuil de salaire : ";
    cin >> seuil;

    if (seuil < 0) {
        cout << "Seuil invalide\n";
        return;
    }

    cout << "\n--- Employes avec salaire > " << seuil << " ---\n";

    compteur = 0;
    for (i = 0; i < employes.size(); i++) {
        if (employes[i].getSalaire() > seuil) {
            cout << employes[i].getPrenom() << " " << employes[i].getNom();
            cout << " (Mat: " << employes[i].getMatricule() << ")";
            cout << " - " << employes[i].getSalaire() << " FCFA\n";
            compteur++;
        }
    }

    if (compteur == 0) {
        cout << "Aucun employe trouve\n";
    } else {
        cout << "\nNombre trouve : " << compteur << "\n";
    }
}

void GestionEmployes::supprimerEmploye() {
    int mat, i;

    if (employes.size() == 0) {
        cout << "\nListe vide\n";
        return;
    }

    cout << "\nMatricule a supprimer : ";
    cin >> mat;

    for (i = 0; i < employes.size(); i++) {
        if (employes[i].getMatricule() == mat) {
            employes.erase(employes.begin() + i);
            cout << "Employe supprime avec succes !\n";
            return;
        }
    }

    cout << "Matricule introuvable\n";
}

void GestionEmployes::trierParSalaire() {
    int i, j;
    Employe temp;

    if (employes.size() == 0) {
        cout << "\nAucun employe a trier\n";
        return;
    }

    // Tri à bulles
    for (i = 0; i < employes.size() - 1; i++) {
        for (j = 0; j < employes.size() - i - 1; j++) {
            if (employes[j].getSalaire() > employes[j + 1].getSalaire()) {
                temp = employes[j];
                employes[j] = employes[j + 1];
                employes[j + 1] = temp;
            }
        }
    }

    cout << "\nListe triee par ordre croissant de salaire\n";
}

void GestionEmployes::sauvegarder() {
    ofstream fichier("employes.xml");
    int i;

    if (!fichier) {
        cout << "\nImpossible d'ouvrir le fichier\n";
        return;
    }

    fichier << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    fichier << "<employes>\n";

    for (i = 0; i < employes.size(); i++) {
        fichier << "  <employe>\n";
        fichier << "    <matricule>" << employes[i].getMatricule() << "</matricule>\n";
        fichier << "    <nom>" << employes[i].getNom() << "</nom>\n";
        fichier << "    <prenom>" << employes[i].getPrenom() << "</prenom>\n";
        fichier << "    <salaire>" << employes[i].getSalaire() << "</salaire>\n";
        fichier << "  </employe>\n";
    }

    fichier << "</employes>\n";
    fichier.close();

    cout << "\nDonnees sauvegardees (" << employes.size() << " employes)\n";
}

void GestionEmployes::charger() {
    ifstream fichier("employes.xml");
    string ligne;
    Employe emp;
    bool dansEmploye;

    if (!fichier) {
        cout << "\nFichier introuvable\n";
        return;
    }

    employes.clear();
    dansEmploye = false;

    while (getline(fichier, ligne)) {
        if (ligne.find("<employe>") != string::npos) {
            dansEmploye = true;
            emp = Employe();
        }
        else if (ligne.find("</employe>") != string::npos) {
            employes.push_back(emp);
            dansEmploye = false;
        }
        else if (dansEmploye) {
            if (ligne.find("<matricule>") != string::npos) {
                int debut = ligne.find(">") + 1;
                int fin = ligne.find("</");
                string valeur = ligne.substr(debut, fin - debut);
                emp.setMatricule(stoi(valeur));
            }
            else if (ligne.find("<nom>") != string::npos) {
                int debut = ligne.find(">") + 1;
                int fin = ligne.find("</");
                emp.setNom(ligne.substr(debut, fin - debut));
            }
            else if (ligne.find("<prenom>") != string::npos) {
                int debut = ligne.find(">") + 1;
                int fin = ligne.find("</");
                emp.setPrenom(ligne.substr(debut, fin - debut));
            }
            else if (ligne.find("<salaire>") != string::npos) {
                int debut = ligne.find(">") + 1;
                int fin = ligne.find("</");
                string valeur = ligne.substr(debut, fin - debut);
                emp.setSalaire(stof(valeur));
            }
        }
    }

    fichier.close();
    cout << "\n" << employes.size() << " employes charges\n";
}

void GestionEmployes::afficherMenu() {
    cout << "\n================================\n";
    cout << "   GESTION DES EMPLOYES\n";
    cout << "================================\n";
    cout << "1. Ajouter un employe\n";
    cout << "2. Afficher tous les employes\n";
    cout << "3. Rechercher par seuil de salaire\n";
    cout << "4. Supprimer un employe\n";
    cout << "5. Trier par salaire\n";
    cout << "6. Sauvegarder dans fichier\n";
    cout << "7. Charger depuis fichier\n";
    cout << "8. Quitter\n";
    cout << "\nVotre choix : ";
}

void GestionEmployes::executer() {
    int choix;

    cout << "\n*** Programme de gestion des employes ***\n";

    while (true) {
        afficherMenu();
        cin >> choix;

        if (cin.fail()) {
            cout << "\nSaisie invalide !\n";
            viderBuffer();
            continue;
        }

        if (choix == 1) {
            ajouterEmploye();
        }
        else if (choix == 2) {
            afficherTous();
        }
        else if (choix == 3) {
            rechercherParSeuil();
        }
        else if (choix == 4) {
            supprimerEmploye();
        }
        else if (choix == 5) {
            trierParSalaire();
        }
        else if (choix == 6) {
            sauvegarder();
        }
        else if (choix == 7) {
            charger();
        }
        else if (choix == 8) {
            cout << "\nMerci d'avoir utilise ce programme !\n";
            cout << "Au revoir.\n";
            break;
        }
        else {
            cout << "\nChoix invalide ! (Entrez 1-8)\n";
        }
    }
}

// ========================================
// Fonction main
// ========================================
int main() {
    GestionEmployes gestion;
    gestion.executer();
    return 0;
}
