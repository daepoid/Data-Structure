#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct anod* Ty_Node_Ptr;
typedef struct anod {
	int key;     //�й�
	char name[50]; // �̸�
	Ty_Node_Ptr leftChild, rightChild; // ����� �ڽĿ� ���� ������
}Ty_Node;

int Tree_Height;

Ty_Node_Ptr search_ins_position(Ty_Node_Ptr root, char sname[50]) {
	Ty_Node_Ptr prev = NULL;

	while (root) {
		
		prev = root;
		if (strcmp(root->name, sname) > 0) { // node->name�� ������ ���Ľ� �ڿ� ���� ���
			root = root->leftChild;
		}
		else if (strcmp(root->name, sname) < 0) { // node->name�� ������ ���Ľ� �տ� ���� ���
			root = root->rightChild;
		}
		else if (strcmp(root->name, sname) == 0) { // �����Ϸ��� ������ ���� Ʈ���� ��尡 �̹� �ִ�.
			printf("�����Ϸ��� ��尡 Ʈ���� �̹� �ֽ��ϴ�.\n");
			printf("%s, %d\n", root->name, root->key);
			printf("�ش� ���� �ߺ��Ͽ� ���Ե��� ������, ����Ͽ� �����մϴ�.\n");
			return NULL;
		}
	}
	return prev;
}
// insert�� ��ġ�� ã�� �Լ�
// linked list �������� �ۼ��� ���� ����
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
// i :   �̸��� �й��� �Է¹޾� �̿� ���� �� ���ڵ带 BST �� �ִ´�.
void inorder(Ty_Node_Ptr ptr) {
	
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%s %d\n", ptr->name, ptr->key);
		inorder(ptr->rightChild);
	}
} // inorder ������� ��ȸ
// p :  ��� BST ���� ��� ���ڵ带 in-order ������ ����Ѵ� (�� �ٿ� �� ���ڵ� �� ���.)
void Delete_Node(Ty_Node_Ptr *root, char sname[50]) {
	Ty_Node_Ptr prev, ptr, temp, temp2;
	
	ptr = search_del_position(*root, sname, &prev);

	if (!ptr) {
		printf("%s�� Ʈ������ ã�� �� �����ϴ�.\n", sname);
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
		printf("���� �Ǿ����ϴ�\n");
		free(ptr);
	}
}  
////////////////////////////////////Ȯ��///////////////////////////
// d :  ���� ���ڵ��� �̸��� �Է¹޾� �� ���ڵ带 �����.
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
		printf("�̸� : %s  �й� : %d  ���� : %d\n", root->name, root->key, Tree_Level);
	}
	else {
		printf("%s�� ã�� �� �����ϴ�.\n", sname);
	}
}
// s :  �̸��� �Է� �޾� �̸� ���� ��带 ã�Ƽ� ����Ѵ� (����: �� ����� ������ ����� ��.) 
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
// h :  ��ü ����Ž��Ʈ���� ���̸� ���Ͽ� ����Ѵ�.
void Find_Brother(Ty_Node_Ptr root, char sname[50]) {
	Ty_Node_Ptr prev = NULL;
	
	while (root) {
		if (strcmp(root->name, sname) == 0) {
			if (!prev) {
				printf("��Ʈ ��� �Դϴ�.\n");
				break;
			}
			else {
				if (prev->leftChild && strcmp(prev->leftChild->name, sname) != 0) {
					printf("%s�� ������ %s �̰� ������ �ֽ��ϴ�.\n", sname, prev->leftChild->name);
				}
				else if (prev->rightChild && strcmp(prev->rightChild->name, sname) != 0) {
					printf("%s�� ������ %s �̰� ������ �ֽ��ϴ�.\n", sname, prev->rightChild->name);
				}
				else {
					printf("�ش���� ������ �����ϴ�.\n");
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
		printf("�Է��Ͻ� �̸��� Ʈ���� �����ϴ�.\n");
	}
}
// b :  �̸��� �Է¹޾� �̸� ���� ����� ���� �Ǵ� ���� ���� ����� ������ ����Ѵ�. (����� �������� ǥ���� ��.)
void Print_Parent_Node(Ty_Node_Ptr root, char sname[50]) {
	Ty_Node_Ptr prev = NULL;

	while (root) {
		if (strcmp(root->name, sname) == 0) {
			if (!prev) {
				printf("Ʈ���� ��Ʈ�Դϴ�.(parent����)\n");
			}
			else {
				printf("%s�� �θ�� %s\n", sname, prev->name);
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
// u :  �̸��� �Է¹޾� �� �̸��� ���� ����� �θ� ����� ������ ����Ѵ�.
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
	printf("=====Ʈ���� ����� �л����� ������ inorder ������� ���=====\n");
	inorder(root);

	while (1) {
		printf("������ �۾��� (i, p, d, s, h, b, u, e)? : ");
		scanf("%s", &CommandSelect); // %c�� �ϸ� scanf�� �ƴ϶� �ٸ� ���� ��� �Ұ� ����. 
		// Ŀ��Ʈ�� �Է��ϰ� ���͸� �Է��ϸ� �� ���� Ű�� �Է��� �� ó�� ���´�.
		switch (CommandSelect)
		{
		case 'i': // i :   �̸��� �й��� �Է¹޾� �̿� ���� �� ���ڵ带 BST �� �ִ´�.
			printf("�̸�, �й� ������ �����͸� �Է��� �ּ���\n");
			scanf("%s %d", name, &key);
			Insert_TreeNode(&root, name, key);
			break;
		case 'p': // p :  ��� BST ���� ��� ���ڵ带 in-order ������ ����Ѵ� (�� �ٿ� �� ���ڵ� �� ���.)
			printf("inorder������� ����մϴ�.\n");
			inorder(root);
			break;
		case 'd': // d :  ���� ���ڵ��� �̸��� �Է¹޾� �� ���ڵ带 �����.
			scanf("%s", name);
			Delete_Node(&root, name);
			break;
		case 's': // s :  �̸��� �Է� �޾� �̸� ���� ��带 ã�Ƽ� ����Ѵ� (����: �� ����� ������ ����� ��.) 
			scanf("%s", name);
			Search_TreeNode(root, name);
			break;
		case 'h': // h :  ��ü ����Ž��Ʈ���� ���̸� ���Ͽ� ����Ѵ�.
			Tree_Height = 0; // �ʱ�ȭ
			Find_Height(root, 0);
			printf("Ʈ���� ���� = %d\n", Tree_Height);
			break;
		case 'b': //    b :  �̸��� �Է¹޾� �̸� ���� ����� ���� �Ǵ� ���� ���� ����� ������ ����Ѵ�.
				  // (����� �������� ǥ���� ��.)
			scanf("%s", name);
			Find_Brother(root, name);
			break;
		case 'u': // u :  �̸��� �Է¹޾� �� �̸��� ���� ����� �θ� ����� ������ ����Ѵ�.
			scanf("%s", name);
			Print_Parent_Node(root, name);
			break;
		case 'e': // e :  ���α׷��� �����Ѵ�.
			printf("���α׷��� �����մϴ�\n");
			exit(1);
		}
	}

	return 0;
}