#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

#define MAXVAL 32

typedef struct astr {
	char name[30];
	double gpa;
}element;

typedef struct node  * typeNodePtr;
typedef struct node {
	element data;
	int nodeNumber;
	typeNodePtr leftChild, rightChild;
} typeNode;

int countNumber = 1;
int searchnum;
int sp = 0;
int val[MAXVAL];
//���ÿ� ��� ��ȣ�� �����Ͽ� ó��

int mark[32] = {0};

void push(int nodeNum) {
	if (sp < MAXVAL)
		val[sp++] = nodeNum;
	else
		printf("error: stack full, can't push %d \n", nodeNum);
}

int pop() {
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty \n");
		return 0;
	}
}

typeNodePtr findNode(typeNodePtr head) {

	typeNodePtr prev;
	int sep;

	prev = NULL;

	if (!head->leftChild->leftChild || !head->leftChild->rightChild) {
		return head->leftChild;
	}
	else if (!head->rightChild->leftChild || !head->rightChild->rightChild) {
		return head->rightChild;
	}
	else {// �� �κп��� �������� ����

		findNode(head->rightChild);

		findNode(head->leftChild);
	}

	return prev;
}

typeNodePtr search_ins_position(typeNodePtr head) {
	typeNodePtr prev;
	int save;

	prev = NULL;
	while (head) {
		if (!(head->leftChild)) {
			// ���� �Ǵ� ������ ��尡 ������� �� �ش� �θ� ����� �ڸ��� ����
			return head;
		}
		else if (!(head->rightChild)) {
			return head;
		}
		else { 
			// ������ �̿��Ͽ� ���� ��� �Ǵ� ���� ������ ���� �̵�
			val[sp] = val[sp - 1] + 1;
			save = val[sp];
			prev = head;
			head = findNode(head);
		}
	}
	printf("Error\n");
	return prev;
}

void insert(typeNodePtr* root, char sname[30], double sgpa) {
	typeNodePtr ptr, temp;

	ptr = (typeNodePtr)malloc(sizeof(typeNodePtr));
	strcpy(ptr->data.name, sname);
	ptr->data.gpa = sgpa;
	ptr->leftChild = ptr->rightChild = NULL;
	ptr->nodeNumber = countNumber++;

	if (!(*root)) {
		*root = ptr;
		push(ptr->nodeNumber);
		mark[ptr->nodeNumber] = ptr->nodeNumber;
	}
	else { //����ִ� ���� Ȯ�� �� ���� ������ �̿��Ͽ� ó�� �Ͽ��� �Ѵ�.

		// ���ÿ� �θ��� ������ ������ �ϰ� �̷�ã�� ���� ó�� �Դ� ���ٸ� �ݺ��ϴ� ���°� ���ƺ���
		if (temp->leftChild == NULL) {
			temp->leftChild = ptr;
			mark[ptr->nodeNumber] = ptr->nodeNumber;
		}
		else if (temp->rightChild == NULL) {
			temp->rightChild = ptr;
			mark[ptr->nodeNumber] = ptr->nodeNumber;
		}
		
	}
}

void insert(struct node** root, int data, struct Queue* queue)
{
	struct node* temp = createNode(data);
	if (!*root)
	{
		*root = temp;
	}
	else
	{
		struct node* front = getFront(queue);
		if ((front->leftChild) == '\0')
		{
			front->leftChild = temp;
			temp->parent = front;
		}
		else if ((front->rightChild) == '\0')
		{
			front->rightChild = temp;
			temp->parent = front;
		}
		if (hasBothChild(front))       Dequeue(queue);
	}
	Enqueue(temp, queue);
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
		printf("%s %.2f", ptr->data.name, ptr->data.gpa);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void levelorder(typeNodePtr ptr) {



}

int main() {

	typeNodePtr root = NULL;
	int res;
	double gpa;
	char name[30];

	FILE* fp;
	fp = fopen("Studentdata.txt", "r");

	while (1) {
		res = fscanf(fp, "%s %lf", name, &gpa);
		if (res < 2) {
			break;
		}
		insert(&root, name, gpa);
	}

	printf("inorder�� ���� �մϴ�\n");
	inorder(root);

	printf("preorder�� ���� �մϴ�\n");
	preorder(root);
	/*
	printf("levelorder�� �����մϴ�\n");
	levelorder(root);
	*/

}