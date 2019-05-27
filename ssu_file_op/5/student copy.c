#include <stdio.h>
#include "student.h"
#include <string.h>
#include <stdlib.h>


void pack(char *recordbuf, const STUDENT *s);
void unpack(const char *recordbuf, STUDENT *s);
void read(FILE *fp, char *recordbuf, int rrn);
void add(FILE *fp, const STUDENT *s);
int search(FILE *fp, const char *keyval);
void delete(FILE *fp, const char *keyval);
void printRecord(const STUDENT *s, int n);


int main(int argc, char *argv[])
{
	int search_rrn;
	FILE *fp;
	char recordbuf[RECORD_SIZE];
	STUDENT s;
	if(argv[1][0] =='-'){
		switch(argv[1][1]){
			case'a':
				if(argc != 10){
					fprintf(stderr, "wrong format\n");
					exit(1);
				}
				if((fp = fopen(argv[2],"r+")) ==NULL)
					fp = fopen(argv[2],"w+");
				memset(recordbuf,'\0',sizeof(STUDENT));
				strcpy(s.id, argv[3]);
				strcpy(s.name, argv[4]);
				strcpy(s.dept, argv[5]);
				strcpy(s.year, argv[6]);
				strcpy(s.addr, argv[7]);
				strcpy(s.phone, argv[8]);
				strcpy(s.email, argv[9]);
				add(fp, &s);
				fclose(fp);
				break;
			case's':
				if(argc !=4){
					fprintf(stderr, "wrong foramt\n");
					exit(1);
				}
				if((fp = fopen(argv[2],"r")) ==NULL)
					printf("error\n");
				search_rrn = search(fp,argv[3]);

				read(fp,recordbuf,search_rrn);
				unpack(recordbuf, &s);

				printRecord(&s, search_rrn);
				break;
			case'd':
				if(argc !=4){
					fprintf(stderr,"wrong format\n");
					exit(1);
				}
				if((fp = fopen(argv[2],"r+"))==NULL)
					printf("error\n");
				delete(fp, argv[3]);
				break;
		}
	}


	return 1; 
}
void pack(char *recordbuf, const STUDENT *s)
{
	strcpy(recordbuf,s->id);
	strcat(recordbuf,"#");
	strcat(recordbuf,s->name);
	strcat(recordbuf,"#");
	strcat(recordbuf,s->dept);
	strcat(recordbuf,"#");
	strcat(recordbuf,s->year);
	strcat(recordbuf,"#");
	strcat(recordbuf,s->addr);
	strcat(recordbuf,"#");
	strcat(recordbuf,s->phone);
	strcat(recordbuf,"#");
	strcat(recordbuf,s->email);
	strcat(recordbuf,"#");
}
void unpack(const char *recordbuf, STUDENT *s)
{
	char *field,record[RECORD_SIZE];
	strcpy(record, recordbuf);
	
	field = strtok(record,"#");
	strcpy(s->id,field);
	field = strtok(NULL, "#");
	strcpy(s->name,field);
	field = strtok(NULL, "#");
	strcpy(s->dept,field);
	field = strtok(NULL, "#");
	strcpy(s->year,field);
	field = strtok(NULL, "#");
	strcpy(s->addr,field);
	field = strtok(NULL, "#");
	strcpy(s->phone,field);
	field = strtok(NULL, "#");
	strcpy(s->email,field);
}
void read(FILE *fp, char *recordbuf, int rrn)
{
	fseek(fp, 4+RECORD_SIZE*rrn,SEEK_SET);
	fread(recordbuf, RECORD_SIZE, 1, fp);
}
void add(FILE *fp, const STUDENT *s)
{
	char *recordbuf = (char *)malloc(sizeof(STUDENT));
	short records=0;
	short head=-1;
	char blank[2];
	char tmp[HEADER_SIZE/2];
	char tmp2[HEADER_SIZE/2];
	char tmp3[HEADER_SIZE/2];
	
	
	fread(tmp , 2, 1, fp);
	records = atoi(tmp);
	fseek(fp, 0, SEEK_SET);
	fprintf(fp, "%d", records+1);
	fseek(fp, 0, SEEK_END);
	if(ftell(fp)<=1)
	{
		fseek(fp, 2, SEEK_SET);
		fprintf(fp, "%d", head);
	}
	
	fseek(fp, 2, SEEK_SET);
	fread(tmp2, 2, 1, fp);
	head = atoi(tmp2);
	if(head == -1)
	{
		pack(recordbuf, s); 
		recordbuf[127] = '\0';
		fseek(fp, 0 ,SEEK_END);
		fwrite(recordbuf,RECORD_SIZE,1,fp);
	}
	else
	{
		printf("%d", head);
		fseek(fp, 5+RECORD_SIZE*head, SEEK_SET);
		fread(tmp3, 2, 1, fp);
		fseek(fp, 2,SEEK_SET);
		fprintf(fp, "%c%c", blank[0],blank[0]);
		fseek(fp, 2,SEEK_SET);
		fprintf(fp, "%d", atoi(tmp3));
		pack(recordbuf, s); 
		recordbuf[127] = '\0';
		fseek(fp, 4+RECORD_SIZE*head ,SEEK_SET);
		fwrite(recordbuf,RECORD_SIZE,1,fp);
	}
	
}
int search(FILE *fp, const char *keyval)
{
	char *recordbuf = (char *)malloc(sizeof(STUDENT));
	char id_buf[9];
	char *tmp;
	int rrn =0;
	STUDENT s;
	while(1)
	{
		fseek(fp,4+RECORD_SIZE*rrn,SEEK_SET);
		fread(id_buf,9,1,fp);
		tmp = strtok(id_buf,"#");
		memcpy(id_buf, tmp, 9);
		if(strcmp(id_buf, keyval) == 0)
		{
			read(fp,recordbuf,rrn);
			unpack(recordbuf, &s);
			return rrn;
		}
		rrn++;

	}


}
void delete(FILE *fp, const char *keyval)
{
	char *recordbuf = (char *)malloc(sizeof(STUDENT));
	short rrn=0;
	short tmp_head,tmp_records;
	char id_buf[9];
	char *tmp;
	char tmp1[HEADER_SIZE/2];
	char tmp2[HEADER_SIZE/2];
	char blank[2];
	memset(recordbuf,'\0', sizeof(STUDENT));
	STUDENT s;
	
	while(1)
	{
		fseek(fp,4+RECORD_SIZE*rrn,SEEK_SET);
		fread(id_buf,9,1,fp);
		tmp = strtok(id_buf,"#");
		memcpy(id_buf, tmp, 9);
		if(strcmp(id_buf, keyval) == 0)
		{
			fseek(fp, 2, SEEK_SET);
			fread(tmp1, 2, 1, fp);
			tmp_head = atoi(tmp1);
			fseek(fp,4+RECORD_SIZE*rrn, SEEK_SET);
			fprintf(fp, "%c%c%c", blank[0],blank[0],blank[0]);
			fseek(fp, 4+RECORD_SIZE*rrn, SEEK_SET);
			fprintf( fp, "%c%d", '*',tmp_head);
			fseek(fp, 2, SEEK_SET);
			fwrite(blank , 2 , 1, fp);
			fseek(fp, 2, SEEK_SET);
			fprintf(fp, "%d", rrn);
			fseek(fp, 0, SEEK_SET);
			fread(tmp2, 2, 1, fp);
			tmp_records = atoi(tmp2);
			fseek(fp, 0, SEEK_SET);
			fprintf(fp, "%d", tmp_records-1);
			exit(1);
		}
		rrn++;
	}
	

}
void printRecord(const STUDENT *s, int n)
{
		printf("%s#%s#%s#%s#%s#%s#%s\n", s->id, s->name, s->dept, s->year, s->addr, s->phone, s->email);
}
