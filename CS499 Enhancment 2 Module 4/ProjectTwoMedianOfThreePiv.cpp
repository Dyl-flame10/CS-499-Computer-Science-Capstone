/*
* Name: ProjectTwo_MedianOfThree.cpp
* Author: Dylan Mousseau
* Class: SNHU CS 300
*
* Median-of-three variant of ProjectTwo.cpp, kept for performance comparison.
* The only difference from the baseline is how partition() chooses its pivot:
* the baseline always uses the last element, while this version uses the median
* of the first, middle, and last elements. Everything else -- the partition
* scan, the recursion, the file loading, and the menu -- is identical, so any
* measured difference is attributable to pivot selection alone.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Init course object
struct Course {
	string courseId;
	string courseName;
	vector<string> preReqs;
};
// course data struct
vector<Course> courses;

// forward declarations for quicksort helpers
int medianOfThree(vector<Course>& courses, int low, int high);
int partition(vector<Course>& courses, int low, int high);
void quickSort(vector<Course>& courses, int low, int high);

/*
* Function to sort the course vector by courseId using quicksort
*/
void sortCourses(vector<Course>& courses) {
	quickSort(courses, 0, static_cast<int>(courses.size()) - 1);
}
/*
* Function to recursively sort courses[low..high] using quicksort
*/
void quickSort(vector<Course>& courses, int low, int high) {
	if (low < high) {
		int pivotIndex = partition(courses, low, high);
		quickSort(courses, low, pivotIndex - 1);
		quickSort(courses, pivotIndex + 1, high);
	}
}
/*
* Function to order courses[low], courses[mid], and courses[high] by courseId
* and return the index of their median. Sorting the three in place leaves
* courses[low] <= courses[mid] <= courses[high], so the median sits at mid.
*/
int medianOfThree(vector<Course>& courses, int low, int high) {
	// written this way rather than (low + high) / 2 to avoid integer overflow
	int mid = low + (high - low) / 2;

	if (courses[mid].courseId < courses[low].courseId) {
		swap(courses[mid], courses[low]);
	}
	if (courses[high].courseId < courses[low].courseId) {
		swap(courses[high], courses[low]);
	}
	if (courses[high].courseId < courses[mid].courseId) {
		swap(courses[high], courses[mid]);
	}
	return mid;
}
/*
* Function to partition courses[low..high] around a median-of-three pivot
*/
int partition(vector<Course>& courses, int low, int high) {
	// choose the median of the first, middle, and last elements, then move it
	// into the high slot so the scan below stays the same as the baseline
	int pivotChoice = medianOfThree(courses, low, high);
	swap(courses[pivotChoice], courses[high]);

	string pivot = courses[high].courseId;
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		if (courses[j].courseId <= pivot) {
			i++;
			swap(courses[i], courses[j]);
		}
	}
	swap(courses[i + 1], courses[high]);
	return i + 1;
}
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

			// skip malformed lines (e.g. blank lines) that lack an ID and a name
			if (course.size() < 2) {
				continue;
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

		// sort once here so repeated prints don't have to re-sort
		sortCourses(courses);

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
	// courses are already sorted by loadCourseData()
	if (courses.size() > 0) {
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

		// clear a failed (non-numeric) read so the loop can keep accepting input
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			input = 0;
		}
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
