#include <iostream>
#include <string.h>

using namespace std;

struct Nod
{
    bool endw = false;
    Nod *next[26] = {nullptr};
};

void init(Nod *&root)
{
    root = new Nod;
    root->endw = false;
}

void Insert(Nod *root, const char *word)
{
    if (root == nullptr)
    {
        init(root);
    }

    Nod *temp = root;

    for (int i = 0; i < strlen(word); i++)
    {
        while (temp->next[word[i] - 'a'] != nullptr)
        {
            temp = temp->next[word[i] - 'a'];
        }

        if (temp->next[word[i] - 'a'] == nullptr)
        {
            temp->next[word[i] - 'a'] = new Nod;
        }
    }

    temp->endw = true;
}

void Search(Nod *root, int m, const char *word)
{
    int i = 0;
    Nod *temp = root;

    while (temp != nullptr && i < m)
    {
    }
}

int main()
{
    Nod *tree = nullptr;
    Insert(tree, "cezar");
    Insert(tree, "cez");

    
}