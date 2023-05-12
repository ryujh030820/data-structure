#include <stdio.h>
#include <string.h>

int nfind(char* string, char* pat) {
    int i,j,start=0;
    int lasts=strlen(string)-1;
    int lastp=strlen(pat)-1;
    int endmatch=lastp;

    for(i=0;endmatch<=lasts;endmatch++,start++) {
        if(string[endmatch]==pat[lastp]) {
            for(j=0,i=start;j<lastp&&string[i]==pat[j];i++,j++);
        }

        if(j==lastp) {
            return start;
        }
    }
    return -1;
}

int main(void) {
    int index;

    char pat[]="aab";
    char string[]="ababbaabaa";

    index=nfind(string,pat);

    if(index==-1) {
        printf("The pattern %s was not found in the string.\n",pat);
    }
    else {
        printf("The pattern %s was found at position %d in the string.\n", pat, index);
    }

    return 0;
}