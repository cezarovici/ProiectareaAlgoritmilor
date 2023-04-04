#include <iostream>
#include <chrono>
#include <math.h>

using namespace std;

int numberOfDigits(int x){
    int nr = 0;

    while(x){
        nr++;

        x = x / 10;
    }

    return nr;
}

void test(long long rez,int x , int y, long long(*func)(int ,int) ){
    if ( func(x,y) == rez){
        cout<<"\n Working !";
    }
    else
    {
        cout<<"\n Not working ! -> result is " << func(x,y);
    }
}

long long div1(int x, int y){
    if(x < 10 || y < 10 ){
        return x*y;
    }

    int nox = numberOfDigits(x);
    int noy = numberOfDigits(y);

    int n = max(nox,noy);

    n = (n / 2) + (n % 2);

    float p = pow(10, n);

    int xs = floor(x / p);
    int xd = x - xs * p;
    int ys = floor(y / p);
    float yd = y - ys * p;

    long long x1 = div1(xs, ys);
    long long x2 = div1(xd, yd);
    long long x3 = div1(xs, yd);
    long long x4 = div1(xd, ys);

    return x1 * pow(10, 2 * n) + (x3 + x4) * pow(10, n) + x2;
}

long long div2(int x, int y)
{
    if (x < 10 || y < 10) {
        return x * y;
    }

    int nox = numberOfDigits(x);
    int noy = numberOfDigits(y);

    int n = max(nox,noy);

    n = (n / 2) + (n % 2);

    float p = pow(10, n);
    
    int xs = floor(x / p);
    int xd = x - xs * p;
    int ys = floor(y / p);
    int yd = y - ys * p;
    
    long long x1 = div1(xs, ys);
    long long x2 = div1(xd, yd);
    long long x3 = div1(xs - xd, yd - ys);
   
    return x1* pow(10, 2*n) + (x3 + x1 + x2) * pow(10, n) + x2;
}


int main(){
   int a = 61'438'521;
   int b = 94'736'407;

   long long rez = 5820464697636160;

    auto start = std::chrono::high_resolution_clock::now();
    test(rez,a,b,div1);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = (end - start);
    auto us = std::chrono::duration_cast<std::chrono::microseconds>(duration);
    std::cout << "Duration div1= " << us.count() << std::endl;

    start = std::chrono::high_resolution_clock::now();
    test(rez,a,b,div2);
    end = std::chrono::high_resolution_clock::now();
    duration = (end - start);
    us = std::chrono::duration_cast<std::chrono::microseconds>(duration);
    std::cout << "Duration div2= " << us.count() << std::endl;

    return 0;
}