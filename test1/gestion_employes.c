#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EMPLOYES 100
#define FICHIER_EMPLOYES "employes.dat"

struct employe {
    int matricule;
    char nom[30];
    char prenom[30];
    float salaire;
};

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

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
        printf("\nDesole, le tableau est plein. Capacite maximale atteinte.\n");
        return n;
    }

    printf("\n--- Ajout d'un employe ---\n");

    // Saisie du matricule avec validation
    printf("Matricule : ");
    if (scanf("%d", &matricule) != 1) {
        printf("Erreur de saisie. Le matricule doit etre un nombre entier.\n");
        viderBuffer();
        return n;
    }

    if (matricule <= 0) {
        printf("Le matricule doit etre strictement positif.\n");
        return n;
    }

    if (matriculeExiste(t, n, matricule)) {
        printf("Ce matricule existe deja dans la base.\n");
        return n;
    }

    // Saisie du nom
    printf("Nom : ");
    if (scanf("%29s", nom) != 1) {
        printf("Erreur lors de la saisie du nom.\n");
        viderBuffer();
        return n;
    }

    // Saisie du prénom
    printf("Prenom : ");
    if (scanf("%29s", prenom) != 1) {
        printf("Erreur lors de la saisie du prenom.\n");
        viderBuffer();
        return n;
    }

    // Saisie du salaire avec validation
    printf("Salaire : ");
    if (scanf("%f", &salaire) != 1) {
        printf("Le salaire doit etre un nombre valide.\n");
        viderBuffer();
        return n;
    }

    if (salaire < 0) {
        printf("Le salaire ne peut pas etre negatif.\n");
        return n;
    }

    // Tout est ok, on enregistre
    t[n].matricule = matricule;
    strcpy(t[n].nom, nom);
    strcpy(t[n].prenom, prenom);
    t[n].salaire = salaire;

    printf("\nEmploye ajoute avec success !\n");
    return n + 1;
}

void afficherTous(struct employe t[], int n) {
    int i;

    if (n == 0) {
        printf("\nLa liste est vide. Aucun employe enregistre.\n");
        return;
    }

    printf("\n========== LISTE DES EMPLOYES ==========\n");
    printf("Nombre total : %d\n", n);

    for (i = 0; i < n; i++) {
        printf("\n--- Employe #%d ---\n", i + 1);
        printf("Matricule : %d\n", t[i].matricule);
        printf("Nom : %s\n", t[i].nom);
        printf("Prenom : %s\n", t[i].prenom);
        printf("Salaire : %.2f FCFA\n", t[i].salaire);
    }
    printf("\n========================================\n");
}

void afficherParSeuil(struct employe t[], int n) {
    float seuil;
    int compteur = 0;
    int i;

    if (n == 0) {
        printf("\nAucun employe dans la base.\n");
        return;
    }

    printf("\nSalaire seuil : ");
    if (scanf("%f", &seuil) != 1) {
        printf("Valeur invalide.\n");
        viderBuffer();
        return;
    }

    if (seuil < 0) {
        printf("Le seuil ne peut pas etre negatif.\n");
        return;
    }

    printf("\n--- Employes gagnant plus de %.2f FCFA ---\n", seuil);

    for (i = 0; i < n; i++) {
        if (t[i].salaire > seuil) {
            printf("\n%s %s (Matricule: %d) - Salaire: %.2f FCFA\n",
                   t[i].prenom, t[i].nom, t[i].matricule, t[i].salaire);
            compteur++;
        }
    }

    if (compteur == 0) {
        printf("\nAucun employe trouve au-dessus de ce seuil.\n");
    } else {
        printf("\nTotal : %d employe(s) trouve(s).\n", compteur);
    }
}

int supprimerEmploye(struct employe t[], int n) {
    int matricule, trouve = 0;
    int i, j;

    if (n == 0) {
        printf("\nLa liste est vide, rien a supprimer.\n");
        return n;
    }

    printf("\nMatricule de l'employe a supprimer : ");
    if (scanf("%d", &matricule) != 1) {
        printf("Matricule invalide.\n");
        viderBuffer();
        return n;
    }

    for (i = 0; i < n; i++) {
        if (t[i].matricule == matricule) {
            // Décalage des éléments
            for (j = i; j < n - 1; j++) {
                t[j] = t[j + 1];
            }
            printf("Employe supprime avec succes.\n");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Aucun employe avec ce matricule.\n");
        return n;
    }

    return n - 1;
}

void trierParSalaire(struct employe t[], int n) {
    struct employe temp;
    int i, j;

    if (n == 0) {
        printf("\nAucun employe a trier.\n");
        return;
    }

    // Tri à bulles
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (t[j].salaire > t[j + 1].salaire) {
                temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }

    printf("\nListe triee par salaire croissant.\n");
}

void enregistrerFichier(struct employe t[], int n) {
    FILE *f;

    f = fopen(FICHIER_EMPLOYES, "wb");
    if (f == NULL) {
        printf("\nImpossible d'ouvrir le fichier en ecriture.\n");
        printf("Verifiez les permissions du repertoire.\n");
        return;
    }

    if (fwrite(&n, sizeof(int), 1, f) != 1) {
        printf("Erreur lors de l'ecriture du nombre d'employes.\n");
        fclose(f);
        return;
    }

    if (fwrite(t, sizeof(struct employe), n, f) != n) {
        printf("Erreur lors de l'ecriture des donnees.\n");
        fclose(f);
        return;
    }

    fclose(f);
    printf("\nDonnees sauvegardees avec succes dans '%s' (%d employes).\n",
           FICHIER_EMPLOYES, n);
}

int chargerFichier(struct employe t[]) {
    FILE *f;
    int n;

    f = fopen(FICHIER_EMPLOYES, "rb");
    if (f == NULL) {
        printf("\nFichier '%s' introuvable. Aucune donnee chargee.\n",
               FICHIER_EMPLOYES);
        return 0;
    }

    if (fread(&n, sizeof(int), 1, f) != 1) {
        printf("Erreur de lecture du fichier (nombre d'employes).\n");
        fclose(f);
        return 0;
    }

    if (n < 0 || n > MAX_EMPLOYES) {
        printf("Fichier corrompu : nombre d'employes invalide (%d).\n", n);
        fclose(f);
        return 0;
    }

    if (fread(t, sizeof(struct employe), n, f) != n) {
        printf("Erreur de lecture des donnees.\n");
        fclose(f);
        return 0;
    }

    fclose(f);
    printf("\n%d employe(s) charge(s) depuis '%s'.\n", n, FICHIER_EMPLOYES);
    return n;
}

void afficherMenu() {
    printf("\n======================================\n");
    printf("     GESTION DES EMPLOYES\n");
    printf("======================================\n");
    printf("1. Ajouter un employe\n");
    printf("2. Afficher tous les employes\n");
    printf("3. Rechercher par seuil de salaire\n");
    printf("4. Supprimer un employe\n");
    printf("5. Trier par salaire\n");
    printf("6. Sauvegarder dans un fichier\n");
    printf("7. Charger depuis un fichier\n");
    printf("8. Quitter\n");
    printf("======================================\n");
    printf("Votre choix : ");
}

int main() {
    struct employe tableau[MAX_EMPLOYES];
    int nb_employes = 0;
    int choix;

    printf("\n*** Programme de gestion des employes ***\n");
    printf("Version 1.0\n");

    while (1) {
        afficherMenu();

        if (scanf("%d", &choix) != 1) {
            printf("\nEntree invalide. Veuillez saisir un chiffre.\n");
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
                printf("\nFermeture du programme...\n");
                printf("Au revoir !\n\n");
                return 0;
            default:
                printf("\nChoix invalide. Choisissez entre 1 et 8.\n");
        }
    }

    return 0;
}
