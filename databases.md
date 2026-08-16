---
layout: default
title: Databases
permalink: /databases/
---

# Databases

**Category:** Databases  
**Artifact:** Grazioso Salvare AAC Animal Dashboard 
**Original course:** CS-340 Client/Server Development 
**Repository:** [View the enhanced code on GitHub](https://github.com/Dyl-flame10/CS-340-Client-Server-Development-DM/tree/Enhancement)

[← Back to ePortfolio home]({{ '/' | relative_url }})

---

## Describe the artifact

The Grazioso Salvare AAC animal dashboard is a Dash/Python application used to interact with an External MongoDB of rescue animal records. The dashboard includes a filtered record listing data table, a breed-pie chart relevant to the user's query, and an interactive map of the animals' location.

## Why I selected this artifact

I chose this artifact because it represents an opportunity to improve the database and data layer flaws of the application. The animal records were originally sent as full documents to the client side for aggregation for the data table and pie chart. Additionally, the record attributes include a few redundant fields that can be desynced in update requests. This makes a great target for database normalization. The database instance also had no form of schema validation, meaning attributes that would be considered required can be null and be added to the DB. 

## The enhancements I made

On the data layer, the AnimalShelter CRUD module was extended well beyond its original four methods: read() gained skip, limit, and sort parameters to support fetching a bounded slice of results instead of everything matching a query; a new count() method wraps count_documents for getting totals without fetching documents; and a new aggregate() method runs pipelines directly on the server. On the database side, a migration ran a single aggregation-pipeline update_many that computed and backfilled a rescue_category array field onto all 10,000 documents based on the existing breed/sex/age rules, followed by an index on that field. A $jsonSchema validator was then applied via collMod, enforcing required fields, types, and allowed values on every future insert or update. The redundant age_upon_outcome and monthyear fields were dropped from the data entirely, leaving age_upon_outcome_in_weeks and datetime as the sole sources of those facts.


<img width="716" height="757" alt="Screenshot 2026-08-15 211233" src="https://github.com/user-attachments/assets/7ad01c30-ac4c-401a-a862-5e36151680bd" />

<img width="760" height="1011" alt="Screenshot 2026-08-15 212138" src="https://github.com/user-attachments/assets/a060594a-bf30-4e0d-83ba-7a7bb3dd6106" />

<img width="833" height="122" alt="Screenshot 2026-08-15 212751" src="https://github.com/user-attachments/assets/00fe173e-2596-4b2b-9ef5-71c47e3e0470" />


On the dashboard side, the notebook's callbacks were rewritten around those new capabilities. update_dashboard no longer rebuilds a three-field compound query per filter click — it does a single equality match against rescue_category and now also takes page_current/page_size as inputs, fetching only one page of results per call instead of the full filtered set. update_graphs was decoupled from the table entirely: instead of reading whatever rows the table already had loaded, it runs its own $match+$group aggregation and builds the pie chart from just the resulting {breed, count} pairs. The DataTable itself switched from native to custom pagination, which forced filter_action/sort_action to 'none' (Dash rejects the alternative combination outright) and required a new callback to reset the page to 1 and display a record/page count whenever the filter changes


<img width="771" height="678" alt="Screenshot 2026-08-15 213648" src="https://github.com/user-attachments/assets/1277a9a8-e772-4a2c-8fe5-a5f455d90989" />

<img width="722" height="496" alt="Screenshot 2026-08-15 213723" src="https://github.com/user-attachments/assets/388c9ed1-8cf6-4a26-89e4-a2ce5ec1cc2c" />

<img width="722" height="496" alt="Screenshot 2026-08-15 213723" src="https://github.com/user-attachments/assets/35dcc2bb-fb4c-4876-a67f-9306faf8693e" />

---


## Reflection on the process

[View the enhancement Narrative and Reflection](https://github.com/Dyl-flame10/CS-340-Client-Server-Development-DM/blob/Enhancement/CS499%20Enhancement%203%20Narrative.pdf)

---

[← Back to ePortfolio home]({{ '/' | relative_url }})
