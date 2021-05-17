/*
 * Graph search
 *
 * Data Structures
 *
 * Department of Computer Science
 * at Chungbuk National University
 *
 */

 /* �ִ� vertex 10, ��ȣ 0~9 */
 /* Ž���� ���� Edge ���� ��� ��ȣ ���� vertex ���� Ž�� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTEX 10
#define FALSE 0
#define TRUE 1

typedef struct Graph { // ���� ���� ��� ����ü
    int vertex;
    struct Graph* link;
} Graph;

typedef struct Graphhead {
    Graph* vertex[MAX_VERTEX]; // vertex�� ���� ����� �迭
    int num;               // vertex ��
}Graphhead;

short int visitflag[MAX_VERTEX] = { FALSE, }; // vertex�� �湮 �ߴ��� ǥ��

void Initializegraph(Graphhead *h); // �׷��� �ʱ�ȭ
void Insert_vertex(Graphhead *h);   // vertex ����
void Insert_edge(Graphhead *h);     // edge ����
void freegraph(Graphhead *h);       // �Ҵ�� �޸� ����


int main() {
    char command;
    Graphhead *h = (Graphhead*)malloc(sizeof(Graphhead));
    Initializegraph(h);
    printf("[----- [�ѹο�] [2018038047] -----]\n");
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

            break;
            /* Breath first search */
        case 'b': case 'B':

            break;
            /* print graph */
        case 'p': case 'P':

            break;

        }
    } while (command != 'q' && command != 'Q');
    return 1;
}

void Initializegraph(Graphhead *h) {
    if (h->num != 0) freegraph(h);  // �������� �Ҵ�Ǿ��ִ� �޸� ����
    h->num = 0; // vertex �� �ʱ�ȭ
    for (int i = 0; i < MAX_VERTEX; i++) {
        h->vertex[i] = NULL;    // ��ũ �ʱ�ȭ
        visitflag[i] = FALSE;  // �湮 ��� �ʱ�ȭ
    }
}

void Insert_vertex(Graphhead *h) {
    if (h->num >= MAX_VERTEX) { // vertex�� �� á�ٸ�
        printf("Graph vertex is full! \n");
        return;
    }
    printf("Vertex added\n<Vertex[%d]>\n", h->num);
    h->num++; // vertex �� ����
}

void Insert_edge(Graphhead *h) {     // edge ����, ��ȣ�� ���� ������ ����
    int a, b;
    Graph* node1, * node2;  // ���� �������� �����ϱ� ���� 2�� ����
    Graph* prev, * curr;    // ������ ������ �����ϱ� ���� �׷��� Ž���� ������

    printf("Input vertex num 1 : ");
    scanf("%d", &a);
    printf("Input vertex num 2 : ");
    scanf("%d", &b);

    if (a >= h->num || b >= h->num) {
        printf("ERROR! : Wrong vertex number.\n");
        return;
    }
    node1 = (Graph*)malloc(sizeof(Graph));
    node2 = (Graph*)malloc(sizeof(Graph));
    node1->vertex = b;
    node1->link = NULL;
    node2->vertex = a;
    node2->link = NULL;

    /* edge ���� */
    prev = NULL;
    curr = h->vertex[a];

    if (curr == NULL) h->vertex[a] = node1; // �ش� vertex ��ȣ�� ó�� �����ϴ� ���

    while (curr != NULL && curr->vertex < a) { // ��ȣ�� �� ���� ��� Ž��
        if (curr->vertex == a) {
            printf("ERROR! : Same edge is not allowed."); // �̹� �����ϴ� edge �Է������� ����
            return;
        }
        prev = curr;
        curr = curr->link;
    }
    if (prev == NULL) h->vertex[a] = node1; // �� �տ� �����ϴ� ���
    else prev->link = node1;
    node1->link = curr;

    /* �ݴ�ε� ���� */
    prev = NULL;
    curr = h->vertex[b];

    if (curr == NULL) h->vertex[b] = node2; // �ش� vertex ��ȣ�� ó�� �����ϴ� ���

    while (curr != NULL && curr->vertex < b) { // ��ȣ�� �� ���� ��� Ž��
        if (curr->vertex == b) {
            printf("ERROR! : Same edge is not allowed."); // �̹� �����ϴ� edge �Է������� ����
            return;
        }
        prev = curr;
        curr = curr->link;
    }   
    if (prev == NULL) h->vertex[b] = node2; // �� �տ� �����ϴ� ���
    else prev->link = node2;
    node2->link = curr;
    printf(" Vertex[%d] and Vertex[%d] connected.", a, b);
}

void freegraph(Graphhead *h) { // �Ҵ�� �޸� ����
    int i;
    Graph* prev;
    Graph* curr;

    for (i = 0; i < h->num; i++) { // headnode�� �迭 ���鼭
        prev = h->vertex[i];
        curr = prev;
        while (prev != NULL) {   // linkŸ�� �̵��ϸ鼭
            curr = curr->link;
            free(prev); // �޸� ����
            prev = curr;
        }

    }
}