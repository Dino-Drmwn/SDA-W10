#include <stdio.h>
#include "nbtrees.h"

int main() {
    TreeArray tree;
    int numNodes = 10;

    CreateTree(tree, numNodes);

    // Node A - Root (Level 0)
    tree[1].data = 'A';
    tree[1].firstChild = 2;  // First child of A is B
    tree[1].nextSibling = NIL_INDEX;
    tree[1].parent = NIL_INDEX;

    // Node B - Level 1 (Child of A)
    tree[2].data = 'B';
    tree[2].firstChild = 4;  // First child of B is D
    tree[2].nextSibling = 3;  // Next sibling of B is C
    tree[2].parent = 1;  // Parent of B is A

    // Node C - Level 1 (Child of A)
    tree[3].data = 'C';
    tree[3].firstChild = 6;  // First child of C is F
    tree[3].nextSibling = NIL_INDEX;
    tree[3].parent = 1;  // Parent of C is A

    // Node D - Level 2 (Child of B)
    tree[4].data = 'D';
    tree[4].firstChild = NIL_INDEX;
    tree[4].nextSibling = 5;  // Next sibling of D is E
    tree[4].parent = 2;  // Parent of D is B

    // Node E - Level 2 (Child of B)
    tree[5].data = 'E';
    tree[5].firstChild = 9;  // First child of E is I
    tree[5].nextSibling = NIL_INDEX;
    tree[5].parent = 2;  // Parent of E is B

    // Node F - Level 2 (Child of C)
    tree[6].data = 'F';
    tree[6].firstChild = NIL_INDEX;
    tree[6].nextSibling = 7;  // Next sibling of F is G
    tree[6].parent = 3;  // Parent of F is C

    // Node G - Level 2 (Child of C)
    tree[7].data = 'G';
    tree[7].firstChild = NIL_INDEX;
    tree[7].nextSibling = 8;  // Next sibling of G is H
    tree[7].parent = 3;  // Parent of G is C

    // Node H - Level 2 (Child of C)
    tree[8].data = 'H';
    tree[8].firstChild = NIL_INDEX;
    tree[8].nextSibling = NIL_INDEX;
    tree[8].parent = 3;  // Parent of H is C

    // Node I - Level 3 (Child of E)
    tree[9].data = 'I';
    tree[9].firstChild = NIL_INDEX;
    tree[9].nextSibling = 10; // Next sibling of I is J
    tree[9].parent = 5;  // Parent of I is E

    // Node J - Level 3 (Child of E)
    tree[10].data = 'J';
    tree[10].firstChild = NIL_INDEX;
    tree[10].nextSibling = NIL_INDEX;
    tree[10].parent = 5; // Parent of J is E

    printf("\nPohon yang ditampilkan:\n");
    PrintNonBinaryTree(tree);

    printf("\nLevel dari setiap node:\n");
    printf("Node A: Level %d\n", GetNodeLevel(tree, 'A'));
    printf("Node B: Level %d\n", GetNodeLevel(tree, 'B'));
    printf("Node C: Level %d\n", GetNodeLevel(tree, 'C'));
    printf("Node D: Level %d\n", GetNodeLevel(tree, 'D'));
    printf("Node E: Level %d\n", GetNodeLevel(tree, 'E'));
    printf("Node F: Level %d\n", GetNodeLevel(tree, 'F'));
    printf("Node G: Level %d\n", GetNodeLevel(tree, 'G'));
    printf("Node H: Level %d\n", GetNodeLevel(tree, 'H'));
    printf("Node I: Level %d\n", GetNodeLevel(tree, 'I'));
    printf("Node J: Level %d\n", GetNodeLevel(tree, 'J'));

    printf("\nTraversal PreOrder: ");
    PreOrderTraversal(tree);

    printf("Traversal InOrder: ");
    InOrderTraversal(tree);

    printf("Traversal PostOrder: ");
    PostOrderTraversal(tree);

    printf("Traversal Level Order: ");
    LevelOrderTraversal(tree, numNodes);

    printf("\nJumlah node: %d\n", CountNodes(tree));
    printf("Jumlah daun: %d\n", CountLeaves(tree));
    printf("Kedalaman pohon: %d\n", GetTreeDepth(tree));

    return 0;
}
