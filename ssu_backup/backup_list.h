#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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
    int mtime;
    int number; // -n 옵션
    int saved_count;
    pthread_t tid;
};

void init(struct Backup_list *list){
    list->head = NULL;
    list->size = 0;
}

int search_backup_list(char *pathname, struct Backup_list *list){
    struct Node *node = list->head;
    int cnt=0;

    if(node == NULL) return -1;

    while(1){
        // printf("search %s to %s\n",pathname, node->pathname);
        if(strcmp(pathname, node->pathname) == 0)
            return cnt;
        if(node->next == NULL) break;
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
    for(int i=0; i<4; i++){
        new_node->options[i] = data.options[i];
    }
    new_node->time = data.time;
    new_node->mtime = data.mtime;
    new_node->number = data.number;
    new_node->saved_count = 0;

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

struct Node* get(int n, struct Backup_list *list){
    struct Node *node = NULL;

    if(n > list->size || list->head == NULL)
        return NULL;
    
    node = list->head;
    
    for(int i=0; i<n; i++){
        node = node->next;
    }

    return node;
}

void print_backup_list(struct Backup_list *list){
    struct Node *node = NULL;

    node = list->head;
    if(node == NULL) return;

    while(1){
        printf("%s %d %d %d  ->  ", node->pathname, node->interval, node->mtime, node->saved_count);
        if(node->next == NULL) return;
        node = node->next;
    }
    printf("\n");
}