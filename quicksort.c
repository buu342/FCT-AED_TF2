#include <string.h>
#include "configuration.h"
#include "quicksort.h"


/*===================================
              Prototypes            
===================================*/

int compare(char* str1, int id1, char* str2, int id2);


/*===================================
              quick_sort
  Idea borrowed from Charles Hoare
===================================*/

void quick_sort(char v[MAX_CLIENTS][MAX_INPUT], int keys[MAX_CLIENTS], int min, int max)
{
    // Variables
    int i = min;
    int j = max;
    int mid = (i+j)/2;
    char* p = v[mid];
    
    // Start moving our points
    do
    {
        // Increment left if it's smaller than the pivot
        while (compare(v[i], keys[i], p, keys[mid]) < 0)
            i++;
        
        // Decrement right if it's larger than the pivot
        while (compare(p, keys[mid], v[j], keys[j]) < 0)
            j--;

        // If the value on the left is smaller, swap them.
        if (i <= j)
        {
            char temp[MAX_INPUT];
            
            strcpy(temp, v[i]);
            strcpy(v[i], v[j]);
            strcpy(v[j], temp);

            int temp2 = keys[i];
            keys[i] = keys[j];
            keys[j] = temp2;
            
            i++;
            j--;
        }
    }
    while (i <= j);

    // Call the function (twice), but this time sorting the left and right partitions to the pivot
    if (min < j)
        quick_sort(v, keys, min, j);
    if (i < max)
        quick_sort(v, keys, i, max);
}


/*===================================
              compare
  Custom compare function (made to 
resolve conflicts between same names)
===================================*/

int compare(char* str1, int id1, char* str2, int id2) 
{
    // String compare the two strings
    int result = strcmp(str1, str2);

    // If they're the same, find the largest key
    if(result == 0)
    {
        if(id1 < id2)
            return -1;
        else
            return 1;
    }

    //Otherwise, return the result
    return result;
}