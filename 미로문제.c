#include <stdio.h>

#define MAX_ROW 9
#define MAX_COL 6
#define EXIT_ROW 9
#define EXIT_COL 6
#define MAX_STACK_SIZE 100

using namespace std;

typedef struct {
	short int vert;
	short int horiz;
} offsets;

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;

offsets direction[8] = { //N=0,NE=1,E=2,SE=3,S=4,SW=5,W=6,NW=7
	{-1,0},
	{-1,1},
	{0,1},
	{1,1},
	{1,0},
	{1,-1},
	{0,-1},
	{-1,-1}
};

element st[MAX_STACK_SIZE];

int maze[MAX_ROW + 2][MAX_COL + 2] = {
	{1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,1,1},
	{1,1,1,1,1,1,0,1},
	{1,1,0,0,0,0,1,1},
	{1,0,1,1,1,1,1,1},
	{1,1,0,0,0,0,1,1},
	{1,1,1,1,1,1,0,1},
	{1,1,0,0,0,0,1,1},
	{1,0,1,1,1,1,1,1},
	{1,1,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1}
};
int mark[MAX_ROW + 2][MAX_COL + 2]={0,}; //방문했던 곳 기록
int top;

void push(int* top, element position) {
	(*top)++;
	st[*top].row = position.row;
	st[*top].col = position.col;
	st[*top].dir = position.dir;
}

element pop(int* top) {
	element result;
	if (*top < 0) {
		printf("stack is empty.\n");
	}
	else {
		result = st[*top];
		(*top)--;
	}
	
	return result;
}

void path(void) {
	int i, row, col, nextRow, nextCol, dir, found = false;
	element position;
	mark[1][1] = 1;
	top = 0;
	st[0].row = 1, st[0].col = 1, st[0].dir = 1;

	while (top>-1 && !found) {
		position = pop(&top);
		row = position.row;
		col = position.col;
		dir = position.dir;

		while (dir < 8 && !found) {
			/*dir 방향으로 이동*/
			nextRow = row + direction[dir].vert;
			nextCol = col + direction[dir].horiz;

			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) {
				found = true;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(&top, position);
			}
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;

				push(&top, position);
				row = nextRow;
				col = nextCol;
				dir = 0;
			}
			else {
				++dir;
			}
		}
	}

	if (found == true) {
		while (top>-1) {
			position = pop(&top);
			cout << position.row << " " << position.col << endl;
		}
		printf("탈출 성공\n");
	}
	else {
		printf("탈출 실패\n");
	}
}

int main(void) {
	path();

	return 0;
}