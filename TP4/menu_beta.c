#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"
#include <string.h>

int main()
{
	char racine_nom[DMAX];
    int racine_status;

    printf("Saisir le nom du repertoire racine :\n");   //recuperation nom racine
    fgets(racine_nom,50,stdin);

    char *pos_n=NULL;
    pos_n = strchr(racine_nom, '\n');       //On cherche l'adresse du caractère '\n' stocke par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }

    printf("Quel est le statut du dossier racine ?\n");    //recuperation statut racine
    scanf("%d", &racine_status);
    getchar();    //caractère d'echappement '\n'

    Dir* dirRacine=create_dir(racine_nom, racine_status,NULL, NULL);   //création racine

    if(racine_nom==NULL)            //racine NULL
    {
        printf("Erreur creation dossier racine.\n");
    }
    else        //racine créée
    {
        int choix;
        char sous_dir_nom[DMAX];
        int sous_dir_status;
        int test_add_dir;

        Node *racine_node=create_node(dirRacine, NULL,NULL);
        Dir *current_dir=malloc(sizeof(Dir));
        Node *current_node=malloc(sizeof(Node));
        Dir *new_dir;
        current_node=racine_node;
        current_dir=racine_node->dir;

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

                    printf("Nom du repertoire courant : %s\n",current_dir->name);
                    print_path(current_dir);
                    printf("sous-repertoires :\n");
                    print_tree(current_node->dir->sub);
                    printf("\n");

                    break;
                case 2 :
                    printf("Vous avez choisi de creer un sous-repertoire dans le repertoire courant.\n");
                    Node *dir_sub=malloc(sizeof(Node));
                    current_dir->sub=dir_sub;

                    printf("Saisir le nom du repertoire a creer :\n");   //recuperation nom new_dir
                    fgets(sous_dir_nom,50,stdin);

                    char *pos_n=NULL;
                    pos_n = strchr(sous_dir_nom, '\n');       //On cherche l'adresse du caractère '\n' stocke par fgets
                    if (pos_n != NULL) //
                    {
                        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
                    }

                    printf("Quel est le statut du dossier a creer\n");    //recuperation statut new_dir
                    scanf("%d", &sous_dir_status);
                    getchar();    //caractère d'echappement '\n'

                    //Création du nouveau dossier
                    new_dir=create_dir(sous_dir_nom,sous_dir_status,NULL,current_dir);

                    //Ajout
                    test_add_dir=add_dir_to_sub(new_dir,dir_sub,current_dir);

                    if(test_add_dir==0)
                    {
                        printf("Vous avez creer le dossier %s dans le dossier %s", new_dir->name, current_dir->name);
                    }
                    else
                    {
                        printf("Echec creation dossier");

                    }

                    break;
                case 3 :
                    printf("Vous avez choisi d\'aller dans un sous-repertoire.\n");

                    if(current_dir->sub == NULL)
                        printf("Ce repertoire est vide\n\n");

                    else{
                    print_tree(current_node);
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
                    }
                    break;
                case 4 :
                    printf("Vous avez choisi de retourner a la racine.\n");

                    current_dir=dirRacine;
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

