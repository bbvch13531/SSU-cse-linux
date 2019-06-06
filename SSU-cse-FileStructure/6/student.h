#ifndef _STUDENT_H_
#define _STUDENT_H_

#define RECORD_FILE_NAME    "student.dat"
#define HASH_FILE_NAME     "student.hsh"
#define STUDENT_RECORD_SIZE     120
#define HASH_RECORD_SIZE    14      // 학번(10)+ 레코드 주소(4)
#define SID_FIELD_SIZE	10	// �й� �ʵ��� ũ��

typedef struct _Student
{
	char id[11];		//�й�
	char name[21];		//�̸�
	char addr[31];	    //�ּ�
	char year[2];		//�г�
	char dept[20];		//�а�
    char phone[16];		//��ȭ��ȣ
	char email[26];		//�̸��� �ּ�
} STUDENT;

#endif