#ifndef PROJEKTI_H
#define PROJEKTI_H
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

/**Maa struct**/
typedef struct{
    char name[20]; //country name
    int gold;
    int silver;
    int bronze;
}Country;


//Public functions
Country * add_country (Country *arr, char *str, int num);

Country * update_medals(Country *arr, char *str, int num);

void print_array(Country *arr, int num);

void save_to_file(Country *arr, char* str, int num);

Country * download_file(Country *arr, char *str);
/*void poistu;
*/


#endif // PROJEKTI_H
