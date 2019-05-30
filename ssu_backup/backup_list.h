#include <stdio.h>
#include <string.h>

typedef struct _backup_list{
    struct Backup_list *next;
    char pathname[256];
    int interval;
    int options[4]; // 옵션 설정되면 1 아니면 0
    int time;   // -t 옵션
    int status;
        // status:
        // 0: not saved;
        // 1: saving;
        // 2: saved;
} Backup_list;

int find_backup_list(char *pathname, Backup_list **head){
    Backup_list *list = *head;

    while(list->next != NULL){
        if(strcmp(pathname, list->pathname) == 0)
            return 1;
        list = list->next;
    }
    return 0;
}

void append_backup_list(Backup_list data, Backup_list **head){
    Backup_list *list = *head;
    Backup_list *new_node = (Backup_list *)malloc(sizeof(Backup_list));
    
    new_node->next = data.next;
    strcpy(new_node->pathname, data.pathname);
    new_node->interval = data.interval;
    strcpy(new_node->options, data.options);
    new_node->time = data.time;
    new_node->status = data.status;

    while(list->next != NULL){
        list = list->next;
    }
    list->next = new_node;
}

// return -1 when error occurs;
// return 1 for normal state
int save_recent_list(int n, Backup_list **head){
    Backup_list *list = *head;

    for(int i=0; i<n-1; i++){
        if(list->next == NULL){
            return -1;
        }
        list = list->next;
    }
    list->next = NULL;
    return 1;
}

// search before remove from backup_list
void remove_from_list(char *pathname, Backup_list **head){
    Backup_list *list = *head;

    Backup_list *tmp;

    while(1){
        if(strcmp(list->pathname, pathname) == 0){
            tmp->next = list->next;
        }
        tmp = list;
        list = list->next;
        if(list == NULL)
    }
}