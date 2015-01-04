#ifndef __db_functions_h
#define __db_functions_h

typedef struct node{
  char *key;
  char *value;
  struct node *next;
} *Node;

void readDatabase(char *db);

void readline(char *dest, int n, FILE *source);

void startprocedure(int choice);

void query();

void update_entry();

void new_entry();

void delete_entry();

void print_database();

#endif
