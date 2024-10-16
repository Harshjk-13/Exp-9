#include <stdio.h>
#include <stdlib.h>

// Node structure definition for BST
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a node into the BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        // If the tree is empty, create a new node and return it as the root
        return createNode(value);
    }

    // Recursively insert the value in the correct subtree
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    }

    return root;
}

// Function to search for a value in the BST
struct Node* search(struct Node* root, int value) {
    if (root == NULL || root->data == value) {
        // If the root is NULL or the value is found, return the root
        return root;
    }

    // Recursively search in the left or right subtree
    if (value < root->data) {
        return search(root->left, value);
    } else {
        return search(root->right, value);
    }
}

// Function to find the minimum value node in a subtree
struct Node* findMin(struct Node* root) {
    struct Node* current = root;

    // The leftmost node will have the minimum value
    while (current && current->left != NULL) {
        current = current->left;
    }

    return current;
}

// Function to delete a node from the BST
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        return root;  // If the tree is empty, return NULL
    }

    // Recursively find the node to be deleted
    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Node to be deleted is found

        // Case 1: Node with only one child or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Node with two children
        // Get the in-order successor (smallest in the right subtree)
        struct Node* temp = findMin(root->right);

        // Copy the in-order successor's value to this node
        root->data = temp->data;

        // Delete the in-order successor
        root->right = deleteNode(root->right, temp->data);
    }

    return root;
}

// Function for in-order traversal (left, root, right)
void inOrder(struct Node* root) {
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->data);
        inOrder(root->right);
    }
}

// Function for pre-order traversal (root, left, right)
void preOrder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(root->left);
        preOrder(root->right);
    }
}

// Function for post-order traversal (left, right, root)
void postOrder(struct Node* root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->data);
    }
}

// Main function to demonstrate BST operations
int main() {
    struct Node* root = NULL;

    // Insert nodes into the BST
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("In-order traversal: ");
    inOrder(root);
    printf("\n");

    printf("Pre-order traversal: ");
    preOrder(root);
    printf("\n");

    printf("Post-order traversal: ");
    postOrder(root);
    printf("\n");

    // Search for a value
    int searchValue = 40;
    struct Node* searchResult = search(root, searchValue);
    if (searchResult != NULL) {
        printf("%d found in the BST.\n", searchValue);
    } else {
        printf("%d not found in the BST.\n", searchValue);
    }

    // Delete a node from the BST
    int deleteValue = 50;
    root = deleteNode(root, deleteValue);
    printf("In-order traversal after deleting %d: ", deleteValue);
    inOrder(root);
    printf("\n");

    return 0;
}
