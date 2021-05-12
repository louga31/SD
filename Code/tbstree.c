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
 *  Nom         : Ormancey
 *  Prenom      : Quentin
 *  Num Etud    : 21808876
 **/

/*
 * Exercice 3 : rétablissement de l'invariant de structure.
 */
void fix_tree_threads(ptrThreadedBinaryTree current) {
    current->left = bstree_predecessor(current);
	if (current->left)
		current->leftthread = true;
    current->right = bstree_successor(current);
    if (current->right)
		current->rightthread = true;
	if (current->parent)
	{
        if (current->parent->left == current)
            current->parent->leftthread = false;
        else
            current->parent->rightthread = false;
	}
}

/*
 *  Exercice 1 : Ecrire la fonction d'ajout dans l'arbre binaire de recherche
 *  Exercice 3 : Etablir l'invariant des arbres cousus après insertion
 */
void tbstree_add(ptrThreadedBinaryTree *t, int v) {
    ptrThreadedBinaryTree* cur = t;
    ThreadedBinaryTree* par = NULL;
    bool isthread = false;
    while (*cur && !isthread)
    {
        par = *cur;
        if ((*cur)->root == v)
            return;
        if ((*cur)->root > v)
        {
            isthread = (*cur)->leftthread;
            cur = &(*cur)->left;
        }
        else
        {
            isthread = (*cur)->rightthread;
            cur = &(*cur)->right;
        }
    }
    *cur = tbstree_cons(v);
    (*cur)->parent = par;

    fix_tree_threads(*cur);
}

/*
 * Exercice 2 : Parcours classiques de l'arbre
 */
void tbstree_depth_infix(const ThreadedBinaryTree *t, OperateFunctor f, void *userData) {
    if (tbstree_empty(t))
		return;
	if (t->leftthread)
        tbstree_depth_infix(NULL, f, userData);
    else
		tbstree_depth_infix(t->left, f, userData);
    f(t, userData);
    if (t->rightthread)
        tbstree_depth_infix(NULL, f, userData);
    else
        tbstree_depth_infix(t->right, f, userData);
}

void tbstree_depth_prefix(const ThreadedBinaryTree *t, OperateFunctor f, void *userData) {
    if (tbstree_empty(t))
        return;
    f(t, userData);
    if (t->leftthread)
        tbstree_depth_prefix(NULL, f, userData);
    else
        tbstree_depth_prefix(t->left, f, userData);
    if (t->rightthread)
        tbstree_depth_prefix(NULL, f, userData);
    else
        tbstree_depth_prefix(t->right, f, userData);
}

/*
 * Exercice 4 - parcours de l'arbre en utilisant les coutures
 */
void tbstree_inorder(const ThreadedBinaryTree *t, OperateFunctor f, void *userData) {
	
}
