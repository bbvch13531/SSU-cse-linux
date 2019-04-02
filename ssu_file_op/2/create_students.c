#include <stdio.h>
#include "record.h"
//필요하면 header file 추가 가능

//
// argv[1]: 레코드 파일students.dat에 저장되는 전체 레코드의 수
//

int main(int argc, char **argv){
    // 250 바이트 학생 레코드를 students.dat 파일에 하나씩 저장하는 코드를 구현함
    // 학생 레코드의 데이터는 임의로 생성해도 무방함
    
    FILE * fp;

    fp = fopen("students.dat", "r+");
    

	return 0;
}
