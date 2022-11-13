#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <fstream>
#include <cmath>
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    int N = atoi(argv[1]);
    vector <int> integerList;
    vector <float> result;

    // initializing the vector
    for(int i=0; i<N; i++)
        integerList.push_back(1000 + (rand()%9001));
    
    // printing the list for myself
    for(int i=0; i<N; i++){
        cout << integerList[i];
        cout << " ";
    }
    cout << "\n";
    
    // finding min and max
    float min = integerList[0];
    float max = integerList[0];

    for(int num: integerList){
        if(num < min)
            min = num;
        if(num > max)
            max = num;
    }
    result.push_back(min);
    result.push_back(max);

    // finding range
    result.push_back(max-min);

    // finding mode
    map <int, int> freqMap;
    for(int num: integerList)
        freqMap[num]++;
    
    int maxFreq = 0;
    float mode = 0;
    for(const auto &entry: freqMap){
        if(maxFreq < entry.second){
            maxFreq = entry.second;
            mode = entry.first;
        }
    }
    result.push_back(mode);

    // finding median
    sort(integerList.begin(), integerList.end());
    float median = integerList[N/2];
    if(N%2==0){
        median += integerList[N/2+1];
        median /= 2;
    }
    result.push_back(median);

    // finding sum
    float sum = 0;
    for(int num: integerList)
        sum += num;
    result.push_back(sum);

    // finding arithmetic mean
    float arithmeticMean = sum / N;
    result.push_back(arithmeticMean);

    // finding harmonic mean
    float denominator = 0;

    for(int num: integerList)
        denominator += 1/(float)num;
    
    result.push_back(N/denominator);

    // finding standard deviation
    float numerator = 0;
    for(int num: integerList)
        numerator += pow((num-arithmeticMean), 2);
    numerator = pow(numerator/(N-1), 0.5);

    result.push_back(numerator);

    // finding interquartile range
    result.push_back(integerList[N/4] - integerList[3*N/4]);

    ofstream output;
    output.open("output1.txt");
    for(int i=0; i<10; i++){
        output << result[i];
        output << "\n";
    }
    output.close();

    return 0;
}