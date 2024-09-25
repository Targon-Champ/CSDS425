/*
Name: Shrinidhi Narasimha Hegde
CaseID: sxh1426@case.edu
Filename: proj1.c
Date Created: 3rd September, 2024
Description: This file takes in a txt file as input using -f flag and checks if each line of that file is a valid IPv4 address or not. There are 2 modes of output. "summary mode" activated by -s flag and "list mode" activated by -l flag. You are supposed to use one of the two output mode flags at once and not both. You are supposed to provide a input file using -f without which the code will not execute.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int mode = -1;
char filename[255];

void usage(char *progname) // this funtions describes how the code is supposed to be run. It is called when there is an error in the code.
{
    fprintf(stderr, "%s [-s] [-l] -f filename\n", progname);
    fprintf(stderr, "   -s    results in summary mode\n");
    fprintf(stderr, "   -l    results in list mode\n");
    fprintf(stderr, "		Either one of the two flags above is mandatory!!!\n");
    fprintf(stderr, "   -f X  filename \'X\'\n");
    fprintf(stderr, "		Please do not provide any other extra flags if you want to see this run.\n");
    exit(1);
}

void cmdops(int argc, char *argv[]) // This function handles the user input flags
{
    if (argc != 4)
    {
        fprintf(stderr, "Missing/Extra command line options\n");
        usage(argv[0]); // shows all the possible flags to the user.
    }
    for (int i = 1; i < argc; i++)
    {
        if (strcmp("-l", argv[i]) == 0)
        {
            mode = 1;
        }
        else if (strcmp("-s", argv[i]) == 0)
        {
            mode = 0;
        }
        else if (strcmp("-f", argv[i]) == 0)
        {
            strcpy(filename, argv[i + 1]);
            i++;
        }
        else
        {
            usage(argv[0]); // if none of the conditions are true, then show all the possible flags to the user.
        }
    }
}

int checkline(char *line) // this functions checks if every line is a valid IPv4 or not.
{
    char *token;
    char *ptr = strsep(&line, "\n");
    int dots_count = 0;
    int sub_val;
    while ((token = strsep(&ptr, ".")))
    {
        if (*token == '\0') // check if the token is empty
        {
            return 1;
        }

        for (int i = 0; i < strlen(token); i++) // check if every item in the token is a digit
        {
            if (!isdigit(token[i]))
            {
                return 1;
            }
        }

        sscanf(token, "%d", &sub_val);         // convert string to int
        if ((sub_val >= 0) && (sub_val < 256)) // check if the token is between 0 and 255
        {
            // check for number padding
            if ((sub_val < 10) && (strlen(token) != 1))
            {
                return 1;
            }
            if ((sub_val > 9) && (sub_val < 100) && (strlen(token) != 2))
            {
                return 1;
            }
            if ((sub_val > 99) && (strlen(token) != 3))
            {
                return 1;
            }
            // if everything is right...
            dots_count++;
        }
        else
        {
            return 1;
        }
        if (dots_count == 5)
        { // if the line contains more and 3 dots
            return 1;
        }
    }

    if (dots_count < 4)
    {
        return 1;
    }
    return 0; // if it is a valid IPv4
}

int main(int argc, char **argv)
{
    // this function parses the command line operations and saves the mode of operation and filename in the memory.
    cmdops(argc, argv);

    FILE *file = fopen(filename, "r"); // read the file

    if (file != NULL)
    {
        char line[256];
        char line_cpy[256];
        int line_count = 0;
        int line_validity;
        int valid_count = 0;
        int invalid_count = 0;
        while (fgets(line, 256, file))
        {
            line_count++;
            strcpy(line_cpy, line);
            line_validity = checkline(line);

            if (line_validity == 0)
            {
                valid_count++;
                if (mode == 1)
                {
                    printf("%s +\n", strtok(line_cpy, "\n"));
                }
            }
            else
            {
                invalid_count++;
                if (mode == 1)
                {
                    printf("%s -\n", strtok(line_cpy, "\n"));
                }
            }
        }
        if (mode == 0)
        {
            printf("LINES: %d\n", line_count);
            printf("VALID: %d\n", valid_count);
            printf("INVALID: %d\n", invalid_count);
        }
        fclose(file);
    }
    else
    {
        fprintf(stderr, "Cannot open the file %s", filename); // next line is printed if any error occurs when reading the file.
    }
    return 0;
}