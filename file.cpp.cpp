#include <iostream>
#include <string>
using namespace std;
int enrollmentCount = 0;
const int maxcourse = 5;
const int enrolment = 500;
string code[maxcourse] = { "CSCP1011", "CSHU2833", "CSCS2533", "CSHU1893", "CSSS1713" };
int creditHours[maxcourse] = { 4, 3, 3, 3, 3 };
string courseNames[maxcourse] = { "Programming Fundamentals", "Logical Thinking","Digital Logic Design", "Pakistan Studies",
  "Calculus 1" };
string studentIds[enrolment];
string enrolledCourseCodes[enrolment];
char enrolledSections[enrolment];

void enrollStudent() {
    string studentId, courseCode;
    char section;
    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Choose a course from the following courses:\n";
    for (int i = 0; i < maxcourse; i++) {
        cout << code[i] << " " << creditHours[i] << " // " << courseNames[i] << "\n";
    }
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter the Section (A, B, C, D, E): ";
    cin >> section;
    for (int i = 0; i < enrollmentCount; i++) {
        if (studentIds[i] == studentId && enrolledCourseCodes[i] == courseCode) {
            cout << "Student cannot enroll a course in multiple sections\n";
            return;
        }
    }
    studentIds[enrollmentCount] = studentId;
    enrolledCourseCodes[enrollmentCount] = courseCode;
    enrolledSections[enrollmentCount] = section;
    enrollmentCount++;
    cout << "Student Enrolled Successfully\n";
}
void dropCourse() {
    string studentId, courseCode;
    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    bool found = false;
    for (int i = 0; i < enrollmentCount; i++) {
        if (studentIds[i] == studentId && enrolledCourseCodes[i] == courseCode) {
            studentIds[i] = studentIds[enrollmentCount - 1];
            enrolledCourseCodes[i] = enrolledCourseCodes[enrollmentCount - 1];
            enrolledSections[i] = enrolledSections[enrollmentCount - 1];
            enrollmentCount--;
            found = true;
            cout << "Course dropped successfully\n";
            break;
        }
    }
    if (!found) {
        cout << "Student is not registered in this course\n";
    }
}
void listStudentCourses() {
    string studentId;
    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Course Code\tSection\n";
    for (int i = 0; i < enrollmentCount; i++) {
        if (studentIds[i] == studentId) {
            cout << enrolledCourseCodes[i] << "\t" << enrolledSections[i] << "\n";
        }
    }
}
void updateSection() {
    string studentId, courseCode;
    char newSection;
    cout << "Enter Student ID: ";
    cin >> studentId;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    cout << "Enter the New Section: ";
    cin >> newSection;
    for (int i = 0; i < enrollmentCount; i++) {
        if (studentIds[i] == studentId && enrolledCourseCodes[i] == courseCode) {
            enrolledSections[i] = newSection;
            cout << "Section is Updated Successfully\n";
            return;
        }
    }
    cout << "Student is not enrolled in this course\n";
}
void totalEnrolledStudents() {
    string courseCode;
    cout << "Enter Course Code: ";
    cin >> courseCode;
    int count = 0;
    for (int i = 0; i < enrollmentCount; i++) {
        if (enrolledCourseCodes[i] == courseCode) {
            count++;
        }
    }
    cout << "Total enrolled students for this course are: " << count << "\n";
}
void displayCoursesNotEnrolled() {
    bool courseEnrolled[maxcourse] = { false };
    for (int i = 0; i < enrollmentCount; i++) {
        for (int j = 0; j < maxcourse; j++) {
            if (enrolledCourseCodes[i] == code[j]) {
                courseEnrolled[j] = true;
            }
        }
    }
    bool anyCourseNotEnrolled = false;
    for (int i = 0; i < maxcourse; i++) {
        if (!courseEnrolled[i]) {
            cout << code[i] << " is not enrolled by any student\n";
            anyCourseNotEnrolled = true;
        }
    }
    if (!anyCourseNotEnrolled) {
        cout << "No course found\n";
    }
}
void studentWithMinCourses() {
    string uniqueStudentIds[enrolment];
    int studentCourseCount[enrolment] = { 0 };
    int studentCount = 0;
    for (int i = 0; i < enrollmentCount; i++) {
        bool studentExists = false;
        for (int j = 0; j < studentCount; j++) {
            if (uniqueStudentIds[j] == studentIds[i]) {
                studentCourseCount[j]++;
                studentExists = true;
                break;
            }
        }
        if (!studentExists) {
            uniqueStudentIds[studentCount] = studentIds[i];
            studentCourseCount[studentCount]++;
            studentCount++;
        }
    }
    if (studentCount == 0) {
        cout << "No students are enrolled in any courses\n";
        return;
    }
    int minCourses = studentCourseCount[0];
    string minStudentId = uniqueStudentIds[0];
    for (int i = 1; i < studentCount; i++) {
        if (studentCourseCount[i] < minCourses) {
            minCourses = studentCourseCount[i];
            minStudentId = uniqueStudentIds[i];
        }
    }
    cout << minStudentId << " has registered only " << minCourses << " courses\n";
}
int main() {
    int choice;
    do {
        cout << "********** Menu **********\n";
        cout << "Press 1 for Enrollment of the Student in a Course.\n";
        cout << "Press 2 for drop a Specified Course.\n";
        cout << "Press 3 for Display Students Enrolled courses.\n";
        cout << "Press 4 for Update Section of Student for enrolled Course.\n";
        cout << "Press 5 for Display Total number of Students enrolled in particular course.\n";
        cout << "Press 6 for Display course not enrolled by any student.\n";
        cout << "Press 7 for Display the Student with minimum number of registered course.\n";
        cout << "Enter Choice: ";
        cin >> choice;
        if (choice == 1) {
            enrollStudent();
        }
        else if (choice == 2) {
            dropCourse();
        }
        else if (choice == 3) {
            listStudentCourses();
        }
        else if (choice == 4) {
            updateSection();
        }
        else if (choice == 5) {
            totalEnrolledStudents();
        }
        else if (choice == 6) {
            displayCoursesNotEnrolled();
        }
        else if (choice == 7) {
            studentWithMinCourses();
        }
        else {
            cout << "Invalid choice Please try again.\n";
        }
    } while (choice != 0);
    return 0;
}