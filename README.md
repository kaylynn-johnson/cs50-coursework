# cs50-coursework
 
Self-directed coursework from Harvard's CS50 program, completed independently alongside my professional work in aerospace and mission operations.
 
## Courses
 
### ✅ CS50x — Introduction to Computer Science
> *Completed February 2026 to May 2026*
 
Harvard's foundational CS course covering C, Python, SQL, and web basics. Problem sets span memory management, data structures, algorithms, and full-stack web development.
 
**Topics covered:** C, Python, Flask, SQL, HTML/CSS/JavaScript
 
**Final Project — [FRC Field Supervisor Dashboard](https://github.com/kaylynn-johnson/frc-field-dashboard)**
 
A real-time operations dashboard for FIRST Robotics Competition field supervisors, built with Flask, HTMX, SQLite, APScheduler, and Playwright. The application polls The Blue Alliance API every 60 seconds to track match schedule adherence, displaying time ahead/behind as a color-coded delta for at-a-glance situational awareness during live events.
 
The standout feature is an automated fuel counting pipeline: at match start, a one-shot APScheduler job launches a headless Chromium browser via Playwright, screenshots the event's live webcast, and sends the image to the Anthropic vision API to count game pieces in the neutral zone. A DVR seek strategy compensates for Playwright startup latency by rewinding the YouTube stream to match start regardless of when the job fires. Supervisors can also manually upload field photos for counting. Post-event, a separate analytics page surfaces schedule performance stats (average delta, volatility, on-time streaks) and fuel count trends across all monitored events.
 
Built to operate under real event conditions: loud environment, divided attention, no menu navigation during matches.
 
### ✅ CS50W — Web Programming with Python and JavaScript
> *Completed June 2026 to August 2026*

Harvard's follow-on course focused on backend and frontend web development. Problem sets cover models, views, and templates in Django; JavaScript-driven frontend interactivity; and building, testing, and deploying full-stack web applications.

**Topics covered:** Django, PostgreSQL, JavaScript, HTML/CSS, testing, CI/CD, scalability

**Final Project — [StrideSync](https://github.com/kaylynn-johnson/stride-sync)**

A full-stack cardio-playlist generator that matches songs to a user's running or walking pace, built with Django, PostgreSQL, and vanilla JavaScript. Users input a cardio pace, which is converted to a target BPM via cadence-matching, then used to filter a dataset of approximately 550,000 songs (sourced from Kaggle's Spotify audio features/metadata) by tempo, genre, decade, and popularity — all without a page reload.

Playlists carry a fixed target tempo set at creation; adding a song outside that tempo range triggers a warning with an explicit override, keeping playlists musically coherent rather than just a running list of favorites. Playlists can be shared publicly via a unique link, with view/edit access controlled by ownership. The project is containerized with Docker.

Built to explore the gap between "ops person who codes" and full-stack software engineering: real data modeling decisions and frontend/backend separation via a JSON API.
 
### 🗓️ CS50AI — Introduction to Artificial Intelligence with Python
> *Planned*
 
Covers search algorithms, machine learning, neural networks, and NLP.
 
---
 
## Why CS50?
 
My background is in spacecraft operations and systems engineering. As I've moved toward software engineering, I've used CS50 to formalize fundamentals that fill gaps between professional scripting and production software development — particularly in lower-level programming (C), algorithms, and web architecture.
 
These courses complement the portfolio projects at [github.com/kaylynn-johnson](https://github.com/kaylynn-johnson), which apply these skills in aerospace and data engineering contexts.
 
---
 
## Structure
 
```
cs50-coursework/
├── cs50x/        # Introduction to Computer Science
├── cs50w/        # Web Programming
└── cs50ai/       # AI with Python (planned)
```
 
