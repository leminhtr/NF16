#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

typedef struct dir{
    char* name;
    int status;
    struct node* sub;
    struct dir* father;
}Dir;

typedef struct node{
    Dir* dir;
    struct node* lc;
    struct node* rc;
}Node;

Dir* create_dir(char* name, int status, Node* sub, Dir* father);
Node* create_node(Dir* dir, Node* lc, Node* rc);
Dir* search_dir(char* name, Node* sub);
void print_tree(Node* sub);

#endif // TP4_H_INCLUDED
