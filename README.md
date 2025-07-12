# Chess Matchmaking (Swiss Format)
## What is it?
A terminal based C++ tool for managing chess tournaments held using the Swiss format. It is capable of handling players, matchmaking and tracking scores.

## Stats

![Status](https://img.shields.io/badge/Status-In%20Development-yellow.svg)

## File Structure
```bash
�📂 Swiss Format Manager
 ┣ 📂 data
 ┃  ┗ 📄 test.csv              # Stores all player data
 ┣ 📂 include                  # Contains all header files
 ┣ 📂 scripts                  
 ┃  ┗ 📄 compiler.py           # Compiles all C++ files and runs the exe file if needed
 ┣ 📂 source 
 ┃  ┣📄 main.cpp               # Main driver file
 ┃  ┣📄 csvreader.cpp          # Connects the tool with the csv file (read and write)
 ┃  ┣📄 players.cpp            # Defines a player object
 ┃  ┣📄 matchmaking.cpp        # Contains the main matchmaking algorithm
 ┃  ┣📄 round.cpp              # Responsible for starting the round, setting results and going to the next round
 ┃  ┗📄 tournament.cpp         # Application that connects all units together to make the project 
 ┗ 📄 README.md                # You’re looking at it 😎 (Current version details)
```

## How to Run
- First of all, ensure that the latest version of Python and MinGw C++ compiler are installed.
- To start the application, run the `scripts/compiler.py` file.

## Roadmap
- [x] CSV generation
- [x] Calculate number of rounds
- [x] Matchmaking algorithm
- [x] Progressing the tournament (start round, set winners, end round)
- [x] Score tracking
- [x] Next round behaviours
- [ ] *Tie breakers*
- [ ] View standings and tournament ending

## Contribution
Feel free to make an edit or change to this project to improve its stability. You may do so by first pulling a request or an issue to talk about it. All are welcome!
