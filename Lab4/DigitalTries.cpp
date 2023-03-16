#include <iostream>
#include <string.h>

using namespace std;

#define N 26

struct Nod
{
    bool endw = false;
    Nod *next[26] = {nullptr};
};


Nod* createNode(){
    Nod* newNode = new Nod;

    for (int i = 0 ; i < N ; i++){
        newNode->next[i] = nullptr;
    }

    newNode->endw = false;

    return newNode;
}

void Insert(Nod *root, const char *word)
{
    Nod* temp = root;

    for(int i = 0 ; word[i]!='\0';i++){
        int index = word[i] - 'a';

        if (temp->next[index] == nullptr){
            temp->next[index] = createNode();
        }

        temp = temp->next[index];
    }

    temp->endw = true;
}

bool Search(Nod *root, const char *word)
{

    cout<<"\n Searching : "<< word;

    if (root == nullptr)
    {
        cout << "\n Empty tree";

        return false;
    }

    Nod *temp = root;

    for (int i = 0; i < strlen(word); i++)
    {
        if (temp->next[word[i] - 'a'] == nullptr)
        {
            return false;
        }

        temp = temp->next[word[i] - 'a'];
    }

    return (temp != nullptr && temp->endw);
}

int main()
{
    Nod *tree = new Nod;

    Insert(tree, "cezar");
    Insert(tree, "cez");
    Insert(tree,"mihai");

    cout << Search(tree, "cezar");
    cout << Search(tree,"mih");
    cout<< Search(tree,"mihai");
}