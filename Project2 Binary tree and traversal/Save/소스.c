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
//스택에 노드 번호를 삽입하여 처리

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
	else {// 이 부분에서 스택으로 관리

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
			// 왼쪽 또는 오른쪽 노드가 비어있을 때 해당 부모 노드의 자리를 리턴
			return head;
		}
		else if (!(head->rightChild)) {
			return head;
		}
		else { 
			// 스택을 이용하여 형제 노드 또는 다음 세대의 노드로 이동
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
	else { //비어있는 곳을 확인 할 때에 스택을 이용하여 처리 하여야 한다.

		// 스택에 부모의 노드까지 저장을 하고 미로찾기 과제 처럼 왔다 갔다를 반복하는 형태가 좋아보임
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

	printf("inorder를 실행 합니다\n");
	inorder(root);

	printf("preorder를 실행 합니다\n");
	preorder(root);
	/*
	printf("levelorder를 실행합니다\n");
	levelorder(root);
	*/

}