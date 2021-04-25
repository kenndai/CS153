#include "types.h"
#include "user.h"
#include "stat.h"

int main (int argc, char *argv[]) {
    int pid;
    int childExitStatus = 124;

    if ((pid = fork()) == 0) {
        printf(1, "Hello from child process! My exit status is: %d\n", childExitStatus);
        exit(childExitStatus);
    }
    else if (pid != 0){
        printf(1, "Hello from parent process!\n");

        int status; //should contain 123 after executing wait()
        int cPid = wait(&status);

        if (cPid >= 0) {
            printf(1, "The child process' exit status from wait() is: %d\n", status);

            if (status == childExitStatus) {
                printf(1, "The exit statuses match!\n");
            }
            else {
                printf(1, "The exit statuses do not match!\n");
            }
        }
        else {
            printf(1, "No child processes were found!\n");
        }

    }

    exit(0);
}