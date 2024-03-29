#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/time.h>
#include "record.h"
//필요하면 header file 추가 가능

//
// argv[1]: 레코드 파일students.dat에 저장되는 전체 레코드의 수
//

int main(int argc, char **argv){
    // 250 바이트 학생 레코드를 students.dat 파일에 하나씩 저장하는 코드를 구현함
    // 학생 레코드의 데이터는 임의로 생성해도 무방함
    time_t begin, end;
    FILE * fp;
    Student student = {"20142468", "kyungyoungheo", "Dongjak-gu", "soongsil", "computer", "Hello wo1112rld!"};
    int num;

    num = atoi(argv[1]);
    fp = fopen("students.dat", "w+");
    // printf("size of student = %ld\nsize of others = %ld",sizeof(Student), sizeof(student.others));

    for(int i=0; i<num; i++){
        // fwrite(student.id, sizeof(char), strlen(student.id)+1, fp);
        // fwrite(student.name, sizeof(char), strlen(student.name)+1, fp);
        // fwrite(student.address, sizeof(char), strlen(student.address)+1, fp);
        // fwrite(student.univ, sizeof(char), strlen(student.univ)+1, fp);
        // fwrite(student.dept, sizeof(char), strlen(student.dept)+1, fp);
        // fwrite(student.others, sizeof(char), strlen(student.others)+1, fp);
        
        fwrite(student.id, sizeof(char), 10, fp);
        fwrite(student.name, sizeof(char), 30, fp);
        fwrite(student.address, sizeof(char), 70, fp);
        fwrite(student.univ, sizeof(char), 30, fp);
        fwrite(student.dept, sizeof(char), 40, fp);
        fwrite(student.others, sizeof(char), 70, fp);
        // fwrite("\n", sizeof(char), 1, fp);
    }
    
    fclose(fp);

	return 0;
}
