#include <stdio.h>
#include <stdlib.h> // for rand
#include <string.h>
#include <time.h> // for 
#include <math.h>

#define NUM_EXPERIMENTS 100 

int debug = 1; // turn print statements off with 0
int ARRAY_SIZE = 3;
int comp_count = 0; // keep track of comps
int median = 0;

// Function signatures
int Median(int A[]);
int Select(int A[], int l, int m, int h);
int Partition(int A[], int l, int h);
void swap(int *first, int *second);

int Median(int A[]){
    // Returns the median value in a given array of n numbers
    if(ARRAY_SIZE==1){
        return A[0];
    } else {
        return Select(A, 0, (int)floor(ARRAY_SIZE/2), ARRAY_SIZE-1);
    }
    
}

int Select(int A[], int l, int m, int h){
    // Returns the value at index m in array sliceA[l..h]
    // if the slice were sorted into nondecreasing order
    int pos = Partition(A, l, h);

    if (pos == m){ 
        return A[pos]; 
    } else if (pos > m) {
        return Select(A, l, m, pos-1); 
    } else if (pos < m) {
        return Select(A, pos + 1, m, h);
    }
    
}

int Partition(int A[], int l, int h){
    int pivotval = A[l];
    int pivotloc = l;
    
    for(int j = l+1; j <= h; j++){ 
        if(A[j] < pivotval){ // This is the basic operation
        pivotloc = pivotloc + 1;
            swap(&A[pivotloc], &A[j]);
        }
        comp_count++;
    }
    
    swap(&A[l], &A[pivotloc]);
    return pivotloc;
}

void swap(int *first, int *second) {
    int temp;

    temp = *first;
    *first = *second;  
    *second = temp;  

}

void print_array(int array[]){
    printf("[ ");
    for(int i = 0; i < ARRAY_SIZE; ++i){    
        printf("%d ", array[i]);
    }
    printf("]\n");
}

void run_experiment(int type){
    int A[ARRAY_SIZE];
    clock_t start, finish;

    switch(type){
        case 1: // random

            srand(time(NULL));
            
            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = rand() % 1000 + 1; // Random number between 0 and 1000?
            }

            break;

        case 2: // ordered

            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = i + 1; // Sequence of numbers
            }

            break;
        
        case 3: // reverse-ordered

            for(int i = 0; i < ARRAY_SIZE; ++i){
                A[i] = ARRAY_SIZE - i; // Sequence of numbers
            }

            break;
        
    }
    
    if(debug){
        printf("Initial array: \n");
        print_array(A);
        printf("\n");
    }
    
    median = Median(A);
    
    if(debug){
        printf("Final array: \n");
        print_array(A);
    }
    
}

void write_to_file(char *filename, double value, int array_size){
 
    if(debug){
        printf("\n File: %s\n",filename);
    }

    FILE *fp;
       
    fp=fopen(filename, "a"); //appends
    fprintf(fp, "%f,%d\n", value, array_size);
    fclose(fp);
    
    if(debug){
        printf("\n %s done", filename);
    }
 
}

int main(int argc, char *argv[]) {
    int A[ARRAY_SIZE];
    double average;
    int counter = 0;
    int type = 1;
    char *p;
    
     if(argc != 1){
        type = strtol(argv[1], &p, 10); // takes CL input and converts to string
        ARRAY_SIZE  = strtol(argv[2], &p, 10);

        if(type > 3){
            printf("Command line argument too big.\n\n");
            exit(0);
        }
    }

    // Runs the experiments
    for (int experiments = 0; experiments < NUM_EXPERIMENTS; experiments++){

        if(debug){
            printf("Experiment %d..\n", experiments);
            counter++;
        }

        run_experiment(type);
        
    }

    if(debug){
        printf("Average execution time after %d trials: %f seconds\n", counter, average);
        printf("Comps: %d\n", comp_count/NUM_EXPERIMENTS);
    }

    write_to_file("median_comps_random.csv",comp_count/NUM_EXPERIMENTS, ARRAY_SIZE);   
    
    printf("\nMEDIAN: %d\n", median);

}
