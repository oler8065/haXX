#include <stdio.h>x
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"


// Types
char buffer[128];
Node list = NULL;
int found;
Node cursor;


void readDatabase (char *db){
// Read the input file
char *filename = db;
printf("Loading database \"%s\"...\n\n", filename);
 FILE *database = fopen(filename, "r");

 while(!(feof(database))){
   Node newNode = malloc(sizeof(struct node));
   readline(buffer, 128, database);
   newNode->key = malloc(strlen(buffer) + 1);
   strcpy(newNode->key, buffer);
   readline(buffer, 128, database);
   newNode->value = malloc(strlen(buffer) + 1);
   strcpy(newNode->value, buffer);
   newNode->next = list;
   list = newNode;
 }
}

void readline(char *dest, int n, FILE *source){
  fgets(dest, n, source);
  int len = strlen(dest);
  if(dest[len-1] == '\n')
    dest[len-1] = '\0';
}

void startprocedure(int choice) {
  if (choice == 0) {
    printf("Enter key: ");
    readline(buffer, 128, stdin);
    puts("Searching database...\n");
    found = 0;
    cursor = list;
  }else{
    // new entry case
    printf("Enter key: ");
    readline(buffer, 128, stdin);
    puts("Searching database for duplicate keys...");
    found = 0;
    cursor = list;
  }
}

void query()
{  
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
}

void update_entry()
{
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

}

void new_entry()
{
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
}

void delete_entry()
{
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

}

void print_database()
{
  cursor = list;
  while(cursor != NULL){
    puts(cursor->key);
    puts(cursor->value);
    cursor = cursor->next;
  }

}
