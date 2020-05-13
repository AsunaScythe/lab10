#include "list.h"

Node* init(FILE* f,void* (*struct_create)(char*)){
    Node *new,
         *head = NULL;

    char *data;

    int len;
    char curr;

    while(curr != EOF){
        curr = fgetc(f);
        for(len = 0;curr != '\n'  && curr != EOF ;len++,curr = fgetc(f));
        if(curr == EOF)
            fseek(f,-len, SEEK_CUR );
        else
            fseek(f,-len-2, SEEK_CUR );
        data = malloc(len+1);
        fread(data,1,len,f);
        data[len] = '\0';
        new = calloc(sizeof(Node),1);
        new->data = struct_create(data);
        free(data);
        add_last(&head,new);
        curr = fgetc(f);
    }

    return head;
}

int get_length(Node* some){
    int n;

    for(n = 0;some != NULL;some = some->next,n++);

    return n;
}

void add_first(Node** head,Node* new){
    new->next = *head;
    *head = new;
}

void add_last(Node** head,Node* new){
    Node* curr,
            *some;

    if(*head != NULL){
        some = *head;
        for(curr = some;some!= NULL;some = some->next)
            curr = some;
        curr->next = new;
    }
    else
        *head = new;

    new->next = NULL;
}

void delete_list(Node* head,void (*delete)(void*)){
    Node* prev;

    while((prev = head) != NULL){
        delete(head->data);
        head = head->next;
        free(prev);
    }
}

void print(Node* some,void (*print_some)(void*)){
    for(;some != NULL;some = some->next) {
        print_some(some->data);
        puts("");
    }

}
