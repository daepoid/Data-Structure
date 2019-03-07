#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct type_node *type_ptr;
typedef struct type_node
{
	char name[20];
	int num;
	type_ptr link;
} our_node;

type_ptr search_ins_position(type_ptr head, char str[]) {
	type_ptr prev;

	prev = NULL;
	while (head) {
		if (strcmp(head->name, str) > 0) {
			return prev;
		}
		else {
			prev = head;
			head = head->link;
		}
	}
	return prev;
}