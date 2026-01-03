# Legend of the Lost Code

**Author:** Fernando 908697  
**Course Project:** RPG Game in C

## Description
Legend of the Lost Code is a console-based, turn-based RPG written in C.  
The player explores different areas, fights enemies using dice-based mechanics, completes missions, manages inventory and gold, and ultimately faces the Dark Lord in a final battle.

## Features
- Turn-based combat system  
- Multiple areas and missions (Swamp, Mansion, Cave)  
- Player, enemies, inventory, and shop system  
- Save/load system  
- Cheat system  
- Final boss encounter  
- Modular project structure  

## Project Structure
.
├── Makefile
├── README.md
├── assets/ # Game data and helpers
├── include/ # Global headers and constants
├── src/ # Source code (game logic)
│ ├── combat
│ ├── core
│ ├── entities
│ ├── items
│ ├── menus
│ ├── save_system
│ ├── utils
│ └── world
└── docs/ # Design and Doxygen documentation

## Compilation
This project uses a Makefile.

make
Running the Game
After compilation, run:

- ./shadow_dungeon
Or use:
- make run

Debug Mode
To display the detected source files:
- make debug

Documentation
Doxygen configuration files are available in:
- docs/Doxygen/

Notes
- Written in standard C
