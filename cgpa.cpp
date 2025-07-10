#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int numCourses;
    cout << "Enter the number of courses: ";
    cin >> numCourses;

    vector<string> courseNames(numCourses);
    vector<double> grades(numCourses);
    vector<int> credits(numCourses);
    double totalGradePoints = 0;
    int totalCredits = 0;

    // Input course data
    for (int i = 0; i < numCourses; ++i) {
        cout << "\nCourse " << i + 1 << " name: ";
        cin >> courseNames[i];

        cout << "Enter grade (on 10-point scale): ";
        cin >> grades[i];

        cout << "Enter credit hours: ";
        cin >> credits[i];

        totalGradePoints += grades[i] * credits[i];
        totalCredits += credits[i];
    }

    // Calculate CGPA
    double cgpa = totalGradePoints / totalCredits;

    // Output individual course grades
    cout << "\n----- Grade Summary -----\n";
    cout << left << setw(15) << "Course" 
         << setw(10) << "Grade" 
         << setw(10) << "Credits" << endl;

    for (int i = 0; i < numCourses; ++i) {
        cout << left << setw(15) << courseNames[i] 
             << setw(10) << grades[i] 
             << setw(10) << credits[i] << endl;
    }

    cout << "\nTotal Credits: " << totalCredits << endl;
    cout << fixed << setprecision(2);
    cout << "Final CGPA: " << cgpa << endl;

    return 0;
}
