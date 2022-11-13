#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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

int compare(const void * a, const void * b) {
   return ( *(int*)a - *(int*)b );
}

int power(double base, double power) {
    int res = 1;
    while(power>0){
        res *= base;
        power--;
    }
    return res;
}

void* findMin(void* args){
    minimum = integerList[0];
    pthread_exit(0);
}

void* findMax(void* args){
    maximum = integerList[N-1];
    pthread_exit(0);
}
void* findRange(void* param)
{
    int len = *(int *)param;
    range = integerList[len-1]-integerList[0];
    pthread_exit(0);
}

void* findMode(void* param)
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
    pthread_exit(0);
}

void* findMedian(void* param)
{
    int len = *(int *)param;
    median = integerList[len / 2];
    if (len % 2 == 0)
    {
        median += integerList[len / 2 + 1];
        median /= 2;
    }
    pthread_exit(0);
}

void* findSum(void* param)
{
    sum = 0;
    for (int i=0; i<N; i++)
        sum += integerList[i];
    pthread_exit(0);
}

void* findArithmeticMean(void* param)
{
    int len = *(int *)param;
    int curSum = 0;
    for (int i=0; i<N; i++)
        curSum += integerList[i];
    arithmeticMean = (double)curSum/len;
    pthread_exit(0);
}

void* findHarmonicMean(void* param)
{
    double denominator = 0;
    for (int i=0; i<N; i++)
        denominator += 1 / (double)integerList[i];
    int len = *(int *)param;
    harmonicMean = len / denominator;
    pthread_exit(0);
}

void* findStandardDeviation(void* param)
{
    int len = *(int *)param;
    double numerator = 0;
    int curSum = 0;
    for (int i=0; i<N; i++)
        curSum += integerList[i];
    double curMean = curSum/(double) len;
    for (int i=0; i<N; i++)
        numerator += power(((double)integerList[i] - curMean), 2.0);
    standardDeviation = power(numerator / (len - 1), 0.5);

    pthread_exit(0);
}

void* findIQRRange(void* param)
{
    int len = *(int *)param;
    iqrRange = integerList[len / 4] - integerList[3 * len / 4 + 1];
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    N = atoi(argv[1]);
    integerList = malloc(sizeof(int)*N); // allocate memory with the size of integers * number of args
	for (int i = 0; i < N; i++)
		integerList[i] = 1000 + (rand()%9001);
    qsort(integerList, N, sizeof(int), compare);
    printf("%d\n", N);
	
    pthread_t tid0, tid1, tid2, tid3, tid4, tid5, tid6, tid7, tid8, tid9;
    pthread_create(&tid0, NULL, findMin, &N);
    pthread_create(&tid1, NULL, findMax, &N);
    pthread_create(&tid2, NULL, findRange, &N);
    pthread_create(&tid3, NULL, findMode, &N);
    pthread_create(&tid4, NULL, findMedian, &N);
    pthread_create(&tid5, NULL, findSum, &N);
    pthread_create(&tid6, NULL, findArithmeticMean, &N);
    pthread_create(&tid7, NULL, findHarmonicMean, &N);
    pthread_create(&tid8, NULL, findStandardDeviation, &N);
    pthread_create(&tid9, NULL, findIQRRange, &N);
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    pthread_join(tid6, NULL);
    pthread_join(tid7, NULL);
    pthread_join(tid8, NULL);
    pthread_join(tid9, NULL);

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

}