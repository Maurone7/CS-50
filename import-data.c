//
// Created by Mauro Patimo on 10/6/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct Barenfeld_2016
{
    char source_list[106][20];
    double flux_list[106];
    double flux_list_LOG[106];
    double flux_list_error[106];
    double flux_list_error_LOG[106];
};

struct GAIA_3
{
    double parallaxes[106];
    double distances_106[106];
};

double calculate_distances(double parallaxes)
{
    return 1/parallaxes * 1000;
}

double update_luminosity(double old_luminosity, double new_distance)
{
    return pow(10, old_luminosity) * pow(new_distance, 2) / pow(145, 2);
}

double calculate_upper_error(double base_value, double error_value)
{
    return pow(10, base_value + error_value) - pow(10, base_value);
}

int main()
{
    
    struct Barenfeld_2016 barenfeld_2016;
    struct GAIA_3 gaia_3;
    char flux_list_LOG_error_barenfeld_2016_LOG[106][5];

    char source[100];
    char *filename_A = "/Users/mauro/Dropbox/GitHub/C/Barenfeld Table 1.txt";
    FILE * file_A = fopen(filename_A, "r");

    char *element_A;
    int line_A = 0;
    int index_A = 0;
    while (line_A < 106)
    {
        fgets(source, 256, file_A);
        element_A = strtok(source, " ");
        element_A = strtok(NULL, " ");
        strcpy(barenfeld_2016.source_list[index_A], element_A);
        element_A = strtok(NULL, " ");
        element_A = strtok(NULL, " ");
        element_A = strtok(NULL, " ");
        element_A = strtok(NULL, " ");
        element_A = strtok(NULL, " ");
        barenfeld_2016.flux_list_LOG[index_A] = atof(element_A);
        element_A = strtok(NULL, " ");
        barenfeld_2016.flux_list_error_LOG[index_A] = atof(element_A);

        index_A++;
        line_A++;
    }
    fclose(file_A);

    char *element_B;
    int line_B = 0;
    int index_B = 0;
    char *filename_B = "/Users/mauro/Dropbox/GitHub/C/GAIA3 archive.json";
    FILE * file_B = fopen(filename_B, "r");

    while (line_B < 106)
    {
        fgets(source, 256, file_B);
        element_B = strtok(source, ",");
        element_B = strtok(NULL, ",");
        element_B = strtok(NULL, ",");
        element_B = strtok(NULL, ",");
        element_B = strtok(NULL, ",");
        gaia_3.parallaxes[index_B] = atof(element_B);

        index_B++; line_B++;
    }
    fclose(file_B);

    double distances_106[106];
    for (int i=0; i<106; i++)
    {
        if (gaia_3.parallaxes[i] == 0.0)
        {
            gaia_3.parallaxes[i] = 6.896551724;
        }
        gaia_3.distances_106[i] = calculate_distances(gaia_3.parallaxes[i]);
        barenfeld_2016.flux_list[i] = pow(10, barenfeld_2016.flux_list_LOG[i]);
        barenfeld_2016.flux_list_error[i] = calculate_upper_error(barenfeld_2016.flux_list_LOG[i], barenfeld_2016.flux_list_error_LOG[i]);
    }

    printf("Source \t \t  flux \t   error    distance \n");
    for (int loop_value = 0; loop_value < 106; loop_value++)
    {
        printf("%s %f %f %f \n", barenfeld_2016.source_list[loop_value],
         barenfeld_2016.flux_list_LOG[loop_value], barenfeld_2016.flux_list_error_LOG[loop_value],
        gaia_3.distances_106[loop_value]);
    }
    return 0;
}
