#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"

Dir* create_dir(char* name, int status, Node* sub){
    Dir* newDir=malloc(sizeof(Dir));
    newDir->name=malloc(sizeof(char)*strlen(name));

    strcpy(newDir->name,name);
    newDir->status=status;
    newDir->sub=sub;
    return newDir;
}

Node* create_node(Dir* dir, Node* lc, Node* rc){
    Node* newNode=malloc(sizeof(Node));

    newNode->dir=dir;
    newNode->lc=lc;
    newNode->rc=rc;
    return newNode;
}

int add_dir_to_sub(Dir *dir, Node **sub){

    int comp, comp_left, comp_right;

    if(dir==NULL)   //argument NULL
        return -1;

    if(sub==NULL)
    {
        (*sub)->dir=dir;
        return 0;
    }

    comp=strcmp((*sub)->dir->name, dir->name);
    comp_left=strcmp((*sub)->lc->dir->name, dir->name);
    comp_right=strcmp((*sub)->rc->dir->name, dir->name);


    if(comp>0)  //sub>dir
    {
        if((*sub)->lc==NULL) //fils gauche dispo
        {
            (*sub)->lc->dir=dir;
            return 0;
        }
        else    //fils gauche non libre => ajout fils gauche (récursif)
            return add_dir_to_sub(dir, (*sub)->dir->sub->lc);
    }

    if(comp<0)  //sub<dir
    {
        if((*sub)->rc==NULL) //fils droit dispo
        {
            (*sub)->rc->dir=dir;
            return 0;
        }
        else    //fils droit non libre => ajout fils droit (récursif)
            return add_dir_to_sub(dir, (*sub)->dir->sub->rc);
    }

    if(comp==0 || comp_left==0 || comp_right==0)    //dir existe déjà
        return -1;
}



