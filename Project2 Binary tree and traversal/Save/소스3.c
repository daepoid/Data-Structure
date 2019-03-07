// Program for linked implementation of complete binary tree
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

// For Queue Size
#define SIZE 50

// A tree node

typedef struct astr {
	char name[30];
	double gpa;
}element;

typedef struct node  * typeNodePtr;
typedef struct node {
	element data;
	typeNodePtr leftChild, rightChild;
} typeNode;


// A queue node
typedef struct Queue * typeQueuePtr;
typedef struct Queue 
{
	int front, rear;
	int size;
	struct node* *array;
} typeQueue;

// A utility function to create a new Queue
typeQueuePtr createQueue(int size)
{
	typeQueuePtr queue;
	queue = (typeQueuePtr)malloc(sizeof(typeQueuePtr));

	queue->front = queue->rear = -1;
	queue->size = size;

	queue->array = (typeNodePtr*) malloc(queue->size * sizeof(typeNodePtr));

	int i;
	for (i = 0; i < size; ++i)
		queue->array[i] = NULL;

	return queue;
}

// Standard Queue Functions
bool isEmpty(typeQueuePtr queue)
{
	return queue->front == -1;
}

bool isFull(typeQueuePtr queue)
{
	return queue->rear == queue->size - 1;
}

int hasOnlyOneItem(typeQueuePtr queue)
{
	return queue->front == queue->rear;
}

void Enqueue(typeNodePtr root, typeQueuePtr queue)
{
	if (isFull(queue))
		return;

	queue->array[++queue->rear] = root;

	if (isEmpty(queue))
		++queue->front;
}

typeNodePtr Dequeue(typeQueuePtr queue)
{
	if (isEmpty(queue))
		return NULL;

	typeNodePtr temp = queue->array[queue->front];

	if (hasOnlyOneItem(queue))
		queue->front = queue->rear = -1;
	else
		++queue->front;

	return temp;
}

typeNodePtr getFront(typeQueuePtr queue)
{
	return queue->array[queue->front];
}

// A utility function to check if a tree node has both left and right children
int hasBothChild(typeNodePtr temp)
{
	return temp && temp->leftChild && temp->rightChild;
}

// Function to insert a new node in complete binary tree
void insert(typeNodePtr* root, char sname[], double sgpa, struct Queue* queue)
{
	// Create a new node for given data
	typeNodePtr ptr;

	ptr = (typeNodePtr)malloc(sizeof(typeNode));
	strcpy(ptr->data.name, sname);
	ptr->data.gpa = sgpa;
	ptr->leftChild = ptr->rightChild = NULL;

	// If the tree is empty, initialize the root with new node.
	if (!*root)
		*root = ptr;

	else
	{
		// get the front node of the queue.
		typeNodePtr front = getFront(queue);

		// If the left child of this front node doesn¡¯t exist, set the
		// left child as the new node
		if (!front->leftChild)
			front->leftChild = ptr;

		// If the right child of this front node doesn¡¯t exist, set the
		// right child as the new node
		else if (!front->rightChild)
			front->rightChild = ptr;

		// If the front node has both the left child and right child,
		// Dequeue() it.
		if (hasBothChild(front))
			Dequeue(queue);
	}

	// Enqueue() the new node for later insertions
	Enqueue(ptr, queue);
}

// Standard level order traversal to test above function
void levelOrder(typeNodePtr root)
{
	struct Queue* queue = makeQueue(SIZE);

	Enqueue(root, queue);

	while (!isEmpty(queue))
	{
		typeNodePtr temp = Dequeue(queue);

		printf("%d ", temp->data);

		if (temp->leftChild)
			Enqueue(temp->leftChild, queue);

		if (temp->rightChild)
			Enqueue(temp->rightChild, queue);
	}
}

void inorder(typeNodePtr ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%s %.2f\n", ptr->data.name, ptr->data.gpa);
		inorder(ptr->rightChild);
	}
}

void preorder(typeNodePtr ptr) {

	if (ptr) {
		printf("%s %.2f\n", ptr->data.name, ptr->data.gpa);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}


// Driver program to test above functions
int main()
{
	typeNodePtr root = NULL;
	typeQueuePtr queue = makeQueue(SIZE);
	int i, res;
	char name[30];
	double gpa;

	FILE* fp;
	fp = fopen("Studentdata.txt", "r");

	while (1) {
		res = fscanf(fp, "%s %lf", name, &gpa);
		if (res < 2) {
			break;
		}
		insert(&root, name, gpa, queue);
	}
	printf("inorder\n");
	inorder(root);
	printf("\n----------------------------------\n");
	printf("preorder\n");
	preorder(root);
	//levelOrder(root);

	return 0;
}
