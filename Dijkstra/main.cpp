#include <iostream>

#include <vector>
#include <climits>

#define infinite INT_MAX

using namespace std;

int graph[6][6] = {{0, 1, 2, 5, infinite, infinite},
               {infinite, 0, 1, infinite, 3, infinite},
               {infinite, infinite, 0, 1, 1, infinite},
               {infinite, infinite, infinite, 0, infinite, infinite},
               {infinite, infinite, infinite, 3, 0, infinite},
               {infinite, infinite, infinite, infinite, 1, 0}};

void print(int *p, int n){
    for(int i = 0 ; i < n;i++){
        cout<<p[i]<<" ";
    }
}

void djk(int n, int L[][6], int i0, int D[], int P[])
{
    bool S[6];

    for (int i = 0; i <= n - 1; i++)
    {
        P[i] = i0;
        D[i] = L[i0][i];
        S[i] = false;
    }

    S[i0] = true;

    int contor = 1;

    while (contor <= n)
    {
        int i, min = infinite;

        for (int k = 0; k <= n - 1; k++)
        {
            if (min > D[k] && S[k] == false)
            {
                min = D[k];
                i = k;
                S[i] = true;

                for (int j = 0; j <= n - 1; j++)
                {
                    int s = 0;
         
                    if (D[i] == infinite || L[i][j] == infinite)
                    {
                        s = infinite;
                    }
                    else
                    {
                        s = D[i] + L[i][j];
                    }
                    if (D[j] > s)
                    {
                        D[j] = s;
                        P[j] = i;
                    }
                }
            }
        }
        contor++;
    }
}

int main()
{
    int n = 6;
    
    int P[6];
    int D[6];

    djk(n, graph,0, D, P);

    cout << "D[i]: ";
    print(D,n);
    
    cout << endl;
    cout << "P[i]: ";
    print(P,6);
    cout << endl;

    return 0;
}
