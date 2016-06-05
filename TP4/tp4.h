#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

#define DMAX 50

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
int add_dir_to_sub(Dir *dir, Node *sub, Dir *father);

Dir* search_dir(char* name, Node* sub);
void print_tree(Node* sub);
int print_path(Dir *dir);

#endif // TP4_H_INCLUDED
