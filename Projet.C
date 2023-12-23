#include<stdio.h> //Mohamed Amine Bouhachem//E-Bank//
#include <stdlib.h>
#include<string.h>                             
#include<malloc.h>                            
#include<math.h>
#include<time.h>
void clearScreen() 
{
    system("clear || cls"); 
}
typedef struct CompteBancaire {
    int numeroCompte;
    char nomTitulaire[50];
    float solde;
    struct CompteBancaire *suivant;
} CompteBancaire;
CompteBancaire *teteListe = NULL;
void afficherMenu() 
{
printf("\n\t\t=====================================\n");
printf("\t\t // E-BANK //\n");
printf("\t\t=====================================\n\n");
printf("\n  ========================\n\t>< MENU ><\n  ========================\n\n");
printf("[1]. Creer un nouveau compte.\n");
printf("[2]. Mise a jour des informations d un compte existant.\n");
printf("[3]. Afficher et gerer les transactions bancaires.\n");
printf("[4]. Supprimer un compte existant.\n");
printf("[5]. Afficher les details d un compte existant.\n");
printf("[6]. Afficher la liste des clients.\n");
printf("[7]. Afficher mes transactions precedentes;\n");
printf("[8]. Quitter\n\n");
printf("  ========================\n\n");
printf("Choisissez une option : ");
}
// Fonction pour trouver un compte par son numéro
CompteBancaire *trouverCompte(CompteBancaire *teteListe, int numeroCompte)
{
    CompteBancaire *courant=teteListe;
    while (courant != NULL)
    {
        if (courant->numeroCompte==numeroCompte)
        {
            return courant;
        }
        courant = courant->suivant;
    }
    return NULL;
}
CompteBancaire* ajouterCompte(CompteBancaire* teteListe, int numeroCompte, const char* nomTitulaire, float solde) {
    CompteBancaire* nouveauCompte = (CompteBancaire*)malloc(sizeof(CompteBancaire));
    if (nouveauCompte == NULL) {
        return teteListe;
    }
    nouveauCompte->numeroCompte = numeroCompte;
    strncpy(nouveauCompte->nomTitulaire, nomTitulaire, sizeof(nouveauCompte->nomTitulaire));
    nouveauCompte->solde = solde;
    nouveauCompte->suivant = teteListe; 
    return nouveauCompte; 
}
CompteBancaire* MAJcompte(CompteBancaire *teteListe, int numeroCompte, const char *nouveauNomTitulaire, float nouveauSolde) {
    CompteBancaire *courant = teteListe;
    while (courant!=NULL) {
        if (courant->numeroCompte==numeroCompte) {
            strncpy(courant->nomTitulaire,nouveauNomTitulaire,sizeof(courant->nomTitulaire));
            courant->solde=nouveauSolde;
            printf("Le compte a ete mis a jour avec succes.\n");
            printf("Nouvelles informations du compte :\n");
            printf("Numéro de compte: %d\n", courant->numeroCompte);
            printf("Titulaire du compte: %s\n", courant->nomTitulaire);
            printf("Solde: %.2f\n", courant->solde);
            return teteListe; 
        }
        courant=courant->suivant;
    }
    printf("Aucun compte trouve avec le numéro : %d\n", numeroCompte);
    return teteListe; 
}
CompteBancaire *Supprimercompte(CompteBancaire *teteListe, int numeroCompte) {
    CompteBancaire *courant = teteListe;
    CompteBancaire *precedent = NULL;
    while (courant!=NULL && courant->numeroCompte!=numeroCompte) {
        precedent=courant;
        courant=courant->suivant;
    }
    if (courant!=NULL) {
        if (precedent != NULL) {
            precedent->suivant=courant->suivant;
        } else {
            teteListe=courant->suivant; 
        }
        free(courant);
        printf("Le compte a ete supprime avec succes.\n");
    } else {
        printf("Aucun compte trouvé avec le numero : %d\n", numeroCompte);
    }
    return teteListe;
}
void afficherListe(CompteBancaire *teteListe){
    CompteBancaire *courant = teteListe;

	while (courant != NULL)
	{
		printf("\n  numeroCompte : ");
		printf("%d", courant->numeroCompte);
		printf("\n  nomTitulaire : ");
		printf("%s", courant->nomTitulaire);
		printf("\n  solde : ");
		printf("%f", courant->solde);
		printf("\n");

        courant = courant->suivant;  
	}
}
void Affichercompte(CompteBancaire **teteListe, int numeroCompte) {
    CompteBancaire *courant = *teteListe;
    while (courant != NULL) {
        if (courant->numeroCompte == numeroCompte) {
            printf("\n  numeroCompte : ");
            printf("%d", courant->numeroCompte);
            printf("\n  nomTitulaire : ");
            printf("%s", courant->nomTitulaire);
            printf("\n  solde : ");
            printf("%f", courant->solde);
            printf("\n");
            return;
        }
        courant = courant->suivant;
    }
    printf("Aucun compte trouve avec le numero : %d\n", numeroCompte);
}
// Structure représentant une transaction bancaire
typedef struct Transaction
{
    int numeroCompte;
    float montant;
    char type; // 'R' pour retrait, 'V' pour versement
    struct Transaction *suivant;   
} Transaction;
// Libérer la mémoire allouée pour la liste des comptes
void libererMemoireListe(CompteBancaire **teteListe)
{
    CompteBancaire *courant=*teteListe;
    CompteBancaire *suivant;
    while (courant != NULL)
    {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }

    *teteListe = NULL; 
}
// Libérer la mémoire allouée pour la liste des transactions
void libererMemoireTransactions(Transaction **listeTransactions) {
    Transaction *courant = *listeTransactions;
    Transaction *suivant;
    while (courant != NULL) {
        suivant = courant->suivant;
        free(courant);
        courant = suivant;
    }
    *listeTransactions = NULL; // Met à jour la liste des transactions à NULL après la libération
}
// Ajouter une transaction à la liste des transactions
void ajouterTransaction(Transaction **listeTransactions, int numeroCompte, float montant, char type)
{
    Transaction *nouvelleTransaction = (Transaction *)malloc(sizeof(Transaction));
    if (nouvelleTransaction == NULL)
    {
        printf("Erreur d allocation memoire pour la transaction.\n");
        exit(EXIT_FAILURE);
    }
    nouvelleTransaction->numeroCompte = numeroCompte;
    nouvelleTransaction->montant = montant;
    nouvelleTransaction->type = type;
    nouvelleTransaction->suivant = *listeTransactions;
    *listeTransactions = nouvelleTransaction;
}
// Afficher les transactions d'un compte spécifique
void afficherTransactionsCompte(Transaction *listeTransactions, int numeroCompte)
{
    printf("Transactions pour le compte %d :\n",numeroCompte);
    while (listeTransactions != NULL)
    {
        if (listeTransactions->numeroCompte==numeroCompte)
        {
            printf("Type: %c, Montant: %.2f\n", listeTransactions->type, listeTransactions->montant);
        }
        listeTransactions=listeTransactions->suivant;
    }
}
// Fonction pour gérer les transactions (retrait ou versement)
void gererTransactions(CompteBancaire *compte, Transaction **listeTransactions)
{
    int choix;
    float montant;
    printf("1. Retrait\n");
    printf("2. Versement\n");
    printf("Choisissez une option : ");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        printf("Entrez le montant du retrait : ");
        scanf("%f", &montant);

        if (montant > 0 && montant<=compte->solde)
        {
            compte->solde-=montant;
            printf("Retrait de %.2f effectue avec succes.\n", montant);
            ajouterTransaction(listeTransactions, compte->numeroCompte, montant, 'R');
        }
        else
        {
            printf("Montant invalide ou solde insuffisant.\n");
        }
        break;
    case 2:
        printf("Entrez le montant du versement : ");
        scanf("%f", &montant);
        if (montant > 0)
        {
            compte->solde += montant;
            printf("Versement de %.2f effectue avec succes.\n", montant);
            ajouterTransaction(listeTransactions, compte->numeroCompte, montant, 'V');
        }
        else
        {
            printf("Montant invalide.\n");
        }
        break;
    default:
        printf("Option invalide.\n");
        break;
    }
}
// Fonction pour afficher les transactions précédentes d'un compte
void afficherTransactionsPrecedentes(CompteBancaire *compte, Transaction *listeTransactions)
{
    printf("Transactions precedentes pour le compte %d :\n", compte->numeroCompte);
    while (listeTransactions!=NULL)
    {
        if (listeTransactions->numeroCompte==compte->numeroCompte)
        {
            printf("Type: %c, Montant: %.2f\n", listeTransactions->type, listeTransactions->montant);
        }
        listeTransactions = listeTransactions->suivant;
    }
}
Transaction *listeTransactions=NULL; 
int main()
{
        CompteBancaire *teteListe=NULL;
        //initial data//
        teteListe = ajouterCompte(teteListe, 123, "Omar Jerbi", 1000.0);
        teteListe = ajouterCompte(teteListe, 456, "Kamel Presse", 500.0);
        teteListe = ajouterCompte(teteListe,600,"Ayoub Poldiro",450.0);
        teteListe = ajouterCompte(teteListe, 444 , "Malik Monk", 800.0);
        teteListe = ajouterCompte(teteListe,700,"Rayen Vendredi",600.0);
        teteListe = ajouterCompte(teteListe, 333 , "Ahmed Lamta", 900.0);
        teteListe = ajouterCompte(teteListe, 500 , "Salma Hayek", 100.0);
        // initial data//

    int choix;
    do
    {
        clearScreen();
        afficherMenu();
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
            {
                clearScreen();
                int numeroCompte;
                char nomTitulaire[50];
                float solde;
                printf("Entrez le numero de compte : ");
                scanf("%d", &numeroCompte);
                printf("Entrez le nom du titulaire : ");
                scanf("%s", nomTitulaire);
                printf("Entrez le solde initial : ");
                scanf("%f", &solde);
                teteListe = ajouterCompte(teteListe, numeroCompte, nomTitulaire, solde);
                break;
            }
            case 2:
            {
                clearScreen();
                int numeroCompteMAJ;
                char nouveauNomTitulaire[50];
                float nouveauSolde;
                printf("Entrez le numero de compte a mettre a jour : ");
                scanf("%d", &numeroCompteMAJ);
                CompteBancaire *compteMAJ = trouverCompte(teteListe, numeroCompteMAJ);

                if (compteMAJ != NULL) 
				{
                    printf("Entrez le nouveau nom du titulaire : ");
                    scanf("%s", nouveauNomTitulaire);
                    printf("Entrez le nouveau solde : ");
                    scanf("%f", &nouveauSolde);
                    
                    teteListe = MAJcompte(teteListe, numeroCompteMAJ, nouveauNomTitulaire, nouveauSolde);
                 }        
                 else 
                 {
                     printf("Aucun compte trouve avec le numero : %d\n", numeroCompteMAJ);
                 }
                 
                 printf("\nAppuyez sur n importe quelle touche pour revenir au menu...");
                 getchar();
                 getchar();
                 break;
            }
            case 3:
            {
                clearScreen();
                int numeroCompteTransaction;
                printf("Entrez le numero de compte pour les transactions : ");
                scanf("%d", &numeroCompteTransaction);
                CompteBancaire *compteTransaction = trouverCompte(teteListe, numeroCompteTransaction);
                if (compteTransaction != NULL)
                {
                    clearScreen();
                    gererTransactions(compteTransaction, &listeTransactions);
                }
                else
                {
                    printf("Aucun compte trouve avec le numéro : %d\n", numeroCompteTransaction);
                }
                printf("\nAppuyez sur n importe quelle touche pour revenir au menu...");
                getchar();
                getchar();
                break;
            }
            case 4:
            {
				clearScreen();
				int numeroCompteSupprime;
				printf("Entrez le numero de compte à supprimer : ");
				scanf("%d", &numeroCompteSupprime);
				teteListe = Supprimercompte(teteListe, numeroCompteSupprime);
				printf("\nAppuyez sur n importe quelle touche pour revenir au menu...");
				getchar();
				getchar();
				break;
			}
			case 5:
			{
				clearScreen();
				int numeroCompteAffiche;
				printf("Entrez le numero de compte a afficher : ");
				scanf("%d", &numeroCompteAffiche);
				Affichercompte(&teteListe, numeroCompteAffiche);
				printf("\nAppuyez sur n importe quelle touche pour revenir au menu...");
				getchar();
				getchar();
				
				break;
			}
			case 6:
			{
				clearScreen();
				printf("Liste des clients :\n");
				afficherListe(teteListe);
				printf("\nAppuyez sur n importe quelle touche pour revenir au menu...");
				getchar();
				getchar();
				break;
			}
			case 7:
			{
				clearScreen();
				int numeroCompteG;
				printf("Entrez le numero de compte pour afficher les transactions precedentes : ");
				scanf("%d", &numeroCompteG);
                CompteBancaire *compteTransactionsPrecedentes = trouverCompte(teteListe, numeroCompteG);
                if (compteTransactionsPrecedentes != NULL)
                {
                    clearScreen();
                    afficherTransactionsPrecedentes(compteTransactionsPrecedentes, listeTransactions);
                }
                else
                {
                    printf("Aucun compte trouvé avec le numero : %d\n", numeroCompteG);
                }
                printf("\nAppuyez sur n importe quelle touche pour revenir au menu...");
                getchar();
                getchar();
                break;
            }
            case 8:
            {
            	libererMemoireListe(&teteListe);
            	libererMemoireTransactions(&listeTransactions);
            	printf("Merci d avoir utilisé E-Bank. A bientot !\n");
            	exit(0);  
            	break;
            }
            default:
            {
            	printf("Option invalide.\n");
            	break;
            }
        }
    } while (choix != 0);
    libererMemoireListe(&teteListe);
    libererMemoireTransactions(&listeTransactions);
    return 0;
}
