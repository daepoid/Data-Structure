#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#pragma warning(disable:4996)

#define Max_vertex 12
#define False 0
#define True 1
#define Infinite 10000000

typedef struct nodestruc *nodePointer;
typedef struct nodestruc {
	int no;  // ���� ��ȣ
	float cost;  // ������ ��밡��ġ
	nodePointer link;  // ���Ḯ��Ʈ�� ���� ��忡 ���� ������
} ty_node;
nodePointer vertex[Max_vertex];  // ��������Ʈ �׷���

double cost[Max_vertex][Max_vertex]; // ��������� ������ ������� ǥ��. ���������� ������.

double distance[Max_vertex]; // �Ÿ� �����ϴ� �迭

int first = 1;

int dijkstra[Max_vertex];  // Dijkstra algorithm ���� ����

void Read_and_make_graph() {

	FILE *fp;
	fp = fopen("graphdata.txt", "r");

	char ch; //���Ͽ��� �޴� ����
	int i; // vertex
	int j; // ����� vertex�� ��
	char ah[100] = { '\0' };//���Ͽ��� ���ڷ� ���� �� �޴� ���ڿ�
	double a[100]; //���Ͽ��� ���� ���� double�迭�� �ٲپ� ����
	int tmp = 0; // ah
	int tmp2 = 0; // a	
	int tmp_check; // ah �ٽ��ʱ�ȭ �Ҷ�
	int tmp2_check; //a �ٽ� �ʱ�ȭ �Ҷ�
	nodePointer np, prev;

	while ((ch = fgetc(fp)) != EOF) {
		if (isspace(ch) == 0) {
			ah[tmp++] = ch;
		}
		else {
			if (ah[0] != NULL) { // ���� ���ڰ� �ִ��� ������ Ȯ��
				sscanf(ah, "%lf", &a[tmp2++]);  //���� ���ڸ� ������ ���ڿ��� double�� �迭�� ����
				for (tmp_check = 0; tmp_check < tmp; tmp_check++) {
					ah[tmp_check] = NULL; // �ٽ� ���ڸ� �ޱ� ���� �ʱ�ȭ
				}
				tmp = 0; // �迭 �ʱ�ȭ �Ǽ� �ε����� �ʱ�ȭ
				if (ch == '\n') {
					if (first == 1) {
						for (i = 0; i < (int)a[0]; i++) {
							vertex[i] = (nodePointer)malloc(sizeof(ty_node));
						}
						first++;
						for (tmp2_check = 0; tmp2_check < tmp2; tmp2_check++) {
							a[tmp2_check] = 0.0;// �ٽ� �ޱ� ���� �ʱ�ȭ
						}
						tmp2 = 0;
					}
					else {
						vertex[(int)a[0]]->no = (int)a[0];
						prev = vertex[(int)a[0]];  //��������Ʈ�� ����� ���� �տ� �����͸� ����
						for (j = 0; j < (tmp2 - 1) / 2; j++) {
							np = (nodePointer)malloc(sizeof(ty_node));  //���� �����͸� ����� �����Ű�Ƿν� head�����Ϳ� ���� ��������Ʈ�� �����.
							np->no = (int)a[2 * j + 1];
							prev->link = np;
							prev = np;
							cost[(int)a[0]][(int)a[2 * j + 1]] = a[2 * j + 2];  //���̿� ����� cost�迭�� �����Ѵ�.
						}
						prev->link = NULL;  //��������Ʈ�� ������ 
						for (tmp2_check = 0; tmp2_check < tmp2; tmp2_check++) {
							a[tmp2_check] = 0.0;
						}
						tmp2 = 0;
					}
				}
			}
		}
	}
}

int shortest_path(int start, int destination) { // Dijkstra algorithm �� �����Ͽ� �� ���� ������ �ּҰ�θ� ã���ִ� �Լ�
	int i, j;
	int found[Max_vertex]; // �̹� ã�� ������� Ȯ���ϴ� �迭
	int u; // �������� ����� ���Ե�� ���� ����Ű�� �뵵
	int w; // ã���� �߿��� �Ÿ��� �� ª���� ã�� �뵵
	int g, n, m; // ã�� ����� �����ִ� �뵵
	double min; // �Ÿ��� ���� ª�� ��
	double charge; // cost�� �� �ٲ��� �ʰ� �Ϸ��� ����

	int path[Max_vertex]; // ��� �����ϴ� �迭

	for (i = 0; i < Max_vertex; i++) {
		if (cost[start][i] == 0) {
			distance[i] = Infinite;
		}
		else {
			distance[i] = cost[start][i];
		}
		found[i] = False;
		dijkstra[i] = start; //������ �� ��� ������ �������� ������������ �����Ѵ�.
	}
	found[start] = True;
	dijkstra[start] = -1; // ù �κ��ΰ� Ȯ��
	distance[start] = 0;
	for (i = 0; i < Max_vertex - 1; i++) {
		min = Infinite;
		for (j = 0; j < Max_vertex; j++) {
			if (!found[j] && distance[j] < min) { // ��ã���� �߿��� ���� ���� distance���ϱ�
				min = distance[j];
				u = j;
			}
		}
		found[u] = True; // ���� ���� distance�̹Ƿ� ã��
		g = 0;
		if (u == destination) {
			m = u;
			path[g++] = m;
			while (dijkstra[m] != start) {
				path[g++] = dijkstra[m];
				m = dijkstra[m];
			}
			path[g] = start;
			printf("��� : ");
			for (n = g; n >= 0; n--) {
				printf("%5d", path[n]);
			}
			printf("\n�Ѻ�� : %.1f\n", distance[u]);
			return 0;
		}
		for (w = 0; w < Max_vertex; w++) {
			if (!found[w]) {
				charge = cost[u][w];
				if (charge == 0.0) {    // 0�̸� u���� v�� ���� ���� ����
					charge = Infinite;
				}
				if (distance[u] + charge < distance[w]) { // ���� ã�� u���� ���� distance�� ������ �ٲ۴�
					distance[w] = distance[u] + charge;
					dijkstra[w] = u;
				}
			}
		}
	}
	return 0;
}

int main() {
	int i, start, destination;

	Read_and_make_graph();

	/*
	�׷����� ��Ÿ���� ����Ÿ ȭ�� (ȭ�ϸ�: graphdata.txt �� ������) �� �о
	���α׷� �ȿ� ������� ǥ���� ��� cost (�� ���� 1 ��ſ� �ش� ��ũ�� ����� ����)�� �����.
	�� �۾��� ������ ���� �Լ��� ȣ���Ͽ� ������� �Ѵ�.
	*/

	while (1) {
		printf("�ּҰ�θ� ã�� �� ������ �Է��Ͻÿ�> ");
		scanf("%d %d", &start, &destination);

		if (start == -1 && destination == -1) {
			printf("���α׷��� �����մϴ�.\n");
			break;
		}
		else if (start == -1 || destination == -1) {
		}
		else {
			for (i = 0; i < Max_vertex; i++) { // �ʱ�ȭ �����ϰ� shortest_path�� ����
				dijkstra[i] = -1;
			}
			shortest_path(start, destination);

			/*
			�� �Լ��� ȣ���ϸ� start ���� ����Ͽ� destination ���� ���� �ּ� ��� ��� �� �� ����� �� ����� ����Ѵ�.
			�� �Լ��� Dijkstra �˰����� ������� �����Ѵ�. start �� ���� �������� �Ͽ� Dijkstra �˰����� �����ϴ� ���߿�
			destination �������� �ּ� ��� ����� �������� ���� �ٷ� �� ��� �� �� ����� �Ѻ���� ����ϰ� �˰����� �����Ѵ�.
			*/
		}
	}
}

