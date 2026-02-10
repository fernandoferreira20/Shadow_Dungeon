# Shadow Dungeon

**Course Project:** RPG Game in C

## Authors
Mihai Alexandru Savin
Fernando Ferreira
Otajon Yuldashev
Harshit Soni

## Description
Shadow Dungeon is a RPG game written in C.  
The player explores different areas, fights enemies using dice-based mechanics, completes missions, manages inventory and coins, and ultimately faces the Dark Lord in a final battle.

## Features
- Procedural Generation: Dungeons are generated with enemies and traps.
- Combat System: Turn-based mechanics with dice rolls.
- Save System: Dynamic linked-list system to save/load progress.
- Missions: 3 unique missions plus a hidden Final Boss.
- Cheats: Konami code implementation to modify save states.

## Project Structure
.
├── Makefile
├── README.md
├── assets/     # Game data and helpers
├── include/    # Global headers and constants
├── src/        # Source code (game logic)
│ ├── combat
│ ├── core
│ ├── entities
│ ├── items
│ ├── menus
│ ├── save_system
│ ├── utils
│ └── world
└── docs/       # Design and Doxygen documentation

## Compilation
Method 1: Using Makefile
This project uses a Makefile.
To compile the game automatically:
- make

After compilation, run:
- ./shadow_dungeon
Or use:
- make run

Clean build files: make clean

Method 2: Manual Compilation
If make is not available, you can compile using the standard GCC command:
- gcc -Wall -Wextra -g -O2 -Iinclude -Isrc -Iassets -o shadow_dungeon src/combat/combat.c src/combat/final_boss.c src/core/game_engine.c src/core/main.c src/entities/enemies.c src/entities/player.c src/items/inventory.c src/items/shop.c src/menus/main_menu.c src/menus/menus.c src/menus/mission_menu.c src/save_system/cheats.c src/save_system/save_manager.c src/utils/input.c src/utils/random.c src/utils/utils.c src/world/dungeon.c src/world/missions.c src/world/village.c assets/game_data.c -lm

Debug Mode
To display the detected source files:
- make debug

## Documentation
Doxygen configuration files are available in:
- docs/Doxygen/

## Notes
- Written in standard C
