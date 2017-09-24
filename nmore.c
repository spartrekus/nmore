
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/ioctl.h>
#include <unistd.h>
//printf ("lines %d\n", w.ws_row);
//printf ("columns %d\n", w.ws_col);


#define KGRE  "\x1B[32m"
#define KCYN  "\x1B[36m"
#define KNRM  "\x1B[0m"


////////////////////////////////////////////////////////////////////
char *strrlf(char *str) 
{     // copyleft, C function made by Spartrekus 
      char ptr[strlen(str)+1];
      int i,j=0;
      for(i=0; str[i]!='\0'; i++)
      {
        if (str[i] != '\n' && str[i] != '\n') 
        ptr[j++]=str[i];
      } 
      ptr[j]='\0';
      size_t siz = sizeof ptr ; 
      char *r = malloc( sizeof ptr );
      return r ? memcpy(r, ptr, siz ) : NULL;
}
////////////////////////////////////////////////////////////////////

 
int main(int argc, char *argv[]) 
{

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    double linemax= (double)(w.ws_row);
    double colmax=  (double)(w.ws_col);


    FILE *input = NULL;
 
    if (argc > 1)
        input = fopen(argv[1], "r");
 
    if (!isatty(fileno(stdin))) 
    {
        // duplicate stdin file descriptor and open it as a FILE*
        input = fdopen(dup(fileno(stdin)), "r");
        // reopen stdin on the terminal (assuming stdout is still connected to the terminal)
        freopen(ttyname(fileno(stdout)), "r", stdin);
    }
 
    char line[1000];
    double linepos=0;
    int fooj; 

    while (fgets(line, sizeof line, input) != NULL) 
    {
        printf("%s", strrlf(line));
	linepos++;
	if ( linepos > linemax )
	{
           printf("\r", KGRE );
           printf("%s", KGRE );
	   printf( "|NMORE, another tiny more (GNU)| <Press Key To Continue> \r", KGRE );
           printf("\r", KNRM );
	   getchar();
	   for( fooj = 0; fooj <= colmax-1 ; fooj++ ) printf( " " );
           printf("\r", KNRM );
           printf("%s", KNRM );
           printf("\r", KNRM );
           printf("%s", strrlf(line));
	   linepos = 0;
	}
        printf("\n");
    }
 
    return 0;
}


