#include <iostream>
#include <math.h>
#include <chrono>

using namespace std;

#define N 100000

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

    cout<<" shell sort";

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
                j=j-h;

                cnt++;
            }
            cnt++;

            if (j+h != i)
                vector[j + h] = temp;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = (end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Microsecond (as int)
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration); // Milliseconds (as int)
    const float ms_fractional = static_cast<float>(us.count()) / 1000;         // Milliseconds (as float)
    std::cout << "Duration = " << us.count() << "µs (" << ms_fractional << "ms)" << std::endl;
    cout<<"\n Number of iterations: "<<cnt;

    testSorting(vector, N);
}

void insertionSort(int *vector, int n, type T)
{   long long int cnt = 0;
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

    cout<<" insertion";

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

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = (end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration); // Microsecond (as int)
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(duration); // Milliseconds (as int)
    const float ms_fractional = static_cast<float>(us.count()) / 1000;         // Milliseconds (as float)
    std::cout << "Duration = " << us.count() << "µs (" << ms_fractional << "ms)" << std::endl;
    cout<<"\n Number of iterations: "<<cnt;

    testSorting(vector, N);
}

int main()
{

    int increasingVector[N];
    int decreasingVector[N];
    int randomVector[N];

    int i;

    for (i = 0; i < N; i++)
    {
        increasingVector[i] = i;
        decreasingVector[i] = N - i;
        randomVector[i] = rand();
    }

    insertionSort(increasingVector, N, increasing);
    insertionSort(decreasingVector, N, decreasing);
    insertionSort(randomVector, N, rndm);

    for (i = 0; i < N; i++)
    {
        increasingVector[i] = i;
        decreasingVector[i] = N - i;
        randomVector[i] = rand();
    }

    shellSort(increasingVector,N,increasing);
    shellSort(decreasingVector,N,decreasing);
    shellSort(randomVector,N,rndm);

    return 0;
}