typedef struct _backup_list{
    struct Backup_list *next;
    char pathname[256];
    int interval;
    int options[4]; // 옵션 설정되면 1 아니면 0
    int time;   // -t 옵션

} Backup_list;

int find_backup_list(char *pathname, Backup_list *list){
    while(list->next != NULL){
        if(strcmp(pathname, list->pathname) == 0)
            return 1;
        list = list->next;
    }
    return 0;
}

void append_backup_list(Backup_list *data, Backup_list *list){
    while(list->next != NULL){
        list = list->next;
    }
    list -> next = data;
}

// return -1 when error occurs;
// return 1 for normal state
int save_recent_list(int n, Backup_list *list){
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
void remove_from_list(char *pathname, Backup_list *list){
    Backup_list tmp;

    while(list->next != NULL){
        if(strcmp(list->pathname, pathname) == 0){
            
        }
    }
}