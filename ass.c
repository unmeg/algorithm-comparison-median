#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for 
#include <math.h>

#define ARRAY_SIZE 10 // TODO: Figure out if we want this to be a constant, a variable (for tests) 
// if we take the sizeof(array)/sizeof(array[0]) when the array has just been declared, rather than once
// it's been passed, we can has as global var

/*
* Returns the median value in a given array A of n numbers
* This is the kth element, where k = abs(n/2), if array were sorted
*/
int BruteForceMedian(int A[]){
    int k = (int)ceil(ARRAY_SIZE/2.0); // 9/2 = 5 so we want ceiling; cast to int because it returns a double
    for(int i = 0; i < ARRAY_SIZE; i++){
        int numsmaller = 0; // How many elements are smaller than A[i]
        int numequal = 0; // How many elements are equal to A[i]

            for(int j = 0; j < ARRAY_SIZE; j++){
                if(A[j] < A[i]){
                    numsmaller++;
                } else if(A[j] == A[i]){
                    numequal++;
                }
            }

            if( (numsmaller < k) && k <= (numsmaller + numequal) ){ // if the index of 
                return A[i];
            }

    }
}

void print_array(int array[]){
    printf("[ ");
    for(int i = 0; i < ARRAY_SIZE; ++i){
        printf("%d ", array[i]);
    }
    printf("]\n");
}

int main(int argc, char *argv[]) {
    int A[ARRAY_SIZE];

    // TODO make function that creates arrays 
    // Sequential array:
    // for(int i = 0; i < ARRAY_SIZE; ++i){
    //     A[i] = i + 1; // Sequence of numbers
    // }

    // Random array:
    srand(time(NULL));
            
    for(int i = 0; i < ARRAY_SIZE; ++i){
        A[i] = rand() % (ARRAY_SIZE*10) + 1; // Random number between 0 and 1000?
    }

    printf("Array:\n");
    print_array(A);
    int median = 0;
    median = BruteForceMedian(A);
    printf("MEDIAN: %d\n", median);

}