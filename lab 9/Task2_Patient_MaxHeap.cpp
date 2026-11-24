#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Patient
{
public:
    string name;
    int id;
    int priority;
    Patient* left;
    Patient* right;

    Patient(string n, int i, int p)
    {
        name = n;
        id = i;
        priority = p;
        left = NULL;
        right = NULL;
    }
};

class MaxHeap
{
public:
    Patient* root;

    MaxHeap()
    {
        root = NULL;
    }

    void swapData(Patient* a, Patient* b)
    {
        swap(a->name, b->name);
        swap(a->id, b->id);
        swap(a->priority, b->priority);
    }

    void insert(string n, int i, int p)
    {
        Patient* newNode = new Patient(n, i, p);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        queue<Patient*> q;
        q.push(root);

        while (!q.empty())
        {
            Patient* temp = q.front();
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

    void heapifyUp(Patient* newNode)
    {
        Patient* parent = NULL;
        queue<Patient*> q;
        q.push(root);

        while (!q.empty())
        {
            Patient* temp = q.front();
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

        if (parent != NULL && newNode->priority > parent->priority)
        {
            swapData(newNode, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(Patient* temp)
    {
        Patient* largest = temp;

        if (temp->left != NULL && temp->left->priority > largest->priority)
            largest = temp->left;

        if (temp->right != NULL && temp->right->priority > largest->priority)
            largest = temp->right;

        if (largest != temp)
        {
            swapData(temp, largest);
            heapifyDown(largest);
        }
    }

    void deleteRoot()
    {
        if (root == NULL)
        {
            cout << "No patients left!" << endl;
            return;
        }

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return;
        }

        queue<Patient*> q;
        q.push(root);

        Patient* last = root;
        Patient* lastParent = NULL;

        while (!q.empty())
        {
            Patient* temp = q.front();
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

    void showHighest()
    {
        if (root == NULL)
        {
            cout << "No patients left!" << endl;
            return;
        }

        cout << root->name << " (ID: " << root->id
             << ", Priority: " << root->priority << ")" << endl;
    }

    void display()
    {
        if (root == NULL)
        {
            cout << "No patients left!" << endl;
            return;
        }

        queue<Patient*> q;
        q.push(root);

        while (!q.empty())
        {
            Patient* temp = q.front();
            q.pop();

            cout << temp->name << " (ID: " << temp->id
                 << ", Priority: " << temp->priority << ")" << endl;

            if (temp->left != NULL)
                q.push(temp->left);
            if (temp->right != NULL)
                q.push(temp->right);
        }
    }
};

int main()
{
    MaxHeap h;

    h.insert("Bilal", 1, 60);
    h.insert("Hina", 2, 90);
    h.insert("Zain", 3, 45);
    h.insert("Noor", 4, 85);
    h.insert("Kamran", 5, 70);
    h.insert("Mariam", 6, 95);

    cout << "All Patients (Level Order):" << endl;
    h.display();

    cout << "\nPatient with highest priority:" << endl;
    h.showHighest();

    cout << "\nTreating and removing the patient..." << endl;
    h.deleteRoot();

    cout << "\nNext patient who needs treatment:" << endl;
    h.showHighest();

    cout << "\nRemaining Patients (Level Order):" << endl;
    h.display();

    return 0;
}
