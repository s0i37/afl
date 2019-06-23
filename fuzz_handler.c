#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

void fuzz(char *buf, unsigned int len)
{
	int s;
	struct sockaddr_in addr;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(68);
	sendto(s, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));
	close(s);
}
