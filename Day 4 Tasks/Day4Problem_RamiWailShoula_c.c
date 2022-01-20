//day4Problem_RamiWailShoula_c.c
//#includes
# include <stdio.h>
# include <conio.h>
# include <stdlib.h>
#include"ITI.h"

//struct to access Binary Tree elements by means of handle node
typedef struct BinaryTree {
    int data;
    struct BinaryTree* lchild, * rchild;
} node;
//data storage for delete func
struct node2
{
    int data2;
    struct node2* lchild, * rchild;
};
//funct that allocates a new node with the
//given data while also initializing NULL left and right pointers.
struct node2* newNode(int data2)
{
    struct node2* node2 = (struct node2*)
        malloc(sizeof(struct node2));

    node2->data2 = data2;
    node2->lchild = NULL;
    node2->rchild = NULL;
    return(node2);
}

//funct declarations
void insert(node*, node*);
void inorder(node*);
void preorder(node*);
void postorder(node*);
void _deleteTree(node*);
void deleteTree(node**);
node* search(node*, int, node**);

//main declaration
void main() {
    int choice;
    char ans = 'N';
    int key;
    node* new_node, * root, * tmp, * parent;
    node* get_node();
    root = NULL;
    clrscr(); //ITI.h

    printf("\nProgram For Binary Tree (Creation, Searching, Recursive traversals and full deletion) ");
    do {
        printf("\n1.Create");
        printf("\n2.Search");
        printf("\n3.Recursive Traversals");
        printf("\n4.Delete Tree");
        printf("\n5.Exit");
        printf("\nEnter your choice :");
        scanf_s("%d", &choice);

        switch (choice) {
        case 1:
            do {
                new_node = get_node();
                printf("\nEnter The Element ");
                scanf_s("%d", &new_node->data);

                if (root == NULL) /* Tree is not Created */
                    root = new_node;
                else
                    insert(root, new_node);

                printf("\nWant To enter More Elements?(y/n)");
                ans = getKey(); //ITI.h
            } while (ans == 'y');
            break;

        case 2:
            printf("\nEnter Element to be searched :");
            scanf_s("%d", &key);

            tmp = search(root, key, &parent);
            printf("\nParent of node %d is %d", tmp->data, parent->data);
            break;

        case 3:
            if (root == NULL)
                printf("Tree Is Not Created");
            else {
                printf("\nThe Inorder display : "); //L V R
                inorder(root);
                printf("\nThe Preorder display : "); //V L R
                preorder(root);
                printf("\nThe Postorder display : "); //L R V
                postorder(root);
            }
            break;
        case 4:
            if (root == NULL)
                printf("Tree Is Not Created");
            else {
                deleteTree(&root);
                root = NULL;
                printf("\n Tree deleted ");
                //wonderful thing here is that the tree is emptied completely as if u are starting from scratch 
                //also, it is deleted in postorder direction (from the very lastmost leaf upwards recursively so no errors can occur
            }
            break;
        }
    } while (choice != 5);
}

//funct to get new Node
node* get_node() {
    node* temp; //using temporary node
    temp = (node*)malloc(sizeof(node));
    temp->lchild = NULL;
    temp->rchild = NULL;
    return temp;
}

//funct to create binary tree
void insert(node* root, node* new_node) {
    if (new_node->data < root->data) {
        if (root->lchild == NULL)
            root->lchild = new_node;
        else
            insert(root->lchild, new_node);
    }

    if (new_node->data > root->data) {
        if (root->rchild == NULL)
            root->rchild = new_node;
        else
            insert(root->rchild, new_node);
    }
}

//funct to search for node from binary tree
node* search(node* root, int key, node** parent) {
    node* temp;
    temp = root;
    while (temp != NULL) {
        if (temp->data == key) {
            printf("\nThe %d Element is Present", temp->data);
            return temp;
        }
        *parent = temp;

        if (temp->data > key)
            temp = temp->lchild;
        else
            temp = temp->rchild;
    }
    return NULL;
}

//funct for recursive tree traversal, displays the tree in inorder fashion L V R
void inorder(node* temp) {
    if (temp != NULL) {
        inorder(temp->lchild);
        printf("%d", temp->data);
        inorder(temp->rchild);
    }
}

//funct for recursive tree traversal, displays the tree in preorder fashion V L R
void preorder(node* temp) {
    if (temp != NULL) {
        printf("%d", temp->data);
        preorder(temp->lchild);
        preorder(temp->rchild);
    }
}

//funct for recursive tree traversal, displays the tree in postorder fashion L R V
void postorder(node* temp) {
    if (temp != NULL) {
        postorder(temp->lchild);
        postorder(temp->rchild);
        printf("%d", temp->data);
    }
}

//funct for recursive deletion of tree, traverses tree in post order to
//to delete each and every node of the tree
void _deleteTree(node* temp)
{
    if (temp == NULL) return;

    /* first delete both subtrees */
    _deleteTree(temp->lchild);
    _deleteTree(temp->rchild);

    /* then delete the node */
    printf("\n Deleting node: %d", temp->data);
    free(temp);
}

//funct to delete a full tree from the bottom most leaf (postorder direction), also sets the root as NULL
//this was a new tree can be re-created from scratch
void deleteTree(struct node** temp)
{
    _deleteTree(*temp);
    *temp = NULL;
}