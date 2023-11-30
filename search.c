#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "search.h"

int main(int argc, char *argv[])
{
    int n, num_entries;
    char line[LINE_LEN], *s;
    char *ifile, *search_method;
    FILE *ifp;
    struct Directory directory[DIR_LEN];

    /* parse command line
     *  Usage printout
     *  Determine search method
     *  Open phone book file
     */

    if (argc != 3) {
		fprintf(stderr, "Usage: %s search_method in_file.csv\n", argv[0]);
		return -1;
	}
    search_method = argv[1];
    ifile = argv[2];
    ifp = fopen(ifile, "r");
	if ( ifp == NULL ) {
		fprintf(stderr, "Cannot open %s\n", ifile);
		return -1;
	}

    /* initialize directory structure:
     * all strings have first character as zero (NULL)
     */

    for (int i = 0; i < DIR_LEN; i++){
        directory[i].first[0] = 0;
        directory[i].last[0] = 0;
        directory[i].id[0] = 0;
    }
    

    /* read in directory
     * use fgets(), strtok() and strncpy()
     */

    char row[100];
    char * token;
    for (num_entries = 0; num_entries < DIR_LEN; num_entries++){
        if (fgets(row , 100 , ifp) != NULL){
            token = strtok(row, ",\n");
            strcpy(directory[num_entries].last, token);
            token = strtok(NULL, ",\n");
            strcpy(directory[num_entries].first, token);
            token = strtok(NULL, ",\n");
            strcpy(directory[num_entries].id, token);
        }else {
            break;
        }
    }
    printf("%d Entries in directory\n", num_entries);
    

    /* print directory */

    for (int i=0; i<num_entries; i++) {
		printf("%4d %s %s %6s\n", i, directory[i].last, directory[i].first, directory[i].id);
	}

    while (1) {
        int i;
        /* now ask for any last name */
        printf("Input any last name in phone book (0 to exit):\n");
        scanf("%s", line);
        if (line[0] == '0') {
            break; /* quit */
        }
        printf("You entered:  %s\n", line);

        switch (search_method[0]) {
            case 'l':
                /* linear search */
                i = linear_search(line, directory, num_entries);
                break;
            case 'b':
                /* binary search */
                i = binary_search(line, directory, num_entries);
                break;
            default:
                fprintf(stderr, "ERROR: unknown search method %s", search_method);
                return -1;
        }
        if (i < 0) {
            fprintf(stderr, " ERROR: %s not found\n", line);
        }
        else {
            printf("%s, %s - %s\n",
                directory[i].last,
                directory[i].first,
                directory[i].id);
        }
    }
    return 0;
}

/*
 * linear search
 */
int linear_search(char *target, struct Directory *directory, int num_entries)
{
    //Your code here

    for (int i=0; i<num_entries; i++) {
        if (strcmp(directory[i].last, target) == 0) {return i;}
    }
    return -1;
}

/*
 * binary search
 */

int binary_search_recur(char *target, struct Directory *directory, int low, int high)
{
     /* binary search
     * low is low index in search interval
     * high is high index in search interval
     */

    int mid = floor ((low + high)/2);

    if (strcmp(target,directory[mid].last) == 0) {
        return mid;
    } else if (mid == low-1 || mid == high) {
        return -1;
    } else if (strcmp(target,directory[mid].last) < 0 ) {
        return binary_search_recur(target, directory, low, mid-1);
    } else if (strcmp(target,directory[mid].last) > 0 ) {
        return binary_search_recur(target, directory, mid+1, high);
    }
}

int binary_search(char *target, struct Directory *directory, int num_entries)
{
     /* binary search
     * low is low index in search interval
     * high is high index in search interval
     */

    int low = 0;
    int high = num_entries-1;
    return binary_search_recur(target, directory, low, high);
}