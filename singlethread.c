#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

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

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    int* integerList = malloc(sizeof(int)*N); // allocate memory with the size of integers * number of args
	for (int i = 0; i < N; i++)
		integerList[i] = 1000 + (rand()%9001);

    // initializing the array
    for(int i=0; i<N; i++)
        integerList[i] = 1000 + (rand()%9001);
    
    // printing the list for myself
    for(int i=0; i<N; i++){
        printf("%d\n", integerList[i]);
    }
    
    // finding min and max
    int min = integerList[0];
    int max = integerList[0];

    for(int i=0; i<N; i++){
        if(integerList[i] < min)
            min = integerList[i];
        if(integerList[i] > max)
            max = integerList[i];
    }

    // finding range
    int range = max-min;

    // finding mode
    int maxFreq = 1;
    int curFreq = 1;
    int  mode = integerList[0];
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

    // finding median
    qsort(integerList, N, sizeof(int), compare);
    double median = integerList[N/2];
    if(N%2==0){
        median += integerList[N/2+1];
        median /= 2;
    }

    // finding sum
    double sum = 0;
    for(int i=0; i<N; i++)
        sum += integerList[i];

    // finding arithmetic mean
    double arithmeticMean = sum / N;

    // finding harmonic mean
    double denominator = 0;

    for(int i=0; i<N; i++)
        denominator += 1/(double)integerList[i];
    double harmonicMean = N/denominator;

    // finding standard deviation
    double numerator = 0;
    for(int i=0; i<N; i++)
        numerator += power((integerList[i]-arithmeticMean), 2);
    double standardDeviation = power(numerator/(N-1), 0.5);


    // finding interquartile range
    int iqrRange = integerList[N/4] - integerList[3*N/4];

    FILE *fp; 
    fp = fopen("output.txt", "w");
    fprintf(fp, "%d", min);
    fprintf(fp, "%d", max);

    return 0;
}