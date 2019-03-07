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
	int no;  // 정점 번호
	float cost;  // 간선의 비용가중치
	nodePointer link;  // 연결리스트의 다음 노드에 대한 포인터
} ty_node;
nodePointer vertex[Max_vertex];  // 인접리스트 그래프

double cost[Max_vertex][Max_vertex]; // 비용정보를 가지는 인접행렬 표현. 전역변수로 선언함.

double distance[Max_vertex]; // 거리 저장하는 배열

int first = 1;

int dijkstra[Max_vertex];  // Dijkstra algorithm 내용 저장

void Read_and_make_graph() {

	FILE *fp;
	fp = fopen("graphdata.txt", "r");

	char ch; //파일에서 받는 문자
	int i; // vertex
	int j; // 연결된 vertex의 수
	char ah[100] = { '\0' };//파일에서 문자로 받을 때 받는 문자열
	double a[100]; //파일에서 받은 것을 double배열로 바꾸어 저장
	int tmp = 0; // ah
	int tmp2 = 0; // a	
	int tmp_check; // ah 다시초기화 할때
	int tmp2_check; //a 다시 초기화 할때
	nodePointer np, prev;

	while ((ch = fgetc(fp)) != EOF) {
		if (isspace(ch) == 0) {
			ah[tmp++] = ch;
		}
		else {
			if (ah[0] != NULL) { // 받은 문자가 있는지 없는지 확인
				sscanf(ah, "%lf", &a[tmp2++]);  //받은 문자를 저장한 문자열을 double형 배열에 저장
				for (tmp_check = 0; tmp_check < tmp; tmp_check++) {
					ah[tmp_check] = NULL; // 다시 문자를 받기 위해 초기화
				}
				tmp = 0; // 배열 초기화 되서 인데스도 초기화
				if (ch == '\n') {
					if (first == 1) {
						for (i = 0; i < (int)a[0]; i++) {
							vertex[i] = (nodePointer)malloc(sizeof(ty_node));
						}
						first++;
						for (tmp2_check = 0; tmp2_check < tmp2; tmp2_check++) {
							a[tmp2_check] = 0.0;// 다시 받기 위해 초기화
						}
						tmp2 = 0;
					}
					else {
						vertex[(int)a[0]]->no = (int)a[0];
						prev = vertex[(int)a[0]];  //인접리스트를 만들기 위해 앞에 포인터를 결정
						for (j = 0; j < (tmp2 - 1) / 2; j++) {
							np = (nodePointer)malloc(sizeof(ty_node));  //새로 포인터를 만들어 연결시키므로써 head포인터에 대한 인접리스트를 만든다.
							np->no = (int)a[2 * j + 1];
							prev->link = np;
							prev = np;
							cost[(int)a[0]][(int)a[2 * j + 1]] = a[2 * j + 2];  //사이에 비용을 cost배열에 저장한다.
						}
						prev->link = NULL;  //인접리스트의 마지막 
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

int shortest_path(int start, int destination) { // Dijkstra algorithm 을 변경하여 두 정점 사이의 최소경로를 찾아주는 함수
	int i, j;
	int found[Max_vertex]; // 이미 찾은 노드인지 확인하는 배열
	int u; // 다음으로 비용이 적게드는 것을 가리키는 용도
	int w; // 찾은거 중에서 거리가 더 짧은거 찾는 용도
	int g, n, m; // 찾은 결과를 보여주는 용도
	double min; // 거리가 가장 짧은 것
	double charge; // cost가 막 바뀌지 않게 하려고 만듬

	int path[Max_vertex]; // 경로 저장하는 배열

	for (i = 0; i < Max_vertex; i++) {
		if (cost[start][i] == 0) {
			distance[i] = Infinite;
		}
		else {
			distance[i] = cost[start][i];
		}
		found[i] = False;
		dijkstra[i] = start; //시작할 때 모든 정점의 앞정점은 시작정점으로 시작한다.
	}
	found[start] = True;
	dijkstra[start] = -1; // 첫 부분인거 확인
	distance[start] = 0;
	for (i = 0; i < Max_vertex - 1; i++) {
		min = Infinite;
		for (j = 0; j < Max_vertex; j++) {
			if (!found[j] && distance[j] < min) { // 안찾은것 중에서 가장 작은 distance구하기
				min = distance[j];
				u = j;
			}
		}
		found[u] = True; // 가장 작은 distance이므로 찾음
		g = 0;
		if (u == destination) {
			m = u;
			path[g++] = m;
			while (dijkstra[m] != start) {
				path[g++] = dijkstra[m];
				m = dijkstra[m];
			}
			path[g] = start;
			printf("경로 : ");
			for (n = g; n >= 0; n--) {
				printf("%5d", path[n]);
			}
			printf("\n총비용 : %.1f\n", distance[u]);
			return 0;
		}
		for (w = 0; w < Max_vertex; w++) {
			if (!found[w]) {
				charge = cost[u][w];
				if (charge == 0.0) {    // 0이면 u에서 v로 가는 간선 없음
					charge = Infinite;
				}
				if (distance[u] + charge < distance[w]) { // 새로 찾은 u에서 가는 distance가 작으면 바꾼다
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
	그래프를 나타내는 데이타 화일 (화일명: graphdata.txt 로 통일함) 을 읽어서
	프로그램 안에 인접행렬 표현인 행렬 cost (각 셀은 1 대신에 해당 아크의 비용을 가짐)를 만든다.
	이 작업은 다음과 같은 함수를 호출하여 수행토록 한다.
	*/

	while (1) {
		printf("최소경로를 찾을 두 정점을 입력하시요> ");
		scanf("%d %d", &start, &destination);

		if (start == -1 && destination == -1) {
			printf("프로그램을 종료합니다.\n");
			break;
		}
		else if (start == -1 || destination == -1) {
		}
		else {
			for (i = 0; i < Max_vertex; i++) { // 초기화 먼저하고 shortest_path를 실행
				dijkstra[i] = -1;
			}
			shortest_path(start, destination);

			/*
			이 함수를 호출하면 start 에서 출발하여 destination 으로 가는 최소 비용 경로 및 그 경로의 총 비용을 출력한다.
			이 함수는 Dijkstra 알고리즘을 기반으로 개발한다. start 를 시작 정점으로 하여 Dijkstra 알고리즘을 수행하는 도중에
			destination 정점으로 최소 경로 비용이 결정되자 마자 바로 이 경로 및 그 경로의 총비용을 출력하고 알고리즘을 종료한다.
			*/
		}
	}
}

