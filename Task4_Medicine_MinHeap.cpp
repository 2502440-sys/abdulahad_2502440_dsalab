#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Medicine
{
public:
    string name;
    int id;
    int expiry;
    Medicine* left;
    Medicine* right;

    Medicine(string n, int i, int e)
    {
        name = n;
        id = i;
        expiry = e;
        left = NULL;
        right = NULL;
    }
};

class MinHeap
{
public:
    Medicine* root;

    MinHeap()
    {
        root = NULL;
    }

    void swapData(Medicine* a, Medicine* b)
    {
        swap(a->name, b->name);
        swap(a->id, b->id);
        swap(a->expiry, b->expiry);
    }

    void insert(string n, int i, int e)
    {
        Medicine* newNode = new Medicine(n, i, e);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        queue<Medicine*> q;
        q.push(root);

        while (!q.empty())
        {
            Medicine* temp = q.front();
            q.pop();

            if (temp->left == NULL)
            {
                temp->left = newNode;
                break;
            }
            else
                q.push(temp->left);

            if (temp->right == NULL)
            {
                temp->right = newNode;
                break;
            }
            else
                q.push(temp->right);
        }

        heapifyUp(newNode);
    }

    void heapifyUp(Medicine* newNode)
    {
        Medicine* parent = NULL;
        queue<Medicine*> q;
        q.push(root);

        while (!q.empty())
        {
            Medicine* temp = q.front();
            q.pop();

            if (temp->left == newNode || temp->right == newNode)
            {
                parent = temp;
                break;
            }

            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
        }

        if (parent != NULL && newNode->expiry < parent->expiry)
        {
            swapData(newNode, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(Medicine* temp)
    {
        Medicine* smallest = temp;

        if (temp->left != NULL && temp->left->expiry < smallest->expiry)
            smallest = temp->left;

        if (temp->right != NULL && temp->right->expiry < smallest->expiry)
            smallest = temp->right;

        if (smallest != temp)
        {
            swapData(temp, smallest);
            heapifyDown(smallest);
        }
    }

    void deleteRoot()
    {
        if (root == NULL)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return;
        }

        queue<Medicine*> q;
        q.push(root);

        Medicine* last = root;
        Medicine* lastParent = NULL;

        while (!q.empty())
        {
            Medicine* temp = q.front();
            q.pop();

            if (temp->left != NULL)
            {
                lastParent = temp;
                last = temp->left;
                q.push(temp->left);
            }

            if (temp->right != NULL)
            {
                lastParent = temp;
                last = temp->right;
                q.push(temp->right);
            }
        }

        swapData(root, last);

        if (lastParent->right == last)
            lastParent->right = NULL;
        else
            lastParent->left = NULL;

        delete last;

        heapifyDown(root);
    }

    void display()
    {
        if (root == NULL)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        queue<Medicine*> q;
        q.push(root);

        while (!q.empty())
        {
            Medicine* temp = q.front();
            q.pop();

            cout << temp->name << " (ID: " << temp->id
                 << ", Expiry: " << temp->expiry << ")" << endl;

            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }
};

int main()
{
    MinHeap h;

    h.insert("Panadol", 11, 20270315);
    h.insert("Brufen", 12, 20260910);
    h.insert("Augmentin", 13, 20281201);
    h.insert("Disprin", 14, 20260705);
    h.insert("Calpol", 15, 20270120);
    h.insert("Arinac", 16, 20260512);

    cout << "Medicine Heap (Level Order):" << endl;
    h.display();

    cout << "\nNearest expiry medicine: " << h.root->name
         << " (" << h.root->expiry << ")" << endl;
    cout << "Deleting it..." << endl;
    h.deleteRoot();

    cout << "\nUpdated Medicine Heap (Level Order):" << endl;
    h.display();

    return 0;
}
