#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include "colors.h"


char shell_home[1024]; 
int init_home = 0;

void init_shell_home(void) {
    if (getcwd(shell_home, sizeof(shell_home)) == NULL) {
        perror("getcwd (startup)");
        strcpy(shell_home, "/");  //fallback so shell_home is never garbage value
    }
    init_home = 1;
}

void disp_prompt() {
    char hostname[256];
    char cwd[1024];
    struct passwd *pw; // profile holder

    pw = getpwuid(getuid());
    const char *username = (pw != NULL) ? pw->pw_name : "unknown"; // account for unknown user

    if (gethostname(hostname, sizeof(hostname)) != 0) {
        perror("gethostname");
        strcpy(hostname, "unknown-host");
    }

    if (getcwd(cwd, sizeof(cwd)) == NULL) { // getcwd returns NULL on error to avoid segfault
        perror("getcwd");
        strcpy(cwd, "?");
    }

    if (init_home == 0) { // initialise home when shell first starts
       init_shell_home();
    }

    char dir[1024];
    size_t home_len = strlen(shell_home);

    if (strncmp(cwd, shell_home, home_len) == 0 && (cwd[home_len] == '/' || cwd[home_len] == '\0')) { // check if cwd is within home by comparing n (shell_home) characters
        snprintf(dir, sizeof(dir), "~%s", cwd + home_len); // replace home path with ~; sprintf as we need to store it before printing
    } else {
        snprintf(dir, sizeof(dir), "%s", cwd); // else just print the cwd
    }
    printf("<" COLOR_USER "%s" COLOR_SYMBOLS "@" COLOR_HOST "%s" COLOR_SYMBOLS ":" COLOR_DIR "%s" COLOR_RESET "> ", username, hostname, dir); // format acc to req
}