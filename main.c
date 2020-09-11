
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int lastRet = 0;

int echo(int argc, char *argv[]) {
	for (int i = 1; i < argc; ++i) {
		printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
	}
	return argc - 1;
}

int retcode(int argc, char *argv[]) {
	printf("%d\n", lastRet);
	return 0;
}

void cmdRun(int argc, char *argv[]) {
	//printf("\n");
	if (!strcmp(argv[0], "echo")) {
		lastRet = echo(argc, argv);
		return;
	}
	if (!strcmp(argv[0], "retcode")) {
		lastRet = retcode(argc, argv);
		return;
	}
	printf("%s '%s' %s\n","command", argv[0], "doesn't exist");
	lastRet = -1;
}

int main(int argc, char *argv[]) {
	while (true) {
		char *next = NULL;
		char bufer[256];
		fgets(bufer, sizeof(bufer), stdin);
		char *cmdNulls = ";\n";
		char* s = bufer;
		while (*s == ' ') {
			s++;
		}
		strcpy(bufer, s);
		char *cmdLine = strtok_r(bufer, cmdNulls, &next);
		while (cmdLine != NULL) {
			char *nextIn = NULL;
			char *argNulls = " ";
			char *argLine = cmdLine;
			argLine = strtok_r(argLine, argNulls, &nextIn);
			char *argv[256];
			int argc = 0;
			while (argLine) {
				argv[argc] = argLine;
				argc++;
				argLine = strtok_r(NULL, argNulls, &nextIn);
			} 
			cmdRun(argc, argv);
			cmdLine = strtok_r(NULL, cmdNulls, &next);
			//printf("\n");
		}
	}
	return 0;
}
