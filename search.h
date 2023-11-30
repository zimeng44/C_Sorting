#ifndef  _SEARCH_H
#define  _SEARCH_H

#define LINE_LEN    80      /* length of line in CSV directory file */
#define NAME_LEN    64      /* name string length */
#define NUM_LEN     11      /* ID number string, plus NULL*/
#define DIR_LEN     1024    /* max directory length */

struct Directory {
    char last [NAME_LEN];
    char first[NAME_LEN];
    char id[NUM_LEN];
};

int linear_search(char *target, struct Directory *directory, int num_entries);
int binary_search(char *target, struct Directory *directory, int num_entries);
int comp_last(const void * a, const void * b);

#endif