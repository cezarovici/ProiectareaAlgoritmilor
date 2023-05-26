#include <iostream>
#include <vector>

using namespace std;

# define m 10
# define n 3

struct store{
    int w;
    int p;
};

vector<store> s[n+1];
vector<store> t[n+1];

void interclass(vector <store>s,vector<store> t,int max, vector<store> &r){
    int i =0, j = 0;

    while(i < s.size() && j < t.size()){
        if (s[i].w <= t[j].w){
            if (s[i].w <= max && r.size() || r.back().p < s[i].p){
                r.push_back(s[i]);
            }

            i++;
        }
        else{
            if (t[j].w <= max && r.size() || r.back().p < t[j].p){
                r.push_back(t[j]);
            }
            
            j++;
        }
    }

    while (i < s.size()) {
        if (s[i].w <= max && (r.size() == 0 || s[i].p > r.back().p)) {
            r.push_back(s[i]);
        }
        i++;
    }

    while (j < t.size()) {
        if (t[j].w <= max && (r.size() == 0 || t[j].p > r.back().p)) {
            r.push_back(t[j]);
        }
        j++;
    }
}

void rucsac(int M, int w[], int p[], int x[]) {
    vector <store> S[m];
    vector <store> T[m];

    store temp;

    temp.w = 0;
    temp.p = 0;
    
    S[0].push_back(temp);

    temp.w = w[1];
    temp.p = p[1];

    T[0].push_back(temp);

    for (int i = 1; i <= n; i++) {
        vector <store> temp;
        interclass(S[i - 1], T[i - 1], M, S[i]);

        for (int j = 0; j < S[i].size(); j++) {
            store temp;
            temp.w = S[i].at(j).w + w[i];
            temp.p = S[i].at(j).p + p[i];
            T[i].push_back(temp);
        }

    }
    
    store xy = S[n].back();

    for (int i = n - 1; i >= 0; i--) {
        if (xy.w == S[i].back().w && xy.p == S[i].back().p) {
            x[i + 1] = 0;
        }
        else {
            x[i + 1] = 1;
            xy.w = xy.w - w[i + 1];
            xy.p = xy.p - p[i + 1];
        }
    }
}


int main(){
    vector <store> S[4];
   
    int w[3] = { 3, 5, 6 };
    int p[3] = { 10, 30, 20 };
    int x[5];

    rucsac(m, w, p, x);
    for (int i = 0; i < n; i++) {
        cout << x[i] << " ";
    }


    return 0;
}