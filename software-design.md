---
layout: default
title: Software Design and Engineering
permalink: /software-design/
---

# Software Design and Engineering

**Category:** Software Design and Engineering  
**Artifact:** Travlr Getaways 
**Original course:** CS-465 Full Stack Development  
**Repository:** [View the enhanced code on GitHub](https://github.com/Dyl-flame10/CS-465-Full-Stack-Development-DM/tree/Enhancement))

[← Back to ePortfolio home]({{ '/' | relative_url }})

---

## Describe the artifact

The Travlr Getaways project is an online travel booking application built with Express, Handlebars rendering, and an Angular administrative single-page application for editing trip data.  
## Why I selected this artifact

[Why did this artifact belong in the ePortfolio? Which specific components show off
your software design and engineering skills? 1–2 paragraphs.]
Creating this artifact taught me a lot about building larger applications with multiple modules and components working together. However, there were some architectural concerns
that were not addressed during the course as well as a few bugs/security vulnerabilities in the app.

## The enhancements I made

[What did you change, concretely? Name classes, functions, structures, or queries.
Screenshots or short before/after code snippets go a long way here. 2–3 paragraphs.]

The enhancement's main goal was to restructure the app-api middleware to better align single responsibility and separation of concerns principles. Additionally, the JWT authentication was originally hand-rolled with many issues such as bypassing error-handling in Express and no defined crypto algorithm. The enhancement fixes this by implementing the built-in library to centralize the error path and cover the missed error cases in the hand-rolled version.

```
// Optional: a short before/after snippet
```

## Course outcomes

[Did you meet the course outcomes you planned to meet in your Module One enhancement plan?
If your plan changed, say so and explain the update. Map each enhancement to the
specific outcome it satisfies.]

## Reflection on the process

[What did you learn? What was harder than expected? What would you do differently?
1–2 paragraphs.]

---

[← Back to ePortfolio home]({{ '/' | relative_url }})
