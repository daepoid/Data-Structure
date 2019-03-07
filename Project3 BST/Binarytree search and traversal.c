#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct anod* Ty_Node_Ptr;
typedef struct anod {
	int key;     //학번
	char name[50]; // 이름
	Ty_Node_Ptr leftChild, rightChild; // 노드의 자식에 대한 포인터
}Ty_Node;

int Tree_Height;

Ty_Node_Ptr search_ins_position(Ty_Node_Ptr root, char sname[50]) {
	Ty_Node_Ptr prev = NULL;

	while (root) {
		
		prev = root;
		if (strcmp(root->name, sname) > 0) { // node->name이 사전식 정렬시 뒤에 오는 경우
			root = root->leftChild;
		}
		else if (strcmp(root->name, sname) < 0) { // node->name이 사전식 정렬시 앞에 오는 경우
			root = root->rightChild;
		}
		else if (strcmp(root->name, sname) == 0) { // 삽입하려는 정보를 가진 트리의 노드가 이미 있다.
			printf("삽입하려는 노드가 트리에 이미 있습니다.\n");
			printf("%s, %d\n", root->name, root->key);
			printf("해당 노드는 중복하여 삽입되지 않으며, 계속하여 진행합니다.\n");
			return NULL;
		}
	}
	return prev;
}
// insert할 위치를 찾는 함수
// linked list 과제에서 작성한 것을 응용
Ty_Node_Ptr search_del_position(Ty_Node_Ptr root, char sname[50], Ty_Node_Ptr* prev) {
	
	*prev = NULL;
	
	while (root) {
		
		if (strcmp(root->name, sname) > 0) {
			*prev = root;
			root = root->leftChild;
		}
		else if (strcmp(root->name, sname) < 0) {
			*prev = root;
			root = root->rightChild;
		}
		else if (strcmp(root->name, sname) == 0) {
			return root;
		}
	}
	return NULL;
}

void Insert_TreeNode(Ty_Node_Ptr* root, char sname[50], int key) {
	Ty_Node_Ptr ptr, temp;

	ptr = (Ty_Node_Ptr)malloc(sizeof(Ty_Node));
	ptr->key = key;
	strcpy(ptr->name, sname);
	ptr->leftChild = ptr->rightChild = NULL;

	if (!*root) {
		*root = ptr;
	}
	else {
		temp = search_ins_position(*root, sname);
		if(temp) {
			if (strcmp(temp->name, sname) > 0) {
				temp->leftChild = ptr;
			}
			else {
				temp->rightChild = ptr;
			}
		}
	}
}
// i :   이름과 학번을 입력받아 이에 대한 새 레코드를 BST 에 넣는다.
void inorder(Ty_Node_Ptr ptr) {
	
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%s %d\n", ptr->name, ptr->key);
		inorder(ptr->rightChild);
	}
} // inorder 방식으로 순회
// p :  모든 BST 안의 모든 레코드를 in-order 순으로 출력한다 (한 줄에 한 레코드 씩 출력.)
void Delete_Node(Ty_Node_Ptr *root, char sname[50]) {
	Ty_Node_Ptr prev, ptr, temp, temp2;
	
	ptr = search_del_position(*root, sname, &prev);

	if (!ptr) {
		printf("%s를 트리에서 찾을 수 없습니다.\n", sname);
	}
	else {
		if (ptr->leftChild && ptr->rightChild) {
			temp2 = ptr->leftChild;
			prev = ptr;
			while (temp2->rightChild) {
				prev = temp2;
				temp2 = temp2->rightChild;
			}
			ptr->key = temp2->key;
			strcpy(ptr->name, temp2->name);
			ptr = temp2;
		}

		temp = ptr->leftChild;
		
		if (!temp) {
			temp = ptr->rightChild;
		}
		if (!prev) {
			*root = temp;
		}
		else if (prev->leftChild == ptr) {
			prev->leftChild = temp;
		}
		else {
			prev->rightChild = temp;
		}
		printf("삭제 되었습니다\n");
		free(ptr);
	}
}  
////////////////////////////////////확인///////////////////////////
// d :  지울 레코드의 이름을 입력받아 그 레코드를 지운다.
void Search_TreeNode(Ty_Node_Ptr root, char sname[50]) {
	int Tree_Level = 1;
	
	while (root) {
		
		if (strcmp(root->name, sname) > 0) {
			root = root->leftChild;
			Tree_Level++;
		}
		else if (strcmp(root->name, sname) < 0) {
			root = root->rightChild;
			Tree_Level++;
		}
		else if (strcmp(root->name, sname) == 0) {
			break;
		}
	}
	if (root) {
		printf("이름 : %s  학번 : %d  레벨 : %d\n", root->name, root->key, Tree_Level);
	}
	else {
		printf("%s을 찾을 수 없습니다.\n", sname);
	}
}
// s :  이름을 입력 받아 이를 가진 노드를 찾아서 출력한다 (주의: 이 노드의 레벨도 출력할 것.) 
void Find_Height(Ty_Node_Ptr root, int Tree_Level) {
	if (Tree_Height < Tree_Level) {
		Tree_Height = Tree_Level;
	}

	Tree_Level++;
	
	if (root) {
		Find_Height(root->leftChild, Tree_Level);
		Find_Height(root->rightChild, Tree_Level);
	}
}
// h :  전체 이진탐색트리의 높이를 구하여 출력한다.
void Find_Brother(Ty_Node_Ptr root, char sname[50]) {
	Ty_Node_Ptr prev = NULL;
	
	while (root) {
		if (strcmp(root->name, sname) == 0) {
			if (!prev) {
				printf("루트 노드 입니다.\n");
				break;
			}
			else {
				if (prev->leftChild && strcmp(prev->leftChild->name, sname) != 0) {
					printf("%s의 형제는 %s 이고 좌측에 있습니다.\n", sname, prev->leftChild->name);
				}
				else if (prev->rightChild && strcmp(prev->rightChild->name, sname) != 0) {
					printf("%s의 형제는 %s 이고 우측에 있습니다.\n", sname, prev->rightChild->name);
				}
				else {
					printf("해당노드는 형제가 없습니다.\n");
				}
				break;
			}
		}
		else if (strcmp(root->name, sname) > 0) {
			prev = root;
			root = root->leftChild;
		}
		else {
			prev = root;
			root = root->rightChild;
		}
	}
	if (!root) {
		printf("입력하신 이름이 트리에 없습니다.\n");
	}
}
// b :  이름을 입력받아 이를 가진 노드의 우측 또는 좌측 형제 노드의 내용을 출력한다. (어느측 형제인지 표시할 것.)
void Print_Parent_Node(Ty_Node_Ptr root, char sname[50]) {
	Ty_Node_Ptr prev = NULL;

	while (root) {
		if (strcmp(root->name, sname) == 0) {
			if (!prev) {
				printf("트리의 루트입니다.(parent없음)\n");
			}
			else {
				printf("%s의 부모는 %s\n", sname, prev->name);
			}
			break;
		}
		else if (strcmp(root->name, sname) > 0) {
			prev = root;
			root = root->leftChild;
		}
		else {
			prev = root;
			root = root->rightChild;
		}
	}
}
// u :  이름을 입력받아 이 이름을 가진 노드의 부모 노드의 내용을 출력한다.
int main() {
	Ty_Node_Ptr root = NULL;
	int res, key;
	char CommandSelect, name[50];

	FILE* fp;
	fp = fopen("sdata.txt", "r");

	while (1) {
		res = fscanf(fp, "%d %s", &key, name);
		if (res < 2) {
			break;
		}
		Insert_TreeNode(&root, name, key);
	}
	printf("=====트리에 저장된 학생들의 정보를 inorder 방식으로 출력=====\n");
	inorder(root);

	while (1) {
		printf("수행할 작업은 (i, p, d, s, h, b, u, e)? : ");
		scanf("%s", &CommandSelect); // %c로 하면 scanf가 아니라 다른 것을 써야 할거 같다. 
		// 커멘트를 입력하고 엔터를 입력하면 두 개의 키를 입력한 것 처럼 나온다.
		switch (CommandSelect)
		{
		case 'i': // i :   이름과 학번을 입력받아 이에 대한 새 레코드를 BST 에 넣는다.
			printf("이름, 학번 순서로 데이터를 입력해 주세요\n");
			scanf("%s %d", name, &key);
			Insert_TreeNode(&root, name, key);
			break;
		case 'p': // p :  모든 BST 안의 모든 레코드를 in-order 순으로 출력한다 (한 줄에 한 레코드 씩 출력.)
			printf("inorder방식으로 출력합니다.\n");
			inorder(root);
			break;
		case 'd': // d :  지울 레코드의 이름을 입력받아 그 레코드를 지운다.
			scanf("%s", name);
			Delete_Node(&root, name);
			break;
		case 's': // s :  이름을 입력 받아 이를 가진 노드를 찾아서 출력한다 (주의: 이 노드의 레벨도 출력할 것.) 
			scanf("%s", name);
			Search_TreeNode(root, name);
			break;
		case 'h': // h :  전체 이진탐색트리의 높이를 구하여 출력한다.
			Tree_Height = 0; // 초기화
			Find_Height(root, 0);
			printf("트리의 높이 = %d\n", Tree_Height);
			break;
		case 'b': //    b :  이름을 입력받아 이를 가진 노드의 우측 또는 좌측 형제 노드의 내용을 출력한다.
				  // (어느측 형제인지 표시할 것.)
			scanf("%s", name);
			Find_Brother(root, name);
			break;
		case 'u': // u :  이름을 입력받아 이 이름을 가진 노드의 부모 노드의 내용을 출력한다.
			scanf("%s", name);
			Print_Parent_Node(root, name);
			break;
		case 'e': // e :  프로그램을 종료한다.
			printf("프로그램을 종료합니다\n");
			exit(1);
		}
	}

	return 0;
}