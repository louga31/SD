#include "tbstree.h"
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

/**
 * This function output one node using the <a href="https://www.graphviz.org/documentation/">dot</a> syntax.
 * A node must defined its shape and its links to the left and right subtrees. If one of this subtree is NULL,
 * a grey box with the label NIL is drawn.
 * @dot
 * digraph node_example {
 *      node [shape = record];
 *      parent [label="bstree_parent()"]
 *      treeroot [label="{{<parent>}|root|{<left>|<right>}}"];
 *      left [label="bstree_left()"];
 *      right [label="bstree_right()"];
 *      parent:s ->treeroot:parent:c [headclip=false, tailclip=false]
 *      treeroot:left:c -> left:n [headclip=false, tailclip=false]
 *      treeroot:right:c -> right:n [headclip=false, tailclip=false]
 * }
 * @enddot
 * @param t the tree node to draw.
 * @param userData the file to output the dot commands. Concretely, this parameter will be of type FILE * when the functor is called.
 */

void node_to_dot(const ThreadedBinaryTree *t, void *userData) {
    FILE *file = (FILE *) userData;

    printf("%d ", tbstree_root(t));
    fprintf(file, "\tn%d [label=\"{{<parent>}|%d|{<left>|<right>}}\"];\n",
            tbstree_root(t), tbstree_root(t));

    if (!tbstree_isleftthreaded(t)) {
        if (tbstree_left(t)) {
            fprintf(file, "\tn%d:left:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                    tbstree_root(t), tbstree_root(tbstree_left(t)));
        } else {
            fprintf(file, "\tlnil%d [style=filled, fillcolor=dodgerblue, label=\"NIL\"];\n", tbstree_root(t));
            fprintf(file, "\tn%d:left:c -> lnil%d:n [headclip=false, tailclip=false, color=dodgerblue]\n",
                    tbstree_root(t), tbstree_root(t));
        }
    } else {
        fprintf(file, "\tn%d:left:s -> n%d:right:s [style=dashed, headclip=false, tailclip=false, color=crimson]\n",
                        tbstree_root(t), tbstree_root(tbstree_left(t)));
    }
    if (!tbstree_isrightthreaded(t)) {
        if (tbstree_right(t)) {
            fprintf(file, "\tn%d:right:c -> n%d:parent:c [headclip=false, tailclip=false]\n",
                    tbstree_root(t), tbstree_root(tbstree_right(t)));
        } else {
            fprintf(file, "\trnil%d [style=filled, fillcolor=dodgerblue, label=\"NIL\"];\n", tbstree_root(t));
            fprintf(file, "\tn%d:right:c -> rnil%d:n [headclip=false, tailclip=false, color=dodgerblue]\n",
                    tbstree_root(t), tbstree_root(t));
        }
    } else {
        fprintf(file, "\tn%d:right:s -> n%d:left:s [style=dashed, headclip=false, tailclip=false, color=aquamarine4]\n",
                tbstree_root(t), tbstree_root(tbstree_right(t)));
    }
}

/**
 * Print the value of a node.
 * @param t the tree node to output
 * @param userData unused pointer.
 */
void print_tree(const ThreadedBinaryTree *t, void *userData) {
    (void) userData;
    printf("%d ", tbstree_root(t));
}

/** Main function for testing the Tree implementation.
 * The main function expects one parameter that is the file where values added to the tree, searched into the
 * tree and removed from the tree are to be read.
 *
 * This file must contain the following informations :
 * - on the first line, the number of values to be added to the tree,
 * - on the second line, the values to be added, separated by a space (or tab).
 *
 * The values will be added in the order they are read from the file.
 */
int main(int argc, char **argv) {

    if (argc < 2) {
        fprintf(stderr, "usage : %s filename\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        perror(argv[1]);
        return 1;
    }

    ThreadedBinaryTree *theTree = tbstree_create();

    printf("Adding values to the tree.\n\t");
    int n;
    fscanf(input, "%d", &n);

    for (int i = 0; i < n; ++i) {
        int v;
        fscanf(input, "%d", &v);
        tbstree_add(&theTree, v);
    }
    printf("Done.\n");

    printf("Inorder visit of the tree.\n\t");
    tbstree_depth_infix(theTree, print_tree, NULL);
    printf("\nDone.\n");

    char* dotname = malloc(sizeof(char) * strlen(argv[1]) + 1);
    strncpy(dotname, argv[1], strlen(argv[1])+1);
    strncpy(dotname+strlen(dotname)-3, "dot", 3);
    printf("Exporting the tree to %s.\n\t", dotname);
    FILE *output = fopen(dotname, "w");
    fprintf(output, "digraph ThreadedBinaryTree {\n\tgraph [ranksep=0.75, nodesep = 0.75];\n\tnode [shape = record];\n\n");
    tbstree_depth_prefix(theTree, node_to_dot, output);
    fprintf(output, "\n}\n");
    fclose(output);
    printf("\nDone.\n");

    printf("Using the threads to visit the tree.\n\t");
    tbstree_inorder(theTree, print_tree, NULL);
    printf("\nDone.\n");
    fclose(input);
    return 0;
}
