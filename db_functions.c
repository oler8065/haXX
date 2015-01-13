#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"
#include "print_functions.h"

typedef struct tree{
  char * key;
  char * value;
  struct tree * left;
  struct tree * right;
} Tree;

//Types
char buffer[128];
int found;
int dupecheck;
Tree * cursor;
Tree * treeRoot = NULL;

void readline(char * dest, int n, FILE * source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}


Tree * newNode(char * key, char * value){
  if(key == NULL && value == NULL){
    return NULL;
  }
  Tree * new = (struct tree*)malloc(sizeof(struct tree));

  new->key = (char*)malloc(strlen(key) + 1);
  strcpy(new->key, key);
  new->value = (char*)malloc(strlen(value) + 1);
  strcpy(new->value, value);
  new->right = NULL;
  new->left = NULL;
  
  return new;
}

void treeInsert(Tree ** tree, Tree * node){  
  if(*tree == NULL) {
    *tree = node;
    return;

  }else{
    if(strcmp(node->key, (*tree)->key)  < 0){
      treeInsert(&(*tree)->left, node);

    }else{
      treeInsert(&(*tree)->right, node);
    }
  }
}

void * initTree(char * db){
  char * filename = db;
  printf("Loading database \"%s\"...\n\n", filename);
  FILE * database = fopen(filename, "r");
  Tree * newTree;
  newTree = NULL;
  char key[128];
  char value[128];  

  while(!feof(database)){     
    readline(key, 128, database);
    readline(value, 128, database);
     
    if((key[0] != '\0') && (value[0] != '\0')){
      Tree * treeNode = newNode(key, value);
      treeInsert(&newTree, treeNode);
    }
  }  
  treeRoot = newTree;
  fclose(database);
  return treeRoot; 
}

void startprocedure(int choice) {
  if (choice == 0) {
    printf("Enter key: ");
    readline(buffer, 128, stdin);
    puts("\nSearching database...\n");
    found = 0;
    cursor = treeRoot;

  }else{
    printf("Enter key: ");
    readline(buffer, 128, stdin);
    puts("\nSearching database for duplicate keys...\n");
    found = 0;
    cursor = treeRoot;
  }
}


Tree * searchKey(Tree ** tree, char * key){
  cursor = *tree;

  if(cursor == NULL){
    return NULL;

  }else{ 
    if(strcmp(key, cursor->key) == 0){      
      
    }else if(strcmp(key, cursor->key) < 0){
      searchKey(&(cursor->left), key);
     
    }else{
      searchKey(&(cursor->right), key); 
    }
  }
  return cursor;
}

void searchDuplicate(Tree ** tree, char * key){
  cursor = *tree;
  
  if(cursor == NULL){
    dupecheck = 0;

  }else{
    if(strcmp(key, cursor->key) == 0){
      dupecheck = 1;

    }else if(strcmp(key, cursor->key) < 0){
      searchDuplicate(&(cursor->left), key);

    }else{
      searchDuplicate(&(cursor->right), key); 
    }
  }
}

void query(){
  startprocedure(0);
  char * tempKey = malloc(strlen(buffer) + 1);
  strcpy(tempKey, buffer);  
  Tree * Node = searchKey(&treeRoot, tempKey);
   
  if(Node != NULL){
    printNode(Node);
    
  }else{
    puts("Key not found in database!\n");
  }
  free(tempKey);
}

void update_entry(){
  startprocedure(0);
  char * tempKey = malloc(strlen(buffer) + 1);
  strcpy(tempKey, buffer);
  Tree * Node = searchKey(&treeRoot, tempKey);
  
  if(Node != NULL){
    printf("Enter new value to insert:\n");
    readline(buffer, 128, stdin);
    char * tempValue = malloc(strlen(buffer) + 1);
    strcpy(tempValue, buffer);
    strcpy(Node->value, tempValue);
    printf("Entry updated: \n");
    printNode(Node);
    free(tempValue);

  }else{
    puts("Key not found in database!\n");
  }
  free(tempKey);
}



void new_entry(){  
  startprocedure(1);
  char * tempKey = malloc(strlen(buffer) + 1);
  strcpy(tempKey, buffer);
  searchDuplicate(&treeRoot, tempKey);

  if(dupecheck == 1){
    printf("key \"%s\" already exists!\n", buffer);
 
  }else{
    printf("Enter value: ");
    readline(buffer, 128, stdin);
    char * tempVal = malloc(strlen(buffer) + 1);
    strcpy(tempVal, buffer);
    Tree * insertNode = newNode(tempKey, tempVal);
    treeInsert(&treeRoot, insertNode);
    
    printf("Key: %s with value: %s added to database\n", tempKey, tempVal);
    free(tempVal);
  }
  free(tempKey); 
}    

Tree * findMinNode(Tree * tree){
  Tree * cursor = tree;
  
  while(cursor->left != NULL){
    cursor = cursor->left;
  }
  return cursor;
}

Tree * deleteNode(Tree * tree, char * key){
  if(tree == NULL) return tree;

  if(strcmp(key, tree->key) < 0){
    tree->left = deleteNode(tree->left, key);
  }
  
  else if(strcmp(key, tree->key) > 0){
    tree->right = deleteNode(tree->right, key);
  }

  else{
    if (tree->left == NULL){
      Tree * temp = tree->right;
      return temp;
      
    }else if(tree->right == NULL){
      Tree * temp = tree->left;
      return temp;      
    }
    
    Tree * temp = findMinNode(tree->right);
    tree->key = temp->key;
    tree->value = temp->value;
    tree->right = deleteNode(tree->right, temp->key);    
  }
  return tree;
}

void delete_entry(){
  startprocedure(0);
  char * tempKey = malloc(strlen(buffer) + 1);
  strcpy(tempKey, buffer);
  Tree * temp = searchKey(&treeRoot, tempKey);
  
  if(temp != NULL){
    treeRoot = deleteNode(treeRoot, tempKey);
    puts("Database entry deleted\n");

  }else{
    puts("Key not found in database!\n");
  }
  free(tempKey);
}

void freeNode(Tree * node){
  free(node->key);
  free(node->value);
  free(node);
}

void cleanMemory(Tree * tree){
  if(tree == NULL){
    return;

  }else{
    cleanMemory(tree->left);
    cleanMemory(tree->right);
  }
  freeNode(tree);
  return;
}

void print_database(){
  printTree(treeRoot);
}

void printNode(Tree * node){ 
  printf("Value: %s Key: %s\n", node->value, node->key);
}

void printTree(Tree * tree){
  if(tree == NULL){
    return;
  
  }else{
    printTree(tree->left);
    printf("%s %s\n",(char *)tree->value,(char *)tree->key);
    printTree(tree->right);
  }
  return;
}

void exit_process(){
  cleanMemory(treeRoot);
}
