#include "types.h"
#include "user.h"
#include "stat.h"

void exitAndWaitTest() {
    int pid;
    int childExitStatus = 123;

    if ((pid = fork()) == 0) {
        printf(1, "Hello from child process! My exit status is: %d\n", childExitStatus);
        exit(childExitStatus);
    }
    else if (pid != 0){
        printf(1, "Hello from parent process!\n");

        int status; //should contain 123 after executing wait()
        int cPid = waitpid(pid, &status, 0);

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
}

void waitpidTest() {
    int pid1, pid2;
    int status1, status2;

    if ((pid1 = fork()) == 0) {
        printf(1, "Child process 1 is running\n");
        exit(10);
    }
    else if ((pid2 = fork()) == 0) {
        printf(1, "Child process 2 running\n");
        exit(20);
    }
    else {
        waitpid(pid2, &status2, 0);
        printf(1, "Parent process reaped child process 2! Exit status is %d\n", status2);
        waitpid(pid1, &status1, 0);
        printf(1, "Parent process reaped child process 1! Exit status is %d\n", status1);
    }
}

int main (int argc, char *argv[]) {
    waitpidTest();
    //exitAndWaitTest();
    exit(0);
}
