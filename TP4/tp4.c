#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"

Dir* create_dir(char* name, int status, Node* sub, Dir* father){
    Dir* newDir=malloc(sizeof(Dir));
    newDir->name=malloc(sizeof(char)*strlen(name));

    strcpy(newDir->name,name);
    newDir->status=status;
    newDir->sub=sub;
    newDir->father=father;
    return newDir;
}

Node* create_node(Dir* dir, Node* lc, Node* rc){
    Node* newNode=malloc(sizeof(Node));

    newNode->dir=dir;
    newNode->lc=lc;
    newNode->rc=rc;
    return newNode;
}

Dir* search_dir(char* name, Node* sub){
    if(sub==NULL){
        return NULL;
    }
    if(strcmp(sub->dir->name,name)==0){
        return sub->dir;
    }
    if(sub->rc!=NULL){
        if(strcmp(sub->dir->name,name)==-1){
            return search_dir(name,sub->rc);
        }
    }
    if(sub->lc!=NULL){
        if(strcmp(sub->dir->name,name)==1){
            return search_dir(name,sub->lc);
        }
    }
    return NULL;
}

void print_tree(Node* sub){
    if(sub->lc!=NULL)
        print_tree(sub->lc);
    if(sub->dir->status==1)
        printf("%s\n",sub->dir->name);
    if(sub->rc!=NULL)
        print_tree(sub->rc);
}

Dir *to_father_dir(Dir* dir){
    if(dir!=NULL){
        if(dir->father==NULL){
            printf("Ce repertoire n'a pas de repertoire parent ! Nous restons dans ce repertoire\n");
            return dir;
        }
        return dir->father;
    }
    printf("Ce repertoire n'existe pas\n");
    return NULL;
}

int add_dir_to_sub(Dir *dir, Node *sub, Dir *father){
    if(dir==NULL || father==NULL)   //argument NULL
    {
        printf("Erreur. Le dossier a ajoute ou le dossier pere n'existe pas.\n");
        return -1;
    }

    dir->father=father; //Lien avec le dossier père.

    if(sub->dir==NULL)   //aucun sous-dir
    {
        //Node *new_sub=create_node(dir,NULL, NULL);
        sub->dir=dir;
        printf("%s a ete ajoute au dossier %s.\n", dir->name, dir->father->name);
        return 0;
    }

    int comp;
    comp=strcmp(sub->dir->name, dir->name);

    if(comp>0)  //sub>dir
    {
        if(sub->lc==NULL) //fils gauche dispo
        {
            Node *lc=create_node(dir,NULL, NULL);
            sub->lc=lc;
            printf("%s a ete ajoute au dossier %s.\n", dir->name, dir->father->name);
            return 0;
        }
        else    //fils gauche non libre => ajout fils gauche (récursif)
        {
            return add_dir_to_sub(dir, sub->lc,sub->lc->dir);
        }
    }

    if(comp<0)  //sub<dir
    {
        if(sub->rc==NULL) //fils droit dispo
        {
            Node *rc=create_node(dir,NULL,NULL);
            sub->rc=rc;
            printf("%s a ete ajoute au dossier %s.\n", dir->name, dir->father->name);
            return 0;
        }
        else    //fils droit non libre => ajout fils droit (récursif)
        {
            return add_dir_to_sub(dir, sub->rc, sub->rc->dir);
        }

    }

    //comp_left=strcmp(sub->lc->dir->name, dir->name);
    //comp_right=strcmp(sub->rc->dir->name, dir->name);
    if(comp==0)    //dir existe déjà
    {
        printf("Ce dossier existe deja.\n");
        return -1;
    }


    return 0;
}

int print_path(Dir *dir)
{
    if(dir==NULL)
        return -1;
    int i=0;
    char *tab_absolute_dir_name[DMAX];
    Dir *temp_father=malloc(sizeof(Dir));	//temp directory
    temp_father=dir;

    while(temp_father!=NULL)    //stockage nom dossier de current à racine
    {
        tab_absolute_dir_name[i]=temp_father->name;
        temp_father=temp_father->father;
        i++;
    }

    i--;    //Annule dernier i++ en trop du while
    printf("Arborescence : ");
    while(i>=0)     //affichage nom dossier de racine à current (donc ordre décroissant du tableau)
    {
        printf("%s/", tab_absolute_dir_name[i]);
        i--;
    }
    printf("\n");
    return 0;
}
