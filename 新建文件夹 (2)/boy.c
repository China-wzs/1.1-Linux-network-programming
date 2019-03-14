//包含头文件
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>  //open的头文件
#include <unistd.h> //read  write close
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/*
	演示tcp通信的基本流程
	男朋友的代码
*/
int main()
{
	int iphonex;
	int ret;
	char buf[50];
	//*定义ipv4地址结构体变量
	struct sockaddr_in bindaddr;
	bindaddr.sin_family=AF_INET;
	bindaddr.sin_port=htons(20000); //男朋友自己的端口号
	bindaddr.sin_addr.s_addr=inet_addr("192.168.222.129"); //男朋友自己的ip地址

	//定义ipv4地址结构体变量
	struct sockaddr_in girladdr;
	girladdr.sin_family=AF_INET;
	girladdr.sin_port=htons(10000); //女朋友的端口号
	girladdr.sin_addr.s_addr=inet_addr("192.168.222.128"); //女朋友的ip地址
	
	//创建套接字--》买手机
	iphonex=socket(AF_INET,SOCK_STREAM,0);
	if(iphonex==-1)
	{
		printf("创建套接字失败!\n");
		return -1;
	}
	//绑定ip地址和端口号
	ret=bind(iphonex,(struct sockaddr *)&bindaddr,sizeof(bindaddr));
	if(ret==-1)
	{
		printf("绑定失败!\n");
		return -1;
	}
	//拨号给女朋友
	ret=connect(iphonex,(struct sockaddr *)&girladdr,sizeof(girladdr));
	if(ret==-1)	
	{
		 perror("connect");
		printf("连接失败!\n");
		return -1;
	}
	//发送信息给女朋友
	printf("请输入要发送给女朋友的信息！\n");
	scanf("%s",buf);
	send(iphonex,buf,50,0);
	//挂机
	close(iphonex);
	return 0;
}
