#ifndef PROMPT_H
#define PROMPT_H

void init_shell_home(void);
void disp_prompt(void);

extern char shell_home[1024]; // give access to shell_home to other files

#endif