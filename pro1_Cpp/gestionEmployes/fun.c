
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Servomoteur {
private:
    string nom;
    int angleActuel;
    int angleMin;
    int angleMax;
    int vitesse;  // degrés par seconde

public:
    // COMPLÈTE CE CONSTRUCTEUR
    Servomoteur(string n, int min, int max, int v) {
        // À TOI : initialise tous les attributs
        // angleActuel doit démarrer au milieu : (min + max) / 2
    }

    // COMPLÈTE CETTE MÉTHODE
    // Retourne le temps nécessaire (en secondes) pour atteindre l'angle
    // Retourne -1 si l'angle est hors limites
    float deplacer(int angleDest) {
        // À TOI :
        // 1. Vérifier si angleDest est entre angleMin et angleMax
        // 2. Si non → afficher erreur et retourner -1
        // 3. Calculer la distance : |angleDest - angleActuel|
        // 4. Calculer le temps : distance / vitesse
        // 5. Mettre à jour angleActuel
        // 6. Retourner le temps
    }

    // COMPLÈTE CETTE MÉTHODE
    int getPosition() {
        // À TOI : retourne angleActuel
    }

    // COMPLÈTE CETTE MÉTHODE
    void afficher() {
        // À TOI : affiche quelque chose comme :
        // "[Base] Position: 90° (limites: 0-180°, vitesse: 30°/s)"
    }
};

// TEST
int main() {
    Servomoteur base("Base", 0, 180, 30);

    base.afficher();

    cout << "\nDeplacement vers 120°...\n";
    float temps = base.deplacer(120);
    cout << "Temps: " << temps << "s\n";

    base.afficher();

    cout << "\nDeplacement vers 200° (hors limites)...\n";
    temps = base.deplacer(200);

    return 0;
}
```

---

## 📝 CE QUE TU DOIS OBTENIR COMME SORTIE :
```
[Base] Position: 90° (limites: 0-180°, vitesse: 30°/s)

Deplacement vers 120°...
Temps: 1s

[Base] Position: 120° (limites: 0-180°, vitesse: 30°/s)

Deplacement vers 200° (hors limites)...
ERREUR: Angle 200° hors limites [0-180]
