# Chess Matchmaking (Swiss Format)
## What is it?
A terminal based C++ tool for managing chess tournaments held using the Swiss format. It is capable of handling players, matchmaking and tracking scores.

## Stats

![Version](https://img.shields.io/badge/Version-1.1.1-blue.svg)
![Status](https://img.shields.io/badge/Status-Completed-green.svg)

## File Structure
```bash
📂Swiss Format Manager
 ┣ 📂 data
 ┃  ┣ 📄 players.csv           # Contains all player data
 ┃  ┗ 📄 standings.csv         # Stores final standings
 ┣ 📂 include                  # Contains all header files
 ┣ 📂 scripts                  
 ┃  ┗ 📄 compiler.py           # Compiles all C++ files and runs the exe file if needed
 ┣ 📂 source 
 ┃  ┣ 📄 main.cpp              # Main driver file
 ┃  ┣ 📄 csvreader.cpp         # Connects the tool with the csv file (read and write)
 ┃  ┣ 📄 players.cpp           # Defines a player object
 ┃  ┣ 📄 matchmaking.cpp       # Contains the main matchmaking algorithm
 ┃  ┣ 📄 round.cpp             # Responsible for starting the round, setting results and going to the next round
 ┃  ┣ 📄 tournament.cpp        # Application that connects all units together to make the project 
 ┃  ┗ 📄 console_utils.cpp     # A list of console utility functions for better UX
 ┣ 📄 CHANGELOG.md             # Version history
 ┗ 📄 README.md                # You’re looking at it 😎 (Current version details)
```

## How to Run
- First of all, ensure that the latest version of Python and MinGw C++ compiler are installed.
- To start the application, run the `scripts/compiler.py` file.

## Inspiration
I recently took part in a casual chess tournament that used the Swiss system for matchmaking. The organizers were using a digital tool to track player scores and match progress — it was clean, minimal, and super efficient.

That got me curious.<br>
👉 How does the Swiss format actually work?<br>
👉 What kind of logic powers the matchmaking?<br>
👉 Could I build a tool like that myself?<br>

So I decided to explore the entire system from scratch — understanding the rules, structure, and pairing logic. This project is the result of that deep dive.<br>

My goal? To create a lightweight, beginner-friendly Swiss Tournament Manager that works for:
- 🏆 Serious tournament tracking
- 🏡 Casual home games with friends and family

Whether you're a chess enthusiast or just organizing a fun event, I hope this tool makes your tournament experience smoother and smarter. ♟️💻

## Roadmap
- [x] Assigning colours to players
- [x] Display players based on colours assigned
- [x] Sonneborn-Berger tie breaker check

## Contribution
Feel free to make an edit or change to this project to improve its stability. You may do so by first pulling a request or an issue to talk about it. All are welcome!
