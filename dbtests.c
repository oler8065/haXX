#include "db_functions.h"
#include "CUnit/Basic.h"
#include <string.h>
#include <stdlib.h>


int init_suite1(void){
  
  return 0;
}

int clean_suite1(void){

  return 0;
}


void testnewNode(void){

  Tree * nodeCreate = newNode("Kalle", "11");
  CU_ASSERT(nodeCreate != NULL);
  Tree * nodeCreate1 = newNode("Hej", "1337");
  CU_ASSERT(nodeCreate1 != nodeCreate);

}

void testinitTree(void){

  Tree * database = initTree("SWE.db");
  CU_ASSERT(database != NULL);

}

void testtreeIns(void){

  puts("treeInsert\n");

  Tree * node = newNode("Kajsa", "12");
  Tree * tree = NULL;
  treeInsert(&tree, node);
  CU_ASSERT(tree == node);
}

void testQuery(void){

  Tree * tree = initTree("SWE.db");
  Tree * Node  = searchKey(&tree, "Anna");
  CU_ASSERT(Node != NULL); 
  Tree * Node1 = searchKey(&tree, "Robert");
  CU_ASSERT(Node1 == NULL);
}

void testdeleteNode(void){

  Tree * tree = initTree("SWE.db");
  deleteNode(tree, "Boris");
  Tree * node2 = searchKey(&tree, "Boris");
  CU_ASSERT(node2 == NULL);
}

void testupdateEntry(void){

  Tree * tree = initTree("SWE.db");
}  

void testcleanMemory(void){

  Tree * tree1 = initTree("SWE.db");
  Tree * tree2 = initTree("SWE.db");
  cleanMemory(tree1);
  CU_ASSERT(tree1 != tree2);
}


int main(){

   CU_pSuite pSuite = NULL;

   /* initialize the CUnit test registry */
   if (CUE_SUCCESS != CU_initialize_registry())
      return CU_get_error();

   /* add a suite to the registry */
   pSuite = CU_add_suite("Suite_1", init_suite1, clean_suite1);
   if (NULL == pSuite) {

      CU_cleanup_registry();
      return CU_get_error();
   }

   /* add the tests to the suite */
   /* NOTE - ORDER IS IMPORTANT - MUST TEST fread() AFTER fprintf() */
   if ((NULL == CU_add_test(pSuite, "test of newNode", testnewNode)) |
       (NULL == CU_add_test(pSuite, "test of initTree", testinitTree)) |
       (NULL == CU_add_test(pSuite, "test of tree ins", testtreeIns)) |
       (NULL == CU_add_test(pSuite, "test of query", testQuery)) |
       (NULL == CU_add_test(pSuite, "test of deleteNode", testdeleteNode)) |
       (NULL == CU_add_test(pSuite, "test of cleanmemory", testcleanMemory)))//|
       //       (NULL == CU_add_test(pSuite, "test of h_alloc_union()", test_h_alloc_union))


   {
      CU_cleanup_registry();
      return CU_get_error();
   }

   /* Run all tests using the CUnit Basic interface */
   CU_basic_set_mode(CU_BRM_VERBOSE);
   CU_basic_run_tests();
   CU_cleanup_registry();
   return CU_get_error();
}

