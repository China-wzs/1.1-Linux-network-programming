//包含头文件
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //open的头文件
#include <unistd.h> //read  write close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/ip.h>
/*
	演示tcp通信的基本流程
	女朋友的代码
*/
int main()
{
	int iphonex;
	int iphonexplus;
	int ret;
	char buf[50];
	//定义ipv4地址结构体变量
	int tmp =1;
	int val = 0;
        iphonex=socket(AF_INET,SOCK_STREAM,0);
        if(iphonex==-1)
        {
                printf("创建套接字失败!\n");
                return -1;
        }
//    int a= setsockopt(iphonex,SOL_SOCKET,SO_REUSEADDR,(void *)&val,sizeof(int));
	struct sockaddr_in bindaddr;
	bindaddr.sin_family=AF_INET;
	bindaddr.sin_port=htons(10000); //女朋友自己的端口号
	//bindaddr.sin_addr.s_addr=inet_addr("127.2.2.222"); //女朋友自己的ip地址
	
	bindaddr.sin_addr.s_addr=inet_addr("192.168.222.128"); //女朋友自己的ip地址
	//定义ipv4地址结构体变量
	struct sockaddr_in boyaddr;
	int addrsize=sizeof(boyaddr);
	
	//创建套接字--》买手机	iphonex=socket(AF_INET,SOCK_STREAM,0);
	
	int a=setsockopt(iphonex, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(int));	
	if(a<0)
	{
		perror("setsockopt failed");
	}
	//绑定ip地址和端口号
	ret=bind(iphonex,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
	if(ret==-1)
	{
		perror("bind");	
        	printf("绑定失败!\n");
		return -1;
	}
	//待机--》监听
	ret=listen(iphonex,5);
	if(ret==-1)
	{
		printf("监听失败!\n");
		return -1;
	}
	//愿意接受连接请求
	iphonexplus=accept(iphonex,(struct sockaddr *)&boyaddr,&addrsize);
	if(iphonexplus==-1)
	{
		printf("接受客户端连接失败！\n");
		return -1;
	}
	//接收客户端发送过来的内容
	recv(iphonexplus,buf,50,0);
	printf("我男朋友发送过来的内容是:%s\n",buf);
	//挂机
	close(iphonex);
	close(iphonexplus);
	return 0;
}
