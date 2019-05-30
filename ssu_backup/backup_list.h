typedef struct _backup_list{
    struct Backup_list *next;
    char pathname[256];
    int interval;
    int options[4]; // 옵션 설정되면 1 아니면 0
    int number; // -n 옵션
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