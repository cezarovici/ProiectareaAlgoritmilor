#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define N 100'000

enum type
{
    increasing,
    decreasing,
    rndm,
};

bool testSorting(int *vector, int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        if (vector[i] > vector[i + 1])
        {
            cout << "\n Sorting -> false";
            return false;
        }
    }

    cout << "\n\n ____Vector sorted!_____ \n\n";
    return true;
}

void shellSort(int *vector, int n, type T)
{
    long long int cnt = 0;
    switch (T)
    {
    case increasing:
    {
        cout << "\n Increasing";
        break;
    }
    case decreasing:
    {
        cout << "\n Decreasing";
        break;
    }
    case rndm:
    {
        cout << "\n Random: ";
        break;
    }
    }

    cout << " shell sort";

    auto start = std::chrono::high_resolution_clock::now();

    int k = log2(n) - 2;
    for (int s = k; s >= 0; s--)
    {
        int h = pow(2, s + 1) - 1;

        for (int i = h; i <= n - 1; i++)
        {
            int temp = vector[i];
            int j = i - h;

            while (j >= 0 && temp < vector[j])
            {
                vector[j + h] = vector[j];
                j = j - h;

                cnt++;
            }
            cnt++;

            if (j + h != i)
                vector[j + h] = temp;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = (end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Microsecond (as int)
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration); // Milliseconds (as int)
    const float ms_fractional = static_cast<float>(us.count()) / 1000;         // Milliseconds (as float)
    std::cout << "Duration = " << us.count() << "µs (" << ms_fractional << "ms)" << std::endl;
    cout << "\n Number of iterations: " << cnt;

    testSorting(vector, N);
}

void insertionSort(int *vector, int n, type T)
{
    long long int cnt = 0;
    switch (T)
    {
    case increasing:
    {
        cout << "\n Increasing";
        break;
    }
    case decreasing:
    {
        cout << "\n Decreasing";
        break;
    }
    case rndm:
    {
        cout << "\n Random: ";
        break;
    }
    }

    cout << " insertion";

    auto start = std::chrono::high_resolution_clock::now();

    for (int k = 1; k < n; k++)
    {
        int i = k - 1;
        int temp = vector[k];

        while (i >= 0 && temp < vector[i])
        {
            vector[i + 1] = vector[i];
            i--;

            cnt++;
        }
        cnt++;

        if (i != k - 1)
            vector[i + 1] = temp;
    }

    auto end = high_resolution_clock::now();
    auto duration = (end - start);
    auto us = duration_cast<microseconds>(duration);                   // Microsecond (as int)
    auto ms = duration_cast<milliseconds>(duration);                   // Milliseconds (as int)
    const float ms_fractional = static_cast<float>(us.count()) / 1000; // Milliseconds (as float)
    std::cout << "Duration = " << us.count() << "µs (" << ms_fractional << "ms)" << std::endl;
    cout << "\n Number of iterations: " << cnt;

    testSorting(vector, N);
}

void merge(int *vector, int start, int end, int mid, int *temp)
{

    int i = start;
    int j = mid + 1;
    int k = -1;

    while (i <= mid && j <= end)
    {
        k++;

        if (vector[i] < vector[j])
        {
            temp[k] = vector[i];
            i++;
        }
        else
        {
            temp[k] = vector[j];
            j++;
        }
    }

    while (i <= mid)
    {
        k++;
        temp[k] = vector[i];
        i++;
    }

    while (j <= end)
    {
        k++;
        temp[k] = vector[j];
        j++;
    }
}

void mergeSort(int *vector, int start, int end)
{

    int mid = (start + end) / 2;

    if (start < end)
    {
        mergeSort(vector, start, mid);
        mergeSort(vector, mid + 1, end);

        int *temp = new int[end - start + 1];
        merge(vector, start, end, mid, temp);

        for (int i = start; i <= end; i++)
            vector[i] = temp[i - start];
    }

    // testSorting(vector, N);
}

void partitioneaza(int *vector, int start, int end, int &k)
{
    int x = vector[start];
    int i = start + 1;
    int j = end;

    while (i <= j)
    {
        if (vector[i] <= x)
            i++;
        else if (vector[j] >= x)
            j--;

        if (i < j)
        {
            if (vector[i] > x && vector[j] < x)
            {
                swap(vector[i], vector[j]);
                i++;
                j--;
            }
        }
    }

    k = i - 1;
    vector[start] = vector[k];
    vector[k] = x;
}

void quickSort1(int *vector, int start, int end)
{
    if (start < end)
    {
        int k;

        partitioneaza(vector, start, end, k);
        quickSort1(vector, start, k - 1);
        quickSort1(vector, k + 1, end);
    }
}

void quickSort2(int *vector , int start, int end){
    while(start < end){
        int k;

        partitioneaza(vector, start, end, k);

        if( k - start < end - k){
            quickSort2(vector, start, k - 1);
            start = k + 1;
        }
        else{
            quickSort2(vector, k + 1, end);
            end = k - 1;
        }
    }
}

void TestTime(int *vector, int n, void (*sort)(int *, int, int))
{
    auto start = std::chrono::high_resolution_clock::now();

    sort(vector, 0, n - 1);
    auto end = std::chrono::high_resolution_clock::now();

    testSorting(vector, n);

    auto duration = (end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Microsecond (as int)

    std::cout << "Duration = " << us.count() << endl
              << endl;
}

int main()
{

    int increasingVector[N];
    int decreasingVector[N];
    int randomVector[N];

    int i;

    // for (i = 0; i < N; i++)
    // {
    //     increasingVector[i] = i;
    //     decreasingVector[i] = N - i;
    //     randomVector[i] = rand();
    // }

    // insertionSort(increasingVector, N, increasing);
    // insertionSort(decreasingVector, N, decreasing);
    // insertionSort(randomVector, N, rndm);

    // for (i = 0; i < N; i++)
    // {
    //     increasingVector[i] = i;
    //     decreasingVector[i] = N - i;
    //     randomVector[i] = rand();
    // }

    // shellSort(increasingVector, N, increasing);
    // shellSort(decreasingVector, N, decreasing);
    // shellSort(randomVector, N, rndm);

    for (i = 0; i < N; i++)
    {
        increasingVector[i] = i;
        decreasingVector[i] = N - i;
        randomVector[i] = rand();
    }

    cout << "merge sort \n";
    TestTime(increasingVector, N, mergeSort);
    TestTime(decreasingVector, N, mergeSort);
    TestTime(randomVector, N, mergeSort);

    for (i = 0; i < N; i++)
    {
        increasingVector[i] = i;
        decreasingVector[i] = N - i;
        randomVector[i] = rand();
    }

    cout << "quick sort 1\n";
    TestTime(increasingVector, N, quickSort1);
    TestTime(decreasingVector, N, quickSort1);
    TestTime(randomVector, N, quickSort1);

    for (i = 0; i < N; i++)
    {
        increasingVector[i] = i;
        decreasingVector[i] = N - i;
        randomVector[i] = rand();
    }

    cout << "quick sort 2\n";
    TestTime(increasingVector, N, quickSort2);
    TestTime(decreasingVector, N, quickSort2);
    TestTime(randomVector, N, quickSort2);

    return 0;
}