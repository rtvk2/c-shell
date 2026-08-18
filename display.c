#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>


char shell_home[1024]; 
int init_home = 0;

void disp_prompt() {
    char hostname[256];
    char cwd[1024];
    struct passwd *pw; // profile holder

    pw = getpwuid(getuid());
    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));

    if (init_home == 0) { // initialise home when shell first starts
        strcpy(shell_home, cwd);
        init_home = 1;
    }

    char dir[1024];

    if (strncmp(cwd, shell_home, strlen(shell_home)) == 0) { // check if cwd is within home by comparing n (shell_home) characters
        sprintf(dir, "~%s", cwd + strlen(shell_home)); // replace home path with ~; sprintf as we need to store it before printing
    } else {
        strcpy(dir, cwd);  // else just copy cwd to dir
    }
    printf("<%s@%s:%s> ", pw->pw_name, hostname, dir); // format acc to req
}