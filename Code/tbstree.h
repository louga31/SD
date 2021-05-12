/*-----------------------------------------------------------------*/
/*
 Licence Informatique - Structures de données
 Mathias Paulin (Mathias.Paulin@irit.fr)
 
 Interface pour l'implantation du TAD ThreadedBinarySearchTree.

 */
/*-----------------------------------------------------------------*/
#ifndef __TBSTREE__H__
#define __TBSTREE__H__
#include <stdbool.h>

/*------------------------  TBSTreeType  -----------------------------*/

/** Opaque definition of the type BinaryTree */
typedef struct _tbstree ThreadedBinaryTree;
typedef ThreadedBinaryTree *ptrThreadedBinaryTree;


/*------------------------  BaseTBSTree  -----------------------------*/

/** Constructor : builds an empty BinarySearchTree
 */
ThreadedBinaryTree *tbstree_create();

/** Operator : is the tree empty ?
 * bstree_empty : BinarySearchTree -> boolean
 */
bool tbstree_empty(const ThreadedBinaryTree *t);

/** Operator : returns the value of the root of the tree.
 * @pre !bstree_empty(t)
 */
int tbstree_root(const ThreadedBinaryTree *t);

/** Operator : returns the left subtree.
 * @pre !bstree_empty(t)
 */
ThreadedBinaryTree *tbstree_left(const ThreadedBinaryTree *t);

/** Operator : returns the right subtree.
 * @pre !bstree_empty(t)
 */
ThreadedBinaryTree *tbstree_right(const ThreadedBinaryTree *t);

/** Operator : is the root of tree right threaded ?
 * @param t the tree to test
 * @return true if left child is a thread, false else
 */
bool tbstree_isleftthreaded(const ThreadedBinaryTree *t);

/** Operator : is the root of tree right threaded ?
 * @param t the tree to test
 * @return true if right child is a thread, false else
 */
bool tbstree_isrightthreaded(const ThreadedBinaryTree *t);


/*------------------------  TreeDictionary  -----------------------------*/

/** Constructor : add a new value to the BinarySearchTree.
 *
 * @param t
 * @param v
 */
void tbstree_add(ptrThreadedBinaryTree *t, int v);


/*------------------------  TreeVisitors  -----------------------------*/

/** Functor with user data to be used with the several visitors that can run on trees.
 *  This functor receive as argument subtree from which the root node must be processes and an opaque
 *  pointer to user provided data.
 */
typedef void(*OperateFunctor)(const ThreadedBinaryTree *, void *);

/** Depth first, infix visitor */
void tbstree_depth_infix(const ThreadedBinaryTree *t, OperateFunctor f, void *userData);
/** Depth first, prefix visitor */
void tbstree_depth_prefix(const ThreadedBinaryTree *t, OperateFunctor f, void *userData);
/** Inorder visitor that uses the tree's threads */
void tbstree_inorder(const ThreadedBinaryTree *t, OperateFunctor f, void *userData);

#endif /* __TBSTREE__H__ */
