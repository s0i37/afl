#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

struct Args {
	char *buf;
	unsigned int len;
} args;
int s = 0;

void tcp(struct Args *args)
{	
	char resp[1000];
	char buf[1000];
	FILE *f;
	int size;

	if(s == 0)
	{
		struct sockaddr_in addr;

		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = inet_addr("127.0.0.1");
		addr.sin_port = htons(445);
		while( connect(s, (struct sockaddr *)&addr, sizeof(addr)) != 0 )
			sleep(0.1);
	}
	
	f = fopen("/root/temp/a1","rb");
	size = fread(&buf, 1, 1000, f);
	fclose(f);
	send(s, &buf, size, 0);
	recv(s, &resp, 1000, 0);

	send(s, args->buf, args->len, 0);
	recv(s, &resp, 1000, 0);
	s = 0;
	close(s);
}

void udp(struct Args *args)
{
	int s;
	struct sockaddr_in addr;

	s = socket(AF_INET, SOCK_DGRAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(137);
	sendto(s, args->buf, args->len, 0, (struct sockaddr *)&addr, sizeof(addr));
	close(s);
}

void* fuzz(char *buf, unsigned int len)
{
	pthread_t thread;

	args.buf = buf;
	args.len = len;
	//pthread_create(&thread, 0, tcp, (void *)&args);
	pthread_create(&thread, 0, udp, (void *)&args);
}