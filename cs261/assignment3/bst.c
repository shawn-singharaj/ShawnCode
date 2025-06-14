/*
 * This file is where you should implement your binary search tree.  It already
 * contains skeletons of the functions you need to implement (along with
 * documentation for each function).  Feel free to implement any additional
 * functions you might need.  Also, don't forget to include your name and
 * @oregonstate.edu email address below.
 *
 * Name: Shawn Singharaj
 * Email: singhars@oregonstate.edu
 */

#include <stdlib.h>

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
  struct bst* bst = (struct bst*) malloc(sizeof(struct bst));
  bst->root = NULL;
  return bst;
}

/*
Takes the bst root as a parameter to recursively free the left and right
subtrees node by node.
*/
void bst_free_node(struct bst_node* node) {
  if (node == NULL) {
      return;
  }

  // recursively free the left and right subtrees
  bst_free_node(node->left);
  bst_free_node(node->right);

  // free the current node
  free(node);
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
void bst_free(struct bst* bst) {
  bst_free_node(bst->root);
  free(bst);
  return;
}

/*
Takes the bst root as a parameter to traverse the whole tree using preorder and increments each time the function
is recursively called.
*/
int bst_traverse_size(struct bst_node* node) {
  if (node == NULL) {
    return 0;  
  }

  int size = 1;  // count the current node
  size += bst_traverse_size(node->left);   // traverse left subtree
  size += bst_traverse_size(node->right);  // traverse right subtree

  return size;
}


/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {

  return bst_traverse_size(bst->root);

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
void bst_insert(struct bst* bst, int key, void* value) {

  // allocate memory for new node leaf and set values to it
  struct bst_node* new_node = (struct bst_node*) malloc(sizeof(struct bst_node));

  new_node->key = key;
  new_node->value = value;
  new_node->left = NULL;
  new_node->right = NULL;

  // if the bst is null, set the new node as the root
  if(bst->root == NULL){
    bst->root = new_node;
    return;
  }

  
  struct bst_node* itr = bst->root;
  struct bst_node* par = NULL;

  // traverse through the tree 
  while(itr != NULL){
    par = itr;

    // if the key is less than the current node, go left
    if(key < itr->key){
      itr = itr->left;
    }
    // if the key is greater than the current node, go right
    else if(key > itr->key){
      itr = itr->right;
    }
  }

  // set the new node to the left or right of the found parent node
  if(key < par->key){
    par->left = new_node;
  }
  else{
    par->right = new_node;
  }

  return;
}

/*
Recursively traverse through the tree to find the indicated key passed an argument that then returns
the value it holds
*/
void* bst_traverse(struct bst_node* node, int key) {
  if (node == NULL) {
    return 0;  
  }

  // if current node matches the key, return that value
  if(node->key == key){
    return node->value;
  }

  // preorder traverse left subtree
  void* val = bst_traverse(node->left, key);   

  // if finds a value that matches, return it
  if (val != NULL) {
    return val;
  }

  // if the key is in the right subtree
  return bst_traverse(node->right, key); 
}


/*
Traverses to the key, passed as an argument, of choice using preorder and determines if it has
1, 2, or no children
*/
int identify_key(struct bst_node* node, int key){
  if(node == NULL){
    return 0;
  }

  // returns 1, 2, or 3 depending on if the node has no, one, or two children respectively
  if(node->key == key){
    if(node->right == NULL && node->left == NULL){
      return 1;
    }
    else if(node->right == NULL || node->left == NULL){
      return 2;
    }
    else if(node->right != NULL && node->left != NULL){
      return 3;
    }
  }

  // traverse left tree
  int left = identify_key(node->left, key);

  // if the key has been found
  if(left != 0){
    return left;
  }

  // traverse right tree
  return identify_key(node->right, key);
}

/*
Traverses to the selected key using the passed argument using preorder to find the leaf, then
frees the memory of the node
*/
int bst_remove_leaf(struct bst_node* node, int key){
  if(node == NULL){
    return 0;
  }

  // if node is on the right of the parent, free
  if(node->right != NULL && node->right->key == key){
    free(node->right);
    node->right = NULL;
  }

  // if node is on the left of the parent, free
  if(node->left != NULL && node->left->key == key){
    free(node->left);
    node->left = NULL;
  }

  // traverse left subtree
  int left = bst_remove_leaf(node->left, key);

  // if found match, break
  if(left != 0){
    return left;
  }

  // traverse right subtree if no match yet
  return bst_remove_leaf(node->right, key);
}

/*
Function takes in the root and returns the left most node of the subtree
*/
struct bst_node* find_min(struct bst_node* node) {
  // find the minimum node in a subtree
  while (node->left != NULL) {
      node = node->left;
  }
  return node;
}

/*
If the node is not a leaf, the function will traverse to the key that matches the parameter based on if
the key is less than the current key and removes it once the key is found. 
*/
struct bst_node* bst_remove_node(struct bst_node* node, int key){
  if(node == NULL){
    return 0;
  }

  // if argument is less, then go left
  if(key < node->key){
    node->left = bst_remove_node(node->left, key);
  }
  // if argument is greater, then go right
  else if(key > node->key){
    node->right = bst_remove_node(node->right, key);
  }
  else{ // if node has two children
    if (node->left != NULL && node->right != NULL) {
      struct bst_node* temp = find_min(node->right); // find left most node

      node->key = temp->key; // current node replaced by that node

      node->right = bst_remove_node(node->right, temp->key); // remove that node
    } 
    else {
        // node has only one child or no children
        struct bst_node* temp = node;
        if (node->left != NULL) {
            node = node->left;  // promote the left child
        } else {
            node = node->right;  // promote the right child 
        }
        free(temp);  // free the old node
    }
  }
return node;

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
void bst_remove(struct bst* bst, int key) {
  switch(identify_key(bst->root, key)){
    case 1:
      bst_remove_leaf(bst->root, key);
      break;
    case 2:
      bst_remove_node(bst->root, key);
      break;
    case 3:
      bst_remove_node(bst->root, key);
      break;
    default:
      break;    
  }
  return;
}

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

  return bst_traverse(bst->root, key);
}

/*****************************************************************************
 **
 ** BST puzzle functions
 **
 *****************************************************************************/

 /*
 Traverses the tree via preorder to find the lengths of each route of the tree and returns the longest path 
 */
int bst_height_helper(struct bst_node* bst){
  if(bst == NULL){
    return -1;
  }
  // if root has no children
  if(bst->left == NULL && bst->right == NULL){
    return 0;
  }

  // traverse each subtree
  int left_longest = bst_height_helper(bst->left);
  int right_longest = bst_height_helper(bst->right);
  
  // return the longest height + 1 for current node
  if(left_longest > right_longest){
    return 1 + left_longest;
  }
  else{
    return 1 + right_longest;
  }
}

/*
 * This function should return the height of a given BST, which is the maximum
 * depth of any node in the tree (i.e. the number of edges in the path from
 * the root to that node).  Note that the height of an empty tree is -1 by
 * convention.
 *
 * Params:
 *   bst - the BST whose height is to be computed
 *
 * Return:
 *   Should return the height of bst.
 */
 int bst_height(struct bst* bst) {
  return bst_height_helper(bst->root);
 }


 /*
 Uses the passed in root and the desired sum and the function traverses the tree via preorder to 
 find the sum of each path and returns if the user sum exists 
 */
int bst_sum_helper(struct bst_node* bst, int sum){
  if(bst == NULL){
    return 0;
  }

  // decrement sum by the key
  sum -= bst->key;

  // reach the end
  if(bst->left == NULL && bst->right == NULL){
    if(sum == 0){ // if the sum is decremented to end, return true
      return 1;
    }
    else{ // false
      return 0;
    }
  }

  return bst_sum_helper(bst->left, sum) || bst_sum_helper(bst->right, sum);
  
}


/*
 * This function should determine whether a specified value is a valid path
 * sum within a given BST.  In other words, this function should check whether
 * the given BST contains any path from the root to a leaf in which the keys
 * sum to the specified value.
 *
 * Params:
 *   bst - the BST whose paths sums to search
 *   sum - the value to search for among the path sums of `bst`
 *
 * Return:
 *   Should return 1 if `bst` contains any path from the root to a leaf in
 *   which the keys add up to `sum`.  Should return 0 otherwise.
 */
int bst_path_sum(struct bst* bst, int sum) {

  return bst_sum_helper(bst->root, sum);
}

/*
Traverses the tree and increments a sum that increments when the desired key falls between the lower
and upper bounds
*/
int bst_range_helper(struct bst_node* bst, int lower, int upper){
  if(bst == NULL){
    return 0;
  }
  
  int sum = 0;

  // if key is between the bounds, increment sum
  if(lower <= bst->key && bst->key <= upper){
    sum += bst->key;
  }

  // if the key is greater than the lower bound, increment the sum and go left
  if(lower < bst->key){
    sum += bst_range_helper(bst->left, lower, upper); 
  }
  if(upper > bst->key){
    sum += bst_range_helper(bst->right, lower, upper);

  }
  return sum;
  
}

/*
 * This function should compute a range sum in a given BST.  Specifically, it
 * should compute the sum of all keys in the BST between a given lower bound
 * and a given upper bound.  For full credit, you should not process any subtree
 * whose keys cannot be included in the range sum.
 *
 * Params:
 *   bst - the BST within which to compute a range sum
 *   lower - the lower bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *   upper - the upper bound of the range over which to compute a sum; this
 *     should be considered an *inclusive* bound; in other words a key that's
 *     equal to this bound should be included in the sum
 *
 * Return:
 *   Should return the sum of all keys in `bst` between `lower` and `upper`.
 */
int bst_range_sum(struct bst* bst, int lower, int upper) {

  return bst_range_helper(bst->root, lower, upper);
}