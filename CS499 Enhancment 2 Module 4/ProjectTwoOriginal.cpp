/*
* Name: ProjectTwo.cpp
* Author: Dylan Mousseau
* Class: SNHU CS 300
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Init course object
struct Course {
	string courseId;
	string courseName;
	vector<string> preReqs;
};
// course data struct
vector<Course> courses;
/*
* Function to load course data into vector
*/
void loadCourseData() {
	// default course data file
	string fName = "CS 300 ABCU_Advising_Program_Input.csv";

	// opening file
	ifstream inFile;
	inFile.open(fName);

	if (inFile.is_open()) {
		string line;
		// read each line
		while (getline(inFile, line)) {
			vector<string> course;
			string word;
			stringstream ss(line);
			// add course data using a "," as a delimiter
			while (getline(ss, word, ',')) {
				course.push_back(word);
			}

			// new course object 
			Course newCourse = Course();
			newCourse.courseId = course[0];
			newCourse.courseName = course[1];

			// add prerequisites if they exist
			if (course.size() > 2) {
				for (unsigned int i = 2; i < course.size(); i++) {
					newCourse.preReqs.push_back(course[i]);
				}
			}
			// add course object to vector
			courses.push_back(newCourse);
		}
		cout << "Course data successfully loaded!" << endl;
	}
	else {
		cout << "Failed to load course data: File not found." << endl;
	}

	inFile.close();
}
/*
* Function to print a list of courses from course vector
*/
void printCourses() {
	// sort courses alphanumerically
	if (courses.size() > 0) {
		for (unsigned int i = 0; i < courses.size() - 1; ++i) {
			for (unsigned int j = 0; j < courses.size() - i - 1; ++j) {
				if (courses[j].courseId > courses[j + 1].courseId) {
					swap(courses[j + 1], courses[j]);
				}
			}
		}

		cout << "Here is a sample schedule: " << endl << endl;
		// print each courseID and course name in vector
		for (unsigned int i = 0; i < courses.size(); i++) {
			cout << courses[i].courseId << ", " << courses[i].courseName << endl;
		}
	}
	else {
		cout << "Failed to print list: Data not loaded." << endl;
	}

}
/*
* Function to print a single course with prerequisites
*/
void printCourse() {
	if (courses.size() > 0) {
		string input;
		bool courseExists = false;

		cout << "What course do you want to know about? ";
		cin >> input;
		// uppercase input
		transform(input.begin(), input.end(), input.begin(), ::toupper);
		// search for requested course
		for (unsigned int i = 0; i < courses.size(); i++) {
			if (courses[i].courseId == input) {
				courseExists = true;
				// print course info + prerequisites if any
				cout << courses[i].courseId << ", " << courses[i].courseName << endl;
				cout << "Prerequisites: ";
				if (courses[i].preReqs.size() > 0) {
					for (unsigned int j = 0; j < courses[i].preReqs.size() - 1; j++) {
						cout << courses[i].preReqs[j] << ", ";
					}

					cout << courses[i].preReqs[courses[i].preReqs.size() - 1] << endl;
				}
				else {
					cout << "None" << endl;
				}
			}
		}
		if (courseExists == false) {
			cout << "Course not found." << endl;
		}
	}
	else {
		cout << "Failed to print course: Data not loaded." << endl;
	}
}
/*
* Main menu loop for course planner
*/
int main() {
	int input = 0;
	// menu choice loop
	while (input != 9) {
		// header
		cout << endl << "Welcome to the course planner." << endl;
		// main menu
		cout << endl << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl << endl;

		cout << "What would you like to do? ";
		cin >> input;
		cout << endl;

		switch (input) {
		// load vector
		case 1:
			loadCourseData();
			break;
		// print all courses
		case 2:
			printCourses();
			break;
		// search for specific course
		case 3:
			printCourse();
			break;
		// exit program
		case 9:
			cout << "Thank you for using the course planner!" << endl;
			break;
		// invalid input message
		default:
			cout << input << " is not a valid option.";
		}
		cout << endl;
	}
	return 0;

}

