#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 101
#define FALSE 0
#define TRUE 1
#define MIN2(x,y) ((x)<(y)?(x):(y))

short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
short int visited[MAX_VERTICES];
int articulation_point[MAX_VERTICES];
int num = 0;
int cnt = 0;

typedef struct GraphNode
{
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType {
    int n;
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

void init(GraphType* g) {
    int v;
    g->n = MAX_VERTICES;
    for (v = 0; v < MAX_VERTICES; v++)
        g->adj_list[v] = NULL;
}

void insert_edge(GraphType* g, int u, int v)
{
    GraphNode* node1;
    GraphNode* node2;
    if (u >= g->n || v >= g->n) {
        fprintf(stderr, "그래프: 정점 번호 오류");
        return;
    }
    node1 = (GraphNode*)malloc(sizeof(GraphNode));
    node1->vertex = v;
    node1->link = g->adj_list[u];
    g->adj_list[u] = node1;

    node2 = (GraphNode*)malloc(sizeof(GraphNode));
    node2->vertex = u;
    node2->link = g->adj_list[v];
    g->adj_list[v] = node2;
}

void getAP(GraphType* g, int v, int parent) {
    int child = 0;
    int min_low = 0;
    int is_articulation_point = FALSE;
    dfn[v] = low[v] = ++num;
    visited[v] = TRUE;

    GraphNode* p = g->adj_list[v];
    while (p != NULL) {
        int w = p->vertex;
        if (visited[w] == FALSE) {
            child++;
            getAP(g, w, v);
            low[v] = MIN2(low[v], low[w]);

            if (low[w] >= dfn[v])
                is_articulation_point = TRUE;
        }
        else if (w != parent) {
            low[v] = MIN2(low[v], dfn[w]);
        }

        p = p->link;
    }

    if ((parent != -1 && is_articulation_point == TRUE) || (parent == -1 && child >= 2)) {
        articulation_point[cnt++]=v;
    }
}

int main(void) {
    int u, v;
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    init(g);

    FILE* fp = fopen("AP.txt", "r");

    if (fp == NULL) {
        fprintf(stderr, "Cannot open the file");
        return 0;
    }

    while (fscanf(fp, "(%d,%d)%*c", &u, &v) != EOF) {
        insert_edge(g, u, v);
    }

    for (int i = 0; i < g->n; i++) {
        if (visited[i] == FALSE)
            getAP(g, i, -1);
    }

    for(int i=cnt-1;i>=0;i--) {
        /*if(i==cnt-1) {
            printf("AP: ");
        }
        if(i!=0) {
            printf("%d, ",articulation_point[i]);
        }
        else {
            printf("%d",articulation_point[i]);
        }*/
    }

    free(g);
    fclose(fp);

    return 0;
}
