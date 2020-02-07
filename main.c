#include "projekti.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>


//compares two objects on the list
int cmp (const void *a_p, const void *b_p){
    const Country *a = a_p;
    const Country *b = b_p;

    //compare gold medals
    if (a->gold > b->gold){
        return -1;
    }else if (a->gold < b->gold){
        return 1;
    }
    //compare silver medals
    if (a->silver > b->silver){
        return -1;
    }else if (a->silver < b->silver){
        return 1;
    }
    //compare bronze medals
    if (a->bronze > b->bronze){
        return -1;
    }else if (a->bronze < b->bronze){
        return 1;
    }

    return 0; //palauta nolla jos ovat identtiset
}

/*Adds a country to the list and names it str. This function also adds one more space in to the country array*/
Country * add_country (Country *arr, char *str, int num){
    arr = realloc(arr, (num+1)*sizeof(Country)); //add space for one country
    sscanf(str, "%*c %s", arr[num].name);
    arr[num].gold = 0;
    arr[num].silver = 0;
    arr[num].bronze = 0;
    printf("Following country has been added: %s\n", arr[num].name);

    return arr;
}

/*updates the ranks for given country*/
Country * update_medals(Country *arr, char *str, int num){
    int gold ,silver, bronze, i = 0;
    //int silver = 0;
    //int brons = 0;
    char *name = calloc(20, (num+1)*sizeof(char));
    sscanf(str, "%*c %s %d %d %d", name, &gold, &silver, &bronze);

    for (; i<num; i++){ //this for loop goes through the list and finds the country that is needed
        if (strcmp(arr[i].name, name)==0){
            arr[i].gold = arr[i].gold + gold;
            arr[i].silver = arr[i].silver + silver;
            arr[i].bronze = arr[i].bronze + bronze;
            printf("Medals have been updated %s %d %d %d\n", arr[i].name, arr[i].gold, arr[i].silver, arr[i].bronze);
        }
    }
    free(name);

    return arr;
}

//Arranges countries in correct order and then prints the list
void print_array(Country *arr, int num){
    qsort(arr, num, sizeof(Country), cmp);
    printf("Medals have been sorted:\n");
    for(int i = 0; i<num; i++){
        printf("%s %d %d %d\n", arr[i].name, arr[i].gold, arr[i].silver, arr[i].bronze);
    }

    return;
}

//writes all the information from array to a file
void save_to_file(Country *arr, char *str, int num){
    char *filename = calloc(20, sizeof(char));
    int i = 0;
    int check = 1;
    sscanf(str, "%*c %s", filename);

    FILE *file = fopen(filename, "w");

    if (!file){
        printf("Could not create file\n");
        free(filename);
        return;
    }

    do{
        check = fprintf(file, "%s %d %d %d\n", arr[i].name, arr[i].gold, arr[i].silver, arr[i].bronze);
        i++;
    } while (check > 0 && i < num);

    if (file == NULL){//incase file creation failed
        printf("Something went wrong\n");
    }else {
        printf("Information was saved succesfully\n");
    }
    fclose(file);
    free(filename);
    return;
}


Country * download_file(Country *arr, char *str){
    int i = 0;
    char* check;
    char *filename = calloc(20, sizeof(char));
    sscanf(str, "%*c %s", filename);

    FILE *file = fopen(filename, "r");

    if(!file){
        printf("Could not open file\n");
        free(filename);
        return arr;
        }

    free(arr);
    Country *arr2 = calloc(1, sizeof(Country));  //initiates list for countries
    char *buffer = calloc(50, sizeof(char));

    while (check != NULL){
        check = fgets(buffer, 50, file);
        arr2 = realloc(arr2, (i+1)*sizeof(Country));
        sscanf(buffer, "%s %d %d %d", arr2[i].name, &arr2[i].gold, &arr2[i].silver, &arr2[i].bronze);
        i++;
    }

    printf("Information has been copied from file succesfully.\n");

    arr2[i-1].name[0] = '0';

    fclose(file);
    free(filename);

    return arr2;
}

int main(){
    Country *arr = calloc(1, sizeof(Country));  //initiates list for countries
    arr[0].name[0] = '\0';                      //sets the first country as empty string
    int number_of_countries = 0;


    char *buffer = calloc(50, sizeof(char)); //buffer for user inputs


    for(char command = 'k';command != 'Q'; ){
        buffer[0] = '\0';
        printf("Please, enter a command.\n");
        fgets(buffer, 50, stdin);
        int n = strlen(buffer);


        if(n>0 && buffer[n-1]=='\n'){ //this if-loop deletes the final "\n" from buffer string
            buffer[n-1]=0;
        }
        printf("\n");
        command = buffer[0];

        /*If command is A, then following if structure will add a
        country to the list of countries*/
        if (command == 'A'){
            arr = add_country(arr, buffer, number_of_countries);
            number_of_countries++;
        }
        /*If command is M, then following if structure will
        update the medals for the given country*/
        if (command == 'M'){
            arr = update_medals(arr, buffer, number_of_countries);

        }

        if (command == 'L'){
            print_array(arr, number_of_countries);
        }

        if (command == 'W'){
            save_to_file(arr, buffer, number_of_countries);
        }

        if (command == 'O'){
            arr = download_file(arr, buffer);
            number_of_countries = 0;

            for(int i = 0; arr[i].name[0]!='0'; i++){
                number_of_countries++;
            }
        }

    }
    printf("Exiting program and clearing memory.\n");
    free(buffer);
    free(arr);
    return 0;
    }
