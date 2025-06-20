#include <stdio.h>
#include "nbtrees.h"

int main() {
    Isi_Tree tree;
    int jml_node = 10;

    Create_tree(tree, jml_node);

    tree[1].info = 'A';
    tree[1].ps_fs = 2;
    tree[1].ps_nb = 0;
    tree[1].ps_pr = 0;

    tree[2].info = 'B';
    tree[2].ps_fs = 4;
    tree[2].ps_nb = 3;
    tree[2].ps_pr = 1;

    tree[3].info = 'C';
    tree[3].ps_fs = 6;
    tree[3].ps_nb = 0;
    tree[3].ps_pr = 1;

    tree[4].info = 'D';
    tree[4].ps_fs = 0;
    tree[4].ps_nb = 5;
    tree[4].ps_pr = 2;

    tree[5].info = 'E';
    tree[5].ps_fs = 9;
    tree[5].ps_nb = 0;
    tree[5].ps_pr = 2;

    tree[6].info = 'F';
    tree[6].ps_fs = 0;
    tree[6].ps_nb = 7;
    tree[6].ps_pr = 3;

    tree[7].info = 'G';
    tree[7].ps_fs = 0;
    tree[7].ps_nb = 8;
    tree[7].ps_pr = 3;

    tree[8].info = 'H';
    tree[8].ps_fs = 0;
    tree[8].ps_nb = 0;
    tree[8].ps_pr = 3;

    tree[9].info = 'I';
    tree[9].ps_fs = 0;
    tree[9].ps_nb = 10;
    tree[9].ps_pr = 5;

    tree[10].info = 'J';
    tree[10].ps_fs = 0;
    tree[10].ps_nb = 0;
    tree[10].ps_pr = 5;

    printf("\nPohon yang ditampilkan:\n");
    PrintTree(tree);

    printf("\nLevel dari setiap node:\n");
    printf("Node A: Level %d\n", Level(tree, 'A'));
    printf("Node B: Level %d\n", Level(tree, 'B'));
    printf("Node C: Level %d\n", Level(tree, 'C'));
    printf("Node D: Level %d\n", Level(tree, 'D'));
    printf("Node E: Level %d\n", Level(tree, 'E'));
    printf("Node F: Level %d\n", Level(tree, 'F'));
    printf("Node G: Level %d\n", Level(tree, 'G'));
    printf("Node H: Level %d\n", Level(tree, 'H'));
    printf("Node I: Level %d\n", Level(tree, 'I'));
    printf("Node J: Level %d\n", Level(tree, 'J'));

    printf("\nTraversal PreOrder: ");
    PreOrder(tree);

    printf("Traversal InOrder: ");
    InOrder(tree);

    printf("Traversal PostOrder: ");
    PostOrder(tree);

    printf("Traversal Level Order: ");
    Level_order(tree, jml_node);

    printf("\nJumlah node: %d\n", nbElmt(tree));
    printf("Jumlah daun: %d\n", nbDaun(tree));
    printf("Kedalaman pohon: %d\n", Depth(tree));

    return 0;
}
