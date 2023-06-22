#include <iostream>
#include <algorithm>
#include <fstream>
#include <string.h>
#include <vector>

using namespace std;

string fileName = "fisier_text";

struct character
{
    char val;
    int freq;
};

struct nod
{
    character ch;
    nod *fs;
    nod *fd;
};

struct greatest
{
    bool operator()(const nod *a, const nod *b) const
    {
        return a->ch.freq > b->ch.freq;
    }
};

nod *makeNod(nod *temp1, nod *temp2)
{
    nod *rezNod = new nod;

    rezNod->ch.freq = temp1->ch.freq + temp2->ch.freq;

    rezNod->ch.val = ';';

    rezNod->fs = temp1;
    rezNod->fd = temp2;

    return rezNod;
}

vector<nod *> LEP(vector<nod *> B)
{
    make_heap(B.begin(), B.end(), greatest());

    while (B.size() > 1)
    {
        pop_heap(B.begin(), B.end(), greatest());
        nod *t1 = B.back();
        B.pop_back();

        pop_heap(B.begin(), B.end(), greatest());
        nod *t2 = B.back();
        B.pop_back();

        nod *t = makeNod(t1, t2);

        B.push_back(t);
    }

    return B;
}

void huffmanCodification(const nod *node, char chr, string &out, string inter = "")
{
    if (node != nullptr)
    {
        if (node->ch.val == chr)
        {
            out = inter;
        }
        else
        {
            huffmanCodification(node->fs, chr, out, inter + "0");
            huffmanCodification(node->fd, chr, out, inter + "1");
        }
    }
}

string readFrom(string fileToRead)
{
    string buffer;

    ifstream file(fileToRead);

    file >> buffer;

    return buffer;
}

int main()
{
    string in = readFrom(fileName);
    vector<nod *> noduri;

    int freq[255] = {0};
    for (int i = 0; i < in.length(); i++)
    {
        freq[in[i]]++;
    }

    for (int i = 0; i < 255; i++)
    {
        if (freq[i] != 0)
        {
            nod *temp = new nod;

            temp->ch.val = (char)(i + 'A');
            temp->ch.freq = freq[i];

            noduri.push_back(temp);
        }
    }

    noduri = LEP(noduri);

    string temp;
    string rez = "";

    for (int i = 0; i < in.length(); i++)
    {
        huffmanCodification(noduri[0], in[i], temp);
        rez = rez + " " + temp;
    }

    // cout << "\nCuvantul Necodificat: " << in;
    // cout << "\nCuvantul Codificat:" << rez << "\n";
}