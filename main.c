#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "sort.h"
#include "list.h"


typedef struct{
    char *Name;
    char *Data;
    int *SES;
} GROUP;



void delete_GROUP(GROUP*);

GROUP* group_create(char*);

void delete_default(void*);

void print_group(GROUP*);

void print_default(char*);

void** linked(Node*);

int comp_group(GROUP**,GROUP**);

Node* filtr(Node*,int (*)(void*));

int true(GROUP*);

int to_int(char*,char*);

int comp_arr(GROUP*,GROUP*);

int main(){
    char *name;

    Node  *list,
          *new;

    GROUP **array;

    int i,
        j;

    puts("Enter filename");

    name = calloc(sizeof(char),80);

    gets(name);

    FILE* f = fopen(name,"r");

    puts("LIST:");

    list = init(f,group_create);

    print(list,print_group);

    //создаётся массив указателей на структуры GROUP;
    array = linked(list);

    sort(array,array+get_length(list),sizeof(void*),comp_group);

    puts("SES:");

    for(i = 0;i<get_length(list);i++){
        print_group(array[i]);
        puts("");
    }

    puts("Data:");

    //создаётся спиисок, где каждое звено ханит указатель на структуру, удовлетворяющую условию
    new = filtr(list,true);

    print(new,print_group);


    //Часть с массивом
    i = get_length(list);
    GROUP *arr,
          *curr;

    Node* curr_node;

    arr = calloc(sizeof(GROUP),i);


    puts("NAME:");
    for(curr_node = list,curr = arr;curr_node!= NULL;curr_node = curr_node->next,curr++)
        copy(curr_node->data,curr,sizeof(GROUP));

    sort(arr,curr,sizeof(GROUP),comp_arr);

    for(j = 0;j < i;j++) {
        print_group(&arr[j]);
        puts("");
    }


    getch();
    return 0;
}

int true(GROUP* some){
    char* string;
    int flag;
    string = some->Data;

    if(to_int(string+6,string+10)>1997)
        flag = 1;
    else if (to_int(string+6,string+10)==1997){
        if(to_int(string+3,string+5)==12)
            flag =  1;
        else
            flag =  0;
    }
    else
        flag =  0;

    return flag;

}

int to_int(char*begin,char*end){
    int i;

    i = 0;

    for(i = 0;begin<end;begin++){
        i = i*10 + *begin - 48;
    }
    return i;
}


void** linked(Node* some){
    void** array,
        **curr;

    array = calloc(sizeof(void*),get_length(some));

    for(curr = array;some!= NULL;some = some->next,curr++)
        *curr = some->data;

    return array;
}

int comp_group(GROUP**a,GROUP**b){

    int a_sum,
        b_sum,
        i;
    a_sum = 0;
    b_sum = 0;
    for(i = 0;i<3;i++){
        a_sum += (*a)->SES[i];
        b_sum += (*b)->SES[i];
    }
    return a_sum < b_sum;
}

GROUP* group_create(char *str){
    GROUP *new;
    new = calloc(sizeof(GROUP),1);
    int len,
        i;
    char *next;

    for(next = str;*next != ',';next++);
    len = next-str;
    new->Name = calloc(sizeof(char),len+1);
    copy(str,new->Name,len);
    new->Name[len] = '\0';

    str = next+1;
    for(next = str;*next != ',';next++);
    len = next-str;
    new->Data = calloc(sizeof(char),len+1);
    copy(str,new->Data,len);
    new->Data[len] = '\0';

    new->SES = calloc(sizeof(int),3);
    for(i = 0;i < 3;i++) {
        str = next + 1;
        for (next = str; *next != '\0' && *next != ','; next++);
        new->SES[i] = to_int(str,next);
    }

    return new;
}

void delete_GROUP(GROUP* some){
    if(some != NULL) {
        free(some->Data);
        free(some->Name);
        free(some->SES);
        free(some);
    }
}

void print_group(GROUP* some){
    int i;

    print_default(some->Name);
    printf(" ");
    print_default(some->Data);
    printf(" ");

    for(i=0;i<3;i++){
        printf("%d ",some->SES[i]);
    }
}

void delete_default(void* some){
        free(some);
}

void print_default(char* some){
    for(;*some != '\0';some++)
        printf("%c",*some);
}

Node* filtr(Node* list,int (*true)(void*)){
    Node *head,
            *new;

    for(head = NULL;list != NULL;list = list->next){
        if(true(list->data)){
            new = calloc(sizeof(Node),1);
            new->data = list->data;
            add_first(&head,new);
        }
    }
    return head;
}

int comp_arr(GROUP* a,GROUP* b){
    char *curr_a,
         *curr_b;
    int flag;

    for(curr_a=a->Name,curr_b = b->Name; (*curr_a != '\0' && *curr_b != '\0')&&(*curr_a == *curr_b);curr_a++,curr_b++);
    if(*curr_a != '\0' && *curr_b != '\0')
        if(*curr_a<*curr_b)
            flag = 1;
        else
            flag = 0;
    else
        if(*curr_a == '\0')
            flag = 1;
        else
            flag = 0;

    return flag;
}
