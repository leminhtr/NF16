#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tp4.h"

Dir* create_dir(char* name, int status, Node* sub){
    Dir* newDir=malloc(sizeof(Dir));
    newDir->name=malloc(sizeof(char)*strlen(name));
    Node* newNode=malloc(sizeof(Node));

    strcpy(newDir->name,name);
    newDir->status=status;
    newNode=NULL;
    newDir->sub=newNode;
    return newDir;
}

Node* create_node(Dir* dir, Node* lc, Node* rc){
    Node* newNode=malloc(sizeof(Node));
    Dir* newDir=malloc(sizeof(Dir));
    Node* newlc=malloc(sizeof(Node));
    Node* newrc=malloc(sizeof(Node));

    newDir=NULL;
    newlc=NULL;
    newrc=NULL;

    newNode->dir=newDir;
    newNode->lc=newlc;
    newNode->rc=newrc;
    return newNode;
}


