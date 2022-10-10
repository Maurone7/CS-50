//
// Created by Mauro Patimo on 10/6/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    
    char source_list_barenfeld_2016[106][20];
    char source[100];
    char *filename = "/Users/mauro/Dropbox/GitHub/C/Barenfeld Table 1.txt";
    FILE * file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("Not Opened \n");
        return 1;
    }

    char *element;
    int line = 0;
    int index = 0;
    while (line < 106)
    {
        fgets(source, 256, file);
        element = strtok(source, " ");
        element = strtok(NULL, " ");
        strcpy(source_list_barenfeld_2016[index], element);
        index++;
        /* printf("%d \n", line); */
        line++;
    }
    fclose(file);

    for (int loop_value = 0; loop_value < sizeof(source_list_barenfeld_2016)/sizeof(source_list_barenfeld_2016[0]); loop_value++)
    {
        printf("%s \n", source_list_barenfeld_2016[loop_value]);
    }
    return 0;
}
