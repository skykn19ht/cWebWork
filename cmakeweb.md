1下载sqlite3;

sudo apt-get install sqlite3；

2 建库

sqlite cms.db

3建表

CREATE TABLE IF NOT EXISTS news(
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    title TEXT,
    content TEXT,
    created_at TEXT
);

4插入数据

INSERT INTO news (title, content, created_at) VALUES ('震惊！美国总统看到最后都惊呆了！','first news', '2019-12-28');
INSERT INTO news (title, content, created_at) VALUES ('震惊！韩红听了都想打人！', 'second news','2019-12-29');
INSERT INTO news (title, content, created_at) VALUES ('震惊！男人看了会沉默！','third news', '2019-12-30');
INSERT INTO news (title, content, created_at) VALUES ('震惊！女人看了会流泪！','fourth news', '2019-12-31');
INSERT INTO news (title, content, created_at) VALUES ('震惊！全中国都在看这个！','fivth news', '2020-01-01');

5下载apache

sudo apt-get install apache2

6启动CGI支持

找到var下的www文件,打开,创建cgi-bin文件夹

 找到ETC下面的server-cgi-bin,将地址改为自己的地址

将下面的三行软连接写入,要用最高权限

ln -s /etc/apache2/mods-available/cgid.conf  /etc/apache2/mods-enabled/cgid.conf

ln -s /etc/apache2/mods-available/cgid.load  /etc/apache2/mods-enabled/cgid.load 

ln -s /etc/apache2/mods-available/cgi.load   /etc/apache2/mods-enabled/cgi.load

重启apache   /etc/init.d/apache2 restart

7编译cgi 增删改查

编译语句：gcc xxx.c sqlite3.o lpthread -ldl  -o -xxx.cgi









