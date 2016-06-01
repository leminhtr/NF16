#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main()
{
    //Node* noeud1=create_node();
    Dir* dirvoulu=create_dir("toto",1,NULL);
    Dir* dir1=create_dir("rbwegrh",1,NULL);
    Dir* dir2=create_dir("rbwegrh",1,NULL);
    Dir* dir3=create_dir("rbwegrh",1,NULL);
    Dir* dir4=create_dir("rbwegrh",1,NULL);
    Dir* dir5=create_dir("rbwegrh",1,NULL);
    Dir* dir6=create_dir("blabla",1,NULL);
    Node* node6=create_node(dir6,NULL,NULL);
    Node* node5=create_node(dir5,NULL,NULL);
    Node* node4=create_node(dir4,NULL,NULL);
    Node* node3=create_node(dir3,node6,NULL);
    Node* node2=create_node(dir2,node4,node5);
    Node* node1=create_node(dir1,node2,node3);
    printf("%s",node6->dir->name);
    //dirvoulu=search_dir("blabla",node1);
    printf("%s",dirvoulu->name);
    return 0;
}
