#include "../backup_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    struct Backup_list list;
    struct Node append[5];
    char msg[5][10]={
        "aaa",
        "bbb",
        "ccc",
        "ddd",
        "eee"
    };

    init(&list);
    struct Node head;
    head.interval = -1;
    strcpy(head.pathname, "headhead");
    append_backup_list(head, &list);
    
    for(int i=0; i<5; i++){
        append[i].interval = i;
        strcpy(append[i].pathname, msg[i]);
        append_backup_list(append[i], &list);
    }

    printf("%d\n",head.interval);
    struct Node *n;
    n = list.head;
    for(int i=0; i<5; i++){
        if(n->next == NULL)  break;
        printf("i=%d, inetval=%d %s\n", i, n->interval, n->pathname);
        n = n->next;
    }
    exit(0);
}