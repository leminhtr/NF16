#include <stdio.h>
#include <stdlib.h>
#include "tp3.h"
#include <string.h>

int main()
{
	int choix, boolean=0;
	int numero_chambre=0;
	T_Hotel *ch_hotel;
	char site_ville[STRING_MAX]= {0}, nom[STRING_MAX]={0}, prenom[STRING_MAX]={0}, sub_string[STRING_MAX]={0};
	int age=0, test_ajout=0;

	while(1)
	{
        //================création site temp====================
        T_Site *temp_site=malloc(sizeof(T_Site));
        temp_site->ville=malloc(sizeof(char)*(STRING_MAX));

		if(boolean==0)		// choix 1,9
	    {
	    	printf("Selectionnez une option :\n");
			printf("1. Creer une chaine d\'hotels\n");
			printf("9. Quitter\n");

			scanf("%d", &choix);
	        getchar();


			switch(choix)
			{
	            case 1 :
	                printf("Vous avez choisi de creer une chaine d\'hotels.\n");
	                printf("Quel est le nom de la chaine d\'hotel ?\n");
	                char ch_hotel_nom[STRING_MAX];

	                fgets(ch_hotel_nom,STRING_MAX, stdin);

	                ch_hotel=creerHotel(ch_hotel_nom);
	                if(ch_hotel!=NULL)
	                	boolean=1;
	                break;

				case 9 :
						printf("Vous avez choisi de quitter.\n");
						exit(0);

				default :
						break;
			}
		}

		else		//choix 2-9
		{


			printf("Selectionnez une option :\n");
			printf("2. Ajouter un site a une chaine d\'hotels\n");
			printf("3. Ajouter une reservation dans un site\n");
			printf("4. Afficher les sites d\'une chaine d\'hotels\n");
			printf("5. Afficher les clients d\'un site\n");
			printf("6. Supprimer une reservation dans un site\n");
			printf("7. Supprimer un site\n");
			printf("8. Rechercher un client par son nom\n");
			printf("9. Quitter\n");

			scanf("%d", &choix);
			getchar();

		switch(choix)
		{
                case 2 :
                        printf("Vous avez choisi d\'ajouter un site a une chaine d\'hotels.\n");
                        printf("Quel est la ville du site ?\n");

                        fgets(site_ville,STRING_MAX,stdin);                 //saisie du site

                        if(site_ville!=NULL)
                            {
                                T_Site *Site=creerSite(site_ville);

                                if(Site!=NULL)                              //toutes les saisies sont ok
                                {
                                    test_ajout=ajouterSite(ch_hotel,Site);              //ajout du site a la chaine d'hotel
                                    if(test_ajout==0)
                                        printf("Erreur ajout du site\n");
                                }
                            }
                        break;

                case 3 :
                        printf("Vous avez choisi d\'ajouter une reservation dans un site.\n");
                        printf("Quel est la ville du site de la reservation ?\n");

                        fgets(site_ville,STRING_MAX,stdin);                                 //saisie du site voulu

                        if(site_ville!=NULL)
                            {   //================Recherche du site=====================
                                temp_site=rechercherSite(ch_hotel, site_ville);
                                if(temp_site==NULL)
                                    break;
                                
                                printf("Les chambres sont numerote de 1 a %d.\n", ROOM_MAX);
                                
                                int complet=print_available_room(temp_site);			//Quel chambre est dispo ?
								if (complet==1)											//site complet
									break;
								
								printf("Quel chambre voulez-vous prendre ?\n");
								scanf("%d", &numero_chambre);
								getchar();
								if(numero_chambre<=0 || numero_chambre>200)	//[1;200] ?
								{
									printf("Cette chambre n'existe pas.\n");
									break;
								}

								if (complet==0)                     //site non vide et non complet
								{
    								int dispo=search_room_availability(temp_site, numero_chambre);	//chambre déjà occupée ?
    								if (dispo==0)
    									break;
								}
                                //-------------------Création du client pour l'ajout-------------------
                                printf("Quel est le nom du client ?\n");
                                fgets(nom,STRING_MAX, stdin);                               //saisie nom client
                                if(nom!=NULL)
                                    {
                                        printf("Quel est le prenom du client ?\n");
                                        fgets(prenom,STRING_MAX,stdin);                     //saisie prenom client
                                        if(prenom!=NULL)
                                        {
                                            printf("Quel est l\'age du client ?\n");        //saisie age client
                                            scanf("%d", &age);
                                            getchar();
                                            if(age!=0)                                  //toutes les saisies sont ok
                                            {
                                                T_Client *new_client=creerClient(nom, prenom, age, numero_chambre); //creation du client
                                                if(new_client!=NULL)
                                                {
                                                    test_ajout=ajouterClient(temp_site, new_client);    //ajout de la reservation
                                                    if(test_ajout==0)
                                                        printf("Erreur ajout reservation.\n");
                                                    else
                                                        {
                                                            printf("Reservation reussie.\n");
                                                            numero_chambre++;
                                                        }
                                                }
                                                else
                                                {printf("Erreur creation client.\n");}
                                            }
                                            else
                                            {printf("Erreur saisie age.\n");}
                                        }
                                        else
                                        {printf("Erreur saisie prenom.\n");}
                                    }
                                    else
                                    {printf("Erreur saisie nom.\n");}
                            }
                            else
                            {printf("Erreur saisie ville du site.\n");}
                        break;

                case 4 :
                        printf("Vous avez choisi d\'afficher les sites de la chaine d\'hotels.\n");
                        afficherHotel(ch_hotel);
                        break;

                case 5 :
                        printf("Vous avez choisi d\'afficher les clients d\'un site.\n");
                        printf("Quel est la ville du site ?\n");

                        fgets(site_ville,STRING_MAX,stdin);                                 //saisie de la chaine d'hotel voulu
                        if(site_ville!=NULL)                                                //toutes les saisies sont ok
                                {
                                    //================Recherche du site=====================
                                    temp_site=rechercherSite(ch_hotel,site_ville);
                                    if(temp_site!=NULL)
                                        afficherSite(temp_site);
                                }
                        break;

                case 6 :


                        printf("Vous avez choisi de supprimer une reservation dans un site.\n");
                        printf("Quel est la ville du site de la reservation ?\n");

                        fgets(site_ville,STRING_MAX,stdin);

                        if(site_ville!=NULL)
                        {
                            //================Recherche du site=====================
                            temp_site=rechercherSite(ch_hotel,site_ville);
                            if(temp_site==NULL)
                                break;

                            printf("Quel est le nom de la personne à annuler la reservation ?\n");
                            fgets(nom,STRING_MAX,stdin);

                            if(nom!=NULL)
                            {
                                printf("Quel est le prenom de la personne à annuler la reservation ?\n");
                                fgets(prenom,STRING_MAX,stdin);
                                if(prenom!=NULL)                                                            //toutes les saisies sont ok
                                {
                                    test_ajout=supprimerClient(temp_site, nom, prenom);
                                    if(test_ajout==0)
                                        printf("Erreur suppresion.\n");
                                }
                            }
                        }
                        break;

                case 7 :
                        printf("Vous avez choisi de supprimer un site appartenant a une chaine d\'hotel.\n");

                        if(ch_hotel!=NULL)
                        {
                            printf("Quel est la ville du site ?\n");
                            fgets(site_ville,STRING_MAX,stdin);
                            if(site_ville!=NULL)                                    //toutes les saisies sont ok
                            {
                                test_ajout=supprimerSite(ch_hotel, site_ville);
                                if(test_ajout==0)
                                    printf("Erreur suppresion.\n");
                            }

                        }
                        break;

                case 8 :
                        printf("Vous avez choisi de rechercher un client appartenant a une chaine d\'hotel.\n");
                        printf("Qui recherchez-vous ?\n");

                        fgets(sub_string, STRING_MAX, stdin);

                        if(sub_string!=NULL)
                        {
                            rechercherClients(ch_hotel,sub_string);
                        }
                        break;

                case 9 :
                        printf("Vous avez choisi de quitter.\n");
                        exit(0);

                default :
                        break;
		}

		}
	}
    return 0;
}