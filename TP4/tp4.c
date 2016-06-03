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

int add_dir_to_sub(Dir *dir, Node **sub){
    if(dir==NULL)   //argument NULL

        return -1;

    if((*sub)->dir==NULL)   //aucun sous-dir
    {
        //printf("test");
        //Node *new_sub=create_node(dir,NULL, NULL);
        (*sub)->dir=dir;
        return 0;
    }

    int comp, comp_left, comp_right;
    comp=strcmp((*sub)->dir->name, dir->name);
    comp_left=strcmp((*sub)->lc->dir->name, dir->name);
    comp_right=strcmp((*sub)->rc->dir->name, dir->name);

    if(comp>0)  //sub>dir
    {
        if((*sub)->lc==NULL) //fils gauche NULL
        {
            Node *lc=create_node(dir,NULL, NULL);	//création du fils gauche puis ajout
            (*sub)->lc=lc;
            return 0;
        }
        else    //fils gauche non libre => ajout fils gauche (récursif)
        {
            Node **ptr_node_lc=&((*sub)->lc);	//Besoin argument type Node **
            return add_dir_to_sub(dir, ptr_node_lc);
        }
    }

    if(comp<0)  //sub<dir
    {
        if((*sub)->rc==NULL) //fils droit NULL
        {
            Node *rc=create_node(dir,NULL,NULL);	//création du fils droit puis ajout
            (*sub)->rc=rc;
            return 0;
        }
        else    //fils droit non libre => ajout fils droit (récursif)
        {
            Node **ptr_node_rc=&((*sub)->rc); 	//Besoin argument type Node **
            return add_dir_to_sub(dir, ptr_node_rc);
        }

    }

    if(comp==0 || comp_left==0 || comp_right==0)    //dir existe déjà
        return -1;

    return 0;
}

void print_path(Dir *dir)
{
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
    while(i!=0)     //affichage nom dossier de racine à current (donc ordre décroissant du tableau)
    {
        printf("%s/", tab_absolute_dir_name[i]);
        i--;
    }

}