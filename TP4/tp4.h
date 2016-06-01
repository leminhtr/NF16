#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

typedef struct dir{
    char* name;
    int status;
    struct node* sub;
}Dir;

typedef struct node{
    Dir* dir;
    struct node* lc;
    struct node* rc;
}Node;

Dir* create_dir(char* name, int status, Node* sub);
Node* create_node(Dir* dir, Node* lc, Node* rc);
Dir* search_dir(char* name, Node* sub);

#endif // TP4_H_INCLUDED
