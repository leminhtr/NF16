#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main()
{
    //Node* noeud1=create_node();
    Dir* dirvoulu=create_dir("toto",1,NULL);
    Dir* dir1=create_dir("maurice",1,NULL);
    Dir* dir2=create_dir("guignol",1,NULL);
    Dir* dir3=create_dir("robert",1,NULL);
    Dir* dir4=create_dir("chantal",1,NULL);
    Dir* dir5=create_dir("keler",1,NULL);
    Dir* dir6=create_dir("olympe",1,NULL);
    Node* node6=create_node(dir6,NULL,NULL);
    Node* node5=create_node(dir5,NULL,NULL);
    Node* node4=create_node(dir4,NULL,NULL);
    Node* node3=create_node(dir3,node6,NULL);
    Node* node2=create_node(dir2,node4,node5);
    Node* node1=create_node(dir1,node2,node3);
    /*dirvoulu=search_dir("olympe",node1);
    if(dirvoulu!=NULL)
        printf("%s",dirvoulu->name);
    else
        printf("Ce dossier n'est pas présent parmi les sous-dossiers du dossier parent actuel");*/
    print_tree(node1);
    return 0;
}
