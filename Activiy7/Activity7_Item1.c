#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct treeNode {
    int value;
    struct treeNode* leftChild;
    struct treeNode* rightChild;
    int height; // for AVL balancing
} treeNode;

int getMax (int first, int second) {
    return (first > second) ? first : second;
}

int getHeight (treeNode* node) {
    if (node == NULL) { return 0; }
    return node->height;
}

int calculateBalanceFactor (treeNode* node) {
    if (node == NULL) { return 0; }
    return getHeight(node->leftChild) - getHeight(node->rightChild);
}

treeNode* createNewNode (int value) {
    treeNode* newNode = (treeNode*) malloc (sizeof(treeNode));
    newNode->value = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->height = 1; // New node is initially added at leaf
    return newNode;
}

treeNode* rightRotation(treeNode* unbalancedNode) {
    treeNode* newRoot = unbalancedNode->leftChild;
    treeNode* tempSubtree = newRoot->rightChild;

    // Perform rotation
    newRoot->rightChild = unbalancedNode;
    unbalancedNode->leftChild = tempSubtree;

    // Update heights
    unbalancedNode->height = 1 + getMax(getHeight(unbalancedNode->leftChild), getHeight(unbalancedNode->rightChild));
    newRoot->height = 1 + getMax(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

    // Return new root
    return newRoot;
}

treeNode* leftRotation(treeNode* unbalancedNode) {
    treeNode* newRoot = unbalancedNode->rightChild;
    treeNode* tempSubtree = newRoot->leftChild;

    // Perform rotation
    newRoot->leftChild = unbalancedNode;
    unbalancedNode->rightChild = tempSubtree;

    // Update heights
    unbalancedNode->height = 1 + getMax(getHeight(unbalancedNode->leftChild), getHeight(unbalancedNode->rightChild));
    newRoot->height = 1 + getMax(getHeight(newRoot->leftChild), getHeight(newRoot->rightChild));

    // Return new root
    return newRoot;
}

treeNode* insertAVL(treeNode* rootNode, int value) {
    // Perform normal BST insertion
    if (rootNode == NULL) {
        return createNewNode(value);
    }
    if (value < rootNode->value) {
        rootNode->leftChild = insertAVL(rootNode->leftChild, value);
    } else if (value > rootNode->value) {
        rootNode->rightChild = insertAVL(rootNode->rightChild, value);
    } else {
        // Duplicate values are not allowed in the AVL tree
        return rootNode;
    }

    // Update height of this ancestor node
    rootNode->height = 1 + getMax(getHeight(rootNode->leftChild), getHeight(rootNode->rightChild));

    // Get the balance factor to check whether this node became unbalanced
    int balanceFactor = calculateBalanceFactor(rootNode);

    // If the node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balanceFactor > 1 && value < rootNode->leftChild->value) {
        return rightRotation(rootNode);
    }

    // Right Right Case
    if (balanceFactor < -1 && value > rootNode->rightChild->value) {
        return leftRotation(rootNode);
    }

    // Left Right Case
    if (balanceFactor > 1 && value > rootNode->leftChild->value) {
        rootNode->leftChild = leftRotation(rootNode->leftChild);
        return rightRotation(rootNode);
    }

    // Right Left Case
    if (balanceFactor < -1 && value < rootNode->rightChild->value) {
        rootNode->rightChild = rightRotation(rootNode->rightChild);
        return leftRotation(rootNode);
    }

    // Return the (unchanged) node pointer
    return rootNode;
}

// Standard BST insertion (without balancing)
treeNode* insertBST(treeNode* rootNode, int value){
    if (rootNode == NULL) {
        return createNewNode(value);
    }
    if (value < rootNode->value) {
        rootNode->leftChild = insertBST(rootNode->leftChild, value);
    } else if (value > rootNode->value) {
        rootNode->rightChild = insertBST(rootNode->rightChild, value);
    }
    // Duplicate values are not allowed in the BST
    return rootNode;
}

treeNode* searchTree(treeNode* rootNode, int targetValue) {
    if (rootNode == NULL || rootNode->value == targetValue) {
        return rootNode;
    }
    if (targetValue < rootNode->value) {
        return searchTree(rootNode->leftChild, targetValue);
    } else {
        return searchTree(rootNode->rightChild, targetValue);
    }
}

treeNode* findMinimumNode (treeNode* currentNode) {
    treeNode* minimumNode = currentNode;
    while (minimumNode && minimumNode->leftChild != NULL) 
        minimumNode = minimumNode->leftChild;
    return minimumNode;
}

treeNode* deleteAVL(treeNode* rootNode, int value) {
    // STEP 1: PERFORM STANDARD BST DELETE
    if (rootNode == NULL) {
        return rootNode;
    }
    if (value < rootNode->value) {
        rootNode->leftChild = deleteAVL(rootNode->leftChild, value);
    } else if (value > rootNode->value) {
        rootNode->rightChild = deleteAVL(rootNode->rightChild, value);
    } else {
        // Node with only one child or no child
        if ((rootNode->leftChild == NULL) || (rootNode->rightChild == NULL)) {
            treeNode* temp = rootNode->leftChild ? rootNode->leftChild : rootNode->rightChild;

            // No child case
            if (temp == NULL) {
                temp = rootNode;
                rootNode = NULL;
            } else { // One child case
                *rootNode = *temp; // Copy the contents of the non-empty child
            }
            free(temp);
        } else {
            // Node with two children: Get the inorder successor (smallest in the right subtree)
            treeNode* temp = findMinimumNode(rootNode->rightChild);

            // Copy the inorder successor's data to this node
            rootNode->value = temp->value;

            // Delete the inorder successor
            rootNode->rightChild = deleteAVL(rootNode->rightChild, temp->value);
        }
    }

    // If the tree had only one node then return
    if (rootNode == NULL) {
        return rootNode;
    }

    // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE
    rootNode->height = 1 + getMax(getHeight(rootNode->leftChild), getHeight(rootNode->rightChild));

    // STEP 3: GET THE BALANCE FACTOR OF THIS NODE (to check whether this node became unbalanced)
    int balanceFactor = calculateBalanceFactor(rootNode);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balanceFactor > 1 && calculateBalanceFactor(rootNode->leftChild) >= 0) {
        return rightRotation(rootNode);
    }

    // Left Right Case
    if (balanceFactor > 1 && calculateBalanceFactor(rootNode->leftChild) < 0) {
        rootNode->leftChild = leftRotation(rootNode->leftChild);
        return rightRotation(rootNode);
    }

    // Right Right Case
    if (balanceFactor < -1 && calculateBalanceFactor(rootNode->rightChild) <= 0) {
        return leftRotation(rootNode);
    }

    // Right Left Case
    if (balanceFactor < -1 && calculateBalanceFactor(rootNode->rightChild) > 0) {
        rootNode->rightChild = rightRotation(rootNode->rightChild);
        return leftRotation(rootNode);
    }
    

    // Return the (potentially) balanced node pointer
    return rootNode;
}

treeNode * deleteBST(treeNode* rootNode, int value) {
    //basic bst deletion
    if (rootNode == NULL) {
        return rootNode;
    }   
    if (value < rootNode->value) {
        rootNode->leftChild = deleteBST(rootNode->leftChild, value);
    } else if (value > rootNode->value) {
        rootNode->rightChild = deleteBST(rootNode->rightChild, value);
    } else {
        // Node with only one child or no child
        if (rootNode->leftChild == NULL) {
            treeNode* temp = rootNode->rightChild;
            free(rootNode);
            return temp;
        } else if (rootNode->rightChild == NULL) {
            treeNode* temp = rootNode->leftChild;
            free(rootNode);
            return temp;
        }

        // Node with two children: Get the inorder successor (smallest in the right subtree)
        treeNode* temp = findMinimumNode(rootNode->rightChild);

        // Copy the inorder successor's data to this node
        rootNode->value = temp->value;

        // Delete the inorder successor
        rootNode->rightChild = deleteBST(rootNode->rightChild, temp->value);
    }
    return rootNode;
}

int calculateTreeHeight(treeNode* node) {
    if (node == NULL) {
        return 0;
    }
    int leftHeight = calculateTreeHeight(node->leftChild);
    int rightHeight = calculateTreeHeight(node->rightChild);
    return 1 + getMax(leftHeight, rightHeight);
}

void freeTree(treeNode* node) {
    if (node == NULL) {
        return;
    }
    freeTree(node->leftChild);
    freeTree(node->rightChild);
    free(node);
}

// for average case performance testing
void generateRandomDataSet(int* dataSet, int dataSetSize) {
    for (int index= 0; index< dataSetSize; index++) {
        dataSet[index] = rand() % 1000; // Random integers between 0 and 999
    }
}

// for worst case performance testing
void generateSortedDataSet(int* dataSet, int dataSetSize) {
    for (int index= 0; index< dataSetSize; index++) {
        dataSet[index] = index; // Sorted integers
    }
}

void generateReverseSortedDataSet(int* dataSet, int dataSetSize) {
    for (int index= 0; index< dataSetSize; index++) {
        dataSet[index] = dataSetSize - index; // Reverse sorted integers
    }
}   

void runPerformanceComparison (int* testData, int dataSize, const char* dataSetType) {
    printf("===============================\n");
    printf("Performance Comparison for %s Data Set of Size %d:\n", dataSetType, dataSize);  

    treeNode* bstRoot = NULL;
    treeNode* avlRoot = NULL;

    clock_t startTime, endTime;
    double avlOperationTIme, bstOperationTime;
    double avlInsertionTime, bstInsertionTime;
    double avlSearchTime, bstSearchTime;
    double avlDeletionTime, bstDeletionTime;

    // TEST 1: Insertion performance
    printf("\n---------------\n");
    printf("Insertion Test:\n");

    // avl insertion
    startTime = clock();
    for (int index= 0; index< dataSize; index++) {
        avlRoot = insertAVL(avlRoot, testData[index]);
    }

    endTime = clock();

    avlInsertionTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("AVL Tree Insertion Time: %f seconds\n", avlInsertionTime);

    // bst insertion
    startTime = clock();
    for (int index= 0; index< dataSize; index++) {
        bstRoot = insertBST(bstRoot, testData[index]);
    }
    endTime = clock();

    bstInsertionTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("BST Insertion Time: %f seconds\n", bstInsertionTime);

    // TEST 2: Search performance
    printf("\n---------------\n");
    printf("Search Test:\n");
    int searchOperationsCount = dataSize / 10; // Search for 10% of the data size

    // AVL search
    startTime = clock();
    for (int index= 0; index< searchOperationsCount; index++) {
        searchTree(avlRoot, testData[index]);
    }
    endTime = clock();

    avlSearchTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("AVL Tree Search Time: %f seconds\n", avlSearchTime);


    // BST search
    startTime = clock();
    for (int index= 0; index< searchOperationsCount; index++) {
        searchTree(bstRoot, testData[index]);
    }
    endTime = clock();

    bstSearchTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("BST Search Time: %f seconds\n", bstSearchTime);

    // TEST 3: Deletion performance
    printf("\n---------------\n");
    printf("Deletion Test:\n");
    int deleteOperationsCount = dataSize / 10; // Delete 10% of the data size

    // AVL deletion
    startTime = clock();
    for (int index= 0; index< deleteOperationsCount; index++) {
        avlRoot = deleteAVL(avlRoot, testData[index]);
    }
    endTime = clock();

    avlDeletionTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("AVL Tree Deletion Time: %f seconds\n", avlDeletionTime);

    // BST deletion
    startTime = clock();
    for (int index= 0; index< deleteOperationsCount; index++) {
        int randomIndex = rand() % dataSize;
        bstRoot = deleteBST(bstRoot, testData[randomIndex]);
    }
    endTime = clock();
    bstDeletionTime = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;
    printf("BST Deletion Time: %f seconds\n\n", bstDeletionTime);
    printf("Performance Ratio (BST/AVL) for Insertion, Search, Deletion respectively: \n");
    printf("Insertion Ratio: %f\n", bstInsertionTime / avlInsertionTime);
    printf("Search Ratio: %f\n", bstSearchTime / avlSearchTime);
    printf("Deletion Ratio: %f\n", bstDeletionTime / avlDeletionTime);

    // TEST 4: Tree Structure Analysis
    printf("\n---------------\n");
    printf("Tree Structure Analysis:\n");   
    int avlHeight = calculateTreeHeight(avlRoot);
    int bstHeight = calculateTreeHeight(bstRoot);
    double theoreticalOptimalHeight = log2(dataSize + 1);

    printf("AVL Tree Height: %d\n", avlHeight);
    printf("BST Height: %d\n", bstHeight);  
    printf("Theoretical Optimal Height (log2(n+1)): %f\n\n\n", theoreticalOptimalHeight);



    // Free allocated memory
    freeTree(bstRoot);
    freeTree(avlRoot);
}


int main() { 
    srand(time(NULL)); // Seed for random number generation

    int testSize[] = {1000, 5000, 10000}; // Different sizes for testing
    int numberOfSizes = sizeof(testSize) / sizeof(testSize[0]);

    for (int index = 0; index < numberOfSizes; index++) {
        int dataSize = testSize[index];
        int* randomDataSet = (int*) malloc (dataSize * sizeof(int));
        int* sortedDataSet = (int*) malloc (dataSize * sizeof(int));
        int* reverseSortedDataSet = (int*) malloc (dataSize * sizeof(int));

        // Average Case: Random Data Set
        generateRandomDataSet(randomDataSet, dataSize);
        runPerformanceComparison(randomDataSet, dataSize, "Random");

        // Worst Case 1: Sorted Data Set
        generateSortedDataSet(sortedDataSet, dataSize);
        runPerformanceComparison(sortedDataSet, dataSize, "Sorted");

        // Worst Case 2: Reverse Sorted Data Set
        generateReverseSortedDataSet(reverseSortedDataSet, dataSize);
        runPerformanceComparison(reverseSortedDataSet, dataSize, "Reverse Sorted");

        free(randomDataSet);
        free(sortedDataSet);
        free(reverseSortedDataSet);
    }

    return 0;
}