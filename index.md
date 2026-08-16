---
layout: default
title: Dylan's CS-499 ePortfolio
---

# Computer Science Capstone ePortfolio

**Southern New Hampshire University — CS-499**

[Self-Assessment](#professional-self-assessment) ·
[Code Review](#code-review) ·
[Software Design & Engineering](#artifact-one--software-design-and-engineering) ·
[Algorithms & Data Structures](#artifact-two--algorithms-and-data-structures) ·
[Databases](#artifact-three--databases)

---

## Professional Self-Assessment

[Write 3–5 paragraphs here. Things to cover, based on the rubric:]

- What drew you to computer science and how the program shaped your goals.
- How building this ePortfolio helped you showcase your strengths and shape your professional goals.
- Collaborating in a team environment.
- Communicating with stakeholders.
- Data structures and algorithms.
- Software engineering and database work.
- Security mindset.
- A closing paragraph that ties the three artifacts below together and explains how, as a set, they represent the full range of your computer science skills.

The computer science program at SNHU has greatly helped me understand both the technical and soft skills required in the computer science industry. As someone planning to transition from another field, the coursework that I have done throughout my time in the program has given me the opportunity to develop and hone my skills that can help me in pursuing a career in web development. Additionally, the process of creating this ePortfolio has also given me the chance to reflect on the projects I have worked on, the principles and mindsets I have learned, and how important soft skills are in this line of work.

The coursework in the program covered a lot of the key aspects of the industry as I see it. throughout all of my technical courses, interacting with my peers in the weekly discussion topics helped me develop a new angle to view ideas the differ from mine. Reading though various posts regarding new and exciting technology or reflections on infamous cyberattacks expanded my appreciation to consider every aspect of a topic or project, even if it differs from your own ideas or findings, as previously unseen value or a resolution to a dispute may be discovered. Instructor feedback was also a great resource to guide my thinking and development workflows into more efficient sessions. Another aspect I learned particularly from my System Analysis and Design class (CS-255) taught me the value of being able to communicate systems development to different audiences, mainly non-technical audiences such as consumers or other stakeholders. After taking this course, I view meeting with stakeholders as more of a dialogue than any regular reporting. It taught me how important it is to focus on the operational conversations and to discuss problems or stakeholder conflict directly, as problems untouched or hidden can cause damage further down the dev cycle. Diversity is another aspect of communication I have strengthened greatly because of these courses. A shareholder meeting may look like written reports about cost, ROI, problems, etc. This typically differs from stakeholders, who have varied interests or expectations on a project, requiring different presentations to effectively communicate progress or concerns. To summarize, working in system design classes like CS-255 have greatly expanded my communication skills in knowing how to adapt between technical and non-technical audiences.

The three key areas of this ePortfolio, software engineering & design, algorithms and data structures, and databases, are all foundational skills required for any form of development role. While the artifacts presented in this ePortfolio are key examples of improvement in these areas, there were other projects from other courses that help me develop these skills. For example, in my Mobile Architect & Programming course (CS-360), I was tasked with creating weight tracking application that allowed users to record their weight once per day and analyze their progress towards a specific goal. Despite mobile programming never really appealing to me at the time, I found this course to be one I enjoyed most. It was the first course I was required to develop a full, functional application with multiple components that need to communicate with each other. Designing the UI really taught me about the emphasis that should be placed on accessibility when designing client-facing applications. The backend of the project was also originally tough for me, but I value what I learned from it. This is where I really began to develop an object-oriented approach to programming, learning how to develop reusable components with minor modifications to streamline the development process as well as make it easier should other developers need to modify the program. my Intro to Struct Databases (DAD-220) course was also pivotal to learning how to navigate SQL and NoSQL DBs, structuring queries, and emphasizing important principles like data normalization and defining relationships. My Secure Coding (CS-405) course was also great in developing my understanding of what unsafe code looks like and how to keep on top of evolving digital threats. Aside from the artifacts, many of the courses in the computer science program at SNHU have taught me plenty of technical and soft skills/principles to help me in future career endeavors. I only look to continue to build on this foundational knowledge in the future.

The three artifacts presented in this ePortfolio below are all projects from the program that were flawed or could be improved upon in ways relevant to the three computer science categories: Software Design & Engineering, Algorithms & Data Structures, and Databases. Before explaining the enhancements made, I created a code-review going over each codebase, highlighting the areas of concern and discussing the plan to enhance the project. The first artifact is Travlr Getaways from CS-465, an online travel booking application that features a client-facing express UI, rendered using Handlebars, and an Angular admin single-page application that allows logged in users to edit and add trip listings. I chose this artifact to represent software design & engineering because I believe it provided the best opportunity to showcase my skills and understanding of good design principles. Originally, Travlr's auth and error handling was written in a per-instance basis, leaving a lot of redundant code and open edge cases. The enhancement greatly emphasizes the importance of the separation of concerns and single responsibility design principles of software engineering by creating a centralized reuseable middleware for the Express and Angular sides to work with.

The second artifact regarding algorithms and data structures is a console-based course planner algorithm used to sort a list of courses and print one or many records from the data structure. This was part of my CS-300 class focused on algorithmic design and data structures. This artifact was inherently flawed and needed to be revised. The original sort algorithm was not only baked into the print function but was also grossly inefficient for the use-case in ALL cases. Instead of simply implementing an algorithm with a better fit. I decided to use two different variants of a quicksort algorithm and design a performance benchmark to compare the two along with the original. This is one of my personal favorite enhancements as it expands on simply fixing an inefficient solution by providing complementary data to back up a decision.

Finally, the third artifact regarding databases is the Grazioso Salvare AAC Animal Dashboard project from CS-340. This project is a client-facing UI using the Dash framework to access rescue animal records from an external MongoDB instance. It features a data table with an accompanying interactive map to geolocate animals in the Austin, TX area as well as a pie chart showing the breed spread of the selected query. This project was also very inefficient when transferring data between the server and client as well has redundant attributes in the schema. This artifact was chosen to represent the database section because the enhancment implements integral modern DB elements and principles such as schema validation, server-side aggregation, and database normalization.

---

## Code Review

Before enhancing each artifact, I performed a code review walking through the existing
functionality, identifying weaknesses and limitations, and outlining my planned
enhancements for each of the three categories.

**▶ [Watch the code review](https://youtu.be/Y07bWIF6CzQ)**

---

## Artifact One — Software Design and Engineering

**Artifact:** Travlr Getaways · **Original course:** CS-465 Full Stack Development

Travlr Getaways is an online travel booking application built to plan vacations for customers. Travlr also has an accompanying admin page for editing trip data. The app is built using Express, Handlebars rendering, and Angular.

**Enhancements:** Restructured middleware, centralized error handling/HTTP response, general bug fixes 

<!-- Buttons: swap the URLs, leave the rest alone -->
[Enhanced Repository](https://github.com/Dyl-flame10/CS-465-Full-Stack-Development-DM/tree/Enhancement){: .btn }
[Full Narrative]({{ '/software-design/' | relative_url }}){: .btn }

---

## Artifact Two — Algorithms and Data Structures

**Artifact:** Course Planner Algorithm · **Original course:** CS-300 DSA: Analysis and Design

The course planner algorithm was designed to sort and look-up a number of courses. in my time in CS-300, we were tasked with finding the ideal data structure for the planner, which I determined to be a vector due to the low memory overhead.

**Enhancements:** Swapped sorting algorithm, added comparable algorithms, created an algorithm preformance comparison script

[Enhanced Repository](https://github.com/Dyl-flame10/CS300-DSA-Analysis-And-Design-DM/tree/Enhancement){: .btn }
[Full Narrative]({{ '/algorithms-data-structures/' | relative_url }}){: .btn }

---

## Artifact Three — Databases

**Artifact:** Grazioso Salvare AAC Animal Dashboard · **Original course:** CS-340 Client/Server Development

The Grazioso Salvare AAC Animal Dashboard is an animal rescue DB dashboard designed to help employees find a suited animal for a rescue case. It was built in Python using common libs such as Pandas and MatPlotLib. The UI is also built using the Dash framework. The project interacts with an external MongoDB instance to retrieve shelter records.

**Enhancements:** Normalized record attributes, added server-side aggregation, schema validation, pagination

[Enhanced Repository](https://github.com/Dyl-flame10/CS-340-Client-Server-Development-DM/tree/Enhancement){: .btn }
[Full Narrative]({{ '/databases/' | relative_url }}){: .btn }

---

## Contact

[Dylan Mousseau] · [mousseaudylan@gmail.com] · [github.com/Dyl-flame10](https://github.com/Dyl-flame10) · [LinkedIn]([your linkedin url])
