#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>

#define serverport  8888
int main(int argc,char* argv[])
{
	
	int clientsocket;
	struct sockaddr_in server_addr,cxl_addr;
	char buff[1024];
	int ret,num;
	int server_addr_size;
	//socket
	clientsocket=socket(AF_INET, SOCK_STREAM, 0);
	if(clientsocket==-1)perror("socket");
		
	//��ʼ��
	server_addr.sin_family     = AF_INET;
	server_addr.sin_port  	   = htons(serverport);
	server_addr.sin_addr.s_addr=inet_addr("192.168.2.126");

	cxl_addr.sin_family     = AF_INET;
	cxl_addr.sin_port  	   = htons(serverport);
	cxl_addr.sin_addr.s_addr=inet_addr("47.107.150.126");
	
	memset(server_addr.sin_zero, 0, 8);

	ret=bind(clientsocket, (struct sockaddr *) &cxl_addr,sizeof(struct sockaddr));
	if(ret==-1)perror("bind");
	
	//connect
	ret=connect(clientsocket,(struct sockaddr *) &server_addr,sizeof(struct sockaddr));
	if(ret==-1)perror("connect");

	
	while(1)
	{		
		num = read(0, buff, 1024);
		write(clientsocket, buff, num); /*���͸�������*/	
		num = read(clientsocket, buff, 1024); /*�ӷ�������ȡ����*/
		if(num>0)
		{
			printf("get date form server: ");
			write(1, buff, num); /*д����׼���*/		
			
		}
	}	
	close(clientsocket);
	return 0;
}










