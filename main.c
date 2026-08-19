#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "prompt.h"

int main() {

     init_shell_home();
     disp_prompt();
    return 0;
}