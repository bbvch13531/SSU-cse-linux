#ifndef _STUDENT_H_
#define _STUDENT_H_

#define RECORD_FILE_NAME    "student.dat"
#define HASH_FILE_NAME     "student.hsh"
#define MAX_RECORD_SIZE     127 //including 7 delimeters

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
