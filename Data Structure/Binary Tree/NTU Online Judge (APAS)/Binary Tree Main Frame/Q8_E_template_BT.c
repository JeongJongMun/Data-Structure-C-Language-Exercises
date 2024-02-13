//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section E - Binary Trees Questions
Purpose: Implementing the required functions for Question 8 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _btnode
{
    int item;
    struct _btnode *left;
    struct _btnode *right;
} BTNode; // You should not change the definition of BTNode

/////////////////////////////////////////////////////////////////////////////////

typedef struct _stackNode
{
    BTNode *btnode;
    struct _stackNode *next;
} StackNode;

typedef struct _stack
{
    StackNode *top;
} Stack;

///////////////////////// Function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
int hasGreatGrandchild(BTNode *node);

BTNode *createBTNode(int item);

BTNode *createTree();
void push(Stack *stack, BTNode *node);
BTNode *pop(Stack *stack);

void printTree(BTNode *node);
void removeAll(BTNode **node);

///////////////////////////// main() /////////////////////////////////////////////

int main()
{
    char e;
    int c, value;
    BTNode *root;

    c = 1;
    root = NULL;

    printf("1: Create a binary tree.\n");
    printf("2: Find the great grandchildren of the binary tree.\n");
    printf("0: Quit;\n");

    while (c != 0)
    {
        printf("Please input your choice(1/2/0): ");
        if (scanf("%d", &c) > 0)
        {
            switch (c)
            {
            case 1:
                removeAll(&root);
                root = createTree();
                printf("The resulting binary tree is: ");
                printTree(root);
                printf("\n");
                break;
            case 2:
                printf("\nThe values stored in all nodes of the tree that has at least one great-grandchild are: ");
                hasGreatGrandchild(root);
                removeAll(&root);
                break;
            case 0:
                removeAll(&root);
                break;
            default:
                printf("Choice unknown;\n");
                break;
            }
        }
        else
        {
            scanf("%c", &e);
        }
    }
    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

int hasGreatGrandchild(BTNode *node)
{
    /* add your code here */
    if (node == NULL)
        return -1;
    int left = hasGreatGrandchild(node->left);
    int right = hasGreatGrandchild(node->right);

    if (left + 1 > 2 || right + 1 > 2)
        printf("%d ", node->item);
    return ((left > right) ? left : right) + 1;
}
/*
TC1:
1
50 30 60 25 65 x x 20 x x x 10 75 x x x 15 x x
2 0
\n
ANS: 50

TC2:
1
1 2 3 4 5 6 7 8 9 x x x 10 11 x x x x 12 x x x x x 13 14 15 x x 16 x 17 x x 18 19 20 x x x x
2 0
\n
ANS: 6 4 2 16 15 13 3 1

TC3:
1
1 2 3 4 x x x x x
2 0
\n
ANS: NULL

TC4:
1
x
2 0
\n
ANS: NULL

TC5:
1
100 x x
2 0
\n
ANS: NULL

TC6:
1
55 100 x 200 x 300 x x x
2 0
\n
ANS: 55
*/

//////////////////////////////////////////////////////////////////////////////////

BTNode *createBTNode(int item)
{
    BTNode *newNode = malloc(sizeof(BTNode));
    newNode->item = item;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

//////////////////////////////////////////////////////////////////////////////////

BTNode *createTree()
{
    Stack stack;
    BTNode *root, *temp;
    char s;
    int item;

    stack.top = NULL;
    root = NULL;
    printf("Input an integer that you want to add to the binary tree. Any Alpha value will be treated as NULL.\n");
    printf("Enter an integer value for the root: ");
    if (scanf("%d", &item) > 0)
    {
        root = createBTNode(item);
        push(&stack, root);
    }
    else
    {
        scanf("%c", &s);
    }

    while ((temp = pop(&stack)) != NULL)
    {

        printf("Enter an integer value for the Left child of %d: ", temp->item);

        if (scanf("%d", &item) > 0)
        {
            temp->left = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        printf("Enter an integer value for the Right child of %d: ", temp->item);
        if (scanf("%d", &item) > 0)
        {
            temp->right = createBTNode(item);
        }
        else
        {
            scanf("%c", &s);
        }

        if (temp->right != NULL)
            push(&stack, temp->right);
        if (temp->left != NULL)
            push(&stack, temp->left);
    }
    return root;
}

void push(Stack *stack, BTNode *node)
{
    StackNode *temp;

    temp = malloc(sizeof(StackNode));
    if (temp == NULL)
        return;
    temp->btnode = node;
    if (stack->top == NULL)
    {
        stack->top = temp;
        temp->next = NULL;
    }
    else
    {
        temp->next = stack->top;
        stack->top = temp;
    }
}

BTNode *pop(Stack *stack)
{
    StackNode *temp, *top;
    BTNode *ptr;
    ptr = NULL;

    top = stack->top;
    if (top != NULL)
    {
        temp = top->next;
        ptr = top->btnode;

        stack->top = temp;
        free(top);
        top = NULL;
    }
    return ptr;
}

void printTree(BTNode *node)
{
    if (node == NULL)
        return;

    printTree(node->left);
    printf("%d ", node->item);
    printTree(node->right);
}

void removeAll(BTNode **node)
{
    if (*node != NULL)
    {
        removeAll(&((*node)->left));
        removeAll(&((*node)->right));
        free(*node);
        *node = NULL;
    }
}
