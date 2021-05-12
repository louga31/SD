#include "tbstree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------  TBSTreeType  -----------------------------*/

struct _tbstree {
    // Links towards subtrees
    ThreadedBinaryTree *parent;
    ThreadedBinaryTree *left;
    ThreadedBinaryTree *right;
    // Key of the tree
    int root;
    // are the left and right pointers threads ?
    bool leftthread;
    bool rightthread;
};

/*------------------------  BaseTBSTree  -----------------------------*/

ThreadedBinaryTree *tbstree_create() {
    return NULL;
}


bool tbstree_empty(const ThreadedBinaryTree *t) {
    return t == NULL;
}

int tbstree_root(const ThreadedBinaryTree *t) {
    assert(!tbstree_empty(t));
    return t->root;
}

ThreadedBinaryTree *tbstree_left(const ThreadedBinaryTree *t) {
    assert(!tbstree_empty(t));
    return t->left;
}


ThreadedBinaryTree *tbstree_right(const ThreadedBinaryTree *t) {
    assert(!tbstree_empty(t));
    return t->right;
}

bool tbstree_isleftthreaded(const ThreadedBinaryTree *t) {
    assert(!tbstree_empty(t));
    return t->leftthread;
}

bool tbstree_isrightthreaded(const ThreadedBinaryTree *t) {
    assert(!tbstree_empty(t));
    return t->rightthread;
}

/*------------------------  Private interface -----------------------------*/

ThreadedBinaryTree *tbstree_cons(int root) {
    ThreadedBinaryTree *t = malloc(sizeof(struct _tbstree));
    t->parent = NULL;
    t->left = NULL;
    t->right = NULL;
    t->root = root;
    t->leftthread = false;
    t->rightthread = false;
    return t;
}

ThreadedBinaryTree *bstree_successor(const ThreadedBinaryTree *x) {
    assert(!tbstree_empty(x));
    ThreadedBinaryTree *y = x->right;
    if (y) {
        while (y->left)
            y = y->left;
    } else {
        y = x->parent;
        while (y && (x == y->right)) {
            x = y;
            y = y->parent;
        }
    }
    return y;
}

ThreadedBinaryTree *bstree_predecessor(const ThreadedBinaryTree *x) {
    assert(!tbstree_empty(x));
    ThreadedBinaryTree *y = x->left;
    if (y) {
        while (y->right)
            y = y->right;
    } else {
        y = x->parent;
        while (y && (x == y->left)) {
            x = y;
            y = y->parent;
        }
    }
    return y;
}

/***************************************************************************************/
/**                               Control start here                                  **/
/***************************************************************************************/
/**
 *  Nom         :
 *  Prenom      :
 *  Num Etud    :
 **/

/*
 * Exercice 3 : rétablissement de l'invariant de structure.
 */
void fix_tree_threads(ptrThreadedBinaryTree current) {

}

/*
 *  Exercice 1 : Ecrire la fonction d'ajout dans l'arbre binaire de recherche
 *  Exercice 3 : Etablir l'invariant des arbres cousus après insertion
 */
void tbstree_add(ptrThreadedBinaryTree *t, int v) {
    /* Exercice 1 */
    /* Add the value into the Binary search tree */

    /* Exercice 3 */
    /* Fix threads on the new inserted node */
}

/*
 * Exercice 2 : Parcours classiques de l'arbre
 */
void tbstree_depth_infix(const ThreadedBinaryTree *t, OperateFunctor f, void *userData) {
}

void tbstree_depth_prefix(const ThreadedBinaryTree *t, OperateFunctor f, void *userData) {
}

/*
 * Exercice 4 - parcours de l'arbre en utilisant les coutures
 */
void tbstree_inorder(const ThreadedBinaryTree *t, OperateFunctor f, void *userData) {
}
