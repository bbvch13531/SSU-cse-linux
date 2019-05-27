#include <stdio.h>
#include <string.h>
#include "student.h"

#define HEADER_SIZE 2

void pack(char *recordbuf, const STUDENT *s){
	strcpy(recordbuf, s->id), strcat(recordbuf, "|");
	strcat(recordbuf, s->name), strcat(recordbuf, "|");
	strcat(recordbuf, s->dept), strcat(recordbuf, "|");
	strcat(recordbuf, s->year), strcat(recordbuf, "|");
	strcat(recordbuf, s->addr), strcat(recordbuf, "|");
	strcat(recordbuf, s->phone), strcat(recordbuf, "|");
	strcat(recordbuf, s->email), strcat(recordbuf, "|");
}

void unpack(const char *recordbuf, STUDENT *s){
	char buf[MAX_RECORD_SIZE + 1];
	strcpy(buf, recordbuf);
	
	for(int i = 0; buf[i]; i++)
		if(buf[i] == '|')
			buf[i] = 0;
	
	int idx = 0;

	strcpy(s->id, buf + idx), idx = idx + strlen(buf + idx) + 1;
	strcpy(s->name, buf + idx), idx = idx + strlen(buf + idx) + 1;
	strcpy(s->dept, buf + idx), idx = idx + strlen(buf + idx) + 1;
	strcpy(s->year, buf + idx), idx = idx + strlen(buf + idx) + 1;
	strcpy(s->addr, buf + idx), idx = idx + strlen(buf + idx) + 1;
	strcpy(s->phone, buf + idx), idx = idx + strlen(buf + idx) + 1;
	strcpy(s->email, buf + idx);
}

void readRecord(FILE *fp, char *recordbuf){
	for(int i = 0, j = 0; i < 7; i++){
		char c = 0;

		while(c != '|'){
			fread(&c, sizeof(c), 1, fp);
			recordbuf[j++] = c;
		}
	}
}

void printRecord(const STUDENT *s, int n)
{
	int i;

	for(i=0; i<n; i++)
	{
		printf("%s|%s|%s|%s|%s|%s|%s\n", s[i].id, s[i].name, s[i].dept, s[i].year, s[i].addr, s[i].phone, s[i].email);
	}
}

void add(FILE *record_fp, FILE *index_fp, const STUDENT *s){
	char recordbuf[MAX_RECORD_SIZE + 1] = "\0";
	pack(recordbuf, s);

	short prev = 0, cur, next;
	char len = (char)strlen(recordbuf), sz;

	fseek(record_fp, 0, SEEK_SET);
	fread(&cur, sizeof(cur), 1, record_fp);

	while(cur != -1){
		cur += HEADER_SIZE;
		fseek(record_fp, cur, SEEK_SET);

		fread(&sz, sizeof(sz), 1, record_fp);
		fread(&next, sizeof(next), 1, record_fp);
		fread(&sz, sizeof(sz), 1, record_fp);

		if(len <= sz)
			break;
		else
			prev = cur, cur = next;
	}

	if(cur == -1){
		short cnt;
		fseek(index_fp, 0, SEEK_SET);
		fread(&cnt, sizeof(cnt), 1, index_fp);

		cnt++;
		fseek(index_fp, 0, SEEK_SET);
		fwrite(&cnt, sizeof(cnt), 1, index_fp);

		fseek(record_fp, 0, SEEK_END);
		fseek(index_fp, 0, SEEK_END);

		short idx = ftell(record_fp) - HEADER_SIZE;
		printf("%d\n", idx);

		fwrite(&idx, sizeof(idx), 1, index_fp);
		fwrite(recordbuf, len, 1, record_fp);
	}
	else{
		fseek(record_fp, prev + (prev == 0 ? 0 : 1), SEEK_SET);
		fwrite(&next, sizeof(next), 1, record_fp);

		fseek(record_fp, cur, SEEK_SET);
		fwrite(recordbuf, len, 1, record_fp);
	}
}

int search(FILE *record_fp, FILE *index_fp, const char *keyval){
	short cnt;
	fseek(index_fp, 0, SEEK_SET);
	fread(&cnt, sizeof(cnt), 1, index_fp);

	for(int i = 0; i < cnt; i++){
		short idx;
		fread(&idx, sizeof(idx), 1, index_fp);
		fseek(record_fp, idx + HEADER_SIZE, SEEK_SET);

		char c;
		fread(&c, sizeof(c), 1, record_fp);
		fseek(record_fp, -1, SEEK_CUR);

		if(c == '*')
			continue;

		char buf[11] = "\0";
		int j = 0;

		while(fread(&c, sizeof(c), 1, record_fp) && c != '|')
			buf[j++] = c;

		if(!strcmp(buf, keyval)){
			STUDENT s;
			char recordbuf[MAX_RECORD_SIZE + 1] = "\0";
			fseek(record_fp, idx + HEADER_SIZE, SEEK_SET);

			readRecord(record_fp, recordbuf);
			unpack(recordbuf, &s);
			printRecord(&s, 1);

			return 1;
		}
	}

	return 0;
}

void delete(FILE *record_fp, FILE *index_fp, const char *keyval){
	short cnt;
	fseek(index_fp, 0, SEEK_SET);
	fread(&cnt, sizeof(cnt), 1, index_fp);

	for(int i = 0; i < cnt; i++){
		short idx;
		fread(&idx, sizeof(idx), 1, index_fp);
		fseek(record_fp, idx + HEADER_SIZE, SEEK_SET);

		char c;
		fread(&c, sizeof(c), 1, record_fp);
		fseek(record_fp, -1, SEEK_CUR);

		if(c != '*'){
			char buf[11] = "\0";
			int j = 0;
			
			while(fread(&c, sizeof(c), 1, record_fp) && c != '|')
				buf[j++] = c;
			
			if(!strcmp(buf, keyval)){
				char recordbuf[MAX_RECORD_SIZE + 1] = "\0";
				fseek(record_fp, idx + HEADER_SIZE, SEEK_SET);
				readRecord(record_fp, recordbuf);
				
				short cur = 0, next;
				fseek(record_fp, 0, SEEK_SET);
				fread(&next, sizeof(next), 1, record_fp);

				while(next != -1){
					cur = next + HEADER_SIZE + 1;
					fseek(record_fp, cur, SEEK_SET);
					fread(&next, sizeof(next), 1, record_fp);
				}

				fseek(record_fp, cur, SEEK_SET);
				fwrite(&idx, sizeof(idx), 1, record_fp);

				char a = '*', c = (char)strlen(recordbuf), d = 0;
				short b = -1;

				fseek(record_fp, idx + HEADER_SIZE, SEEK_SET);
				fwrite(&a, sizeof(a), 1, record_fp);
				fwrite(&b, sizeof(b), 1, record_fp);
				fwrite(&c, sizeof(c), 1, record_fp);

				for(int i = 0; i < c - 4; i++)
					fwrite(&d, sizeof(d), 1, record_fp);

				break;
			}
		}
	}
}

int main(int argc, char *argv[])
{
	FILE *record_fp, *index_fp;
	
	if((record_fp = fopen(RECORD_FILE_NAME, "r+b")) == NULL){
		record_fp = fopen(RECORD_FILE_NAME, "w+b");

		short a = -1;
		fwrite(&a, sizeof(a), 1, record_fp);
	}

	if((index_fp = fopen(INDEX_FILE_NAME, "r+b")) == NULL){
		index_fp = fopen(INDEX_FILE_NAME, "w+b");

		short a = 0;
		fwrite(&a, sizeof(a), 1, index_fp);
	}

	if(!strcmp(argv[1], "-a")){
		STUDENT s;

		strcpy(s.id, argv[2]);
		strcpy(s.name, argv[3]);
		strcpy(s.dept, argv[4]);
		strcpy(s.year, argv[5]);
		strcpy(s.addr, argv[6]);
		strcpy(s.phone, argv[7]);
		strcpy(s.email, argv[8]);
		
		add(record_fp, index_fp, &s);
	}
	else if(!strcmp(argv[1], "-d"))
		delete(record_fp, index_fp, argv[2]);
	else if(!strcmp(argv[1], "-s"))
		search(record_fp, index_fp, argv[2]);
	else{
		short cnt, idx;
		fread(&cnt, sizeof(cnt), 1, index_fp);

		for(int i = 0; i < cnt; i++){
			fread(&idx, sizeof(idx), 1, index_fp);
			printf("%d\n", idx);

			char c;
			fseek(record_fp, idx + HEADER_SIZE, SEEK_SET);
			fread(&c, sizeof(c), 1, record_fp);
			fseek(record_fp, -1, SEEK_CUR);

			if(c == '*'){
				char a;
				short b;

				fread(&a, sizeof(a), 1, record_fp);
				printf("%c", a);
				fread(&b, sizeof(b), 1, record_fp);
				printf("%d", b);
				fread(&a, sizeof(a), 1, record_fp);
				printf("%d", a);

				for(int j = 0; j < a - 4; j++){
					char t;
					fread(&t, sizeof(t), 1, record_fp);
					printf("%d", t);
				}
				printf("1\n");
			}
			else{
				char recordbuf[MAX_RECORD_SIZE + 1];
				memset(recordbuf, 0, sizeof(recordbuf));
				
				for(int k = 0, j = 0; k < 7; k++){
					c = 0;

					while(c != '|'){
						fread(&c, sizeof(c), 1, record_fp);
						recordbuf[j++] = c;
					}
				}

				printf("%s\n", recordbuf);
			}
		}
	}

	fclose(record_fp);
	fclose(index_fp);

	return 0;
}
