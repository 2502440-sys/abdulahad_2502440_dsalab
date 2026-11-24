#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Order
{
public:
    int id;
    string customer;
    int amount;
    Order* left;
    Order* right;

    Order(int i, string c, int a)
    {
        id = i;
        customer = c;
        amount = a;
        left = NULL;
        right = NULL;
    }
};

class MaxHeap
{
public:
    Order* root;

    MaxHeap()
    {
        root = NULL;
    }

    void swapData(Order* a, Order* b)
    {
        swap(a->id, b->id);
        swap(a->customer, b->customer);
        swap(a->amount, b->amount);
    }

    void insert(int i, string c, int a)
    {
        Order* newNode = new Order(i, c, a);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        queue<Order*> q;
        q.push(root);

        while (!q.empty())
        {
            Order* temp = q.front();
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

    void heapifyUp(Order* newNode)
    {
        Order* parent = NULL;
        queue<Order*> q;
        q.push(root);

        while (!q.empty())
        {
            Order* temp = q.front();
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

        if (parent != NULL && newNode->amount > parent->amount)
        {
            swapData(newNode, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(Order* temp)
    {
        Order* largest = temp;

        if (temp->left != NULL && temp->left->amount > largest->amount)
            largest = temp->left;

        if (temp->right != NULL && temp->right->amount > largest->amount)
            largest = temp->right;

        if (largest != temp)
        {
            swapData(temp, largest);
            heapifyDown(largest);
        }
    }

    int deleteRoot()
    {
        int value = root->amount;

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return value;
        }

        queue<Order*> q;
        q.push(root);

        Order* last = root;
        Order* lastParent = NULL;

        while (!q.empty())
        {
            Order* temp = q.front();
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

        return value;
    }

    void display()
    {
        if (root == NULL)
        {
            cout << "Heap is empty!" << endl;
            return;
        }

        queue<Order*> q;
        q.push(root);

        while (!q.empty())
        {
            Order* temp = q.front();
            q.pop();

            cout << "Order " << temp->id << " - " << temp->customer
                 << " - Rs. " << temp->amount << endl;

            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }

    void heapSort()
    {
        int sorted[100];
        int count = 0;

        while (root != NULL)
        {
            sorted[count] = deleteRoot();
            count++;
        }

        cout << "Order amounts in ascending order: ";
        for (int i = count - 1; i >= 0; i--)
        {
            cout << sorted[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    MaxHeap h;

    h.insert(1, "Ali", 4500);
    h.insert(2, "Sara", 1200);
    h.insert(3, "Ahmed", 8000);
    h.insert(4, "Fatima", 2500);
    h.insert(5, "Usman", 6700);
    h.insert(6, "Ayesha", 3100);

    cout << "Max Heap before sorting (Level Order):" << endl;
    h.display();

    cout << endl;
    h.heapSort();

    return 0;
}
