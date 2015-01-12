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

//Types
char buffer[128];
int found;
int dupecheck;
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
  strcpy(new->key, key);
  new->value = (char*)malloc(strlen(value) + 1);
  strcpy(new->value, value);
  new->right = NULL;
  new->left = NULL;
  
  return new;
}

void treeIns(Tree ** tree, Tree * node){
  
  if(*tree == NULL) {
    *tree = node;
    return;

  }else{
    if(strcmp(node->key, (*tree)->key)  < 0){
      treeIns(&(*tree)->left, node);

    }else{
      treeIns(&(*tree)->right, node);
    }
  }
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
      treeIns(&newTree, treeNode);
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
    printf("Enter key: ");
    readline(buffer, 128, stdin);
    puts("Searching database for duplicate keys...");
    found = 0;
    cursor = treeRoot;
  }
}


Tree * searchKey (Tree ** tree, char * key){

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


void query(){

  startprocedure(0);
  char * tempKey = malloc(strlen(buffer) + 1);
  strcpy(tempKey, buffer);  
  Tree * Node = searchKey(&treeRoot, tempKey);
   
  if(Node != NULL){
    printNode(Node);
    
  }else{
    puts("Key not found in database!");
  }
  free(tempKey);
}

void update_entry(){

  startprocedure(0);
  char * tempKey = malloc(strlen(buffer) + 1);
  strcpy(tempKey, buffer);
  Tree * Node = searchKey(&treeRoot, tempKey);
  
  if(Node != NULL){
    printf("Enter new value to insert\n");
    readline(buffer, 128, stdin);
    char * tempValue = malloc(strlen(buffer) + 1);
    strcpy(tempValue, buffer);
    strcpy(Node->value, tempValue);
    printf("Value updated: ");
    printNode(Node);
    free(tempValue);

  }else{
    puts("Key not found in database!");
  }
  free(tempKey);

}

void searchDuplicate (Tree ** tree, char * key){

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
    printf("%s \n", tempKey);
    Tree * insertNode = newNode(tempKey, tempVal);
    treeIns(&treeRoot, insertNode);
    
    printf("Key: %s with value: %s added to database", tempKey, tempVal);
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

Tree * delNode(Tree * tree, char * key){

  if(tree == NULL) return tree;

  if(strcmp(key, tree->key) < 0){
    tree->left = delNode(tree->left, key);
  }
  
  else if(strcmp(key, tree->key) > 0){
    tree->right = delNode(tree->right, key);
  }

  else{

    if (tree->left == NULL){
      Tree * temp = tree->right;
      free(tree);
      return temp;
      
    }else if(tree->right == NULL){
      Tree * temp = tree->left;
      free(tree);
      return temp;      
    }
    
    Tree * temp = findMinNode(tree->right);
    tree->key = temp->key;
    tree->value = temp->value;
    tree->right = delNode(tree->right, temp->key);    
  }
  return tree;
}

void delete_entry(){

  startprocedure(0);
  char * tempKey = malloc(strlen(buffer) + 1);
  strcpy(tempKey, buffer);
  Tree * temp = searchKey(&treeRoot, tempKey);
  
  if(temp != NULL){
    delNode(treeRoot, tempKey);
    puts("Database entry deleted");

  }else{
    puts("Key not found in database!");
  }
  free(tempKey);
  //free(temp);
}


void printTree(Tree* tree){

  if(tree == NULL){
    return;
  
  }else{
    printTree(tree->left);
    printf("%s %s\n",(char *)tree->value,(char *)tree->key);
    printTree(tree->right);
  }
  return;
}

void print_database(){
  printTree(treeRoot);

}

void freeNode(Tree * node){
  free(node->key);
  free(node->value);
  free(node);
}

void cleanMemory(Tree ** tree){
  if ((*tree)->left != NULL){
    freeNode((*tree)->left);
    puts("1");
  }
  if ((*tree)->right != NULL){
    freeNode((*tree)->right);  
    puts("2");
  }
  freeNode(*tree);
  puts("3");
}
 
void exitProcedure(){

  cleanMemory(&treeRoot);
  puts("Memory cleared \n");

}
