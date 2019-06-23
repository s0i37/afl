#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>

static void tcp(void* buf, unsigned int len)
{
	int s;
	struct sockaddr_in addr;

	s = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(445);
	connect(s, (struct sockaddr *)&addr, sizeof(addr));
	send(s, buf, len, 0);
	close(s);
}

static void udp(char *buf, unsigned int len)
{
	int s;
	struct sockaddr_in addr;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(137);
	sendto(s, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));
	close(s);
}

void* fuzz(char *buf, unsigned int len)
{
	udp(buf, len);
	//tcp(buf, len);
}