/*
 * Graph search
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

 /* 최대 vertex 10, 번호 0~9 */
 /* 탐색시 여러 Edge 있을 경우 번호 작은 vertex 먼저 탐색 */
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

typedef struct Graph { // 인접 정점 담는 구조체
    int vertex;
    struct Graph* link;
} Graph;

typedef struct Graphhead {
    Graph* vertex[MAX_VERTEX]; // vertex에 대한 헤드노드 배열
    int num;               // vertex 수
}Graphhead;

/* for queue */
#define MAX_QUEUE_SIZE		20
int queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

short int visitflag[MAX_VERTEX] = { FALSE, }; // vertex에 방문 했는지 표시

void Initializegraph(Graphhead* h); // 그래프 초기화
void Insert_vertex(Graphhead* h);   // vertex 삽입
void Insert_edge(Graphhead* h);     // edge 삽입
void printgraph(Graphhead* h);      // vertex의 인접한 vertex 출력
void dfs(Graphhead* h, int v);      // 깊이 우선 탐색

void bfs(Graphhead* h, int v);      // 너비 우선 탐색
int deQueue();
void enQueue(int v);

void initflag();                    // visitflag 초기화
void freegraph(Graphhead* h);       // 할당된 메모리 해제


int main() {
    char command;
    int i;
    Graphhead* h = (Graphhead*)malloc(sizeof(Graphhead));
    Initializegraph(h);
    printf("[----- [한민우] [2018038047] -----]\n");
    do {
        printf("\n\n");
        printf("----------------------------------------------------------------\n");
        printf("                         Graph Searches                         \n");
        printf("----------------------------------------------------------------\n");
        printf(" Initialize Graph     = z                                       \n");
        printf(" Insert Vertes        = v       Insert Edge                 = e \n");
        printf(" Depth First Search   = d       Breath First Search         = b \n");
        printf(" Print Graph          = p       Quit                        = q \n");
        printf("----------------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command);

        switch (command) {
            /* Initialize graph */
        case 'z': case 'Z':
            Initializegraph(h);
            break;
            /* Quit */
        case 'q': case 'Q':
            freegraph(h);
            free(h);
            break;
            /* Insert Vertes */
        case 'v': case 'V':
            Insert_vertex(h);
            break;
            /* Insert Edge */
        case 'e': case 'E':
            Insert_edge(h);
            break;
            /* Depth first search */
        case 'd': case 'D':
            printf("dfs start vertex : ");
            scanf("%d", &i);
            dfs(h, i);
            initflag();
            break;
            /* Breath first search */
        case 'b': case 'B':
            printf("bfs start vertex : ");
            scanf("%d", &i);
            dfs(h, i);
            initflag();
            break;
            /* print graph */
        case 'p': case 'P':
            printgraph(h);
            break;

        }
    } while (command != 'q' && command != 'Q');
    return 1;
}

void Initializegraph(Graphhead* h) {
    if (h->num != 0) freegraph(h);  // 동적으로 할당되어있던 메모리 해제
    h->num = 0; // vertex 수 초기화
    for (int i = 0; i < MAX_VERTEX; i++) {
        h->vertex[i] = NULL;    // 링크 초기화
        visitflag[i] = FALSE;  // 방문 기록 초기화
    }
}

void Insert_vertex(Graphhead* h) {
    if (h->num >= MAX_VERTEX) { // vertex가 꽉 찼다면
        printf("Graph vertex is full! \n");
        return;
    }
    printf("Vertex added\n<Vertex[%d]>\n", h->num);
    h->num++; // vertex 수 증가
}

void Insert_edge(Graphhead* h) {     // edge 삽입, 번호가 작은 순으로 삽입
    int a, b;
    Graph* node1, * node2;  // 양쪽 방향으로 삽입하기 위해 2개 선언
    Graph* prev, * curr;    // 오름차 순으로 삽입하기 위해 그래프 탐색할 포인터

    printf("Input vertex num 1 : ");
    scanf("%d", &a);
    printf("Input vertex num 2 : ");
    scanf("%d", &b);

    if (a >= h->num || b >= h->num) {
        printf("ERROR! : Wrong vertex number.\n");
        return;
    }
    if (a == b) {
        printf("ERROR! : Not allowed same vertex number");
        return;
    }
    node1 = (Graph*)malloc(sizeof(Graph));
    node2 = (Graph*)malloc(sizeof(Graph));
    node1->vertex = b;
    node1->link = NULL;
    node2->vertex = a;
    node2->link = NULL;

    /* edge 삽입 */
    prev = NULL;
    curr = h->vertex[a];

    if (curr == NULL) h->vertex[a] = node1; // 해당 vertex 번호에 처음 삽입하는 경우
    else {
        while (curr != NULL && curr->vertex <= b) { // 번호가 더 작은 노드 탐색
            if (curr->vertex == b) {
                printf("ERROR! : Same edge is not allowed."); // 이미 존재하는 edge 입력했으면 오류
                return;
            }
            prev = curr;
            curr = curr->link;
        }
        if (prev == NULL) h->vertex[a] = node1; // 맨 앞에 삽입하는 경우
        else prev->link = node1;
        node1->link = curr;
    }
    /* 반대로도 삽입 */
    prev = NULL;
    curr = h->vertex[b];

    if (curr == NULL) h->vertex[b] = node2; // 해당 vertex 번호에 처음 삽입하는 경우
    else {
        while (curr != NULL && curr->vertex <= a) { // 번호가 더 작은 노드 탐색
            if (curr->vertex == a) {
                printf("ERROR! : Same edge is not allowed."); // 이미 존재하는 edge 입력했으면 오류
                return;
            }
            prev = curr;
            curr = curr->link;
        }
        if (prev == NULL) h->vertex[b] = node2; // 맨 앞에 삽입하는 경우
        else prev->link = node2;
        node2->link = curr;
    }
    printf(" Vertex[%d] and Vertex[%d] connected.", a, b);
}

void printgraph(Graphhead* h) { // 그래프 출력
    Graph* p;
    for (int i = 0; i < h->num; i++) {
        p = h->vertex[i];
        printf("Vertex [%d] ", i);
        while (p != NULL) {
            printf("-> %d ", p->vertex);
            p = p->link;
        }
        printf("\n");
    }
}

void dfs(Graphhead* h, int v) { // 깊이 우선 탐색
    Graph* w;
    visitflag[v] = TRUE;
    printf("%5d", v);
    for (w = h->vertex[v]; w; w = w->link) {
        if (!visitflag[w->vertex])
            dfs(h, w->vertex);
    }
}

void bfs(Graphhead* h, int v) { // 너비 우선 탐색
    Graph* w;
    front = rear = -1;
    printf("%5d",v);
    visitflag[v] = TRUE;
    enQueue(v);
    while(front!=rear){
        v = deQueue();
        for(w = h->vertex[v]; w; w = w->link){
            if(!visitflag[w->vertex]){
                printf("%5d",w->vertex);
                enQueue(w->vertex);
                visitflag[w->vertex] = TRUE;
            }
        }
    }
}

int deQueue(){
	if(front == rear) return NULL; // 큐가 공백이면 NULL 리턴
	else{
		front = (front + 1) % MAX_QUEUE_SIZE; // front를 앞으로 한 칸 이동시킨다
		return queue[front]; // front에 노드 삭제
	}
}

void enQueue(int v){
	rear = (rear +1) % MAX_QUEUE_SIZE; // rear을 앞으로 한 칸 이동시킨다
	queue[rear] = v; // rear자리에 노드 삽입
}

void initflag() {
    for (int i = 0; i < MAX_VERTEX; i++) visitflag[i] = FALSE;
}

void freegraph(Graphhead* h) { // 할당된 메모리 해제
    int i;
    Graph* prev;
    Graph* curr;

    for (i = 0; i < h->num; i++) { // headnode의 배열 돌면서
        prev = h->vertex[i];
        curr = prev;
        while (prev != NULL) {   // link타고 이동하면서
            curr = curr->link;
            prev = curr;
        }
    }
}