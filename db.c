#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "db_functions.h"
#include "print_functions.h"


int main(int argc, char *argv[]){
  if (argc < 2){
    puts("Usage: db [FILE]");
    return -1;
  }
  print_welcome();  
  readDatabase(argv[1]);
  int choice = -1;
  while(choice != 0){
    print_menu_choice();
    scanf("%d", &choice);
    while(getchar() != '\n'); // Clear stdin
 
    switch(choice){
    case 1:
      // Query
      query();
      break;

    case 2:
      // Update
      update_entry();
      break;

    case 3:
      // Insert
      new_entry();
      break;

    case 4:
      // Delete
      delete_entry();
      break;

    case 5:
      // Print database
      print_database();
      break;
    case 0:
      // Exit
      puts("Good bye!");
      break;
    default:
      // Please try again
      puts("Could not parse choice! Please try again");
    }
    puts("");
  }

  return 0;
}
