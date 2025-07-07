#include <stdio.h>
#include <stdlib.h>


typedef struct Cellule {
    int val;  
    struct Cellule* suivant;  
} Cellule;


typedef struct Liste {
    Cellule* tete; 
} Liste;


typedef struct Pile {
    Cellule* sommet;  
} Pile;


int depiler(Pile* p) {
    if (p->sommet == NULL) {
        printf("La pile est vide!\n");
        exit(1);  
    }
    Cellule* temp = p->sommet;  
    int val = temp->val;  
    p->sommet = temp->suivant;  
    free(temp);  
    return val;  
}


void empiler(Pile* p, int valeur) {
    Cellule* nouvelleCellule = (Cellule*)malloc(sizeof(Cellule));  
    if (nouvelleCellule == NULL) {  
        printf("Erreur d'allocation mémoire!\n");
        exit(1);  
    }
    nouvelleCellule->val = valeur;  
    nouvelleCellule->suivant = p->sommet;  
    p->sommet = nouvelleCellule;  
}


void insererDebut(Liste* liste, int valeur) {
    Cellule* nouvelleCellule = (Cellule*)malloc(sizeof(Cellule));  
    if (nouvelleCellule == NULL) {  
        printf("Erreur d'allocation mémoire!\n");
        return;
    }
    nouvelleCellule->val = valeur;  
    nouvelleCellule->suivant = liste->tete; 
    liste->tete = nouvelleCellule;  
}

void insererFin(Liste* liste, int valeur) {
    Cellule* nouvelleCellule = (Cellule*)malloc(sizeof(Cellule));  
    if (nouvelleCellule == NULL) {  
        printf("Erreur d'allocation mémoire!\n");
        return;
    }
    nouvelleCellule->val = valeur;  
    nouvelleCellule->suivant = NULL;  
    
    if (liste->tete == NULL) {  
        liste->tete = nouvelleCellule;
    } else {
        Cellule* temp = liste->tete;
        while (temp->suivant != NULL) {  
            temp = temp->suivant;
        }
        temp->suivant = nouvelleCellule; 
    }
}

void remplir(Liste* liste) {
    printf("Insertion au debut :\n");
    for (int i = 5; i > 0; i--) {
        insererDebut(liste, i);  
    }

    printf("Insertion a la fin :\n");
    for (int i = 6; i <= 10; i++) {
        insererFin(liste, i);  
    }
}


void afficherListe(Liste* liste) {
    Cellule* temp = liste->tete;
    while (temp != NULL) {
        printf("%d -> ", temp->val);  
        temp = temp->suivant;
    }
    printf("NULL\n");  
}


int estSymetrique(Liste* liste) {
    if (liste == NULL || liste->tete == NULL) {
        return 1;  
    }

    Pile pile;
    pile.sommet = NULL; 
    
    
    Cellule* courant = liste->tete;
    while (courant != NULL) {
        empiler(&pile, courant->val);
        courant = courant->suivant;
    }

    courant = liste->tete;
    while (courant != NULL) {
        int valeurPile = depiler(&pile);  
        if (courant->val != valeurPile) {  
            return 0;  
        }
        courant = courant->suivant;
    }

    return 1;  
}


int main() {
    Liste maListe;
    maListe.tete = NULL;

   
    remplir(&maListe);
    printf("Liste : ");
    afficherListe(&maListe);  

  
    if (estSymetrique(&maListe) == 1) {
        printf("La liste est symétrique.\n");
    } else {
        printf("La liste n'est pas symétrique.\n");
    }

    return 0;
}



noeud* somme_poly(noeud* p1, noeud* p2) {
    noeud *res = NULL, *temp, *fin = NULL;

    while (p1 != NULL && p2 != NULL) {
        temp = (noeud*)malloc(sizeof(noeud));
        if (temp == NULL) {
            printf("Erreur d'allocation mémoire\n");
            return res;
        }

        temp->valeur.x = somme(p1->valeur.x, p2->valeur.x);
        temp->valeur.y = somme(p1->valeur.y, p2->valeur.y);
        temp->suivant = NULL;

        if (res == NULL) {
            res = temp;       // Premier nœud
            fin = temp;
        } else {
            fin->suivant = temp;  // Ajout à la fin
            fin = temp;
        }

        p1 = p1->suivant;
        p2 = p2->suivant;
    }

    return res;
}


void supprimStation(NoeudStation** tete, const char* cle) {
    NoeudStation* courant = *tete;
    NoeudStation* precedent = NULL;

    while (courant != NULL) {
        if (strcmp(courant->station.type, cle) == 0) {
            NoeudStation* temp = courant;
            if (precedent == NULL) {
                // Suppression en tête
                *tete = courant->suivant;
            } else {
                precedent->suivant = courant->suivant;
            }
            courant = courant->suivant;
            free(temp);
        } else {
            precedent = courant;
            courant = courant->suivant;
        }
    }
}

