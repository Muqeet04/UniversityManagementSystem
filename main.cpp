#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Person {
protected:
  int age;
  string name;
  string id;

public:
  void setInfo(string n, int a, string i) {
    name = n;
    age = a;
    id = i;
  }

  void display() {
    cout << "Name: " << name << endl;
    cout << "ID: " << id << endl;
    cout << "Age: " << age << endl;
  }

  // New methods for file handling
  void saveToFile(ofstream& file) {
    file << name << endl;
    file << age << endl;
    file << id << endl;
  }

  void loadFromFile(ifstream& file) {
    getline(file, name);
    file >> age;
    file.ignore(); // Consume the newline character
    getline(file, id);
  }
};

class Student : public Person {
protected:
  char grade[5];

public:
  string department;
  string courses[5];

  Student() { // Initialize grades to empty
    for (int i = 0; i < 5; i++) {
      grade[i] = ' ';
    }
  }

  void setGrades(const char g[]) {
    for (int i = 0; i < 5; i++)
      grade[i] = g[i];
  }

  void display() {
    Person::display();
    cout << "Department: " << department << endl;
    for (int i = 0; i < 5; i++) {
      if (!courses[i].empty()) { // Only display non-empty courses
        cout << "Course " << (i + 1) << ": " << courses[i] << endl;
        cout << "Grade: " << grade[i] << endl;
      }
    }
  }

  // New methods for file handling
  void saveToFile(ofstream& file) {
    Person::saveToFile(file);
    file << department << endl;
    for (int i = 0; i < 5; i++) {
      file << courses[i] << endl;
    }
    for (int i = 0; i < 5; i++) {
      file << grade[i] << endl;
    }
  }

  void loadFromFile(ifstream& file) {
    Person::loadFromFile(file);
    getline(file, department);
    for (int i = 0; i < 5; i++) {
      getline(file, courses[i]);
    }
    for (int i = 0; i < 5; i++) {
      file >> grade[i];
    }
    file.ignore(); // Consume the newline character
  }
};

class Faculty : public Person {
protected:
  double salary;

public:
  string subject;
  string department;

  void setSalary(double s) {
    salary = s;
  }

  void display() {
    Person::display();
    cout << "Department: " << department << endl;
    cout << "Subject: " << subject << endl;
    cout << "Salary: " << salary << endl;
  }

  // New methods for file handling
  void saveToFile(ofstream& file) {
    Person::saveToFile(file);
    file << department << endl;
    file << subject << endl;
    file << salary << endl;
  }

  void loadFromFile(ifstream& file) {
    Person::loadFromFile(file);
    getline(file, department);
    getline(file, subject);
    file >> salary;
    file.ignore(); // Consume the newline character
  }
};

class Course {
public:
  string name;
  string code;
  int creditHour;
  Faculty instructor;

  Course() : creditHour(0) {} // Initialize creditHour to 0

  void display() {
    if (!name.empty()) { // Only display if course has been set
      cout << "Course Name: " << name << endl;
      cout << "Course Code: " << code << endl;
      cout << "Credit Hours: " << creditHour << endl;
      cout << "Instructor Details:" << endl;
      instructor.display();
      cout << "------------------------" << endl;
    }
  }

  // New methods for file handling
  void saveToFile(ofstream& file) {
    file << name << endl;
    file << code << endl;
    file << creditHour << endl;
    instructor.saveToFile(file);
  }

  void loadFromFile(ifstream& file) {
    getline(file, name);
    getline(file, code);
    file >> creditHour;
    file.ignore(); // Consume the newline character
    instructor.loadFromFile(file);
  }
};

// Function to save all data to files
void saveAllData(Student s[], int studentNum, Faculty f[], int facultyCount, Course c[], int courseCount) {
  // Save students data
  ofstream studentFile("students.txt");
  if (studentFile.is_open()) {
    studentFile << studentNum << endl;
    for (int i = 0; i < studentNum; i++) {
      s[i].saveToFile(studentFile);
    }
    studentFile.close();
    cout << "Students data saved successfully." << endl;
  } else {
    cout << "Error opening students file for writing." << endl;
  }

  // Save faculty data
  ofstream facultyFile("faculty.txt");
  if (facultyFile.is_open()) {
    facultyFile << facultyCount << endl;
    for (int i = 0; i < facultyCount; i++) {
      f[i].saveToFile(facultyFile);
    }
    facultyFile.close();
    cout << "Faculty data saved successfully." << endl;
  } else {
    cout << "Error opening faculty file for writing." << endl;
  }

  // Save courses data
  ofstream courseFile("courses.txt");
  if (courseFile.is_open()) {
    courseFile << courseCount << endl;
    for (int i = 0; i < courseCount; i++) {
      c[i].saveToFile(courseFile);
    }
    courseFile.close();
    cout << "Courses data saved successfully." << endl;
  } else {
    cout << "Error opening courses file for writing." << endl;
  }
}

// Function to load all data from files
void loadAllData(Student s[], int& studentNum, Faculty f[], int& facultyCount, Course c[], int& courseCount) {
  // Load students data
  ifstream studentFile("students.txt");
  if (studentFile.is_open()) {
    studentFile >> studentNum;
    studentFile.ignore(); // Consume the newline character
    for (int i = 0; i < studentNum; i++) {
      s[i].loadFromFile(studentFile);
    }
    studentFile.close();
    cout << "Students data loaded successfully." << endl;
  } else {
    cout << "No existing students data found." << endl;
    studentNum = 0;
  }

  // Load faculty data
  ifstream facultyFile("faculty.txt");
  if (facultyFile.is_open()) {
    facultyFile >> facultyCount;
    facultyFile.ignore(); // Consume the newline character
    for (int i = 0; i < facultyCount; i++) {
      f[i].loadFromFile(facultyFile);
    }
    facultyFile.close();
    cout << "Faculty data loaded successfully." << endl;
  } else {
    cout << "No existing faculty data found." << endl;
    facultyCount = 0;
  }

  // Load courses data
  ifstream courseFile("courses.txt");
  if (courseFile.is_open()) {
    courseFile >> courseCount;
    courseFile.ignore(); // Consume the newline character
    for (int i = 0; i < courseCount; i++) {
      c[i].loadFromFile(courseFile);
    }
    courseFile.close();
    cout << "Courses data loaded successfully." << endl;
  } else {
    cout << "No existing courses data found." << endl;
    courseCount = 0;
  }
}

int main() {
  Student s[10];
  Faculty f[5];
  Course c[5];
  int studentNum = 0;
  int facultyCount = 0;
  int courseCount = 0;

  // Load existing data when program starts
  loadAllData(s, studentNum, f, facultyCount, c, courseCount);

  int choice;
  do{
    cout << "\n=== University Management System ===" << endl;
    cout << "1. Add Student" << endl;
    cout << "2. Add faculty" << endl;
    cout << "3. Assign course to student" << endl;
    cout << "4. Display students" << endl;
    cout << "5. Display Faculty" << endl;
    cout << "6. Display Courses" << endl;
    cout << "7. Assign Course to Faculty" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
    cin >> choice;
    cin.ignore(); // Clear the input buffer

    switch (choice) {
      case 1:
        if (studentNum < 10) {
          string name, id;
          int age;
          cout << "Enter name: ";
          getline(cin, name);
          cout << "Enter age: ";
          cin >> age;
          cin.ignore(); // Clear the buffer
          cout << "Enter id: ";
          getline(cin, id);
          s[studentNum].setInfo(name, age, id);
          cout << "Enter department: ";
          getline(cin, s[studentNum].department);
          studentNum++;
          saveAllData(s, studentNum, f, facultyCount, c, courseCount);
        } else {
          cout << "Student number exceeded" << endl;
        }
        break;
      case 2:
        if (facultyCount < 5) {
          string name, id;
          int age;
          double salary;
          cout << "Enter name: ";
          getline(cin, name);
          cout << "Enter age: ";
          cin >> age;
          cin.ignore(); // Clear the buffer
          cout << "Enter id: ";
          getline(cin, id);
          f[facultyCount].setInfo(name, age, id);

          cout << "Enter department: ";
          getline(cin, f[facultyCount].department);
          cout << "Enter subject: ";
          getline(cin, f[facultyCount].subject);
          cout << "Enter salary: ";
          cin >> salary;
          f[facultyCount].setSalary(salary);

          facultyCount++;
          saveAllData(s, studentNum, f, facultyCount, c, courseCount);
        } else {
          cout << "Faculty limit reached!" << endl;
        }
        break;

      case 3:
        if (studentNum == 0) {
          cout << "No students available!" << endl;
          break;
        }
        int sid;
        cout << "Enter student index (0 to " << studentNum - 1 << "): ";
        cin >> sid;
        cin.ignore(); // Clear the buffer
        if (sid >= 0 && sid < studentNum) {
          for (int i = 0; i < 5; i++) {
            cout << "Enter course " << i + 1 << ": ";
            getline(cin, s[sid].courses[i]);
          }
          char grades[5];
          cout << "Enter grades (5 characters A/B/C etc.): ";
          for (int i = 0; i < 5; i++) {
            cin >> grades[i];
          }
          s[sid].setGrades(grades);
          saveAllData(s, studentNum, f, facultyCount, c, courseCount);
        } else {
          cout << "Invalid student index!" << endl;
        }
        break;
      case 4:
        if (studentNum == 0) {
          cout << "No students available!" << endl;
        } else {
          for (int i = 0; i < studentNum; i++) {
            cout << "\nStudent " << i + 1 << ":" << endl;
            s[i].display();
            cout << "------------------------" << endl;
          }
        }
        break;
      case 5:
        if (facultyCount == 0) {
          cout << "No faculty available!" << endl;
        } else {
          for (int i = 0; i < facultyCount; i++) {
            cout << "\nFaculty " << i + 1 << ":" << endl;
            f[i].display();
            cout << "------------------------" << endl;
          }
        }
        break;
      case 6:
        if (courseCount == 0) {
          cout << "No courses available!" << endl;
        } else {
          for (int i = 0; i < courseCount; i++) {
            cout << "\nCourse " << i + 1 << ":" << endl;
            c[i].display();
          }
        }
        break;
      case 7:
        if (courseCount < 5 && facultyCount > 0) {
          int fid;
          cout << "Enter faculty index (0 to " << facultyCount - 1 << "): ";
          cin >> fid;
          cin.ignore(); // Clear the buffer
          if (fid >= 0 && fid < facultyCount) {
            cout << "Enter course name: ";
            getline(cin, c[courseCount].name);
            cout << "Enter course code: ";
            getline(cin, c[courseCount].code);
            cout << "Enter credit hours: ";
            cin >> c[courseCount].creditHour;

            c[courseCount].instructor = f[fid];

            courseCount++;
            saveAllData(s, studentNum, f, facultyCount, c, courseCount);
          } else {
            cout << "Invalid faculty index!" << endl;
          }
        } else {
          cout << "Faculty unavailable or course limit reached!" << endl;
        }
        break;
      case 8:
        cout << "Saving data and exiting system..." << endl;
        saveAllData(s, studentNum, f, facultyCount, c, courseCount);
        break;

      default:
        cout << "Invalid choice!" << endl;
    }
  } while(choice != 8);

  return 0;
}