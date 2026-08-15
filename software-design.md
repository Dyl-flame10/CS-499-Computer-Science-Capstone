---
layout: default
title: Software Design and Engineering
permalink: /software-design/
---

# Software Design and Engineering

**Category:** Software Design and Engineering  
**Artifact:** Travlr Getaways 
**Original course:** CS-465 Full Stack Development  
**Repository:** [View the enhanced code on GitHub](https://github.com/Dyl-flame10/CS-465-Full-Stack-Development-DM/tree/Enhancement)

[← Back to ePortfolio home]({{ '/' | relative_url }})

---

## Describe the artifact

The Travlr Getaways project is an online travel booking application built with Express, Handlebars rendering, and an Angular administrative single-page application for editing trip data.  
## Why I selected this artifact


Creating this artifact taught me a lot about building larger applications with multiple modules and components working together. However, there were some architectural concerns
that were not addressed during the course as well as a few bugs/security vulnerabilities in the app. Firstly, the JWT verification needed to be addressed. Originally, the verification was hand-rolled into a function which manually split the Authorization header, check for malformed values, and called the JWT verify function with a callback. Failures called sent a 401 status automatically, bypassing Express's error pipeline.

<img width="640" height="694" alt="image" src="https://github.com/user-attachments/assets/2aab5816-2328-4779-8ec3-a018d6ece083" />

Additionally, the PUT /trips/:tripCode method did not have an auth check, which could allow trips to be edited without a valid token. Other route controllers also created their own error shape (res.status(xxx).json({})) on every failure branch, and Mongoose promises that were rejected had no error handling. This was an area to showcase an improvement with my understanding and skills in defensive programming. For a real instance of an app like this, it would be imperative to auth requests on both the UI and server side as well as ensuring the failures are shaped correctly and notify when they happen. In short, the middleware of the application was all manually implemented and specified for specific parts of the API, leaving large auth and error handling holes in the application. As an aside, there are a few logic bugs within the angular components (app_admin) and rendering errors on the public facing cite (app_server).



## The enhancements I made

[What did you change, concretely? Name classes, functions, structures, or queries.
Screenshots or short before/after code snippets go a long way here. 2–3 paragraphs.]

The idea behind this enhancement was to better follow the separation of concerns and single responsibility principles as well as create a uniform error handling structure, aside from a few front-end issues on the SPA and public cite, the bulk of changes are in the app_api folder. 

# Before: 
<img width="302" height="290" alt="image" src="https://github.com/user-attachments/assets/8c249f82-9efc-4f62-96de-a63ce7a8a646" />

# After:
<img width="291" height="412" alt="image" src="https://github.com/user-attachments/assets/4c008361-e6af-43b3-bffb-eb4f32cf33e3" />

The Travlr API middleware was completely restructured to separate the responsibilities of the API into separate modules in the new "middleware" and "error" folders. auth.js is a newly implemented JWT authentication layer the properly uses the library and error pipeline, plugging the previously missed edge cases not accounted for in the manual implementation. APIError.js gives the controllers all a single vocabulary to reference when encountering a program failure, ensuring consistent error shapes. ErrorHandler.js is the single place responsible for turning any error into an HTTP response. Each of these new modules represent one task in token authorization and the error handling instead of one file tangling all three responsibilities together, which also removed the boilerplate res.status().json repeated in the controller branches. Finally, wrapping the async controllers in the new asyncHandler module, adding a try/catch block to passport.js, and adding auth to the tripCode request all showcase defensive programming practices.

```

```

## Reflection on the process

[View the enhancement Narrative and Reflection](https://github.com/Dyl-flame10/CS-465-Full-Stack-Development-DM/blob/Enhancement/Travlr%20Enhancement%201%20Narrative.pdf)

---

[← Back to ePortfolio home]({{ '/' | relative_url }})
