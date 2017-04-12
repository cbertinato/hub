/* shell.c
Shell for passing commands to instruments
*/

#include "shell.h"

#define DEBUG

void parse_args(char *buffer, char** args, size_t args_size, size_t *nargs)
{
    char *buf_args[args_size]; /* You need C99 */
    char **cp;
    char *wbuf;
    size_t i, j;

    wbuf=buffer;
    buf_args[0]=buffer;
    args[0] =buffer;

    for(cp=buf_args; (*cp=strsep(&wbuf, " \n\t")) != NULL ;){
        if ((*cp != '\0') && (++cp >= &buf_args[args_size]))
            break;
    }

    for (j=i=0; buf_args[i]!=NULL; i++){
        if(strlen(buf_args[i])>0)
            args[j++]=buf_args[i];
    }

    *nargs=j;
    args[j]=NULL;
}


void *initialize_shell(void *arg)
{
	#ifdef DEBUG
		printf("initialize_shell()\n");
	#endif

    char buffer[BUFFER_SIZE];
    char *args[ARR_SIZE];

    int *ret_status;
    size_t nargs;
    FILE *fp = (FILE *)arg;

    printf("$ ");
    while (fgets(buffer, sizeof(buffer), fp) != 0  &&  strcmp(buffer, "bye\n") != 0)
	{
		printf("$ ");
        /*parse_args(buffer, args, ARR_SIZE, &nargs);*/

        fputs(buffer, fp);
	}

	fclose(fp);

    return 0;
}
