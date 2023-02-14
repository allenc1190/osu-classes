/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Allen Chan
 * Email: chanall@oregonstate.edu
 */

#include <stdlib.h>
#include <stdio.h>

#include "bst.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node {
  int key;
  void* value;
  struct bst_node* left;
  struct bst_node* right;
};


/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst {
  struct bst_node* root;
};

/*
 * This function should allocate and initialize a new, empty, BST and return
 * a pointer to it.
 */
struct bst* bst_create() {
  struct bst* bst = malloc(sizeof(bst));
  bst->root = NULL;

  return bst;
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void delete(struct bst_node* node){
  if(node != NULL){
    delete(node->left);
    delete(node->right);
    free(node);
  }
}

void bst_free(struct bst* bst) {
  struct bst_node* tree = bst->root;
  delete(tree);
  free(bst);
  
  return;
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int count = 0;
int count_size(struct bst_node* node){
  //if(count > 13) {
  //  count = 1;
  //}

  if(node == NULL){
    return count;
  }
  //printf("node->key = %d\n", node->key);
  count_size(node->left);
  count++;
  //printf("node->key = %d\n", node->key);
  count_size(node->right);
  
  return count;
}

int bst_size(struct bst* bst) {
  count = 0;
  int c = count_size(bst->root);
  return c;
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */

struct bst_node* bst2(void* value, int key) {
    struct bst_node* bst2 = malloc(sizeof(struct bst_node));

    bst2->left = NULL;
    bst2->right = NULL;
    bst2->key = key;
    bst2->value = value;

    return bst2;
}

void bst_insert(struct bst* bst, int key, void* value) {
 // struct bst_node* curr = bst->root;
  /*if(bst->root == NULL){
    bst->root = malloc(sizeof(struct bst_node));
    bst->root->key = key;
    bst->root->value = value;
    bst->root->left = NULL;
    bst->root->right = NULL;
  }*/

  struct bst_node* curr = bst->root;
  struct bst_node* pre_curr = NULL;

  while(curr != NULL) {
    pre_curr = curr;
    if(curr->key > key) {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }
  }

  if(pre_curr == NULL) {
    bst->root = bst2(value, key);
  }
  else if(pre_curr->key < key){
    pre_curr->right = bst2(value, key);
  }
  else{
    pre_curr->left = bst2(value, key);
  }

  /*struct bst_node* curr = bst->root;
  //printf("curr->key = %d\n", curr->key);
  while(curr != NULL){
    if(curr->key < key){
      if(curr->right == NULL){
        struct bst_node* node = malloc(sizeof(struct bst_node));
        node->key = key;
        node->value = value;
        curr->right = node;

        node->left = NULL;
        node->right = NULL;
        //printf("curr_>key = %d\n", node->key);
        break;
      }
      else{
        curr = curr->right;
      }
    }
    else{
      if(curr->left == NULL){
        struct bst_node* node = malloc(sizeof(struct bst_node));
        node->key = key;
        node->value = value;
        curr->left = node;

        node->left = NULL;
        node->right = NULL;
        break;
      }
      else{
        curr = curr->left;
      }
    }
  }*/


  return;
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */

struct bst_node* find(struct bst* bst, int key){
  struct bst_node* curr = bst->root;
  struct bst_node* parent = NULL;

  while(curr != NULL){
    if(curr->key > key){
      parent = curr;
      curr = curr->left;
    }
    else if(curr->key < key){
      parent = curr;
      curr = curr->right;
    }
    if(curr->key == key){
      if(parent == NULL)
        parent = curr;
      return parent;
    }
  }
  printf("missing node\n");
}

/*struct bst_node* min(struct bst_node* node){
  struct bst_node* curr = node;

  while(curr->left != NULL){
    curr = curr->left;
  }
  return curr;
}*/

/*struct bst_node* find_bst(struct bst* bst, int key){
  struct bst_node* curr = bst->root;

  while(curr != NULL){

  }
}*/

/*int suc = 0;
struct bst_node* inorder(struct bst* bst, struct bst_node* node, int key){
  struct bst* baby_bst = NULL;
  struct bst_node* curr = bst->root;

  printf("key = %d\n", key);
  while(curr->key != key){
    printf("curr = %d\n", curr->key);
    if(curr->key < key){
      inorder(bst, curr->right;
    }
    else if(curr->key > key) {
      curr = curr->left;
    } else { //if(key == key)
      curr = NULL;
    }
    
  }
  baby_bst->root = curr;
  while(curr->left != NULL && curr->right != NULL){

  }
  printf("curr key after = %d\n", curr->key);
  return curr;
  
/*if(node != NULL){
  printf("node1 = %d\n", node->key);
    inorder(node->left, key);
    if(node->key == key){
      printf("insdie 1\n");
        suc = 1;
      //return node->right;
    }
    if(suc == 1)
      printf("inside loop\n");
      printf("node = %d\n", node->key);
      return node;
    inorder(node->right, key);
  }*/

//}

/*struct bst_node* search(struct bst* bst, struct bst_node* node){

  struct bst_node* curr = bst->root;

  while(curr != NULL){ 
    if(node->key > curr->key){
      curr = curr->right;
    }
    else if(node->key < curr->key){
      curr = curr->right;
    }
    if(node->key == curr->key){
      return curr;
    }
  }*/

  /*struct bst_node* curr = bst->root;

  while(curr != NULL){
    if(node->key == curr->key){
      return 1;
    }
    else if(node->key < curr->key){
      curr = curr->left;
    }
    else if(node->key > curr->key){
      curr = curr->right;
    }
  }
  return 0;*/
//}

int find_min(struct bst_node* curr) {
  while(curr->left != NULL) {
    curr = curr->left;
  }

  return curr->key;
}

/*struct bst_node* struct_bst_remove(struct bst_node* curr, int key) {
  
    if(curr == NULL) {
      curr = NULL;  
    }
    else if(curr->key < key) {
      struct_bst_remove(curr->right, key);
    } else if(curr->key > key) {
      struct_bst_remove(curr->left, key);
    } else { //if(curr->key == key)
      if(curr->left != NULL && curr->right != NULL) {
        curr->key = find_min(curr->right);
        curr->right = struct_bst_remove(curr->right, curr->key);
        return curr;
      } else if(curr->left != NULL) {
        struct bst_node* rest = curr->left;
        return rest;
      } else if(curr->right != NULL) {
        struct bst_node* rest = curr->right;
        return rest;
      } else {
        return NULL;
      }
    }
}*/

struct bst_node* remove_node(struct bst_node* curr, int key) {
  if(curr == NULL) {
    return NULL;
  }
  else if(curr->key > key){
    curr->left = remove_node(curr->left, key);
    return curr;
  }
  else if(curr->key < key){
    curr->right = remove_node(curr->right, key);
    return curr;
  }
  else{
    if(curr->right != NULL && curr->left != NULL){
      curr->key = find_min(curr->right);
      curr->right = remove_node(curr->right, curr->key);
      return curr;
    }
    else if(curr->left != NULL){
      struct bst_node* rest = curr->left;
      free(curr);
      return rest;
    }
    else if(curr->right != NULL){
      struct bst_node* rest = curr->right;
      free(curr);
      return rest;
    }
    else{
      free(curr);
      return NULL;
    }
  }
}

void bst_remove(struct bst* bst, int key) {
  bst->root = remove_node(bst->root, key); 
}

  /*struct bst_node* s_parent = NULL;
  struct bst_node* parent = NULL;
  struct bst_node* curr = bst->root;
  struct bst_node* node = NULL;

  printf("now removing %d\n",key);

  parent = find(bst, key);
  printf("parent->key = %d\nparent->left = %d\nparent->right = %d\n", parent->key, parent->left->key, parent->right->key);
  
  if(parent->left == NULL){
    printf("Testing\n"); 
    curr = parent->right;
  }
  else if(parent->right == NULL){
    printf("Testing2\n");
    curr = parent->left;
  }
  else if(parent->right != NULL && parent->left != NULL){
    printf("Testing3\n");
    if(parent->left->key == key){
      printf("Testing4\n");
      curr = parent->left;
      printf("TESTING6\n");
    }
    else{
      printf("Testing5\n");
      curr = parent->right;
    }
  }

  if(curr->left == NULL && curr->right == NULL){
    if(parent->left == curr){
      parent->left = NULL;
    }
    else if(parent->right == curr){
      parent->right = NULL;
    }
    //parent->right = NULL;
    //parent->left = NULL;
  }
  else if(curr->left == NULL && curr->right != NULL){
    parent->right = curr->right;
  }
  else if(curr->left != NULL && curr->right == NULL){
    parent->left = curr->left;
  }

  else{
      struct bst_node* s_parent = NULL;
      
      node = inorder(bst, bst->root, key);

      if (node==NULL){
        printf("node Null\n");
      }

      //printf("node->key = %d\n", node->key);
      s_parent = find(bst, node->key);
      curr->left = node->left;
      printf("node->key = %d\n", node->key);
      printf("curr->right->key = %d\n", curr->right->key);
      printf("s_parent = %d\n", s_parent->key);

      if(node->key != curr->right->key){
        printf("CHECK\n");
        node->right = s_parent->left;
        curr->right = node->right;
        printf("CHECK3");
      }

      printf("CHECK2");
      parent->left = node->right;
      free(node);

  }
 
  return;
}*/

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key) {
  struct bst_node* curr = bst->root;

  while(curr) {
    if(curr->key == key) {
      return curr->value;
    }
    else if(curr->key < key) {
      curr = curr->right;
    }
    else if(curr->key > key) {
      curr = curr->left;
    } 
  }
  
  return NULL;
}
