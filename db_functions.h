#ifndef __db_functions_h
#define __db_functions_h

typedef struct tree Tree;

void readline(char * dest, int n, FILE * source);

Tree * newNode(char * key, char * value);

void treeInsert (Tree ** tree, Tree * node);

void * initTree (char *db);

void startprocedure(int choice);

Tree * searchKey(Tree ** tree, char * key);

void searchDuplicate(Tree ** tree, char * key);

void query();

void update_entry();

void new_entry();

Tree * findMinNode(Tree * tree);

Tree * deleteNode(Tree * tree, char * key);

void delete_entry();

void freeNode(Tree * node);

void cleanMemory(Tree * tree);

void exit_process();

void print_database();

void printNode(Tree * node);

void printTree(Tree * tree);

#endif
