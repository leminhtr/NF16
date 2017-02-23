#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define ITEMSMAX 20
#define CARACMAX 60
#define PI 3.14159
#define NMAX 50

//2.1
    struct Un_Tableau_Entier {
            int tab[NMAX];      //tableau entier
            int ncase;        //nombre case tableau
    };
    typedef struct Un_Tableau_Entier tab_int;

//2.2
    struct menu {
            char tab[ITEMSMAX][CARACMAX]; // 20 items de 60 caractères
            int n;                        //nombre items
    };
    typedef struct menu menu;

//2.3
    struct tonneau{
            float d;
            float D;
            float L;
            char *contenu;
    };
    typedef struct tonneau tonneau;


void affectation(tonneau *T)
{
    printf("Petit diametre ?\n");
    scanf("%f", &T->d);

    printf("Grand diametre ?\n");
    scanf("%f", &T->D);

    printf("Longueur ?\n");
    scanf("%f", &T->L);

    printf("Contenu ?\n");
    fgets(T->contenu, 20, stdin);

}

void affichage(tonneau T)
{
    printf("Petit diametre = %f\n Grand diametre = %f\n Longueur =%f\n", T.d, T.D, T.L);
    int i=0;
    printf("Contenu : ");

    while((T->contenu[i])!='/0')
    {
        printf("%c", T->contenu[i]);
    }
}


float volume_1(float d, float D, float L){

    return 0;
}

int main()
{
//2.4
    tonneau t;
    affectation(&t);
    affichage(t);











    printf("Hello world!\n");
    return 0;
}

void affectation(tonneau *T)
{
    printf("Petit diametre ?\n");
    scanf("%f", &T->d);

    printf("Grand diametre ?\n");
    scanf("%f", &T->D);

    printf("Longueur ?\n");
    scanf("%f", &T->L);

    printf("Contenu ?\n");
    fgets(T->contenu, 20, stdin);

}

void affichage(tonneau T)
{
    printf("Petit diametre = %f\n Grand diametre = %f\n Longueur =%f\n", T.d, T.D, T.L);
    int i=0;
    printf("Contenu : ");

    while(T.contenu[i]!='/0')
    {
        printf("%c", T.contenu[i]);
    }
}
