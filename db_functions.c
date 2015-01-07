#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"


typedef struct tree{
  char *key;
  char *value;
  struct tree *left;
  struct tree *right;
} Tree;


// Types
char buffer[128];
int found;
Tree * cursor;
Tree * treeRoot = NULL;


void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}



void printNode (Tree *node){
 
  printf("Value: %s Key: %s", node->value, node->key);


}

Tree *newNode(char *key, char *value){
  if(key == NULL && value == NULL){
    return NULL;
  }
  Tree * new = (struct tree*)malloc(sizeof(struct tree));

  new->key = (char*)malloc(strlen(key) + 1);
  new->key = key;
  new->value = (char*)malloc(strlen(value) + 1);
  new->value = value;
  new->right = NULL;
  new->left = NULL;
  
  printNode(new);
  return new;
}


void treeIns(Tree ** tree, Tree * node){
  if(*tree == NULL) {
    puts("1");
    *tree = node;
    return;
  }else if(strcmp(node->key, (*tree)->key)  < 0){
    puts("2");
    treeIns(&(*tree)->left, node);
  }
  else if(strcmp(node->key, (*tree)->key) >= 0){
    puts("3");
    treeIns(&(*tree)->right, node);
  }
}





Tree * treeInsert (Tree * node, Tree * tree){
  puts("Reached treeins");
  

 if(tree == NULL){
    puts("0");
    return node;

 }if(((strcmp(node->key, tree->key)) < 0) && tree->right == NULL){
   
    tree->right = node;
    puts("1");
    return tree;

 }if(((strcmp(node->key, tree->key)) < 0) && tree->right != NULL){
    treeInsert(node, tree->right);
    puts("2");
    return tree;
    

 }if(strcmp(node->key, tree->key) > 0 && tree->left == NULL){
    tree->left = node;
    puts("3");
    return tree;
 }if(((strcmp(node->key, tree->key)) > 0) && tree->left != NULL){
    treeInsert(node, tree->left);
    puts("4");
    return tree;
  }
 puts("slutfall");
 printf("Value: %s Key: %s", tree->value, tree->key);

  return tree;
}

void initTree (char *db){

  char *filename = db;
  printf("Loading database \"%s\"...\n\n", filename);
  FILE *database = fopen(filename, "r");
  Tree * newTree;
  newTree = NULL;
  char key[128];
  char value[128];  

  while(!feof(database)){     
    readline(key, 128, database);
    readline(value, 128, database);
     
    if((key[0] != '\0') && (value[0] != '\0')){
      Tree * treeNode = newNode(key, value);
      printf("%p ", newTree);
      treeIns(&newTree, treeNode);
            puts("ballé");
    }
  }

  treeRoot = newTree;

}


void startprocedure(int choice) {
  if (choice == 0) {
    printf("Enter key: ");
    readline(buffer, 128, stdin);
    puts("Searching database...\n");
    found = 0;
    cursor = treeRoot;
  }else{
    // new entry case
    printf("Enter key: ");
    readline(buffer, 128, stdin);
    puts("Searching database for duplicate keys...");
    found = 0;
    cursor = treeRoot;
  }
}

void query(){

  puts("QUERY");
/*  
  startprocedure(0);
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Found entry:");
      printf("key: %s\nvalue: %s\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }
*/
}

void update_entry(){

  puts("UPDATE");

  /*

  startprocedure(0);
  while(!found && cursor != NULL){
    if(strcmp(buffer, cursor->key) == 0){
      puts("Matching entry found:");
      printf("key: %s\nvalue: %s\n\n", cursor->key, cursor->value);
      found = 1;
    }else{
      cursor = cursor->next;
    }
  }
  if(!found){
    printf("Could not find an entry matching key \"%s\"!\n", buffer);
  }else{
    printf("Enter new value: ");
    readline(buffer, 128, stdin);
    free(cursor->value);
    cursor->value = malloc(strlen(buffer) + 1);
    strcpy(cursor->value, buffer);
    puts("Value inserted successfully!");
  }
  */
}

void new_entry(){

  puts("NEW");

  /*
  startprocedure(1);
  while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          printf("key \"%s\" already exists!\n", cursor->key);
          found = 1;
        }else{
          cursor = cursor->next;
        }
      }
      if(!found){ // Insert new node to the front of the list
        puts("Key is unique!\n");
        Node newNode = malloc(sizeof(struct node));
        newNode->key = malloc(strlen(buffer) + 1);
        strcpy(newNode->key, buffer);
        printf("Enter value: ");
        readline(buffer, 128, stdin);
        newNode->value = malloc(strlen(buffer) + 1);
        strcpy(newNode->value, buffer);
        newNode->next = list;
        list = newNode;
        puts("");
        puts("Entry inserted successfully:");
        printf("key: %s\nvalue: %s\n", list->key, list->value);
      }
  */
}

void delete_entry(){

  puts("DELETE");

  /*

  startprocedure(0);
    Node prev = NULL;
      while(!found && cursor != NULL){
        if(strcmp(buffer, cursor->key) == 0){
          if(prev == NULL){ // Delete first node
            list = cursor->next;
          }else{
            prev->next = cursor->next;
          }
          found = 1;
          printf("Deleted the following entry:\nkey: %s\nvalue: %s\n", cursor->key, cursor->value);
        }else{
          prev = cursor;
          cursor = cursor->next;
        }
      }
      if(!found){
        printf("Could not find an entry matching key \"%s\"!\n", buffer);
      }
  */
}


void printTree(Tree* tree){

  if(tree == NULL){
    return;
  
  }else{
    printTree(tree->left);
    printf("%s %s",tree->value,tree->key);
    printTree(tree->right);
  }
  return;
}

void print_database(){

  printTree(treeRoot);

}
