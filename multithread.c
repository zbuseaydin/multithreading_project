#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>

int* integerList;
int N;
int minimum;
int maximum;
int range;
int mode;
double median;
int sum;
double arithmeticMean;
double harmonicMean;
double standardDeviation;
int iqrRange;
int numThreads;

int compare(const void * a, const void * b)
{
   return ( *(int*)a - *(int*)b );
}

void* findMin(void* params){
    minimum = integerList[0];
}

void* findMax(void* params){
    maximum = integerList[N-1];
}

void* findRange(void* params)
{
    range = integerList[N-1]-integerList[0];
}

void* findMode(void* params)
{
    int maxFreq = 1;
    int curFreq = 1;
    mode = integerList[0];
    for(int i=0; i<N-1; i++){
        if(integerList[i]==integerList[i+1]){
            curFreq++;
            if(curFreq>maxFreq){
                maxFreq = curFreq;
                mode = integerList[i];
            }else{
                curFreq = 1;
            }
        }
    }
}

void* findMedian(void* params)
{
    median = integerList[N / 2];
    if (N % 2 == 0)
    {
        median += integerList[N / 2 + 1];
        median /= 2;
    }
}

void* findSum(void* params)
{
    sum = 0;
    for (int i=0; i<N; i++)
        sum += integerList[i];
}

void* findArithmeticMean(void* params)
{
    int curSum = 0;
    for (int i=0; i<N; i++)
        curSum += integerList[i];
    arithmeticMean = (double)curSum/N;
}

void* findHarmonicMean(void* params)
{
    double denominator = 0;
    for (int i=0; i<N; i++)
        denominator += 1 / (double)integerList[i];
    harmonicMean = N / denominator;
}

void* findStandardDeviation(void* params)
{
    double numerator = 0;
    int curSum = 0;
    for (int i=0; i<N; i++)
        curSum += integerList[i];
    double curMean = curSum/(double) N;
    for (int i=0; i<N; i++)
        numerator += pow(((double)integerList[i] - curMean), 2.0);
    standardDeviation = sqrt(numerator / (N - 1));
}

void* findIQRRange(void* params)
{
    iqrRange = integerList[N / 4] - integerList[3 * N / 4 + 1];
}

void* (*func_ptrs[10])(void *) = {findMin, findMax, findRange, findMode, findMedian, findSum, findArithmeticMean, findHarmonicMean, findStandardDeviation, findIQRRange};


void* execute(void* params){
    int start = *(int *) params * 10/numThreads;
    int increment = (10/numThreads);
    printf("start index: %d\n", start);
    printf("increment: %d\n", increment);
    for(int i=start; i<start+increment; i++)
        (func_ptrs[i])(NULL);
    pthread_exit(0);
}


int main(int argc, char *argv[])
{
    if(argc<3)
    {
        printf("Please enter the number of threads!!!\n");
        return 0;
    }

    N = atoi(argv[1]);
    numThreads = atoi(argv[2]);
    integerList = malloc(sizeof(int)*N); // allocate memory with the size of integers * number of args
	for (int i = 0; i < N; i++)
		integerList[i] = 1000 + (rand()%9001);  // srand
    qsort(integerList, N, sizeof(int), compare);

    if(numThreads==1)
    {
        for(int i=0; i<10; i++)
            (func_ptrs[i])(NULL);
        
    }else{
        pthread_t ids[numThreads]; 
    
        for(int i=0; i<numThreads; i++)
        {
            int* itr = (int *)malloc(sizeof (int)); 
            *itr = i;
            printf("itr: %d\n", *itr);
            pthread_create(&(ids[i]), NULL, execute, (void*) itr);
       //     free(itr);
        }

        for(int i=0; i<numThreads; i++)
        {
            pthread_join(ids[i], NULL);
        }
    }
    
//    printf("%d\n", N);

 //   free(integerList);

    printf("%d\n", minimum);
    printf("%d\n", maximum);
    printf("%d\n", range);
    printf("%d\n", mode);
    printf("%f\n", median);
    printf("%d\n", sum);
    printf("%f\n", arithmeticMean);
    printf("%f\n", harmonicMean);
    printf("%f\n", standardDeviation);
    printf("%d\n", iqrRange);
    return 0;
}