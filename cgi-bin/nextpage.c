#include <stdio.h>
#include<stdlib.h>
#include"sqlite3.h"


int callback(void *para, int col_count, char **col_value, char **col_name){
        for (int i = 1; i < col_count; i++) {
            printf("%s: %s \n", col_name[i], col_value[i]);
      }
	    return 0;
}

int show(sqlite3 *db){
    // printf("<ul>");
	   char *id = getenv("QUERY_STRING");
            char sql[100];
            char *err;
	    sprintf(sql,"select * from news where id = %d",atoi(id));
            if(0 != sqlite3_exec(db,sql,callback,NULL,&err)){
                printf("%s\n",err);
                exit(-1);
            }
           // printf("</ul>");
            return 0;
        }

int main()
{
     printf("Content-Type: text/html\n\n");
     char *header = "<!doctype html>"\
                                   "<html lang='en'>"\
                                   "<head>"\
                                   "<meta charset='utf-8'>"\
                                   "<meta name='viewport' content='width=device-width'>"\
                                   "<title>UC震惊部新闻小组</title>"\
                                   "</head>"\
                                   "<body>";
                                   printf("%s\n",header);
                                   printf("<h1 style='width:1920px;height:100px;background-color:lightgreen;text-align:center;line-height:100px;border-radius:10px;'>大新闻就是!!!!</h1>\n");

                                    sqlite3 *db = NULL;
                                        int res = sqlite3_open("cms.db",&db);
                 if(res !=0){
                     printf("open db fail\n");
                     return -1;
                 }
                 show(db);
                 sqlite3_close(db);
                 printf("</body></html>");
 return 0;
}



