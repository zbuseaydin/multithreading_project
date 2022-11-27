#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <math.h>
#include <sys/time.h>
#include <string.h>

void *threadRoutine(void *param);
int compare(const void *a, const void *b);
void *findMin(void *params);
void *findMax(void *params);
void *findRange(void *params);
void *findMode(void *params);
void *findMedian(void *params);
void *findSum(void *params);
void *findArithmeticMean(void *params);
void *findHarmonicMean(void *params);
void *findStandardDeviation(void *params);
void *findIQRRange(void *params);

int *intArray;
double *resultArray;
int N;
int numThreads;
void *(*functions[10])(void *) = {findMin, findMax, findRange, findMode, findMedian, findSum, findArithmeticMean, findHarmonicMean, findStandardDeviation, findIQRRange};

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Please enter the number of threads!!! (0 or 1 for singlethreaded execution)\n");
        return 0;
    }

    N = atoi(argv[1]); // N is the length of randomized array
    numThreads = atoi(argv[2]);

    if (numThreads > 2 && 10 % numThreads != 0) // functions can not be divided into threads equally
    {
        printf("Number of threads should be a multiplier of 10!!!\n");
        return 0;
    }

    intArray = malloc(sizeof(int) * N); // allocate memory for the integer array of size N
    for (int i = 0; i < N; i++)         // create the array
        intArray[i] = 1000 + (rand() % 9001);
    qsort(intArray, N, sizeof(int), compare);

    resultArray = malloc(sizeof(double) * 11); // allocate memory for the desired 11 output
    struct timeval begin, end;

    if (numThreads == 0 || numThreads == 1) // no multithreading
    {
        gettimeofday(&begin, 0);
        for (int i = 0; i < 10; i++)
        {
            (functions[i])(NULL);
        }
    }
    else // multithreading
    {
        pthread_t ids[numThreads];
        gettimeofday(&begin, 0);
        int *itr;
        for (int i = 0; i < numThreads; i++)
        {
            itr = (int *)malloc(sizeof(int));
            *itr = i;
            pthread_create(&(ids[i]), NULL, threadRoutine, (void *)itr);
        }

        for (int i = 0; i < numThreads; i++)
        {
            pthread_join(ids[i], NULL);
        }
        free(itr);
    }

    free(intArray);

    gettimeofday(&end, 0);
    resultArray[10] = end.tv_sec - begin.tv_sec + (end.tv_usec - begin.tv_usec) * 1e-6;

    FILE *fp;
    char fileName[45];
    sprintf(fileName, "output%d.txt", numThreads);
    fp = fopen(fileName, "w");

    for (int i = 0; i < 11; i++)
    {
        fprintf(fp, "%.5f\n", resultArray[i]);
    }

    fclose(fp);

    return 0;
}

void *threadRoutine(void *params)
{
    int funcPerThread = (10 / numThreads);
    int start = *(int *)params * funcPerThread;
    for (int i = start; i < start + funcPerThread; i++) // each thread runs funcPerThread number of functions
    {
        (functions[i])(NULL);
    }
    pthread_exit(0);
}

int compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void *findMin(void *params)
{
    resultArray[0] = intArray[0];
}

void *findMax(void *params)
{
    resultArray[1] = intArray[N - 1];
}

void *findRange(void *params)
{
    resultArray[2] = intArray[N - 1] - intArray[0];
}

void *findMode(void *params)
{
    int maxFreq = 1;
    int curFreq = 1;
    resultArray[3] = intArray[0];
    for (int i = 0; i < N - 1; i++)
    {
        if (intArray[i] == intArray[i + 1])
        {
            curFreq++;
            if (curFreq > maxFreq)
            {
                maxFreq = curFreq;
                resultArray[3] = intArray[i];
            }
            else
            {
                curFreq = 1;
            }
        }
    }
}

void *findMedian(void *params)
{
    resultArray[4] = intArray[N / 2];
    if (N % 2 == 0)
    {
        resultArray[4] += intArray[N / 2 - 1];
        resultArray[4] /= 2;
    }
}

void *findSum(void *params)
{
    resultArray[5] = 0;
    for (int i = 0; i < N; i++)
        resultArray[5] += intArray[i];
}

void *findArithmeticMean(void *params)
{
    int curSum = 0;
    for (int i = 0; i < N; i++)
        curSum += intArray[i];
    resultArray[6] = (double)curSum / N;
}

void *findHarmonicMean(void *params)
{
    double denominator = 0;
    for (int i = 0; i < N; i++)
        denominator += 1 / (double)intArray[i];
    resultArray[7] = N / denominator;
}

void *findStandardDeviation(void *params)
{
    double numerator = 0;
    int curSum = 0;
    for (int i = 0; i < N; i++)
        curSum += intArray[i];
    double curMean = curSum / (double)N;
    for (int i = 0; i < N; i++)
        numerator += pow(((double)intArray[i] - curMean), 2.0);
    resultArray[8] = sqrt(numerator / (N - 1));
}

void *findIQRRange(void *params)
{
    resultArray[9] = intArray[3 * N / 4] - intArray[N / 4];

    if (N % 4 == 0)
    {
        resultArray[9] += (intArray[3 * N / 4 - 1] - intArray[N / 4 - 1]);
        resultArray[9] /= 2;
    }
    else if (N % 4 == 1)
    {
        resultArray[9] += (intArray[3 * N / 4 + 1] - intArray[N / 4 - 1]);
        resultArray[9] /= 2;
    }
}
