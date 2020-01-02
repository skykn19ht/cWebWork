#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"

typedef struct {
        char *title;
        char *content;
        char *created_at;
}news;

int insert(sqlite3 *db, news new) {
    	char *err;
    	char sql[200];
    	sprintf(sql, "INSERT INTO news (title,content,created_at) VALUES ('%s','%s','%s')", new.title,new.content,new.created_at);
    	if (0 != sqlite3_exec(db, sql, NULL, NULL, &err)){
        printf("\t%s\n", err);
        exit(-1);
    }
    return 0;
}

int callback(void *para, int col_count, char **col_value, char **col_title) {
    for (int i = 0; i < col_count; i++){
        printf("%s: %s \n", col_title[i], col_value[i]);
    }
	printf("\t----------------------------------\n");
    return 0;
}

int show(sqlite3 *db)
{
	char *err;
    	char sql[100];
    	sprintf(sql, "\t\tSELECT * FROM news");
    	if (0 != sqlite3_exec(db, sql, callback, NULL, &err)) {
        	printf("\t\t%s\n", err);
        	exit(-1);
   	 }
	return 0;
}

int del(sqlite3 *db,int x)
{
	char *err;
    char sql[100];
	sprintf(sql, "DELETE FROM news WHERE id='%d'",x);
	if (0 != sqlite3_exec(db, sql, callback, NULL, &err)){
            printf("%s\n", err);
            exit(-1);
         }
        return 0;
}

int modify(sqlite3 *db,news new,int x)
{
	char *err;
    char sql[100];
    sprintf(sql, "UPcreated_at news SET title='%s',content='%s',created_at='%s' WHERE id='%d'",new.title,new.content,new.created_at,x);
    if (0 != sqlite3_exec(db, sql, callback, NULL, &err)) {
            printf("%s\n", err);
            exit(-1);
         }
	return 0;
}

int main()
{
	sqlite3 *db = NULL;	
	int flag=1;
	int x;
	int res = sqlite3_open("cms.db", &db);
    if (res != 0) {
    printf("open db fail\n");
    return -1;
   	}
	while(flag){
		int y;
		printf("---------------菜单----------------\n");
		printf("\t\t1.新增信息\n");
		printf("\t\t2.删除信息\n");
		printf("\t\t3.修改信息\n");
		printf("\t\t4.查看信息\n");
		printf("\t\t5.退出\n");
		printf("---------------------------\n");
		scanf("%d",&y);	
		switch(y){
			case 1:{
				news new;
				printf("\t\t输入标题\n");
				new.title=malloc(sizeof(char));
				new.content=malloc(sizeof(char));
				new.created_at=malloc(sizeof(char));
				scanf("%s",new.title);
				printf("\t\t输入内容\n");
				scanf("%s",new.content);
				printf("\t\t输入日期\n");
				scanf("%s",new.created_at);
				insert(db,new);
				};break;
			case 2:show(db); 
			       printf("\t\t输入要删除的数据id\n");
			       scanf("\t%d",&x);
			       del(db,x);break;
			case 3:
			    {
			       news n;
			       show(db);
			       printf("\t\t输入要修改的信息\n");
                               scanf("%d",&x);
                               printf("\t\t输入修改的标题\n");
                               n.title=malloc(sizeof(char));
                               n.content=malloc(sizeof(char));
                               n.created_at=malloc(sizeof(char));
                               scanf("%s",n.title);
                               printf("\t\t输入修改的内容\n");
                               scanf("%s",n.content);
                               printf("\t\t输入修改的日期\n");
                               scanf("%s",n.created_at);
			       modify(db,n,x);
			       };break;		       
			case 4:
			       show(db);break;
			case 5: 
			       flag=0;	
			       break;
			default :
			       printf("\t\t请输入正确序号1-5\n");
		}
	}
	sqlite3_close(db);
	return 0;
}
