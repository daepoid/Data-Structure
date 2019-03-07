#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

// 큐의 크기
#define SIZE 50
int nodeNumber = 0;

typedef struct astr { // 트리 노드의 정보(이름과 gpa)를 저장

	char name[30];
	double gpa;

}element;

typedef struct node  * typeNodePtr;
typedef struct node { // 트리 노드

	element data;
	int nodeNumber;
	typeNodePtr leftChild, rightChild;

} typeNode; // 트리 노드에 꼭 node Number를 저장 하여야 하는가?

typedef struct Queue * typeQueuePtr;
typedef struct Queue { // 큐 노드

	int front, rear;
	int size;
	typeNodePtr *array;

} typeQueue;

// 새로운 큐를 만들기 위한 함수
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

// ppt에 나와있는 큐 ADT를 구현
// ppt와 실제 사용 방법에 따라 구현에 차이가 있다.
// 큐 - P.10
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
} // ppt에서는 queue를 반환 하지만 굳이 반환 값이 있을 필요가 없어 void 형으로 선언

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

// 완전이진트리의 형태로 새로운 트리노드를 삽입하는 함수
void insert(typeNodePtr* root, char sname[], double sgpa, typeQueuePtr queue)
{
	
	typeNodePtr ptr;

	ptr = (typeNodePtr)malloc(sizeof(typeNode)); // 데이터를 함수 밖에서 받아오고 그 정보를 저장한 노드 생성
	strcpy(ptr->data.name, sname);
	ptr->data.gpa = sgpa;
	ptr->leftChild = ptr->rightChild = NULL;
	ptr->nodeNumber = ++nodeNumber;

	// 맨 처음에 트리가 비어있을 때 if문 안으로 들어감
	// 밑의 코드는 search_ins_position 함수의 구성과 유사
	// 작성한 트리구조는 LinkedList를 변형한 형태이기 때문
	if (!*root) {
		*root = ptr;
	}
	else{

		// 노드를 초기화
		typeNodePtr front = queue->array[queue->front];

		// 왼족 노드가 비어있으면 해당 노드 부터 채운다
		if (!front->leftChild)
			front->leftChild = ptr;

		// 왼쪽이 비어있디 않아야 오른쪽 노드를 채울 기회가 있다
		else if (!front->rightChild)
			front->rightChild = ptr;

		//왼쪽노드, 오른쪽 노드 이중에 하나라도 비어있다면 성립하지 않는다.
		if (front->leftChild && front->rightChild) // front && 를 삭제
			deleteQueue(queue);
	}
	addQueue(ptr, queue);
}
// inorder, preorder, levelorder 모두 ppt에 나와있는 코드
void inorder(typeNodePtr ptr) { // 중위순회

	if (ptr) {
		inorder(ptr->leftChild);
		printf("%s\t%.2f\t%2d번째 노드\n", ptr->data.name, ptr->data.gpa, ptr->nodeNumber);
		inorder(ptr->rightChild);
	}
}

void preorder(typeNodePtr ptr) { // 전위 순회

	if (ptr) {
		printf("%s\t%.2f\t%2d번째 노드\n", ptr->data.name, ptr->data.gpa, ptr->nodeNumber);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}

void levelOrder(typeNodePtr root){ // 레벨 순서 순회

	typeQueuePtr queue = createQueue(SIZE);
	typeNodePtr ptr;

	addQueue(root, queue);

	while (!isEmpty(queue))
	{
		ptr = deleteQueue(queue);
		printf("%s\t%.2f\t%2d번째 노드\n", ptr->data.name, ptr->data.gpa, ptr->nodeNumber);

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
