#ifndef LAB8_LIST_H
#define LAB8_LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node {
    void *data;
    Node *next;
};

void add_first(Node**,Node*);

void add_last(Node**,Node*);

int get_length(Node*);

Node* init(FILE*,void* (*)(char*));

void delete_list(Node*,void (*)(void*));

void print(Node*,void (*)(void*));

#endif //LAB8_LIST_H
