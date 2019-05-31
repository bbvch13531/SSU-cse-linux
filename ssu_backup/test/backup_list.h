#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Backup_list{
    struct Node *head;
    int size;
};

struct Node{
    struct Node *next;

    char pathname[256];
    int interval;
    int options[4]; // 옵션 설정되면 1 아니면 0
    int time;   // -t 옵션
    int status;
        // status:
        // 0: not saved;
        // 1: saving;
        // 2: saved;
};

void init(struct Backup_list *list){
    list->head = NULL;
    list->size =0;
}

int search_backup_list(char *pathname, struct Backup_list *list){
    struct Node *node = list->head;
    int cnt=0;
    while(node->next != NULL){
        if(strcmp(pathname, node->pathname) == 0)
            return cnt;
        node = node->next;
        cnt++;
    }
    return -1;
}

void append_backup_list(struct Node data, struct Backup_list *list){
    struct Node *node = list->head;
    struct Node *new_node = (struct Node *)malloc(sizeof(struct Node));
    

    strcpy(new_node->pathname, data.pathname);
    new_node->interval = data.interval;
    // memcpy(new_node->options, data.options, 16);
    new_node->time = data.time;
    new_node->status = data.status;

    // printf("new_node::pathname=%s append\nlist->size = %d\n", new_node->pathname, list->size);
    if(node == NULL){
        list->head = new_node;
        // printf("first append\n\n");
    }
    else{
        // printf("list->head = %d\n",list->head->interval);
        while(node->next != NULL){
            node = node->next;
            // printf("node::pathname=%s\n",node->pathname);
        }
        node->next = new_node;
    }
    list->size++;
}

// return -1 when error occurs;
// return 1 for normal state
int save_recent_list(int n, struct Backup_list *list){
    struct Node *node = list->head;

    for(int i=0; i<n-1; i++){
        if(node->next == NULL){
            return -1;
        }
        node = node->next;
    }
    node->next = NULL;
    return 1;
}

// search before remove from backup_list
void remove_from_list(char *pathname, struct Backup_list *list){
    struct Node *node = list->head;
    struct Node *tmp;
    int res;
    res = search_backup_list(pathname, list);
    
    if(res != -1){
        if(res == 0){
            list->head = NULL;
        }
        else{
            tmp = node;

            for(int i=0; i<res; i++){
                if(i!=0)
                    tmp = node;
                node = node->next;
            }
            tmp->next = node->next;
        }
    }
    list->size--;
}