#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYES 3
#define FICHIER_EMPLOYES "employes.dat"

struct employe {
    int matricule;
    char nom[30];
    char prenom[30];
    float salaire;
};


void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // faut vider le buffer apres chaque scanf raté sinon le prochain scanf prend les restes et ca plante tout
}

//verif si matricule deja la
int matriculeExiste(struct employe t[], int n, int matricule) {
    int i;
    for (i = 0; i < n; i++) {
        if (t[i].matricule == matricule) {
            return 1;
        }
    }
    return 0;
}

int ajouterEmploye(struct employe t[], int n) {
    int matricule;
    float salaire;
    char nom[30], prenom[30];

    if (n >= MAX_EMPLOYES) {
        printf("\nTableau plein !\n");
        return n;
    }

    printf("\n--- Nouvel employe ---\n");

    printf("Entrez matricule : ");
    if (scanf("%d", &matricule) != 1) {
        printf("Erreur saisie\n");
        viderBuffer();
        return n;
    }

    if (matricule <= 0) {
        printf("Matricule invalide\n");
        return n;
    }

    if (matriculeExiste(t, n, matricule)) {
        printf("Ce matricule existe deja\n");
        return n;
    }

    printf("Nom : ");
    if (scanf("%29s", nom) != 1) {
        printf("Erreur\n");
        viderBuffer();
        return n;
    }

    printf("Prenom : ");
    if (scanf("%29s", prenom) != 1) {
        printf("Erreur\n");
        viderBuffer();
        return n;
    }

    printf("Salaire (FCFA) : ");
    if (scanf("%f", &salaire) != 1) {
        printf("Erreur\n");
        viderBuffer();
        return n;
    }

    if (salaire < 0) {
        printf("Salaire negatif ??\n");
        return n;
    }

    //ok on enregistre
    t[n].matricule = matricule;
    strcpy(t[n].nom, nom);
    strcpy(t[n].prenom, prenom);
    t[n].salaire = salaire;

    printf("Ajoute avec succes\n");
    return n + 1;
}

void afficherTous(struct employe t[], int n) {
    int i;

    if (n == 0) {
        printf("\nAucun employe enregistre\n");
        return;
    }

    printf("\n---------- Liste des employes ----------\n");
    printf("Total : %d\n", n);

    for (i = 0; i < n; i++) {
        printf("\nEmploye %d :\n", i + 1);
        printf("  Matricule : %d\n", t[i].matricule);
        printf("  Nom : %s\n", t[i].nom);
        printf("  Prenom : %s\n", t[i].prenom);
        printf("  Salaire : %.2f FCFA\n", t[i].salaire);
    }
    printf("----------------------------------------\n");
}

void afficherParSeuil(struct employe t[], int n) {
    float seuil;
    int compteur = 0;
    int i;

    if (n == 0) {
        printf("\nPas d'employes dans la liste\n");
        return;
    }

    printf("\nEntrez le seuil de salaire : ");
    if (scanf("%f", &seuil) != 1) {
        printf("Saisie incorrecte\n");
        viderBuffer();
        return;
    }

    if (seuil < 0) {
        printf("Seuil doit etre positif\n");
        return;
    }

    printf("\n--- Employes avec salaire > %.2f ---\n", seuil);

    for (i = 0; i < n; i++) {
        if (t[i].salaire > seuil) {
            printf("\n%s %s (Mat: %d) - %.2f FCFA\n",
                   t[i].prenom, t[i].nom, t[i].matricule, t[i].salaire);
            compteur++;
        }
    }

    if (compteur == 0) {
        printf("\nAucun employe trouve\n");
    } else {
        printf("\nNombre trouve : %d\n", compteur);
    }
}

int supprimerEmploye(struct employe t[], int n) {
    int matricule, trouve = 0;
    int i, j;

    if (n == 0) {
        printf("\nListe vide\n");
        return n;
    }

    printf("\nMatricule de l'employe a supprimer : ");
    if (scanf("%d", &matricule) != 1) {
        printf("Erreur saisie\n");
        viderBuffer();
        return n;
    }

    for (i = 0; i < n; i++) {
        if (t[i].matricule == matricule) {
            //on decale tout
            for (j = i; j < n - 1; j++) {
                t[j] = t[j + 1];
            }
            printf("Employe supprime\n");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Matricule introuvable\n");
        return n;
    }

    return n - 1;
}

void trierParSalaire(struct employe t[], int n) {
    struct employe temp;
    int i, j;

    if (n == 0) {
        printf("\nAucun employe a trier\n");
        return;
    }

    //tri a bulles
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (t[j].salaire > t[j + 1].salaire) {
                temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }

    printf("\nListe triee par ordre croissant de salaire\n");
}

void enregistrerFichier(struct employe t[], int n) {
    FILE *f;

    f = fopen(FICHIER_EMPLOYES, "wb");
    if (f == NULL) {
        printf("\nImpossible d'ouvrir le fichier\n");
        return;
    }

    //ecrire le nombre d'employes
    if (fwrite(&n, sizeof(int), 1, f) != 1) {
        printf("Erreur ecriture\n");
        fclose(f);
        return;
    }

    //puis les employes
    if (fwrite(t, sizeof(struct employe), n, f) != n) {
        printf("Erreur ecriture donnees\n");
        fclose(f);
        return;
    }

    fclose(f);
    printf("\nDonnees enregistrees avec succes (%d employes)\n", n);
}

int chargerFichier(struct employe t[]) {
    FILE *f;
    int n;

    f = fopen(FICHIER_EMPLOYES, "rb");
    if (f == NULL) {
        printf("\nFichier introuvable\n");
        return 0;
    }

    //lire le nombre
    if (fread(&n, sizeof(int), 1, f) != 1) {
        printf("Erreur lecture\n");
        fclose(f);
        return 0;
    }

    if (n < 0 || n > MAX_EMPLOYES) {
        printf("Fichier corrompu\n");
        fclose(f);
        return 0;
    }

    //lire les employes
    if (fread(t, sizeof(struct employe), n, f) != n) {
        printf("Erreur lecture donnees\n");
        fclose(f);
        return 0;
    }

    fclose(f);
    printf("\n%d employes charges\n", n);
    return n;
}

void afficherMenu() {
    printf("\n");
    printf(">> GESTION DES EMPLOYES\n");
    printf("\n");
    printf("  >> 1. Ajouter un employe\n");
    printf("  >> 2. Afficher tous les employes\n");
    printf("  >> 3. Rechercher par seuil de salaire\n");
    printf("  >> 4. Supprimer un employe\n");
    printf("  >> 5. Trier par salaire\n");
    printf("  >> 6. Sauvegarder dans fichier\n");
    printf("  >> 7. Charger depuis fichier\n");
    printf("  >> 8. Quitter\n");
    printf("\n");
    printf("Votre choix >> ");
}

int main() {
    struct employe tableau[MAX_EMPLOYES];
    int nb_employes = 0;
    int choix;

    printf("\nProgramme de gestion des employes\n");

    while (1) {
        afficherMenu();

        if (scanf("%d", &choix) != 1) {
            printf("\nSaisie invalide\n");
            viderBuffer();
            continue;
        }

        switch (choix) {
            case 1:
                nb_employes = ajouterEmploye(tableau, nb_employes);
                break;
            case 2:
                afficherTous(tableau, nb_employes);
                break;
            case 3:
                afficherParSeuil(tableau, nb_employes);
                break;
            case 4:
                nb_employes = supprimerEmploye(tableau, nb_employes);
                break;
            case 5:
                trierParSalaire(tableau, nb_employes);
                break;
            case 6:
                enregistrerFichier(tableau, nb_employes);
                break;
            case 7:
                nb_employes = chargerFichier(tableau);
                break;
            case 8:
                printf("\nMerci d'avoir utilise ce programme\n");
                printf("Au revoir\n");
                return 0;
            default:
                printf("\nChoix invalide (entrez 1-8)\n");
        }
    }

    return 0;
}
