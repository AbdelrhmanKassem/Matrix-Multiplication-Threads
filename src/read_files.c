#include "read_files.h"
#include <stdio.h>
#include <string.h>

long aRows=0;
long aColumns=0;
long bRows=0;
long bColumns=0;
extern char *matAFName;
extern char *matBFName;
extern char *matOutFName;
long long **matA;
long long **matB;
long long **matOutM1;
long long **matOutM2;
long long **matOutM3;
FILE *matAFile;
FILE *matBFile;
FILE *matOutFile;




void read_matrices(){
    read_matrix_A();
    printf("MatA done\n");
    read_matrix_B();
    printf("MatB done\n");
    free_matrix_out();
    printf("space freed\n");
    //here file is created or cleared so that I can just open on append mode later when actually writing
    matOutFile= fopen(matOutFName, "w");
    if (matOutFile==NULL) {
        perror("Couldn't Open Files");
        exit(1);
    }
    printf("file created\n");



}

void free_matrix_out(){

    matOutM1 = malloc(aRows * sizeof(long long *));
    if( matOutM1 == NULL ) {
        perror("Memory Allocation Error: ");
        exit(1);
    }
    matOutM2 = malloc(aRows * sizeof(long long *));
    if( matOutM2 == NULL ) {
        perror("Memory Allocation Error: ");
        exit(1);
    }
    matOutM3 = malloc(aRows * sizeof(long long *));
    if( matOutM3 == NULL ) {
        perror("Memory Allocation Error: ");
        exit(1);
    }
    for(int i=0 ; i < aRows ; i++){
        matOutM1[i] = malloc(bColumns * sizeof(long long));  //allocating memory space for a new row in matrix C using normal multiplication
        if( matOutM1[i] == NULL ) {
            perror("Memory Allocation Error: ");
            exit(1);
        }
        matOutM2[i] = malloc(bColumns * sizeof(long long));  //allocating memory space for a new row in matrix C of method 1
        if( matOutM2[i] == NULL ) {
            perror("Memory Allocation Error: ");
            exit(1);
        }
        matOutM3[i] = malloc(bColumns * sizeof(long long));  //allocating memory space for a new row in matrix C of method 2
        if( matOutM3[i] == NULL ) {
            perror("Memory Allocation Error: ");
            exit(1);
        }
    }
}
void read_matrix_A (){
    FILE *matAFile = fopen(matAFName, "r");
    if(matAFile==NULL){
        perror("Couldn't Open Files");
        exit(1);
        }
        else {
                char* info=malloc(1024);
                fgets(info, 1024, matAFile);
                getDimentions(info,0);
                printf("MatA dims done\n");

                matA = malloc(aRows * sizeof(long long *));
                if( matA == NULL ) {
                        perror("Memory Allocation Error: ");
                        exit(1);
                }

                int i = 0, j= 0;
                for(i ; i < aRows ; i++) {

                    matA[i] = malloc(aColumns * sizeof(long long));

                    if( matA[i] == NULL ) {
                        perror("Memory Allocation Error: ");
                        exit(1);
                    }
                    j=0;
                    for(j ; j < aColumns ; j++){
                        fscanf(matAFile , "%lld" , & matA[i][j]);
                    }
                }
                fclose(matAFile);
        }
}
void read_matrix_B (){
    matBFile = fopen(matBFName, "r");
    if(matBFile==NULL){
        perror("Couldn't Open Files");
        exit(1);
        }
        else {
        	char* info=malloc(1024);
            fgets(info, 1024, matBFile);
            getDimentions(info,1);
            printf("MatB dims done\n");
            matB = malloc(aRows * sizeof(long long *));
                if( matB == NULL ) {
                        perror("Memory Allocation Error: ");
                        exit(1);
                }

                int i = 0, j= 0;
                for(i ; i < bRows ; i++) {

                    matB[i] = malloc(bColumns * sizeof(long long));

                    if( matB[i] == NULL ) {
                        perror("Memory Allocation Error: ");
                        exit(1);
                    }
                    j=0;
                    for(j ; j < bColumns ; j++){
                        fscanf(matBFile , "%lld" , & matB[i][j]);
                    }
                }
                fclose(matBFile);
        }
}

void getDimentions(char* info, int mat){ //mat = 0 indicates files is A and = 1 indicates file is B
    char* token;
    token = strtok(info , "=/t ");
    int isRow =1;
    while(token!= NULL){
    	if(atoi(token)!=0 || token[0]=='0')
    	{
    		if(isRow==1){
    			if(mat == 0){
    				aRows=atoi(token);
    			}
    			else if (mat == 1){
    				bRows=atoi(token);
    			}
    			isRow =0;

    		}
    		else {
    			if(mat == 0){
    				aColumns=atoi(token);
    			}
    			else if (mat == 1){
    				bColumns=atoi(token);
    			}
    		}
    	}
    	token = strtok(NULL , "=/t ");
    }


}



