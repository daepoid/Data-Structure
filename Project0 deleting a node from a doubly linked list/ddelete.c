typedef struct node *nodePointer;
typedef struct node {
	nodePointer llink;
	int data;
	nodePointer rlink;
}node_Pointer;



void ddelete(nodePointer node, nodePointer deleted)
{ /* ���� ���� ����Ʈ���� ���� */
	if (node == deleted)
		printf("Deletion of head node not permitted.\n");
	else {
		deleted->llink->rlink = deleted->rlink;
		deleted->rlink->llink = deleted->llink;
		free(deleted);
	}
}
