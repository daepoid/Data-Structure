#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

// ť�� ũ��
#define SIZE 50
int nodeNumber = 0;

typedef struct astr { // Ʈ�� ����� ����(�̸��� gpa)�� ����

	char name[30];
	double gpa;

}element;

typedef struct node  * typeNodePtr;
typedef struct node { // Ʈ�� ���

	element data;
	int nodeNumber;
	typeNodePtr leftChild, rightChild;

} typeNode; // Ʈ�� ��忡 �� node Number�� ���� �Ͽ��� �ϴ°�?

typedef struct Queue * typeQueuePtr;
typedef struct Queue { // ť ���

	int front, rear;
	int size;
	typeNodePtr *array;

} typeQueue;

// ���ο� ť�� ����� ���� �Լ�
typeQueuePtr createQueue(int size)
{
	typeQueuePtr queue;
	queue = (typeQueuePtr)malloc(sizeof(typeQueuePtr));

	queue->front = queue->rear = -1;
	queue->size = size;

	queue->array = (typeNodePtr*) malloc(queue->size * sizeof(typeNodePtr));

	int i;
	for (i = 0; i < size; ++i) {
		queue->array[i] = NULL;
	}
	return queue;
}

// ppt�� �����ִ� ť ADT�� ����
// ppt�� ���� ��� ����� ���� ������ ���̰� �ִ�.
// ť - P.10
int isEmpty(typeQueuePtr queue)
{
	return queue->front == -1;
}

int isFull(typeQueuePtr queue)
{
	return queue->rear == queue->size - 1;
}

void addQueue(typeNodePtr root, typeQueuePtr queue)
{
	if (isFull(queue)) {
		;
	}
	queue->array[++queue->rear] = root;

	if (isEmpty(queue)) {
		++queue->front;
	}
} // ppt������ queue�� ��ȯ ������ ���� ��ȯ ���� ���� �ʿ䰡 ���� void ������ ����

typeNodePtr deleteQueue(typeQueuePtr queue)
{
	if (isEmpty(queue))
		return NULL;

	typeNodePtr ptr = queue->array[queue->front];

	if (queue->front == queue->rear) {
		queue->front = queue->rear = -1;
	}
	else {
		++queue->front;
	}

	return ptr;
}

// ��������Ʈ���� ���·� ���ο� Ʈ����带 �����ϴ� �Լ�
void insert(typeNodePtr* root, char sname[], double sgpa, typeQueuePtr queue)
{
	
	typeNodePtr ptr;

	ptr = (typeNodePtr)malloc(sizeof(typeNode)); // �����͸� �Լ� �ۿ��� �޾ƿ��� �� ������ ������ ��� ����
	strcpy(ptr->data.name, sname);
	ptr->data.gpa = sgpa;
	ptr->leftChild = ptr->rightChild = NULL;
	ptr->nodeNumber = ++nodeNumber;

	// �� ó���� Ʈ���� ������� �� if�� ������ ��
	// ���� �ڵ�� search_ins_position �Լ��� ������ ����
	// �ۼ��� Ʈ�������� LinkedList�� ������ �����̱� ����
	if (!*root) {
		*root = ptr;
	}
	else{

		// ��带 �ʱ�ȭ
		typeNodePtr front = queue->array[queue->front];

		// ���� ��尡 ��������� �ش� ��� ���� ä���
		if (!front->leftChild)
			front->leftChild = ptr;

		// ������ ����ֵ� �ʾƾ� ������ ��带 ä�� ��ȸ�� �ִ�
		else if (!front->rightChild)
			front->rightChild = ptr;

		//���ʳ��, ������ ��� ���߿� �ϳ��� ����ִٸ� �������� �ʴ´�.
		if (front->leftChild && front->rightChild) // front && �� ����
			deleteQueue(queue);
	}
	addQueue(ptr, queue);
}
// inorder, preorder, levelorder ��� ppt�� �����ִ� �ڵ�
void inorder(typeNodePtr ptr) { // ������ȸ

	if (ptr) {
		inorder(ptr->leftChild);
		printf("%s\t%.2f\t%2d��° ���\n", ptr->data.name, ptr->data.gpa, ptr->nodeNumber);
		inorder(ptr->rightChild);
	}
}

void preorder(typeNodePtr ptr) { // ���� ��ȸ

	if (ptr) {
		printf("%s\t%.2f\t%2d��° ���\n", ptr->data.name, ptr->data.gpa, ptr->nodeNumber);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void levelOrder(typeNodePtr root){ // ���� ���� ��ȸ

	typeQueuePtr queue = createQueue(SIZE);
	typeNodePtr ptr;

	addQueue(root, queue);

	while (!isEmpty(queue))
	{
		ptr = deleteQueue(queue);
		printf("%s\t%.2f\t%2d��° ���\n", ptr->data.name, ptr->data.gpa, ptr->nodeNumber);

		if (ptr->leftChild) {
			addQueue(ptr->leftChild, queue);
		}
		if (ptr->rightChild) {
			addQueue(ptr->rightChild, queue);
		}
	}
}

int main()
{
	typeNodePtr root = NULL;
	typeQueuePtr queue = createQueue(SIZE);
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
	printf("\n==========================================\n");
	printf("inorder\n");
	inorder(root);
	printf("\n==========================================\n");
	printf("preorder\n");
	preorder(root);
	printf("\n==========================================\n");
	printf("levelOrder\n");
	levelOrder(root);

	return 0;
}
