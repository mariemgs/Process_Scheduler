#ifndef MANAGE_H
#define MANAGE_H
#include "process.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int getProcessnbFromFile(char *fileName)
{
    // Read the configuration file
    FILE *file = fopen(fileName, "r");
    char line[256];
    int n=0;
    if (file == NULL)
    {
        //Alert the user if the file doesn't exist
        printf("The file: %s doesn't exist \n", fileName);
    }
    else
    {
        // file exist
        while (fgets(line, sizeof(line), file))
        {
            //first character of the line
            char firstChar = line[0];
            // check if line is empty or is a comment
            if ((firstChar != '#') && (strlen(line) > 2))
            {
                n++;
            }
        }
    }
    return n;
}


#endif