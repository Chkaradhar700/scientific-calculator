#ifndef COMMANDS_H
#define COMMANDS_H

bool isCommand(char *);
void runCommand(char *, char *, int *);

void c_setMode(char *, bool);
void c_back(char *);
void c_setPrecision(int *);
void c_displayInfos(int);
void c_clear();
void c_exit(char *);

#endif /* COMMANDS_H */