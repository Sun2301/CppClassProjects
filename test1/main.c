#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){int n;
    float salaire_seuil;
    printf("Quel est le nombre d'employes ?");
    scanf("%i",&n);
    printf("Quel est le salaire seuil ?");
    scanf("%f",&salaire_seuil);
    struct employe {
        int matricule;
        char nom[30];
        char prenom[30];
        float salaire;
    };
    struct employe t[n];
    int i;
    int j;
    int a;

    int matricule;
    char nom[30];
    char prenom[30];
    float salaire;

    for (i=0; i<n;i++){

        printf("Entrez le matricule de l'employe :");
        scanf("%i",&matricule);

        t[i].matricule=matricule;
        printf("Entrez le nom de l'employe :");
        scanf("%s",nom);
        strcpy(t[i].nom,nom);
        printf("Entrez le prenom de l'employe :");
        scanf("%s",prenom);
        strcpy(t[i].prenom,prenom);
        printf("Entrez le salaire de l'employe :");
        scanf("%f",&salaire);
        t[i].salaire=salaire;
        ;
    };
    for (j=0; j<n; j++) {
            if (t[j].salaire > salaire_seuil){
                printf("\n Employe %i\n", j+1);
                printf(" Matricule : %i\n", t[j].matricule);
                printf(" Nom : %s\n", t[j].nom);
                printf(" Prenom : %s\n", t[j].prenom);
                printf(" Salaire : %.2f\n", t[j].salaire);}
        };
return 0;
}
