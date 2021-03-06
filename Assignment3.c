#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 20
//Will Mitchell Feb 22 2020
//first input the number of words you want to type in and enter
//then type in the words on one line seperated by spaces and enter
//program will output your words in oder such that the last letter of 
//the current word matches the first letter of the next word
//if no such order exists, there will be no output
int permute(int max, int index, char ** array);
void destroyArray(char ** arrList, int max);
int check(char ** array, int max);

int main(){
    int max;
    char ** arrList;
    //scan in number of words and allocate an array of pointers
    scanf("%d", &max);
    arrList = (char**) calloc(max, sizeof(char *));
    //for each word, first allocate a 21 char sized arr in slot
    // 'i' of the array of words, then scan the characters 
    //into that array from the user
    for(int i = 0; i < max; i++){
        arrList[i] = (char*) malloc(BUFFER + 1);
        scanf("%s", arrList[i]);
    }
    //pass the number of words, the current the currect index
    //(initial index) will be zero, and the array of words 
    permute(max, 0, arrList);
    //destroy dynamically allocated char arrays and array of char arrays
    destroyArray(arrList, max);
    return 0;
}
//recursive permutations function
int permute(int max, int index, char ** array){
    //base case
    if (index == max){
        //if this permutation passes the check
        //function, print this function and return
        if(check(array, max) == 1){
            for(int i = 0; i < max; i ++){
                printf("%s ", array[i]);
            }
            printf("\n");
            return 1;
        }
        return 0;
    }
    else{
        //if basecase is not satisfied, loop through to the next itteration
        for (int i = index; i < max; i++){
            //swap word i and the following word
            char tmpVar[BUFFER + 1];
            strcpy(tmpVar, array[index]);
            strcpy(array[index], array[i]);
            strcpy(array[i], tmpVar);
            //recursive call but increase the index by one
            if (permute(max, index + 1, array)){
                return 1;
            }
            //backtracking swap for efficiency
            strcpy(tmpVar, array[index]);
            strcpy(array[index], array[i]);
            strcpy(array[i], tmpVar);
        }
        return 0;
    }
}
//check if the current permutation from perm() is pretty
int check(char ** array, int max){
    //loop through each word, excluding the last
    for(int i = 0; i < max - 1; i++){
        //if the last letter of the ith word does not match the 
        //0th letter of the following word, its not pretty.
        if (array[i][strlen(array[i])-1] != array[i + 1][0]){
            return 0;
        }
    }
    //else it is pretty so return 1
    return 1;
}
//destryo dynamically allocated memory
void destroyArray(char ** arrList, int max){
    //free each sub char array
    for(int i = 0; i < max; i++){
        free(arrList[i]);
    }
    //free array of pointers
    free(arrList);
}