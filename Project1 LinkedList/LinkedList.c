#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable:4996)

typedef struct type_node *type_ptr;
typedef struct type_node
{
	char name[50];
	int st_no;
	float gpa;
	char phone[20];
	char province[30];
	type_ptr link;
} type_node;

type_ptr add_new_student(type_ptr* head);
type_ptr make_connectionlist(type_ptr* head);
type_ptr search_ins_position(type_ptr head, char* s_name);
int delet_node(type_ptr* head, char* stuname);
void Print_between(type_ptr first, char* A, char* B);
void Print_liked_list(type_ptr first);
void getCommand(char checkCommand[]);
void search_num(type_ptr head, char phone[]);

int main() {
	type_ptr head, add, test;
	char tnameA[50], tnameB[50], checkCommand[10];
	char phone[20];
	int num, res;
	char delname[50];
	

	head = NULL;
	test = NULL;

	make_connectionlist(&head);
	printf("<���ĵ� �л����>\n");
	Print_liked_list(head);

	getCommand(checkCommand);
	while (strcmp(checkCommand, "EX") != 0) {

		if (strcmp(checkCommand, "IN") == 0) { // IN ( Inserting a new student) : the data for a new student is read in and a new node is inserted to the linked list.
			
			test = add_new_student(&head);
			if (test != NULL) {
				printf("�߰��Ǿ����ϴ�.\n");
			}
			getCommand(checkCommand);
		}
		else if (strcmp(checkCommand, "PP") == 0) { // PP ( Partial print) : Two names A, B are read in and then all students whose name is between A and B are printed on the screen.
			printf("\n�� �л��� �̸��� �Է��ϼ��� ex)������ ������\n");
			scanf("%s %s", tnameA, tnameB);
			printf("\n----------�Է��� �� �л��� ������ �� �л��� ������ ���----------\n");
			Print_between(head, tnameA, tnameB);
			getCommand(checkCommand);
		}
		else if (strcmp(checkCommand, "DE") == 0) { // DE ( Deleting a student ) : A name is read in and the node with that name is deleted from the linked list.
			printf("�����Ϸ��� �л��� �̸��� �Է��ϼ��� : ");
			scanf("%s", delname);
			res = delet_node(&head, delname);
			if (res == 0) {
				printf("\n��Ͽ� �������� �ʴ� �л��̸��� �Է��ϼ̽��ϴ�.\n");
			}
			else {
				printf("\n%s�л��� ��Ͽ��� �����Ǿ����ϴ�.\n", delname);
			}
			getCommand(checkCommand);
		}
		else if (strcmp(checkCommand, "PT") == 0) { // PT (Print by telephone number) : The first three digits of the phone number is read in. Then all students whose phone number starts with the three digits are printed.
			printf("��ȭ��ȣ �� ���ڸ��� �Է��ϼ��� ex) 010 : ");
			scanf("%s", phone);
			search_num(head, phone);
			getCommand(checkCommand);
		}
		else if (strcmp(checkCommand, "PA") == 0) { // PA ( Print all) : print all students in the linked list.
			printf("********* ������ ���Ḯ��Ʈ *********\n\n");
			Print_liked_list(head);
			//printf("\n********* ���ĵ� ���Ḯ��Ʈ *********\n\n");
			//Sorted_First = Convert_to_sorted_list(First);
			//Print_linked_list(Sorted_First);
			getCommand(checkCommand);
		}
		else if (strcmp(checkCommand, "EX") == 0) { // EX ( Exit ) : exit from the loop and terminate the program.
			break;
		}
		else {
			getCommand(checkCommand);
		}
	}
}

type_ptr make_connectionlist(type_ptr* head) {
	type_ptr np, prev;
	char check_name[50];
	int check_st_no;
	float check_gpa;
	char check_phone[20];
	char check_province[30];
	int res;

	FILE* fp;
	fp = fopen("data.txt", "r");

	while (1) {
		res = fscanf(fp, "%s %d %f %s %s", check_name, &check_st_no, &check_gpa, check_phone, check_province);
		if (res < 5) {
			break;
		}
		np = (type_ptr)malloc(sizeof(type_node));
		strcpy(np->name, check_name);
		np->st_no = check_st_no;
		np->gpa = check_gpa;
		strcpy(np->phone, check_phone);
		strcpy(np->province, check_province);

		if (!head) {
			*head = np;
			np->link = NULL;
		}
		else {
			prev = search_ins_position(*head, check_name);
			if (!prev) {
				np->link = *head;
				*head = np;
			}
			else {
				np->link = prev->link;
				prev->link = np;
			}
		}
	}

	return *head;
}

type_ptr add_new_student(type_ptr* head) {
	type_ptr np, prev;
	char add_name[50], add_phone[20], add_province[30];
	int add_st_no;
	float add_gpa;
	printf("�߰��� �л��� �̸��� �Է��ϼ���\n");
	scanf("%s", add_name);
	printf("�߰��� �л��� �й��� �Է��ϼ���\n");
	scanf("%d", &add_st_no);
	printf("�߰��� �л��� gpa�� �Է��ϼ���\n");
	scanf("%f", &add_gpa);
	printf("�߰��� �л��� ��ȭ��ȣ�� �Է��ϼ��� ex) 010-1234-5678\n");
	scanf("%s", add_phone);
	printf("�߰��� �л��� ��� ������ �Է��ϼ��� ex)����\n");
	scanf("%s", add_province);

	np = (type_ptr)malloc(sizeof(type_node));
	strcpy(np->name, add_name);
	np->st_no = add_st_no;
	np->gpa = add_gpa;
	strcpy(np->phone, add_phone);
	strcpy(np->province, add_province);

	if (!head) {
		*head = np;
		np->link = NULL;
	}
	else {
		prev = search_ins_position(*head, add_name);
		if (!prev) {
			np->link = *head;
			*head = np;
		}
		else {
			np->link = prev->link;
			prev->link = np;
		}
	}
	return *head;
}

type_ptr search_ins_position(type_ptr head, char* s_name) { 
	type_ptr prev;

	prev = NULL;
	while (head) {
		if (strcmp(head->name, s_name) > 0) {
			return prev;
		}
		else {
			prev = head;
			head = head->link;
		}
	}
	return prev;
}

void getCommand(char checkCommand[]) {
	printf("Command�� �Է� : ");
	scanf("%s", checkCommand);
}

void search_num(type_ptr head, char phone[]) {

	type_ptr check;
	check = head;
	int i = 0, ret = 0;

	while (check) {
		if (strncmp(phone, check->phone, 3) == 0) {
			printf("%s %d %f %s %s\n", check->name, check->st_no, check->gpa, check->phone, check->province);
			i++;
		}
		check = check->link;
	}
	if (i == 0) {
		printf("\n�Է��� ���ڷ� �����ϴ� ��ȭ��ȣ�� ��Ͽ� �����ϴ�.\n");
	}

}

void Print_between(type_ptr head, char* A, char* B) {
	type_ptr prev_A, prev_B;
	prev_A = head;
	prev_B = head;

	while (prev_A) {
		if (strcmp(prev_A->name, A) == 0) {
			while (prev_B) {
				if (strcmp(prev_B->name, B) == 0) {
					break;
				}
				else {
					prev_B = prev_B->link;
				}
			}
			if (prev_B == NULL) {
				printf("\n%s�л��� ��Ͽ� �����ϴ�.\n", B);
			}
			else {
				printf("\n<%s�л��� %s�л����� �л����>\n", A, B);
				while (prev_A != prev_B) {
					printf("%s %d %f %s %s\n", prev_A->name, prev_A->st_no, prev_A->gpa, prev_A->phone, prev_A->province);
					prev_A = prev_A->link;
				}
				printf("%s %d %f %s %s\n", prev_B->name, prev_B->st_no, prev_B->gpa, prev_B->phone, prev_B->province);
			}
			break;
		}
		else {
			prev_A = prev_A->link;
		}
	}
	if (prev_A == NULL) {
		printf("\n%s�л��� ��Ͽ� �����ϴ�.\n", A);
	}
}

int delet_node(type_ptr* head, char* delname) {
	type_ptr prev, curr;
	int found = 0;

	curr = *head;
	prev = NULL;
	while (curr) {
		if (strcmp(curr->name, delname) == 0) {
			if (!prev) {
				*head = curr->link;
			}
			else {
				prev->link = curr->link;
			}
			return 1;
		}
		else {
			prev = curr;
			curr = curr->link;
		}
	}
	return 0;
}

void Print_liked_list(type_ptr head) {
	while (head) {
		printf("%s %d %f %s %s\n", head->name, head->st_no, head->gpa, head->phone, head->province);
		head = head->link;
	}
}