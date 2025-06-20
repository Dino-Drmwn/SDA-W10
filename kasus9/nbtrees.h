#ifndef NB_TREES_H
#define NB_TREES_H

#include "boolean.h"

#define MAX_NODES 20
#define NIL_INDEX 0 // Represents a null or non-existent link/node

typedef char ElementType;
typedef int NodeIndex;

typedef struct {
    ElementType data;
    NodeIndex firstChild;
    NodeIndex nextSibling;
    NodeIndex parent;
} TreeNode;

typedef TreeNode TreeArray[MAX_NODES + 1];

// Function Prototypes
void CreateTree(TreeArray tree, int numNodes);
boolean IsTreeEmpty(TreeArray tree);
void PreOrderTraversal(TreeArray tree);
void InOrderTraversal(TreeArray tree);
void PostOrderTraversal(TreeArray tree);
void LevelOrderTraversal(TreeArray tree, int maxNodes);
void PrintNonBinaryTree(TreeArray tree);
boolean SearchTree(TreeArray tree, ElementType dataToFind);
int CountNodes(TreeArray tree);
int CountLeaves(TreeArray tree);
int GetNodeLevel(TreeArray tree, ElementType data);
int GetTreeDepth(TreeArray tree);
ElementType MaxValue(ElementType val1, ElementType val2);

#endif
