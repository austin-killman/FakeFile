#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>

struct Command
{
    char * cmd;
    char ** args;
    char * inputPath;
    char * outputPath;
};

struct Commands
{
    struct Command * allCmd;
    bool multCmd;
};

struct Recipe
{
    char * targetPath;
    char ** preReqPath;
    int preReqCount;
    bool preReq;
    struct Commands commands;
};
