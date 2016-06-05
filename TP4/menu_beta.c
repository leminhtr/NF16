#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#include <string.h>

int main()
{
	char *racine_nom;
    int racine_status;
    
    printf("Saisir le nom du repertoire racine :\n");   //recuperation nom racine
    fgets(racine_nom,50,stdin);
    char *pos_n=NULL;
    pos_n = strchr(racine_nom, '\n');       //On cherche l'adresse du caractère '\n' stocke par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }

    printf("Quel est le statut du dossier racine %s\n", nom_racine);    //recuperation statut racine
    scanf("%d", &racine_status);
    getchar();    //caractère d'echappement '\n'

    Dir* racine=create_dir(nom_racine, racine_status,NULL, NULL);   //création racine

    if(racine_nom==NULL)            //racine NULL
    {
        printf("Erreur creation dossier racine.\n");
    }
    else        //racine créée
    {
        int choix;
        char *sous_dir_nom;

        Node *racine_node=create_node(racine, NULL,NULL);
        Node *current_dir=malloc(sizeof(Dir));
        Node *current_node=malloc(sizeof(Dir))

        while(1)
        {
            printf("Que voulez-vous faire ?\n");
            printf("1. Afficher le nom, et le contenu du repertoire courant ainsi que le chemin absolu\n");
            printf("2. Creer un sous-repertoire dans le repertoire courant\n");
            printf("3. Aller dans un sous-repertoire \n");
            printf("4. Retourner a la racine\n");
            printf("5. Aller dans le repertoire pere\n");
            printf("0. Quitter le programme\n");

            scanf("%d", &choix);
            getchar();


        
            switch(choix)
            {
                case 1 :
                    printf("Vous avez choisi d\'afficher le nom, et le contenu du repertoire courant ainsi que le chemin absolu.\n");

                    printf("Nom du repertoire courant : %s\n"current_dir->name);
                    print_path(current_dir);
                    print_tree(current_dir);
                    printf("\n");

                    break;
                case 2 :
                    printf("Vous avez choisi de creer un sous-repertoire dans le repertoire courant.\n");


                    break;
                case 3 :
                    printf("Vous avez choisi d\'aller dans un sous-repertoire.\n");

                    printf("Dans quel sous-repertoire voulez-vous aller ?\n");
                    fgets(sous_dir_nom, 50, stdin);

                    char *pos_n=NULL;
                    pos_n = strchr(racine_nom, '\n');       //On cherche l'adresse du caractère '\n' stocke par fgets
                    if (pos_n != NULL) //
                    {
                        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
                    }

                    current_dir=search_dir(sous_dir_nom, current_node);

                    if(current_dir==NULL)
                    {
                        printf("Le repertoire %s n\'a pas ete trouve\n",sous_dir_nom);
                    }
                    else
                    {
                        print_path(current_dir);
                    }

                    break;
                case 4 :
                    printf("Vous avez choisi de retourner a la racine.\n");

                    current_dir=racine;
                    current_node=racine_node;

                    break;
                case 5 :
                    printf("Vous avez choisi d\'aller dans le repertoire pere.\n");


                    break;

                case 0 :
                        printf("Vous avez choisi de quitter le programme.\n");
                        exit(0);

                default :
                        break;
            }
        }
    }    
    return 0;
}