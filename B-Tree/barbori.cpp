#define f 2

#include <iostream>

using namespace std;

struct bTree
{
    int numberOfKeys;
    int typeOfNod;
    // 1 leaf 0 intern
    int keys[2 * f - 1];

    bTree *children[2 * f];
};

void createBtree(bTree *&root, int value)
{
    root = new bTree;

    root->typeOfNod = 1;
    root->numberOfKeys = 0;
    root->keys[0] = value;
}

void breakNode(bTree *parent, int index, bTree *&actualTree)
{
    bTree *newNod = new bTree;
    newNod->typeOfNod = actualTree->typeOfNod;
    newNod->numberOfKeys = f - 1;

    for (int j = 0; j <= f - 2; j++)
    {
        newNod->keys[j] = actualTree->keys[j];
    }

    if (actualTree->typeOfNod == 0)
    {
        for (int j = 0; j < f - 1; j++)
        {
            newNod->children[j] = actualTree->children[j + f];
        }
    }
    actualTree->numberOfKeys = f - 1;

    for (int j = parent->numberOfKeys; j >= index + 1; j--)
    {
        parent->children[index + 1] = newNod;
    }

    for (int j = parent->numberOfKeys - 1; j >= index; j--)
    {
        parent->keys[j + 1] = parent->keys[j];
    }

    newNod->keys[index] = actualTree->keys[f - 1];
    newNod->numberOfKeys = actualTree->numberOfKeys + 1;
}

void insertEmptyNode(bTree *&root, int value)
{
    int nrKeys = root->numberOfKeys - 1;

    if (root->typeOfNod == 1)
    {
        while (nrKeys >= 0 && value < root->keys[nrKeys])
        {
            root->keys[nrKeys + 1] = root->keys[nrKeys];
            nrKeys--;
        }

        root->keys[nrKeys + 1] = value;
        root->numberOfKeys++;
    }
    else
    {
        while (nrKeys >= 0 && value < root->keys[nrKeys])
        {
            nrKeys--;
        }
        nrKeys++;

        if (root->children[nrKeys]->numberOfKeys == 2 * f - 1)
        {
            breakNode(root, nrKeys, root->children[nrKeys]);

            if (value > root->keys[nrKeys])
            {
                nrKeys++;
            }
        }

        insertEmptyNode(root->children[nrKeys], value);
    }
}

void insertBtree(bTree *&root, int value)
{
    // check if the root is empty
    if (root == nullptr)
    {
        createBtree(root, value);
    }
    else
    {
        bTree *temp = root;
        // check if is leaf
        if (temp->numberOfKeys == 2 * f - 1)
        {
            bTree *newNode = new bTree;

            root = newNode;
            newNode->typeOfNod = 0;
            newNode->numberOfKeys = 0;
            newNode->children[0] = temp;

            breakNode(newNode, 0, temp);
            insertEmptyNode(newNode, value);
        }
        else
        {
            insertEmptyNode(temp, value);
        }
    }
}

int searchBtree(bTree *root, int value)
{
    int index = 0;
    while (index < root->numberOfKeys && value > root->keys[index])
    {
        index++;
    }

    if (index < root->numberOfKeys && value == root->keys[index])
    {
        cout << " Number " << value << " found\n";
        return 0;
    }
    else
    {
        if (root->typeOfNod == 1)
        {
            searchBtree(root->children[index], value);
        }
        else
        {
            cout << "no " << value << " found";
            return 0;
        }
    }

    return 0;
}

int main()
{

    bTree *root = nullptr;

    insertBtree(root, 10);
    insertBtree(root, 20);
    insertBtree(root, 30);
    insertBtree(root, 40);

    searchBtree(root, 5);

    return 0;
}