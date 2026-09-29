#include <iostream>
using namespace std;

int main() {
    int marks[6][4];
    string subjects[4] = {"English", "Mathematics", "Programming", "AI"};

    for (int i = 0; i < 6; i++) {
        cout << "Enter marks of Student " << (i+1) << ":" << endl;
        for (int j = 0; j < 4; j++) {
            cout << subjects[j] << ": ";
            cin >> marks[i][j];
        }
    }

    cout << endl << "Marks Table:" << endl;
    cout << "Student\tEnglish\tMaths\tProgramming\tAI" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "S" << (i+1) << "\t";
        for (int j = 0; j < 4; j++) {
            cout << marks[i][j] << "\t";
        }
        cout << endl;
    }

    int total[6];
    float average[6];
    for (int i = 0; i < 6; i++) {
        total[i] = 0;
        for (int j = 0; j < 4; j++) {
            total[i] = total[i] + marks[i][j];
        }
        average[i] = total[i] / 4.0;
    }

    cout << endl << "Total and Average Marks:" << endl;
    for (int i = 0; i < 6; i++) {
        cout << "S" << (i+1) << " Total = " << total[i] << ", Average = " << average[i] << endl;
    }

    cout << endl << "Highest Marks in Each Subject:" << endl;
    for (int j = 0; j < 4; j++) {
        int highest = marks[0][j];
        for (int i = 1; i < 6; i++) {
            if (marks[i][j] > highest) {
                highest = marks[i][j];
            }
        }
        cout << subjects[j] << " = " << highest << endl;
    }

    int topStudent = 0;
    for (int i = 1; i < 6; i++) {
        if (total[i] > total[topStudent]) {
            topStudent = i;
        }
    }

    cout << endl << "Student with Highest Total Marks: S" << (topStudent+1) << " with Total = " << total[topStudent] << endl;
    return 0;
}
