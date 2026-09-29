#include <iostream>
using namespace std;

struct Node {
    int id;
    Node* next;
};

Node* head = NULL;

void addProduct(int x) {
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

void removeProduct(int x) {
    if (head == NULL) {
        cout << "Cart is empty." << endl;
        return;
    }

    if (head->id == x) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    Node* current = head;
    while (current->next != NULL) {
        if (current->next->id == x) {
            Node* temp = current->next;
            current->next = temp->next;
            delete temp;
            return;
        }
        current = current->next;
    }
    cout << "Product not found." << endl;
}

int main() {
    addProduct(101);
    addProduct(205);
    addProduct(310);
    addProduct(415);

    cout << "Shopping Cart:" << endl;
    display();

    int x;
    cout << endl;
    cout << "Remove Product (enter number only, e.g. 310): P";
    cin >> x;
    removeProduct(x);

    cout << endl;
    cout << "Updated Cart:" << endl;
    display();

    return 0;
}
