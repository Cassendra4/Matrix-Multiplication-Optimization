#include <iostream>
#include<ctime>
#include<stdlib.h>
#include <fstream>
#include <omp.h>
using namespace std;


int main(int arr, char** argv)
{
//declaring pointer arrays a,b which are to be multipied and mult which stores the results of the multiplication
	double** a;
	double** b;
	double** mult;

     	int r1, c1,r2,c2,i, j, k,jb,kb,ib,ii=0,jj=0,kk=0;//declaring other variables used
	double sum;
     	r1 = atoi(argv[1]) ;//argument from the run command is captured and assigned as no of rows and columns of the matrixes
    	c1 = r1;
   	r2 = r1;
   	c2 = c1;
       
	
     
double time_summation=0;//variable to check the time execution time

//Initializing the pointer arrays a,b and mult

 		a = new double*[r1];
		b = new double*[r1];
		mult = new double*[r1];
		for(int i=0;i<r1;i++){
			a[i]=new double[r1];
		}
		for(int i=0;i<r1;i++){
			b[i]=new double[r1];
		}
		for(int i=0;i<r1;i++){
           		 mult[i] = new double[r1];
		}
	
/* Storing elements of matrix a */
    for(i=0; i<r1; ++i)
    for(j=0; j<c1; ++j)
    {
      a[i][j]=rand() % 100;
    }

  
/* Storing elements of matrix b */
    for(i=0; i<r1; ++i)
    for(j=0; j<c1; ++j)
    {
       b[i][j]=rand() % 100;
    }

/* Initializing elements of matrix mult to 0.*/
  
    for(i=0; i<r1; ++i)
    for(j=0; j<c2; ++j)
    {
       mult[i][j]=0.0;
    }

     double temp;//declaring a tempory variable
//getting the transpose of the b matrix and converting b into its transpose
    for(int i=0; i<r1; i++){
		for(int j=0; j<r1; j++){
			 if(i!=j){
                    temp = b[i][j];
                    b[i][j] = b[j][i];
                    b[j][i] = temp;
                }
		}
	}


	double start,end;
	
   	start = omp_get_wtime( ); //start the timer
/* Multiplying matrix a and b and storing in array mult. */

/*#pragma omp parallel for is used as the clause used by openmp library for parallelization. It divides loop iterations between the spawned threads. 
collapse(2)-OpenMP collapse-clause increases the total number of iterations that will be partitioned across the available number of OMP threads by reducing the granularity of work to be done by each thread.
The PRIVATE clause declares variables in its list to be private to each thread. Hence j and k variables are kept by all the threads as their instances. 
The SHARED clause declares variables in its list to be shared among all threads in the team. Hence a,b and mult should be accessed by all the threads but could not have instances of thier own, we consider them as shared variables among all the threads.*/

  #pragma omp parallel for private(j, k) shared(a,b,mult)
        for(i=0; i<r1; ++i){
            for(j=0; j<r1; ++j){
            	double sum = 0.0;
                for(k=0; k<r1; ++k){
                    sum += a[i][k] * b[j][k];
                }
                mult[i][j] = sum;
            }
        }

end = omp_get_wtime();// end the timer


//deleting the created pointer arrays a,b and mult
    	delete[] a;
	delete[] b;
	delete[] mult;
//printing the time started,ended and time difference	
    	cout << "Time t1 " << start << endl;
    	cout << "Time t2 " << end<< endl;
	cout << "Time when matrix size is " << r1 << ": "<< ((end-start))<< endl;
	time_summation =((end-start));//calculating the time difference
//the time differences are stored in a file
	ofstream outfile;
   	outfile.open("fileopt1000.txt", std::ios_base::app);
   	outfile << time_summation<< endl;
   	outfile.close();

    return 0;
}
