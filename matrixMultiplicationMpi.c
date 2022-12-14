#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

int main(int argc, char*argv[])
{
    int i,j,k;
    int x,c;
    int matrix_a[ms][ms];
    int matrix_b[ms][ms];
    int matrix_c[ms][ms];
    int myrank, p;
    int NRPE;
    double starttime, endtime;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Status status;

    NRPE = ms/p;

    if(myrank ==0)
    {
        //Matrix A

        printf("\nMatrix A");
        
        for(i=0; i<ms; ++i){
            for(j=0; j<ms; ++j){
               matrix_a[i][j] = rand() %10;
            }
        }

        for(i=0; i<ms; ++i){
            for(j=0; j<ms; ++j){
                printf("%3d", matrix_a[i][j]);
                printf("\n");
            }
        }
        
        //Matrix B

        printf("\nMatrix B");

        for(x=0; x<ms; ++x){
            for(c=0; c<ms; ++c){
              printf("%3d",matrix_b[x][c]);
              printf("\n");
            }
        }

    }

   for(i=0, i<ms; i++){
       MPI_Bcast(matrix_b[i], ms*ms, MPI_INT, 0, MPI_COMM_WORLD);
    }

   printf("\n Matrix B process: %d", myrank);

   for(x=0; x<ms; ++x){
       for(c=0; c<ms; ++c){
           printf("%3d", matrix_b[x][c]);
           printf("\n");
        }
    }

   for(i=0; i<p; i++){
       for(j=0; j<ms; j++){
           MPI_Send(&matrix_a[j], ms*NRPE, MPI_INT, i, 0, MPI_COMM_WORLD);
           NPRE++;
        }
    }

   MPI_Recv(&matrix_a, ms*NRPE, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

   for(k=0; k<ms; k++){
       for(i=0; i<ms; i++){
           matrix_c[i][j] = 0;
        
           for(j=0; j<ms; j++){

               matrix_c[i][k]=  matrix_c[i][k] + matrix_a[i][j] * matrix_b[j][k];
    
            }

           MPI_Send(&matrix_c[i][j], ms*ms, MPI_INT, 0, 0, MPI_COMM_WORLD);
        }

    }

    //Matrix C

   if(myrank == 0){
       printf("Resultant Matrix: \n")

       for(i=0; i<ms; i++){
           printf("\n");

        }

       for(k=0; k<ms; k++){
           printf("%3d", matrix_c[i][k];)

        }
    }

   printf("\n")
   return 0;

   MPI_Finalize();

}