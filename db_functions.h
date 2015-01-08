#ifndef __db_functions_h
#define __db_functions_h

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

typedef struct tree Tree;


Tree *newNode(char *key, char *value);

Tree * treeInsert (Tree * node, Tree * tree);

void initTree (char *db);

void readDatabase(char *db);

void readline(char *dest, int n, FILE *source);

void startprocedure(int choice);

void query();

void update_entry();

void new_entry();

void delete_entry();

void printTree(Tree* tree);

void print_database();

#endif
