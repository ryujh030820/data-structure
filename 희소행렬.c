#include <stdio.h>
#define MAX_TERMS 101
#define MAX_COL 50

typedef struct {
    int row;
    int col;
    int value;
}term;

void transpose(term a[],term b[]) {
    int n,i,j,currentb;
    n=a[0].value;
    b[0].row=a[0].col;
    b[0].col=a[0].row;
    b[0].value=n;
    if(n>0) {
        currentb=1;
        for(i=0;i<a[0].col;i++) {
            for(j=1;j<=n;j++) {
                if(a[j].col==i) {
                    b[currentb].row=a[j].col;
                    b[currentb].col=a[j].row;
                    b[currentb].value=a[j].value;
                    currentb++;
                }
            }
        }
    }
}

void fasttranspose(term a[],term b[]) {
    int rowTerms[MAX_COL], startingPos[MAX_COL];
    int i,j,numCols=a[0].col,numTerms=a[0].value;
    b[0].row=numCols;
    b[0].col=a[0].row;
    b[0].value=numTerms;

    if(numTerms>0) {
        for(i=0;i<numCols;i++) {
            rowTerms[i]=0;
        }

        for(i=1;i<=numTerms;i++) {
            rowTerms[a[i].col]++;
        }

        startingPos[0]=1;

        for(i=1;i<numCols;i++) {
            startingPos[i]=startingPos[i-1]+rowTerms[i-1];
        }

        for(i=1;i<=numTerms;i++) {
            j=startingPos[a[i].col]++;
            b[j].row=a[i].col;
            b[j].col=a[i].row;
            b[j].value=a[i].value;
        }
    }
}