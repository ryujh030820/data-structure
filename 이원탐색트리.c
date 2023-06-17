#include <stdio.h>
#include <stdlib.h>

typedef struct node* treePointer;
typedef struct node {
    int data;
    treePointer leftChild, rightChild;
};

treePointer search(treePointer tree, int key) {
    /* 키값이 key인 노드에 대한 포인터를 반환함.
    그런 노드가 없는 경우에는 NULL을 반환 */
    if(!tree) {
        return NULL;
    }
    if(key==tree->data) {
        return tree;
    }
    if(key<tree->data) {
        return search(tree->leftChild,key);
    }
    return search(tree->rightChild,key);
}

treePointer iterSearch(treePointer tree,int key) {
    /* 키값이 key인 노드에 대한 포인터를 반환함.
    그런 노드가 없는 경우에는 NULL을 반환 */
    while(tree) {
        if(key==tree->data) {
            return tree;
        }
        if(key<tree->data) {
            tree=tree->leftChild;
        }
        else {
            tree=tree->rightChild;
        }
    }
    return NULL;
}

treePointer modifiedSearch(treePointer root, int k)
{
    treePointer temp = root;
    while(root)
    {
        temp = root;
        if(k < root->data) {
            root = root->leftChild;
        }
        else if(k > root->data) {
            root = root->rightChild;
        }
        else {
            return NULL;
        }
    }
    return temp;
}

void insert(treePointer* node,int k) {
    /* 트리내의 노드가 k를 가리키고 있으면 아무 일도 하지 않음
    그렇지 않은 경우는 data=k인 새 노드를 첨가 */
    treePointer ptr, temp=modifiedSearch(*node, k);
    if(temp||!(*node)) {
        /* k is not in the tree */
        MALLOC(ptr,sizeof(*ptr));
        ptr->data=k;
        ptr->leftChild=ptr->rightChild=NULL;
        if(*node) { /* insert as child of temp */
            if(k<temp->data) {
                temp->leftChild=ptr;
            }
            else {
                temp->rightChild=ptr;
            }
        }
        else {
            *node=ptr;
        }
    }
}

void split(treePointer* theTree, int k, treePointer* small, int* mid, treePointer* big) {
    /* split the binary search tree with respect to key k */
    if(!theTree) {
        *small=*big=0;
        *mid=-1;
        return;
    }
    treePointer sHead, bHead, s, b, currentNode;
    /* create header nodes for small and big */
    MALLOC(sHead,sizeof(*sHead));
    MALLOC(bHead,sizeof(*bHead));
    s=sHead; b=bHead;
    /* do the split */
    currentNode=*theTree;

    while(currentNode) {
        if(k<currentNode->data) { /* add to big */
            b->leftChild=currentNode;
            b=currentNode;
            currentNode=currentNode->leftChild;
        }
        else if(k>currentNode->data) { /* add to small */
            s->rightChild=currentNode;
            s=currentNode;
            currentNode=currentNode->rightChild;
        }
        else { /* split at currentNode */
            s->rightChild=currentNode->leftChild;
            b->leftChild=currentNode->rightChild;
            *small=sHead->rightChild;
            free(sHead);
            *big=bHead->leftChild;
            free(bHead);
            *mid=currentNode->data;
            free(currentNode);
            return;
        }
    }
    /* no pair with key k */
    s->rightChild=b->rightChild=0;
    *small=sHead->rightChild;
    free(sHead);
    *big=bHead->leftChild;
    free(bHead);
    *mid=-1;
    return;
}