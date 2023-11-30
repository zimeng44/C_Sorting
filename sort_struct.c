#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "sort.h"

int read_students(FILE *ifp, struct Student *sdata){
    char row[100];
    char * token;
    // read one line at a time for MAX_STUDENTS times
    int i;
    for (i = 0; i < MAX_STUDENTS; i++){
        if (fgets(row , 100 , ifp) != NULL){
            token = strtok(row, ",\n");
            strcpy(sdata[i].last, token);
            token = strtok(NULL, ",\n");
            strcpy(sdata[i].first, token);
            token = strtok(NULL, ",\n");
            sdata[i].id = atoi(token);
        }else {
            break;
        }  
    }
    return i;
}

int sort_students(char *sort_key, int num_students, struct Student *sdata){
    int key = 0;
    if (strcmp(sort_key,"last") == 0) {
        key = 0;
    } else{
        key =1;
    }
    switch(key) {
      case 0 :
         qsort(&sdata[0], num_students, sizeof(sdata[0]), comp_last);
         break;
      case 1 :
         qsort(&sdata[0], num_students, sizeof(sdata[0]), comp_id);
         break;
      default :
         printf("Invalid sort key\n" );
         return -1;
   }
   return 0; 
}

int comp_first(const void * a, const void * b){
    struct Student *pa = (struct Student *)a;
    struct Student *pb = (struct Student *)b;
    return (strcmp(pa->first, pb->first));
}

int comp_last(const void * a, const void * b){
    struct Student *pa = (struct Student *)a;
    struct Student *pb = (struct Student *)b;
    return (strcmp(pa->last, pb->last));
}

int comp_id(const void * a, const void * b){
    struct Student *pa = (struct Student *)a;
    struct Student *pb = (struct Student *)b;
    return (pa->id - pb->id);
}

void write_students(FILE *ofp, int num_students, struct Student *sdata){
    for (int i = 0; i < num_students; i++){
        // ofp = sdata[i];
        fprintf(ofp, "%s,%s,%d\n", sdata[i].last, sdata[i].first, sdata[i].id);
        printf("%4d %s %s %6d\n", i, sdata[i].last, sdata[i].first, sdata[i].id);
    }
}