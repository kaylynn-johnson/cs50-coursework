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
 
### 🔄 CS50W — Web Programming with Python and JavaScript
> *In Progress*
 
Covers Django, JavaScript, and modern web application architecture.
 
### 🔄 CS50AI — Introduction to Artificial Intelligence with Python
> *In Progress*
 
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
├── cs50w/        # Web Programming (in progress)
└── cs50ai/       # AI with Python (in progress)
```
 
