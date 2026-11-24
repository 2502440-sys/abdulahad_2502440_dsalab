#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Student
{
public:
    string name;
    int roll;
    int marks;
    Student* left;
    Student* right;

    Student(string n, int r, int m)
    {
        name = n;
        roll = r;
        marks = m;
        left = NULL;
        right = NULL;
    }
};

class MaxHeap
{
public:
    Student* root;

    MaxHeap()
    {
        root = NULL;
    }

    void swapData(Student* a, Student* b)
    {
        swap(a->name, b->name);
        swap(a->roll, b->roll);
        swap(a->marks, b->marks);
    }

    void insert(string n, int r, int m)
    {
        Student* newNode = new Student(n, r, m);

        if (root == NULL)
        {
            root = newNode;
            return;
        }

        queue<Student*> q;
        q.push(root);

        while (!q.empty())
        {
            Student* temp = q.front();
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

    void heapifyUp(Student* newNode)
    {
        Student* parent = NULL;
        queue<Student*> q;
        q.push(root);

        while (!q.empty())
        {
            Student* temp = q.front();
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

        if (parent != NULL && newNode->marks > parent->marks)
        {
            swapData(newNode, parent);
            heapifyUp(parent);
        }
    }

    void heapifyDown(Student* temp)
    {
        Student* largest = temp;

        if (temp->left != NULL && temp->left->marks > largest->marks)
            largest = temp->left;

        if (temp->right != NULL && temp->right->marks > largest->marks)
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
            cout << "Heap is empty!" << endl;
            return;
        }

        if (root->left == NULL && root->right == NULL)
        {
            delete root;
            root = NULL;
            return;
        }

        queue<Student*> q;
        q.push(root);

        Student* last = root;
        Student* lastParent = NULL;

        while (!q.empty())
        {
            Student* temp = q.front();
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

        queue<Student*> q;
        q.push(root);

        while (!q.empty())
        {
            Student* temp = q.front();
            q.pop();

            cout << temp->name << " (Roll: " << temp->roll
                 << ", Marks: " << temp->marks << ")" << endl;

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

    h.insert("Ali", 101, 75);
    h.insert("Sara", 102, 88);
    h.insert("Ahmed", 103, 92);
    h.insert("Fatima", 104, 67);
    h.insert("Usman", 105, 81);
    h.insert("Ayesha", 106, 95);

    cout << "Merit List (Level Order):" << endl;
    h.display();

    cout << "\nDeleting student with highest marks: "
         << h.root->name << " (" << h.root->marks << ")" << endl;
    h.deleteRoot();

    cout << "\nUpdated Merit List (Level Order):" << endl;
    h.display();

    return 0;
}
