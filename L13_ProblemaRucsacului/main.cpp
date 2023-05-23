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
}

int main(){



    return 0;
}