#include "tp3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

T_Client *creerClient(char *nom, char *prenom, int age, int numero_chambre)
{
    T_Client *newClient=malloc(sizeof(T_Client));
    newClient->nom=malloc(sizeof(char)*(strlen(nom)+1));
    newClient->prenom=malloc(sizeof(char)*(strlen(prenom)+1));
    newClient->ville_site=malloc(sizeof(char)*(STRING_MAX));

    char *pos_n=NULL;
    pos_n = strchr(nom, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }
    pos_n = strchr(prenom, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }
    strcpy(newClient->nom, nom);
    strcpy(newClient->prenom, prenom);
    newClient->age=age;
    newClient->numero_chambre=numero_chambre;
    newClient->suivant=NULL;
    return newClient;
}

int print_available_room(T_Site *site)
{
    //================création client temp====================

    T_Client *temp=malloc(sizeof(T_Client));
    temp=site->premier;

    int tab_room[ROOM_MAX]={0};
    int i=0, j,k,boolean;

    if (temp==NULL)
        {
            printf("Toutes les chambres sont libres.\n");
            return 2;
        }
    
    while(temp!=NULL)           //recherche chambre non dispo
    {
        tab_room[i]=temp->numero_chambre;   //stockage dans tab
        temp=temp->suivant;
        i++;
    }
    printf("Le site dispose de %d chambre(s) libre(s).\n", ROOM_MAX-i);
    //i= nb client du site
    if(i==(ROOM_MAX))
        {
            printf("Desole, le site est complet pour le moment.\n");
            return 1;
        }
        
    for(k=1;k<=ROOM_MAX;k++) //dans le pire des cas([1;199]), il reste 1 place
    {
        boolean=1;
        for (j=0; j<i;j++)                      
        {
            if(tab_room[j]==k)  //chambre n°k dans site ?
                {
                    boolean=0;      //n°k non dispo
                    break;
                }
        }
    
        if(boolean==1)    //chambre n°k dispo
            {
                printf("Nous vons conseillons de reserver la chambre numero %d.\n", k);
                break;
            }
    }
    
    return 0;
}

int search_room_availability(T_Site *site, int numero_ch)
{
    //================création client temp====================

    T_Client *temp=malloc(sizeof(T_Client));
    temp->nom=malloc(sizeof(char)*(STRING_MAX));
    temp->prenom=malloc(sizeof(char)*(STRING_MAX));
    temp->ville_site=malloc(sizeof(char)*(STRING_MAX));
    
    temp=site->premier;

    while(temp!=NULL)
    {
        if(temp->numero_chambre==numero_ch)
            {
                printf("La chambre %d n'est pas disponible.\n", numero_ch);
                return 0;           //Chambre occupée
            }
            temp=temp->suivant;
    }
    printf("La chambre %d est disponible.\n", numero_ch);
    return 1;                   //Chambre libre
}

T_Site *creerSite(char *ville)
{
    T_Site *newSite=malloc(sizeof(T_Site));
    newSite->ville=malloc(sizeof(char)*(strlen(ville)+1));

    char *pos_n=NULL;
    pos_n = strchr(ville, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }
    strcpy(newSite->ville,ville);


    newSite->premier=NULL;
    return newSite;
}

T_Site *rechercherSite(T_Hotel *hotel, char *ville)
{
    //================création site temp====================
    T_Site *temp=malloc(sizeof(T_Site));
    temp->ville=malloc(sizeof(char)*(STRING_MAX));

    //================Recherche du site=====================
    temp=hotel->premier;

    char *pos_n=NULL;
    pos_n = strchr(ville, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }

    while(temp!=NULL)
    {
        if(strcmp(temp->ville,ville)==0)
            {
                return (temp);
            }
        temp=temp->suivant;
    }
    if(temp==NULL)
        {
            printf("Ce site n\'existe pas.\n");
            return (temp);
        }
}

T_Hotel *creerHotel(char *nom)
{
    T_Hotel *newHotel=malloc(sizeof(T_Hotel));
    newHotel->nom=malloc(sizeof(char)*(strlen(nom)+1));
    strcpy(newHotel->nom,nom);
    newHotel->premier=NULL;
    return newHotel;
}

int ajouterClient(T_Site *site, T_Client *client)
{
    if (client==NULL || site==NULL)
        return 0;

  //================création client predecesseur============

    T_Client *predecesseur=malloc(sizeof(T_Client));
    predecesseur->nom=malloc(sizeof(char)*(strlen(client->nom)+1));
    predecesseur->prenom=malloc(sizeof(char)*(strlen(client->prenom)+1));
    predecesseur->ville_site=malloc(sizeof(char)*(strlen(site->ville)+1));

    predecesseur=site->premier;

    //================création client temp====================

    T_Client *temp=malloc(sizeof(T_Client));
    temp->nom=malloc(sizeof(char)*(strlen(client->nom)+1));
    temp->prenom=malloc(sizeof(char)*(strlen(client->prenom)+1));
    temp->ville_site=malloc(sizeof(char)*(strlen(site->ville)+1));

    temp=site->premier;

    if (temp==NULL)
    {
        site->premier=client;
        strcpy(client->ville_site,site->ville);
    }
    else if((strcmp(client->nom,temp->nom)<0) ||((strcmp(client->nom,temp->nom)==0)&&(strcmp(client->prenom,temp->prenom)<=0)))
    {
        client->suivant=temp;
        site->premier=client;
        strcpy(client->ville_site,site->ville);
    }
    else
    {
        int bon_emplacement=0;
        while (temp!=NULL && !bon_emplacement)
        {
            if (strcmp(client->nom,temp->nom)<0)        //strcmp() <0 => str1<str2 (ordre trouvé !)
            {
                client->suivant=temp;
                predecesseur->suivant=client;
                strcpy(client->ville_site,site->ville);
                bon_emplacement=1;                     //
            }
            else if (strcmp(client->nom,temp->nom)==0)    // cas=0
            {
                while (temp!=NULL && !bon_emplacement)
                {
                    if (strcmp(client->prenom,temp->prenom)<=0) // strcmp() <=0 => str1<str2
                    {
                        client->suivant=temp;
                        predecesseur->suivant=client;
                        strcpy(client->ville_site,site->ville);
                        bon_emplacement=1;
                    }
                    else                                            // cas >0
                    {
                        predecesseur=temp;
                        temp=temp->suivant;
                        if(temp==NULL)
                        {
                            predecesseur->suivant=client;
                            strcpy(client->ville_site,site->ville);
                            bon_emplacement=1;
                        }
                        else if(strcmp(client->nom,temp->nom)!=0)
                        {
                            client->suivant=temp;
                            predecesseur->suivant=client;
                            strcpy(client->ville_site,site->ville);
                            bon_emplacement=1;
                        }
                    }
                }
            }
            else                                       //cas >0
            {
                predecesseur=temp;
                temp=temp->suivant;
                if(temp==NULL)
                {
                    predecesseur->suivant=client;
                    strcpy(client->ville_site,site->ville);
                    bon_emplacement=1;
                }
            }
        }
    }
    return 1;
}

int ajouterSite(T_Hotel *hotel, T_Site *site)
{

    if (hotel==NULL || site==NULL)
        return 0;

  //================création site predecesseur============

    T_Site *predecesseur=malloc(sizeof(T_Site));
    predecesseur->ville=malloc(sizeof(char)*(strlen(site->ville)+1));
    predecesseur=hotel->premier;

    //================création site temp====================

    T_Site *temp=malloc(sizeof(T_Site));
    temp->ville=malloc(sizeof(char)*(strlen(site->ville)+1));
    temp=hotel->premier;
    if (temp==NULL)
    {
        hotel->premier=site;
        return 1;
    }
    int meme_ville=-1;
    while(temp!=NULL && meme_ville!=0)
    {
        temp=temp->suivant;
        if (temp!=NULL)
        {
            meme_ville=strcmp(site->ville,temp->ville);
        }
    }
    if (temp!=NULL)
    {
        printf("Il y avait deja un site dans la ville de %s appartenant a cette chaine d'hotels\n", site->ville);
        return 0;
    }

    temp=hotel->premier;
    if((strcmp(site->ville,temp->ville)<0))
    {
        site->suivant=temp;
        hotel->premier=site;
    }
    else
    {
        int bon_emplacement=0;
        while (temp!=NULL && !bon_emplacement)
        {
            if (strcmp(site->ville,temp->ville)<0)        //strcmp() <0 => str1<str2 (ordre trouvé !)
            {
                site->suivant=temp;
                predecesseur->suivant=site;
                bon_emplacement=1;                     //
            }
            else                                       //cas >0
            {
                predecesseur=temp;
                temp=temp->suivant;
                if(temp==NULL)
                {
                    predecesseur->suivant=site;
                    bon_emplacement=1;
                }
            }
        }
    }
    return 1;
}

int supprimerClient(T_Site *site, char *nom, char *prenom)
{
    //================création client temp====================

    T_Client *temp=malloc(sizeof(T_Client));
    temp->nom=malloc(sizeof(char)*(STRING_MAX));
    temp->prenom=malloc(sizeof(char)*(STRING_MAX));
    temp->ville_site=malloc(sizeof(char)*(STRING_MAX));
    temp=site->premier;

    //================création client à libérer====================

    T_Client *lib=malloc(sizeof(T_Client));
    lib->nom=malloc(sizeof(char)*(STRING_MAX));
    lib->prenom=malloc(sizeof(char)*(STRING_MAX));
    lib->ville_site=malloc(sizeof(char)*(STRING_MAX));

    char *pos_n=NULL;
    pos_n = strchr(nom, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }
    pos_n = strchr(prenom, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }


    if (temp==NULL)
    {
        printf("Erreur : Le site ne contient aucun client, il est donc impossible de supprimer %s %s\n",nom,prenom);
        return 0;
    }
    else if(temp->suivant==NULL)
    {
        if(strcmp(temp->nom,nom)==0 && strcmp(temp->prenom,prenom)==0)
        {
            printf("%s %s a ete supprime de ce site qui est desormais vide\n",prenom,nom);
            free(temp->nom);
            free(temp->prenom);
            free(temp->ville_site);
            free(temp);
            site->premier=NULL;
            return 1;
        }
        else
        {
            printf("Erreur : %s %s ne fait pas partie du site, aucune action n'est effectuee\n",prenom,nom);
            return 0;
        }
    }
    else
    {
        if(strcmp(temp->nom,nom)==0 && strcmp(temp->prenom,prenom)==0)
        {
            printf("%s %s a ete supprime de ce site\n",prenom,nom);
            site->premier=temp->suivant;
            free(temp->nom);
            free(temp->prenom);
            free(temp->ville_site);
            free(temp);
            return 1;
        }
        while(temp->suivant!=NULL && ((strcmp(temp->suivant->nom,nom)!=0)||(strcmp(temp->suivant->prenom,prenom)!=0)))
            temp=temp->suivant;
        if(temp->suivant==NULL)
        {
            printf("Erreur : %s %s ne fait pas partie de ce site, aucune action n'est effectuee\n",prenom,nom);
            return 0;
        }
        else
        {
            printf("%s %s a ete supprime de ce site\n",prenom,nom);
            lib=temp->suivant;
            temp->suivant=temp->suivant->suivant;
            free(lib->nom);
            free(lib->prenom);
            free(lib->ville_site);
            free(lib);
            return 1;
        }
    }
}

int supprimerSite(T_Hotel *hotel, char *ville)
{
    //================création site temp====================

    T_Site *temp=malloc(sizeof(T_Site));
    temp->ville=malloc(sizeof(char)*(STRING_MAX));
    temp=hotel->premier;
    //================création site à libérer====================

    T_Site *lib=malloc(sizeof(T_Site));
    lib->ville=malloc(sizeof(char)*(STRING_MAX));

    char *pos_n=NULL;
    pos_n = strchr(ville, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }

    if (temp==NULL)
    {
        printf("Erreur : L'hotel %s ne contient aucun site, il est donc impossible de supprimer le site de %s\n",hotel->nom,ville);
        return 0;
    }
    else if(temp->suivant==NULL)
    {
        if(strcmp(temp->ville,ville)==0)
        {
            printf("Le site de %s a ete supprime de l'hotel %s qui ne comporte desormais plus de site\n",ville,hotel->nom);
            while(temp->premier!=NULL)
                supprimerClient(temp,temp->premier->nom,temp->premier->prenom);
            free(temp->ville);
            free(temp);
            hotel->premier=NULL;
            return 1;
        }
        else
        {
            printf("Erreur : Le site de %s ne fait pas partie de l'hotel %s, aucune action n'est effectuee\n",ville,hotel->nom);
            return 0;
        }
    }
    else
    {
        if(strcmp(temp->ville,ville)==0)
        {
            printf("Le site de %s a ete supprime de ce l'hotel %s\n",ville,hotel->nom);
            hotel->premier=temp->suivant;
            while(temp->premier!=NULL)
                supprimerClient(temp,temp->premier->nom,temp->premier->prenom);
            free(temp->ville);
            free(temp);
            return 1;
        }
        while(temp->suivant!=NULL && (strcmp(temp->suivant->ville,ville)!=0))
            temp=temp->suivant;
        if(temp->suivant==NULL)
        {
            printf("Erreur : Le site de %s ne fait pas partie de l'hotel %s, aucune action n'est effectuee\n",ville,hotel->nom);
            return 0;
        }
        else
        {
            printf("Le site de %s a ete supprime de l'hotel %s\n",ville,hotel->nom);
            lib=temp->suivant;
            temp->suivant=temp->suivant->suivant;
            while(lib->premier!=NULL)
                supprimerClient(lib,lib->premier->nom,lib->premier->prenom);
            free(lib->ville);
            free(lib);
            return 1;
        }
    }
}

void afficherHotel(T_Hotel *hotel)
{
    //================création site temp====================
    T_Site *temp=malloc(sizeof(T_Site));
    temp->ville=malloc(sizeof(char)*(STRING_MAX));

    temp=hotel->premier;

     //================création client temp_client====================
    T_Client *temp_client=malloc(sizeof(T_Client));



    int i=0;                            //compteur i

    if(temp==NULL)
    {
        printf("Erreur : Pas de site pour cette chaine d'hotel.\n");

    }
    else
    {
            temp_client=temp->premier;          //<=> hotel->premier->premier (1er client d'un site d'un hotel)
        //===========Comptage des clients de tous les sites d'un hotel================

        while(temp!=NULL)       //on parcourt tous les sites d'un hotel
        {
            i=0;                            //on réinitialise le compteur
            temp_client=temp->premier;
            while(temp_client!=NULL)      //on parcourt les clients d'un site
            {
                i++;
                temp_client=temp_client->suivant;       //client suivant du même site
            }
            temp->nombre_client=i;                  //on affecte le résultat trouvé
            temp=temp->suivant;                     //site suivant

        }

        //===========Affichage des sites d'un hotel===============

        temp=hotel->premier;
        printf("%-20s\tNombre de clients\n", "Nom");
        while(temp!=NULL)
        {
            printf("%-20s\t%d\n", temp->ville, temp->nombre_client);
            temp=temp->suivant;
        }
        printf("\n");
    }
}

void afficherSite(T_Site *site)
{

    //================création client temp====================

    T_Client *temp=malloc(sizeof(T_Client));
    temp->nom=malloc(sizeof(char)*(STRING_MAX+1));
    temp->prenom=malloc(sizeof(char)*(STRING_MAX+1));
    temp=site->premier;

    if(temp==NULL)
        {
            printf("Erreur : Pas de client pour ce site.\n");
        }
    else
    {
        printf("%-20s%-20s%s\t%s\n", "Nom", "Prenom", "Age", "Chambre");
        while(temp!=NULL)
        {
            printf("%-20s%-20s%d\t%d\n", temp->nom, temp->prenom, temp->age, temp->numero_chambre);
            temp=temp->suivant;
        }
        printf("\n");
    }
}

void rechercherClients(T_Hotel *hotel, char *critereNom)
{
    char *pos_n=NULL;
    pos_n = strchr(critereNom, '\n');       //On cherche l'adresse du caractère '\n' stocké par fgets
    if (pos_n != NULL) //
    {
        *pos_n = '\0';                      //On remplace à cette adresse par '\0'.
    }
    int lencritereNom=strlen(critereNom);

    //================création site temp====================
    T_Site *temp=malloc(sizeof(T_Site));
    temp->ville=malloc(sizeof(char)*(STRING_MAX));

    temp=hotel->premier;

    //================création site contenant client dans ordre alpha====================
    T_Site *site_client_alpha=malloc(sizeof(T_Site));
    site_client_alpha->ville=malloc(sizeof(char)*(STRING_MAX));        //pas besoin de la ville de site_client_alpha (liste temporaire)
    site_client_alpha->premier=NULL;

    //================création client temp_client====================
    T_Client *temp_client=malloc(sizeof(T_Client));
    temp_client->nom=malloc(sizeof(char)*(STRING_MAX));
    temp_client->prenom=malloc(sizeof(char)*(STRING_MAX));
    temp_client->ville_site=malloc(sizeof(char)*(STRING_MAX));

    if(temp==NULL)
    {
        printf("Erreur : Pas de site pour cette chaine d'hotel.\n");
    }
    else
    {

    temp_client=temp->premier;          //<=> hotel->premier->premier (1er client d'un site d'un hotel)

    while(temp!=NULL)                   //on parcourt tous les sites d'un hotel
    {
        temp_client=temp->premier;
        while(temp_client!=NULL)      //on parcourt les clients d'un site
        {
            if(strncmp(critereNom, temp_client->nom,lencritereNom)==0) //critereNom est sous-chaine de chaine du 1er au caractère n° lencritereNom
                {
                   //================création client temp_client_alpha====================
                    T_Client *temp_client_alpha=malloc(sizeof(T_Client));
                    temp_client_alpha->nom=malloc(sizeof(char)*(STRING_MAX));
                    temp_client_alpha->prenom=malloc(sizeof(char)*(STRING_MAX));
                    temp_client_alpha->ville_site=malloc(sizeof(char)*(STRING_MAX));

                    temp_client_alpha->suivant=NULL;
                    temp_client_alpha->nom=temp_client->nom;
                    temp_client_alpha->prenom=temp_client->prenom;
                    temp_client_alpha->age=temp_client->age;
                    temp_client_alpha->numero_chambre=temp_client->numero_chambre;
                    strcpy(temp_client_alpha->ville_site,temp_client->ville_site);
                    strcpy(site_client_alpha->ville, temp_client_alpha->ville_site);
                    ajouterClient(site_client_alpha, temp_client_alpha);
                }
            temp_client=temp_client->suivant;       //client suivant du même site
        }
        temp=temp->suivant;                     //site suivant
    }

    temp_client=NULL;
    temp_client=site_client_alpha->premier;

    if(temp_client==NULL)
        {
            printf("Erreur : Aucun client n'a un nom qui commence par %s\n", critereNom);
        }
    else
    {
        printf("%-20s%-20s%s\t%s\t\t%-20s\n", "Nom", "Prenom", "Age", "Chambre", "Ville");
        while(temp_client!=NULL)
        {
            printf("%-20s%-20s%d\t%d\t\t%-20s\n", temp_client->nom, temp_client->prenom, temp_client->age, 
                                                    temp_client->numero_chambre, temp_client->ville_site);
            temp_client=temp_client->suivant;
        }
        printf("\n");
    }

    }

    free(site_client_alpha->ville);     //liste site_client_alpha n'est plus nécessaire
    free(site_client_alpha);

}