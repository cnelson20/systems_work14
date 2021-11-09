#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static void sighandler(int sig) {
	switch (sig) {
	case SIGINT:
		int fd = open("error.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1) {printf("%s\n",strerror(errno));}
		int b = write(fd,"Process terminated by SIGINT\n",strlen("Process terminated by SIGINT\n"));
		if (b == -1) {printf("%s\n",strerror(errno));}
		close(fd);
		exit(1);
	case SIGUSR1:
		printf("ppid: %u\n",getppid());
		break;
	}
}

int main() {
	signal(SIGINT,sighandler);
	signal(SIGUSR1,sighandler);	
	
	while(1) {
		printf("pid: %u\n",getpid());
		sleep(1);
	}
	
	return 0;
}