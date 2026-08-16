/*
* Name: SortBenchmark.cpp
* Author: Dylan Mousseau
* Class: SNHU CS 300 / CS 499
*
* Benchmark harness comparing the three sorting implementations used across the
* versions of the course planner:
*
*   1. Bubble sort              -- ProjectTwoOriginal.cpp (pre-enhancement)
*   2. Quicksort, last pivot    -- ProjectTwo.cpp (enhanced, matches pseudocode)
*   3. Quicksort, median of 3   -- ProjectTwo_MedianOfThree.cpp (variant)
*
* Each sort below is a faithful copy of the one in its source file, with
* counters added for key comparisons, element swaps, and recursion depth.
* All three run on identical copies of the same data so the numbers are
* directly comparable.
*
* IMPORTANT -- build with an enlarged stack. Quicksort with a last-element
* pivot recurses once per element on already-sorted input (50,000 frames at
* n = 50,000), which overflows a default stack:
*
*   g++ -std=c++17 -O2 -static -Wl,--stack,536870912 -o SortBenchmark SortBenchmark.cpp
*
* On MSVC, use the linker option /STACK:536870912 instead.
*
* This program only measures; it does not modify any data file.
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cmath>

using namespace std;

// Init course object -- same shape as the planner's, so swap costs match
struct Course {
	string courseId;
	string courseName;
	vector<string> preReqs;
};

/*
* Counters reset before every measured run
*/
static long long comparisons = 0;
static long long swaps = 0;
static int maxDepth = 0;

// -------------------------------------------------------------------------
// Sort 1 of 3: bubble sort, as written in ProjectTwoOriginal.cpp
// Note there is no early exit, so the comparison count is n(n-1)/2 for every
// input ordering -- this version cannot benefit from data already being sorted.
// -------------------------------------------------------------------------
void bubbleSort(vector<Course>& courses) {
	if (courses.size() == 0) {
		return;
	}
	for (unsigned int i = 0; i < courses.size() - 1; ++i) {
		for (unsigned int j = 0; j < courses.size() - i - 1; ++j) {
			comparisons++;
			if (courses[j].courseId > courses[j + 1].courseId) {
				swaps++;
				swap(courses[j + 1], courses[j]);
			}
		}
	}
}

// -------------------------------------------------------------------------
// Sort 2 of 3: quicksort with a last-element pivot, as written in ProjectTwo.cpp
// -------------------------------------------------------------------------
int partitionLast(vector<Course>& courses, int low, int high) {
	string pivot = courses[high].courseId;
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		comparisons++;
		if (courses[j].courseId <= pivot) {
			i++;
			swaps++;
			swap(courses[i], courses[j]);
		}
	}
	swaps++;
	swap(courses[i + 1], courses[high]);
	return i + 1;
}

void quickSortLast(vector<Course>& courses, int low, int high, int depth) {
	if (depth > maxDepth) {
		maxDepth = depth;
	}
	if (low < high) {
		int pivotIndex = partitionLast(courses, low, high);
		quickSortLast(courses, low, pivotIndex - 1, depth + 1);
		quickSortLast(courses, pivotIndex + 1, high, depth + 1);
	}
}

// -------------------------------------------------------------------------
// Sort 3 of 3: quicksort with a median-of-three pivot, as written in
// ProjectTwo_MedianOfThree.cpp
// -------------------------------------------------------------------------
int medianOfThree(vector<Course>& courses, int low, int high) {
	int mid = low + (high - low) / 2;

	comparisons++;
	if (courses[mid].courseId < courses[low].courseId) {
		swaps++;
		swap(courses[mid], courses[low]);
	}
	comparisons++;
	if (courses[high].courseId < courses[low].courseId) {
		swaps++;
		swap(courses[high], courses[low]);
	}
	comparisons++;
	if (courses[high].courseId < courses[mid].courseId) {
		swaps++;
		swap(courses[high], courses[mid]);
	}
	return mid;
}

int partitionM3(vector<Course>& courses, int low, int high) {
	int pivotChoice = medianOfThree(courses, low, high);
	swaps++;
	swap(courses[pivotChoice], courses[high]);

	string pivot = courses[high].courseId;
	int i = low - 1;
	for (int j = low; j <= high - 1; j++) {
		comparisons++;
		if (courses[j].courseId <= pivot) {
			i++;
			swaps++;
			swap(courses[i], courses[j]);
		}
	}
	swaps++;
	swap(courses[i + 1], courses[high]);
	return i + 1;
}

void quickSortM3(vector<Course>& courses, int low, int high, int depth) {
	if (depth > maxDepth) {
		maxDepth = depth;
	}
	if (low < high) {
		int pivotIndex = partitionM3(courses, low, high);
		quickSortM3(courses, low, pivotIndex - 1, depth + 1);
		quickSortM3(courses, pivotIndex + 1, high, depth + 1);
	}
}

// -------------------------------------------------------------------------
// Reporting helpers
// -------------------------------------------------------------------------

/*
* Function to format a number with thousands separators for readability
*/
string withCommas(long long value) {
	string digits = to_string(value);
	string out;
	int count = 0;
	for (int i = static_cast<int>(digits.size()) - 1; i >= 0; i--) {
		out.push_back(digits[i]);
		count++;
		if (count % 3 == 0 && i > 0) {
			out.push_back(',');
		}
	}
	reverse(out.begin(), out.end());
	return out;
}

/*
* Function to confirm a vector is in ascending courseId order
*/
bool isSorted(const vector<Course>& courses) {
	for (unsigned int i = 1; i < courses.size(); i++) {
		if (courses[i - 1].courseId > courses[i].courseId) {
			return false;
		}
	}
	return true;
}

// one measured run
struct Result {
	long long comparisons;
	long long swaps;
	int depth;       // -1 means not applicable (bubble sort is iterative)
	double ms;
	bool sorted;
};

const int ALGO_COUNT = 3;
const string ALGO_NAMES[ALGO_COUNT] = {
	"Bubble sort",
	"Quicksort (last pivot)",
	"Quicksort (median of 3)"
};

/*
* Function to run one algorithm against a copy of the data and measure it
*/
Result runSort(int algo, vector<Course> data) {
	comparisons = 0;
	swaps = 0;
	maxDepth = 0;

	int high = static_cast<int>(data.size()) - 1;

	auto start = chrono::steady_clock::now();
	if (data.size() > 0) {
		if (algo == 0) {
			bubbleSort(data);
		}
		else if (algo == 1) {
			quickSortLast(data, 0, high, 1);
		}
		else {
			quickSortM3(data, 0, high, 1);
		}
	}
	auto finish = chrono::steady_clock::now();

	Result r;
	r.comparisons = comparisons;
	r.swaps = swaps;
	r.depth = (algo == 0) ? -1 : maxDepth;
	r.ms = chrono::duration<double, milli>(finish - start).count();
	r.sorted = isSorted(data);
	return r;
}

/*
* Function to print one scenario's results as a three-row block
*/
void printBlock(const string& scenario, int n, const Result results[ALGO_COUNT]) {
	cout << endl << "  " << scenario << "  (n = " << withCommas(n) << ")" << endl;
	cout << "  " << string(84, '-') << endl;
	cout << "  " << left << setw(25) << "algorithm"
		<< right << setw(16) << "comparisons"
		<< setw(14) << "swaps"
		<< setw(8) << "depth"
		<< setw(12) << "time (ms)"
		<< setw(9) << "sorted" << endl;

	for (int a = 0; a < ALGO_COUNT; a++) {
		cout << "  " << left << setw(25) << ALGO_NAMES[a]
			<< right << setw(16) << withCommas(results[a].comparisons)
			<< setw(14) << withCommas(results[a].swaps);

		if (results[a].depth < 0) {
			cout << setw(8) << "n/a";
		}
		else {
			cout << setw(8) << withCommas(results[a].depth);
		}

		cout << setw(12) << fixed << setprecision(1) << results[a].ms
			<< setw(9) << (results[a].sorted ? "yes" : "NO") << endl;
	}
}

/*
* Function to load course data, falling back to generated data if the advising
* file is missing so the benchmark still runs
*/
vector<Course> loadData(int wanted) {
	vector<Course> data;
	string fName = "CS 300 ABCU_Advising_Program_Input.csv";

	ifstream inFile;
	inFile.open(fName);

	if (inFile.is_open()) {
		string line;
		while (getline(inFile, line)) {
			vector<string> course;
			string word;
			stringstream ss(line);
			while (getline(ss, word, ',')) {
				course.push_back(word);
			}
			// skip malformed lines that lack an ID and a name
			if (course.size() < 2) {
				continue;
			}
			Course newCourse = Course();
			newCourse.courseId = course[0];
			newCourse.courseName = course[1];
			for (unsigned int i = 2; i < course.size(); i++) {
				newCourse.preReqs.push_back(course[i]);
			}
			data.push_back(newCourse);
		}
		inFile.close();
		cout << "Loaded " << withCommas(static_cast<long long>(data.size()))
			<< " courses from " << fName << endl;
	}
	else {
		cout << "Advising file not found -- generating " << withCommas(wanted)
			<< " synthetic courses instead." << endl;
		for (int i = 0; i < wanted; i++) {
			Course c = Course();
			// pseudo-random but deterministic ids so runs are reproducible
			int scrambled = (i * 7919) % wanted;
			ostringstream id;
			id << "GEN" << setw(6) << setfill('0') << scrambled;
			c.courseId = id.str();
			c.courseName = "Generated Course " + to_string(scrambled);
			data.push_back(c);
		}
	}
	return data;
}

int main() {
	const int SIZE_COUNT = 3;
	const int SIZES[SIZE_COUNT] = { 5000, 20000, 50000 };
	const int LARGEST = SIZES[SIZE_COUNT - 1];

	cout << endl << string(86, '=') << endl;
	cout << "  SORTING BENCHMARK -- three versions of the course planner" << endl;
	cout << string(86, '=') << endl << endl;

	vector<Course> source = loadData(LARGEST);
	if (source.size() == 0) {
		cout << "No data to sort. Exiting." << endl;
		return 1;
	}

	cout << endl << "Note: bubble sort performs n(n-1)/2 comparisons regardless of input" << endl;
	cout << "order, so the largest cases take a couple of minutes. Please wait." << endl;

	// results[algo][scenario][size] kept for the growth analysis at the end
	const int SCENARIO_COUNT = 4;
	const string SCENARIO_NAMES[SCENARIO_COUNT] = {
		"Shuffled (average case)",
		"Already ascending",
		"Reverse descending",
		"Only 10 distinct keys"
	};
	static Result all[ALGO_COUNT][SCENARIO_COUNT][SIZE_COUNT];

	for (int s = 0; s < SIZE_COUNT; s++) {
		int n = SIZES[s];
		if (static_cast<int>(source.size()) < n) {
			cout << endl << "Skipping n = " << withCommas(n)
				<< " (only " << withCommas(static_cast<long long>(source.size()))
				<< " courses available)." << endl;
			continue;
		}

		// build the four input orderings from the same n records
		vector<Course> shuffled(source.begin(), source.begin() + n);

		vector<Course> ascending = shuffled;
		sort(ascending.begin(), ascending.end(),
			[](const Course& a, const Course& b) { return a.courseId < b.courseId; });

		vector<Course> descending = ascending;
		reverse(descending.begin(), descending.end());

		// collapse to 10 distinct keys to expose duplicate-key behavior
		vector<Course> duplicates = shuffled;
		for (unsigned int i = 0; i < duplicates.size(); i++) {
			duplicates[i].courseId = "DUP" + to_string(i % 10);
		}

		cout << endl << endl << string(86, '=') << endl;
		cout << "  n = " << withCommas(n) << endl;
		cout << string(86, '=') << endl;

		for (int sc = 0; sc < SCENARIO_COUNT; sc++) {
			const vector<Course>* input = &shuffled;
			if (sc == 1) input = &ascending;
			else if (sc == 2) input = &descending;
			else if (sc == 3) input = &duplicates;

			Result row[ALGO_COUNT];
			for (int a = 0; a < ALGO_COUNT; a++) {
				row[a] = runSort(a, *input);
				all[a][sc][s] = row[a];
			}
			printBlock(SCENARIO_NAMES[sc], n, row);
		}
	}

	// ---------------------------------------------------------------------
	// Growth analysis: comparing how the comparison count grows against what
	// each complexity class predicts identifies the actual class empirically.
	// ---------------------------------------------------------------------
	cout << endl << endl << string(86, '=') << endl;
	cout << "  GROWTH ANALYSIS -- n from " << withCommas(SIZES[0])
		<< " to " << withCommas(SIZES[SIZE_COUNT - 1])
		<< " (" << (SIZES[SIZE_COUNT - 1] / SIZES[0]) << "x more data)" << endl;
	cout << string(86, '=') << endl;

	double nSmall = SIZES[0];
	double nLarge = SIZES[SIZE_COUNT - 1];
	double growth = nLarge / nSmall;
	double predictQuadratic = growth * growth;
	double predictLinearithmic =
		growth * (log(nLarge) / log(2.0)) / (log(nSmall) / log(2.0));

	cout << endl << "  If comparisons grow by about "
		<< fixed << setprecision(1) << predictQuadratic
		<< "x the behavior is O(n^2)." << endl;
	cout << "  If they grow by about " << predictLinearithmic
		<< "x the behavior is O(n log n)." << endl;

	for (int sc = 0; sc < SCENARIO_COUNT; sc++) {
		cout << endl << "  " << SCENARIO_NAMES[sc] << endl;
		cout << "  " << string(84, '-') << endl;
		int rowsPrinted = 0;
		for (int a = 0; a < ALGO_COUNT; a++) {
			long long small = all[a][sc][0].comparisons;
			long long large = all[a][sc][SIZE_COUNT - 1].comparisons;
			// a zero means that size was skipped for lack of data
			if (small == 0 || large == 0) {
				continue;
			}
			rowsPrinted++;
			double observed = static_cast<double>(large) / static_cast<double>(small);

			// label by whichever prediction it lands closer to, on a log scale
			string verdict;
			double dQuad = fabs(log(observed) - log(predictQuadratic));
			double dLin = fabs(log(observed) - log(predictLinearithmic));
			verdict = (dQuad < dLin) ? "matches O(n^2)" : "matches O(n log n)";

			cout << "  " << left << setw(25) << ALGO_NAMES[a]
				<< right << setw(16) << withCommas(small)
				<< "  ->" << setw(16) << withCommas(large)
				<< "   " << fixed << setprecision(1) << setw(7) << observed << "x"
				<< "   " << verdict << endl;
		}
		if (rowsPrinted == 0) {
			cout << "  (not enough data loaded to compare both sizes)" << endl;
		}
	}

	cout << endl << string(86, '=') << endl;
	cout << "  Benchmark complete." << endl;
	cout << string(86, '=') << endl << endl;

	return 0;
}
