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
