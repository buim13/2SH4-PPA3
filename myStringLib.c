#include <stdio.h>
#include <stdlib.h>

#include "myStringLib.h"

// [COPY AND PASTE] Copy and Paste your Lab 3 Q1 Solution Below

//  This is then your very first reusable custom C library 


int my_strlen(const char * const str1)
{
	// Returns the length of the string - the number of characters, but IGNORING the terminating NULL character
	int k;

    const char * str2 = (char *)str1;

    for (k=0; *str2!='\0'; str2++){
        k++;
    }

    return k;
	
}

int my_strcmp(const char * const str1, const char * const str2)
{
	// Return 0 if the two strings are not identical.  Return 1 otherwise.
	
	// Criteria 1: Check their lenghts.  If not the same length, not equal
	int str1len = my_strlen(str1);
	int str2len = my_strlen(str2);

	int equal = 1;
	// Criteria 2: Check their contents char-by-char.  If mismatch found, not equal
	int i;
	if (str1len!=str2len){
		equal=0;
	} else{
		for(i=0; i<str1len; i++){
			if (str1[i]!=str2[i]){
				equal=0;
				break;
			}
		}
	}

	// if passing the two criteria, strings equal
	return equal;
}


int my_strcmpOrder(const char * const str1, const char * const str2)
{
	/*compare_str alphabetically compares two strings.
    	If str2 is alphabetically smaller than str1 (comes before str1),
    	the function returns a 1, else if str1 is smaller than str2, the
    	function returns a 0.*/
	int i;
	int j;
	int k=-1;
	if (my_strlen(str1) > my_strlen(str2)){ // find the longer string
		j=my_strlen(str1);
	} else if (my_strlen(str1) < my_strlen(str2)){
		j=my_strlen(str2);
	} else{ // my_strlen(str1) == my_strlen(str2)
		j=my_strlen(str1);
	}
	// if two strings are completely identical in order, return -1.
	for (i=0; i<j; i++){
        int str1Num = str1[i], str2Num = str2[i];
        if (str1Num > str2Num){
            k = 1;
            break;
        } else if (str1Num < str2Num){
            k = 0;
            break;
        } else{
            k = -1;
        }
    }
	// We are NOT looking for any custom alphabetical order - just use the integer values of ASCII character
	return k;
	
}


char *my_strcat(const char * const str1, const char * const str2){

	/* this is the pointer holding the string to return */
	char *z = NULL;
	
	/*write your implementation here*/
	int n = my_strlen(str1)+my_strlen(str2), i, j;

	z = (char*)malloc(n * sizeof(char));
	for (i=0; i<my_strlen(str1); i++){
		if (str1[i]!= ' '){
            z[i] = str1[i];
        }
	}
    for (j=0; j<my_strlen(str2); j++, i++){
        if (str2[j]!= ' '){
            z[i] = str2[j];
        }
    }
    z[i] = '\0';

	/* finally, return the string*/
	

	// IMPORTANT!!  Where did the newly allocated memory being released?
	// THINK ABOUT MEMORY MANAGEMENT
	return z;
    
    free(z);
	z = NULL;
}