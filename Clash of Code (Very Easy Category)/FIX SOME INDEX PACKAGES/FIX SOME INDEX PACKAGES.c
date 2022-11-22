#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int indentCount(char* line)
{
    int count = 0;
    for(count = 0; ; ++count)
        if (line[count] != '>')
            break;
    return count;
}

char* getName(char* str, int indent)
{
    char* result = strtok(str + indent, " ");
    return result;
}

char* getPageStr(char* str)
{
    char* result = malloc(10);

    int idx = 0;
    int len = strlen(str);
    while (str[idx] != ' ') ++idx;
    
    strcpy(result, str + idx + 1);
    return result;

}

void printLine(char* str, int len, char* subsections)
{
    // allocate memory bc we're gonna have to do some stupid shit here in a sec
    char* manipulate = malloc(len+1);

    // figure out how many indents we need
    int indent = indentCount(str);
    // increase subsection count
    subsections[indent]++;
    // subsections occuring later than our current one cant exist, so set them all to 0
    memset(subsections + indent + 1, 0, 10);

    // get subsection page
    char* page = getPageStr(str);
    // get subsection name
    char* name = getName(str, indent);
    // create string of spaces to make an indent : +1 for the null byte
    char* indentStr = malloc(indent*4+1);
    // set all characters except for the last null byte to spaces
    memset(indentStr, ' ', indent*4);

    // merge indent, subsection, and name
    sprintf(manipulate, "%s%d %s", indentStr, subsections[indent], name);

    // get period count needed
    int periodCount = len - strlen(manipulate) - strlen(page);
    // allocate memory for the periods : +1 for null byte at the end
    char* periods = malloc(periodCount+1);
    // set all characters except for the last null byte to periods
    memset(periods, '.', periodCount);
    
    // concatenate all results and print
    printf("%s%s%s\n", manipulate, periods, page);

    // free memory to be epic and safe
    free(indentStr);
    free(manipulate);
}

int main()
{
    int len, N;
    scanf("%d", &len);
    scanf("%d", &N); fgetc(stdin);
    char* subsections = malloc(50);

    for (int i = 0; i < N; i++) {
        char line[51];
        scanf("%[^\n]", line); fgetc(stdin);
        printLine(line, len, subsections);
    }

    free(subsections);
    return 0;
}
