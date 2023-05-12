int compare(int x,int y) {
    if(x<y) {
        return -1;
    }
    else if(x==y) {
        return 0;
    }
    else {
        return 1;
    }
}

int binsearch(int list[],int searchnum, int left,int right) {
    int middle;
    
    while(left<=right) {
        middle=(left+right)/2;

        switch(COMPARE(list[middle],searchnum)) {
        case -1:
            //left=middle+1;
            binsearch(list,searchnum,middle+1,right);
            break;
        case 0:
            return middle;
        case 1:
            binsearch(list,searchnum,left,middle-1);
            //right=middle-1;
        }
    }

    return -1;
}