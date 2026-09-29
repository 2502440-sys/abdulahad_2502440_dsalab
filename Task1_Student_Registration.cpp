#include <iostream>
using namespace std;

struct Node {
    int roll;
    Node* next;
};

Node* head = NULL;

void addStudent(int r) {
    Node* newNode = new Node;
    newNode->roll = r;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void display() {
    Node* temp = head;
    cout << "Registered Students:" << endl;
    while (temp != NULL) {
        cout << temp->roll;
        if (temp->next != NULL) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << endl;
}

void search(int r) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->roll == r) {
            cout << "Student Found" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Student Not Found" << endl;
}

int main() {
    addStudent(101);
    addStudent(105);
    addStudent(108);
    addStudent(112);

    display();

    int r;
    cout << "Enter Roll Number to Search: ";
    cin >> r;
    search(r);

    return 0;
}
