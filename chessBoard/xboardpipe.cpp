#include <iostream>
//#include <iomanip>
#include <cstring>
//#include <cstdlib>
//#include <cstdio>
#include <unistd.h>
#include <fcntl.h>
//#include <signal.h>
//#include <string>
using namespace std;


string  readFromProgram( int programOutputEnd)
{
    char *buf;
    buf=(char *) malloc(1024);
    string result;
    int outCount=1;
    fflush(NULL);
    outCount = read(programOutputEnd, buf,8024);
    result += std::string(buf, buf + outCount);
    return result;

}

void forkToReadProgram(int programOutputEnd)
{
    string stx;
    int pid = fork();
    if(pid < 0) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
    if(pid == 0) //child 
	{ 
        //int readFromChess = dup(programSinkOut);
        fcntl(programOutputEnd, F_SETFD,fcntl(programOutputEnd, F_GETFD) | O_NONBLOCK);
        for (;;){
                fflush(NULL);
                stx=readFromProgram(programOutputEnd);
                cout<<stx<<endl;
            }
    }
}

int openChessPipe(int programOutputReplacement, int programInputReplacement){
    char *cmd1[] = { "./gnuchess" , 0};
	char *dir =  "/home/talegria/projects/gnuchess-6.2.9/src";

    int pid = fork();

    if(pid < 0) 
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
    if(pid == 0)  // Child process 
	{	
        //0: stdin. 1: stdout
        dup2(programInputReplacement, 0); 
        

        dup2(programOutputReplacement, 1);
        fcntl(programOutputReplacement, F_SETFL,fcntl(programOutputReplacement, F_GETFL) | O_NONBLOCK);
        
        if (chdir(dir) != 0) {
          perror(dir);
          exit(1);
        }
       
		if ((execvp(cmd1[0], cmd1)) < 0) 
		{
			perror("execl  **********");
			exit(EXIT_FAILURE);
		}

	}

    return pid;
    }

void writeToProgram(char *message, int programInputEnd )
{
    
    int count = strlen(message);
    int outCount = write(programInputEnd, message, count);
    if (outCount==0) {
        perror("write to chess failed");
		exit(EXIT_FAILURE);
    }
    return;
}




string readFromProgram (FILE* stream)
{
    char *buffer;
    buffer=(char *) malloc(1024);
    string result;
    fflush(stream);

    if (fgets (buffer, 1024, stream) != NULL)
        result += std::string(buffer, buffer + sizeof (buffer));

    return result;
}


int main()
{
    int programInput[2];
    int programOutput[2];
    char *buf;
    string buf2="";
    int cnt=0;

    if ((pipe(programInput)) < 0 | (pipe(programOutput)) < 0  ) 
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

    //0: stdin. 1: stdout
    int programOutputReplacement= programOutput[1];
    int programInputReplacement= programInput[0];

    int programOutputEnd = programOutput[0];
    int programInputEnd= programInput[1];



    int chessPID=openChessPipe(programOutputReplacement, programInputReplacement);

    forkToReadProgram(programOutputEnd);
    
    for (;;){
 
        cin>>buf2;
        char bufx[buf2.length() + 1]; 
        strcpy(bufx, buf2.c_str()); 
        cnt=strlen(bufx);
        bufx[cnt]='\n';
        if (bufx[0]!='.')
            writeToProgram(bufx, programInputEnd);
    }

    return 0;
}