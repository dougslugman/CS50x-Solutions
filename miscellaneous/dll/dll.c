#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct dll{
    int val;
    struct dll* next;
    struct dll* prev;
} dllnode;

dllnode* createdll(int value, dllnode** hdr){
    dllnode *node = malloc(sizeof(dllnode));
    if (node == NULL){
        exit(1);
    }
    node->val = value;
    node->next = NULL;
    node->prev = NULL;
    *hdr = node;
    return node;
}

dllnode* addnode(int value, dllnode** hdr){
    dllnode* node = malloc(sizeof(dllnode));
    if (node == NULL){
        exit(1);
    }
    node->next = *hdr;
    node->val = value;
    node->prev = NULL;
    (*hdr)->prev = node;
    *hdr = node;
    return node;
}

dllnode* searchdll(int searchval, dllnode *hdr){
    dllnode* current = hdr;
    while(current != NULL){
        if (current->val == searchval){
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void rmnode(dllnode* target, dllnode** hdr){
    if (target == *hdr) {
        *hdr = target->next;
    }
    if (target->prev != NULL) {
        target->prev->next = target->next;
    }
    if (target->next != NULL) {
        target->next->prev = target->prev;
    }
    free(target);
}

void freedll(dllnode *currentadr){
    if (currentadr == NULL){
        return;
    }
    freedll(currentadr->next);
    free(currentadr);
    return;
}

int main(){
    dllnode *HEADER = NULL;
    dllnode *item1 = createdll(5, &HEADER);
    dllnode *item2 = addnode(7, &HEADER);
    dllnode *item3 = addnode(8, &HEADER);
    dllnode *item4 = addnode(10, &HEADER);
    dllnode *location = searchdll(5, HEADER);
    rmnode(item1, &HEADER);
    freedll(HEADER);
    return 0;
}
