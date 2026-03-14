#include <ctype.h>
#include <stdbool.h>
#include "dictionary.h"
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;
const unsigned int N = 145036;
int count = 0;
node *table[N];
bool check(const char *word)
{
    int comp = hash(word);
    node* header = table[comp];
    if (header == NULL){
        return false;
    }
    while(header != NULL){
        if (strcasecmp(header->word, word) == 0){
            return true;
        }
        header = header->next;
    }
    return false;
}
unsigned int hash(const char *word)
{
    uint32_t hash = 2166136261U;
    for(int i = 0; i < word[i] != '\0'; i++){
        hash ^= toupper(word[i]);
        hash *= 16777619U;
    }
    return hash % N;
}
bool load(const char *dictionary)
{
    
    FILE *source = fopen(dictionary, "r");
    if (source == NULL){
        return false;
    }
    char buffer[LENGTH + 1];
    while(fscanf(source, "%s", buffer) != EOF){
        count++;
        node* cnode = malloc(sizeof(node));
        if (cnode == NULL){
            return false;
        }
        strcpy(cnode->word, buffer);
        unsigned int index = hash(buffer);
        if (table[index] == NULL){
            cnode->next = NULL;
            table[index] =cnode;
        }
        else{
            cnode->next = table[index];
            index[table] = cnode;
        }
    }
    fclose(source);
    return true;
}

unsigned int size(void)
{
    return count;
}
void freesll(node *currentadr){
    if (currentadr == NULL){
        return;
    }
    freesll(currentadr->next);
    free(currentadr);
    return;
}
bool unload(void)
{
    for(long i = 0; i < N; i++){
        if (table[i] == NULL){
            continue;
        }
        freesll(table[i]);
    }
    return true;
}
