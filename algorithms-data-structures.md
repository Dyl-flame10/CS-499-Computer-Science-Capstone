---
layout: default
title: Algorithms and Data Structures
permalink: /algorithms-data-structures/
---

# Algorithms and Data Structures

**Category:** Algorithms and Data Structures  
**Artifact:** Course Planner Algorithm  
**Original course:** CS-300 DSA: Analysis and Design
**Repository:** [View the enhanced code on GitHub](https://github.com/Dyl-flame10/CS300-DSA-Analysis-And-Design-DM/tree/Enhancement)

[← Back to ePortfolio home]({{ '/' | relative_url }})

---

## Describe the artifact

The course planner algorithm was a terminal-based application originally designed to sort through a course list composed of around 100 unique courses. During CS-300, we were tasked with finding the ideal data structure to fit the course planner and I chose a vector. Vectors are memory efficient and support index look-ups for quick sorting. The original sorting algorithm is a hand-rolled form of bubble sort. At the time, the sort was fine as it was only searching through 100 records. However, at a time complexity of O(n^2) in all cases, scaling the project would be a problem. The printCourses and printCourse functions do as they would imply, print a list of courses from the course vector and print one or more courses relevant to user input.

## Why I selected this artifact

I chose this artifact because it was a prime opportunity to showcase my ability to improve a sub-par algorithm. The previously mentioned inefficiency of the bubble sort will only scale as the course list grows. However, I also wanted to illustrate a deeper understanding of choosing between different algorithms by weighing their differences.

## The enhancements I made

The original sorting algorithm was baked into the printCourses function, which is not generally a good practice as the function does more than the name would imply.

<img width="657" height="424" alt="image" src="https://github.com/user-attachments/assets/073b7846-0657-4cf8-9ed5-187025693511" />

To fix this, I first separated the sorting and printing functions to better adhere to single responsibility principles. I then changed the sorting algorithm from bubble sort to quicksort with the pivot element being the last element's course ID. This algorithm is based on the lomuto partition scheme where one pointer tracks elements in a list smaller than the pivot and the other traverses the vector. The partition function handles the sorting, and the quicksort function acts as the recursion driver as it sorts. sortCourses is the wrapper to translate the original course list.

# Sorting Functions (last element)

<img width="690" height="601" alt="image" src="https://github.com/user-attachments/assets/66bf2426-e820-4b23-833d-927c1526ee9f" />

On top of this, I also created another version of the algorithm where the pivot element is selected by the median of the first, middle, and last element's course ID. Other than this change the partition scanning, recursion, and printing functions all remain the same.

# Sorting Functions (median of three)

<img width="665" height="858" alt="image" src="https://github.com/user-attachments/assets/532917b7-1355-4166-803e-f9058f924c53" />

To compare the two quicksort variants as well as the original bubble sort, I also created a benchmark script to test the performance on a 5,000, 20,000, and 50,000 element sample vector. This compares the three algorithms in comparisons, element swaps, recursion depth, time(milliseconds), and a bool on whether the list is sorted or not. On top of this, I created different scenarios where the list is shuffled, sorted in ascending order, sorted in descending order, and only has 10-distinct course IDs. The 10 distinct index keys (course IDs) highlight the weakness in all three algorithms in dealing with duplicate keys. The benchmark also includes a comparison in total comparisons growth from 5,000 to 50,000 elements in the list. This comparison highlights how unsuited bubble sort is for this use case and how different pivot points preform in different vector iterations.


```
```

## Reflection on the process

[View the enhancement Narrative and Reflection](https://github.com/Dyl-flame10/CS300-DSA-Analysis-And-Design-DM/blob/Enhancement/CS-499%20Enhancement%202%20Narrative.pdf)

---

[← Back to ePortfolio home]({{ '/' | relative_url }})
