#include <stdio.h>
#include <stdlib.h>
#include "nbtrees.h"

void Create_tree(Isi_Tree X, int Jml_Node) {
    for (int i = 1; i <= Jml_Node; i++) {
        X[i].info = ' ';
        X[i].ps_fs = nil;
        X[i].ps_nb = nil;
        X[i].ps_pr = nil;
    }
}

boolean IsEmpty(Isi_Tree P) {
    return (P[1].info == ' ');
}

void PreOrderHelper(Isi_Tree P, address currentNodeIdx) {
    if (currentNodeIdx == nil) {
        return;
    }

    printf("%c ", P[currentNodeIdx].info);

    if (P[currentNodeIdx].ps_fs != nil) {
        PreOrderHelper(P, P[currentNodeIdx].ps_fs);
    }

    if (P[currentNodeIdx].ps_nb != nil) {
        PreOrderHelper(P, P[currentNodeIdx].ps_nb);
    }
}

void PreOrder(Isi_Tree P) {
    PreOrderHelper(P, 1);
    printf("\n");
}

void InOrderHelper(Isi_Tree P, address currentNodeIdx) {
    if (currentNodeIdx == nil) {
        return;
    }

    address firstChildIdx = P[currentNodeIdx].ps_fs;

    if (firstChildIdx != nil) {
        InOrderHelper(P, firstChildIdx);
    }

    printf("%c ", P[currentNodeIdx].info);

    if (firstChildIdx != nil) {
        address siblingIdx = P[firstChildIdx].ps_nb;
        while (siblingIdx != nil) {
            InOrderHelper(P, siblingIdx);
            siblingIdx = P[siblingIdx].ps_nb;
        }
    }
}

void InOrder(Isi_Tree P) {
    InOrderHelper(P, 1);
    printf("\n");
}

void PostOrderHelper(Isi_Tree P, address currentNodeIdx) {
    if (currentNodeIdx == nil) {
        return;
    }

    if (P[currentNodeIdx].ps_fs != nil) {
        PostOrderHelper(P, P[currentNodeIdx].ps_fs);
    }

    if (P[currentNodeIdx].ps_nb != nil) {
        PostOrderHelper(P, P[currentNodeIdx].ps_nb);
    }

    printf("%c ", P[currentNodeIdx].info);
}


void PostOrder(Isi_Tree P) {
    PostOrderHelper(P, 1);
    printf("\n");
}

void Level_order(Isi_Tree P, int Maks_node) {
    if (IsEmpty(P)) {
        printf("Pohon kosong\n");
        return;
    }

    address queue[jml_maks + 1];
    int front = 0;
    int rear = 0;

    queue[rear++] = 1;

    while (front < rear) {
        address currentIdx = queue[front++];

        printf("%c ", P[currentIdx].info);

        address childIdx = P[currentIdx].ps_fs;
        while (childIdx != nil) {
            queue[rear++] = childIdx;
            childIdx = P[childIdx].ps_nb;
        }
    }
    printf("\n");
}

int GetChildCount(Isi_Tree P, address nodeIdx) {
    if (nodeIdx == nil) {
        return 0;
    }

    int count = 0;
    address child = P[nodeIdx].ps_fs;
    while (child != nil) {
        count++;
        child = P[child].ps_nb;
    }
    return count;
}

void printSpaces(int count) {
    for (int i = 0; i < count; i++) {
        printf(" ");
    }
}

void PrintTree(Isi_Tree P) {
    if (IsEmpty(P)) {
        printf("Pohon kosong\n");
        return;
    }

    int depth = Depth(P);
    int cols = (1 << (depth + 1)) * 2;
    int rows = (depth + 1) * 2;

    char display[rows][cols + 1];

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            display[i][j] = ' ';
        }
        display[i][cols] = '\0';
    }

    address queue[jml_maks + 1];
    int posQueue[jml_maks + 1];
    int parentPosQueue[jml_maks + 1];
    int front = 0, rear = 0;

    queue[rear] = 1;
    posQueue[rear] = cols / 2;
    parentPosQueue[rear] = -1;
    rear++;

    int currentLevel = 0;
    int nodesAtCurrentLevelCount = 1;
    int nextLevelNodesCount = 0;
    int nodesProcessedThisLevel = 0;

    while (front < rear) {
        address currentIdx = queue[front];
        int currentPos = posQueue[front];
        int parentPos = parentPosQueue[front];
        front++;

        nodesProcessedThisLevel++;

        int row = currentLevel * 2;

        display[row][currentPos] = P[currentIdx].info;

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

        address childIdx = P[currentIdx].ps_fs;
        int childOrder = 0;
        int numChildren = GetChildCount(P, currentIdx);

        int baseChildSpacing = (cols / (1 << (currentLevel + 2))) + 1;
        if (baseChildSpacing < 1) baseChildSpacing = 1;

        int startChildPos = currentPos - (numChildren - 1) * baseChildSpacing / 2;

        while (childIdx != nil) {
            nextLevelNodesCount++;
            int childPos = startChildPos + (childOrder * baseChildSpacing);

            if (childPos < 0) childPos = 0;
            if (childPos >= cols) childPos = cols -1;

            queue[rear] = childIdx;
            posQueue[rear] = childPos;
            parentPosQueue[rear] = currentPos;
            rear++;

            childIdx = P[childIdx].ps_nb;
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


boolean Search(Isi_Tree P, infotype X) {
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ' && P[i].info == X) {
            return true;
        }
    }
    return false;
}

int nbElmt(Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ') {
            count++;
        }
    }
    return count;
}

int nbDaun(Isi_Tree P) {
    int count = 0;
    for (int i = 1; i <= jml_maks; i++) {
        if (P[i].info != ' ' && P[i].ps_fs == nil) {
            count++;
        }
    }
    return count;
}

int LevelHelper(Isi_Tree P, address currentNodeIdx, infotype X, int currentLevel) {
    if (currentNodeIdx == nil) {
        return -1;
    }

    if (P[currentNodeIdx].info == X) {
        return currentLevel;
    }

    int result = LevelHelper(P, P[currentNodeIdx].ps_fs, X, currentLevel + 1);
    if (result != -1) {
        return result;
    }

    return LevelHelper(P, P[currentNodeIdx].ps_nb, X, currentLevel);
}

int Level(Isi_Tree P, infotype X) {
    return LevelHelper(P, 1, X, 0);
}

int DepthHelper(Isi_Tree P, address currentNodeIdx) {
    if (currentNodeIdx == nil) {
        return -1;
    }

    int maxChildDepth = -1;
    address childIdx = P[currentNodeIdx].ps_fs;

    while (childIdx != nil) {
        int childDepth = DepthHelper(P, childIdx);
        if (childDepth > maxChildDepth) {
            maxChildDepth = childDepth;
        }
        childIdx = P[childIdx].ps_nb;
    }

    return maxChildDepth + 1;
}

int Depth(Isi_Tree P) {
    return DepthHelper(P, 1);
}

int Max(infotype Data1, infotype Data2) {
    return (Data1 > Data2) ? Data1 : Data2;
}
