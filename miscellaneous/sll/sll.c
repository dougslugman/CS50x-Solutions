#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct sll{
    int val;
    struct sll* next;
} sllnode;

sllnode* createsll(int value, sllnode** hdr){
    sllnode *node = malloc(sizeof(sllnode));
    if (node == NULL){
        exit(1);
    }
    node->val = value;
    node->next = NULL;
    *hdr = node;
    return node;
}

sllnode* addnode(int value, sllnode** hdr){
    sllnode* node = malloc(sizeof(sllnode));
    if (node == NULL){
        exit(1);
    }
    node->next = *hdr;
    node->val = value;
    *hdr = node;
    return node;
}

sllnode* searchsll(int searchval, sllnode *hdr){
    sllnode* current = hdr;
    while(current != NULL){
        if (current->val == searchval){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void freesll(sllnode *currentadr){
    if (currentadr == NULL){
        return;
    }
    freesll(currentadr->next);
    free(currentadr);
    return;
}

int main(){
    sllnode *HEADER = NULL;
    sllnode *item1 = createsll(5, &HEADER);
    sllnode *item2 = addnode(7, &HEADER);
    sllnode *item3 = addnode(8, &HEADER);
    sllnode *location = searchsll(7, HEADER);
    freesll(HEADER);
    return 0;
}
