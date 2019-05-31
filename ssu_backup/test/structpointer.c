#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List{
    struct Node *head;
    int size;
};

struct Node{
    struct Node *next;
    int value;
};

void init(struct List *list){
    list->head = NULL;
    list->size = 0;
}

void append_list(struct Node data,struct List *list){
    struct Node *node = (struct Node *)malloc(sizeof(struct Node));
    struct Node *tail;

    node->value = data.value;

    if(list->head == NULL){
        list->head = node;
    }
    else{
        tail = list->head;

        while(tail->next != NULL){
            tail = tail->next;
        }
        tail->next = node;
    }

    list->size++;
}

int main(void){
    struct List list;
    struct Node data[5];

    init(&list);

    for(int i=0; i<5; i++){
        data[i].value = i+1;
        append_list(data[i], &list);
    }

    struct Node *head = list.head;
    while(head->next != NULL){
        int i=0;
        printf("i=%d, value=%d\n",i, head->value);
        head= head->next;
    }
    exit(0);
}