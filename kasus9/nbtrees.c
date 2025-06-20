#include <stdio.h>
#include <stdlib.h>
#include "nbtrees.h"

void CreateTree(TreeArray tree, int numNodes) {
    for (int i = 1; i <= numNodes; i++) {
        tree[i].data = ' ';
        tree[i].firstChild = NIL_INDEX;
        tree[i].nextSibling = NIL_INDEX;
        tree[i].parent = NIL_INDEX;
    }
}

boolean IsTreeEmpty(TreeArray tree) {
    return (tree[1].data == ' ');
}

void PreOrderHelper(TreeArray tree, NodeIndex currentNodeIndex) {
    if (currentNodeIndex == NIL_INDEX) {
        return;
    }

    printf("%c ", tree[currentNodeIndex].data);

    if (tree[currentNodeIndex].firstChild != NIL_INDEX) {
        PreOrderHelper(tree, tree[currentNodeIndex].firstChild);
    }

    if (tree[currentNodeIndex].nextSibling != NIL_INDEX) {
        PreOrderHelper(tree, tree[currentNodeIndex].nextSibling);
    }
}

void PreOrderTraversal(TreeArray tree) {
    PreOrderHelper(tree, 1);
    printf("\n");
}

void InOrderHelper(TreeArray tree, NodeIndex currentNodeIndex) {
    if (currentNodeIndex == NIL_INDEX) {
        return;
    }

    NodeIndex firstChildIndex = tree[currentNodeIndex].firstChild;

    if (firstChildIndex != NIL_INDEX) {
        InOrderHelper(tree, firstChildIndex);
    }

    printf("%c ", tree[currentNodeIndex].data);

    if (firstChildIndex != NIL_INDEX) {
        NodeIndex siblingIndex = tree[firstChildIndex].nextSibling;
        while (siblingIndex != NIL_INDEX) {
            InOrderHelper(tree, siblingIndex);
            siblingIndex = tree[siblingIndex].nextSibling;
        }
    }
}

void InOrderTraversal(TreeArray tree) {
    InOrderHelper(tree, 1);
    printf("\n");
}

void PostOrderHelper(TreeArray tree, NodeIndex currentNodeIndex) {
    if (currentNodeIndex == NIL_INDEX) {
        return;
    }

    if (tree[currentNodeIndex].firstChild != NIL_INDEX) {
        PostOrderHelper(tree, tree[currentNodeIndex].firstChild);
    }

    if (tree[currentNodeIndex].nextSibling != NIL_INDEX) {
        PostOrderHelper(tree, tree[currentNodeIndex].nextSibling);
    }

    printf("%c ", tree[currentNodeIndex].data);
}

void PostOrderTraversal(TreeArray tree) {
    PostOrderHelper(tree, 1);
    printf("\n");
}

void LevelOrderTraversal(TreeArray tree, int maxNodes) {
    if (IsTreeEmpty(tree)) {
        printf("Pohon kosong\n");
        return;
    }

    NodeIndex queue[MAX_NODES + 1];
    int front = 0;
    int rear = 0;

    queue[rear++] = 1;

    while (front < rear) {
        NodeIndex currentNodeIndex = queue[front++];

        printf("%c ", tree[currentNodeIndex].data);

        NodeIndex childIndex = tree[currentNodeIndex].firstChild;
        while (childIndex != NIL_INDEX) {
            queue[rear++] = childIndex;
            childIndex = tree[childIndex].nextSibling;
        }
    }
    printf("\n");
}

int GetChildCount(TreeArray tree, NodeIndex nodeIdx) {
    if (nodeIdx == NIL_INDEX) {
        return 0;
    }

    int count = 0;
    NodeIndex child = tree[nodeIdx].firstChild;
    while (child != NIL_INDEX) {
        count++;
        child = tree[child].nextSibling;
    }
    return count;
}

void PrintNonBinaryTree(TreeArray tree) {
    if (IsTreeEmpty(tree)) {
        printf("Pohon kosong\n");
        return;
    }

    int depth = GetTreeDepth(tree);
    int cols = (1 << (depth + 1)) * 2;
    int rows = (depth + 1) * 2;

    char display[rows][cols + 1];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            display[i][j] = ' ';
        }
        display[i][cols] = '\0';
    }

    NodeIndex queue[MAX_NODES + 1];
    int posQueue[MAX_NODES + 1];
    int parentPosQueue[MAX_NODES + 1];
    int front = 0, rear = 0;

    queue[rear] = 1;
    posQueue[rear] = cols / 2;
    parentPosQueue[rear] = -1; // Sentinel for no parent
    rear++;

    int currentLevel = 0;
    int nodesAtCurrentLevelCount = 1;
    int nextLevelNodesCount = 0;
    int nodesProcessedThisLevel = 0;

    while (front < rear) {
        NodeIndex currentNodeIndex = queue[front];
        int currentPos = posQueue[front];
        int parentPos = parentPosQueue[front];
        front++;

        nodesProcessedThisLevel++;

        int row = currentLevel * 2;

        display[row][currentPos] = tree[currentNodeIndex].data;

        if (parentPos != -1) {
            int parentRow = (currentLevel - 1) * 2;
            int connectorRow = parentRow + 1;

            if (currentPos < parentPos) {
                for (int j = currentPos + 1; j < parentPos; j++) {
                    display[connectorRow][j] = '-';
                }
                display[connectorRow][currentPos] = '/';
            } else if (currentPos > parentPos) {
                for (int j = parentPos + 1; j < currentPos; j++) {
                    display[connectorRow][j] = '-';
                }
                display[connectorRow][currentPos] = '\\';
            } else {
                display[connectorRow][currentPos] = '|';
            }
        }

        NodeIndex childIndex = tree[currentNodeIndex].firstChild;
        int childOrder = 0;
        int numChildren = GetChildCount(tree, currentNodeIndex);

        int baseChildSpacing = (cols / (1 << (currentLevel + 2))) + 1;
        if (baseChildSpacing < 1) baseChildSpacing = 1;

        int startChildPos = currentPos - (numChildren - 1) * baseChildSpacing / 2;

        while (childIndex != NIL_INDEX) {
            nextLevelNodesCount++;
            int childPos = startChildPos + (childOrder * baseChildSpacing);

            if (childPos < 0) childPos = 0;
            if (childPos >= cols) childPos = cols -1;

            queue[rear] = childIndex;
            posQueue[rear] = childPos;
            parentPosQueue[rear] = currentPos;
            rear++;

            childIndex = tree[childIndex].nextSibling;
            childOrder++;
        }

        if (nodesProcessedThisLevel == nodesAtCurrentLevelCount) {
            currentLevel++;
            nodesAtCurrentLevelCount = nextLevelNodesCount;
            nextLevelNodesCount = 0;
            nodesProcessedThisLevel = 0;
        }
    }

    for (int i = 0; i < rows; i++) {
        boolean hasContent = false;
        for (int j = 0; j < cols; j++) {
            if (display[i][j] != ' ') {
                hasContent = true;
                break;
            }
        }
        if (hasContent) {
            printf("%s\n", display[i]);
        }
    }
}


boolean SearchTree(TreeArray tree, ElementType dataToFind) {
    for (int i = 1; i <= MAX_NODES; i++) {
        if (tree[i].data != ' ' && tree[i].data == dataToFind) {
            return true;
        }
    }
    return false;
}

int CountNodes(TreeArray tree) {
    int count = 0;
    for (int i = 1; i <= MAX_NODES; i++) {
        if (tree[i].data != ' ') {
            count++;
        }
    }
    return count;
}

int CountLeaves(TreeArray tree) {
    int count = 0;
    for (int i = 1; i <= MAX_NODES; i++) {
        if (tree[i].data != ' ' && tree[i].firstChild == NIL_INDEX) {
            count++;
        }
    }
    return count;
}

int GetNodeLevelHelper(TreeArray tree, NodeIndex currentNodeIndex, ElementType dataToFind, int currentLevel) {
    if (currentNodeIndex == NIL_INDEX) {
        return -1;
    }

    if (tree[currentNodeIndex].data == dataToFind) {
        return currentLevel;
    }

    int result = GetNodeLevelHelper(tree, tree[currentNodeIndex].firstChild, dataToFind, currentLevel + 1);
    if (result != -1) {
        return result;
    }

    return GetNodeLevelHelper(tree, tree[currentNodeIndex].nextSibling, dataToFind, currentLevel);
}

int GetNodeLevel(TreeArray tree, ElementType data) {
    return GetNodeLevelHelper(tree, 1, data, 0);
}

int GetTreeDepthHelper(TreeArray tree, NodeIndex currentNodeIndex) {
    if (currentNodeIndex == NIL_INDEX) {
        return -1;
    }

    int maxChildDepth = -1;
    NodeIndex childIndex = tree[currentNodeIndex].firstChild;

    while (childIndex != NIL_INDEX) {
        int childDepth = GetTreeDepthHelper(tree, childIndex);
        if (childDepth > maxChildDepth) {
            maxChildDepth = childDepth;
        }
        childIndex = tree[childIndex].nextSibling;
    }

    return maxChildDepth + 1;
}

int GetTreeDepth(TreeArray tree) {
    return GetTreeDepthHelper(tree, 1);
}

ElementType MaxValue(ElementType val1, ElementType val2) {
    return (val1 > val2) ? val1 : val2;
}
