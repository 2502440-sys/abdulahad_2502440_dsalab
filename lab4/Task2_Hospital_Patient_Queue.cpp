#include <iostream>
using namespace std;

struct Node {
    int id;
    Node* next;
};

Node* head = NULL;

void addPatient(int x) {
    Node* newNode = new Node;
    newNode->id = x;
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
    while (temp != NULL) {
        cout << "P" << temp->id;
        if (temp->next != NULL) {
            cout << " -> ";
        }
        temp = temp->next;
    }
    cout << endl;
}

void servePatient() {
    if (head == NULL) {
        cout << "No patient in queue." << endl;
        return;
    }
    Node* temp = head;
    cout << "Patient P" << temp->id << " is being served." << endl;
    head = head->next;
    delete temp;
}

int main() {
    addPatient(101);
    addPatient(102);
    addPatient(103);
    addPatient(104);

    cout << "Waiting Patients:" << endl;
    display();

    cout << endl;
    servePatient();

    cout << endl;
    cout << "Updated Queue:" << endl;
    display();

    return 0;
}
