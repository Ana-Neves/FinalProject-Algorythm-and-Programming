
# Arcade Brick Breaker 🧱👾

Welcome to the **Arcade Brick Breaker** repository! This project is an Arkanoid/Breakout-style arcade game developed as the Final Project for the **Algorithms and Programming** course at the Federal University of Rio Grande do Sul (UFRGS). 

It was built entirely in **C** utilizing the **Raylib** library for graphics and hardware acceleration.

## 🎯 Project Overview

The objective of the game is to control a horizontal platform at the bottom of the screen to bounce a ball upwards, destroying various configurations of bricks without letting the ball fall off the screen. 

The game emphasizes the use of fundamental programming concepts such as pointers, custom data structures (`structs`), file handling (text and binary), and modularized architecture.

## ✨ Features

- **Custom Levels:** Levels are loaded dynamically from text matrices (`.txt` files), allowing easy creation of new challenges.
- **Dynamic Physics:** Accurate ball collision and bounce angles against walls, the platform, and bricks.
- **Multiple Brick Types:** Includes indestructible bricks and breakable bricks requiring varying amounts of hits (1 to 4 collisions).
- **Power-Ups:** - 🔥 *Fireball:* Destroys any breakable brick in a single hit.
  - 📏 *Platform Expansion:* Temporarily doubles the size of the player's platform.
  - 🎱 *Extra Balls:* Spawns additional balls on the screen to multiply the destruction.
- **Save & Load System:** Save your current game state (score, lives, remaining bricks) into a binary file to resume later.
- **High Scores:** Tracks and displays the Top 5 highest scores in a local file.

## 📂 Repository Structure

```text
📦 FinalProject-Algorythm-and-Programming
 ┣ 📂 assets       # Contains game assets, including level maps (e.g., fase_1.txt)
 ┣ 📂 docs         # Project documentation, diagrams, and final reports
 ┣ 📂 src          # Source code files (.c) and headers (.h)
 ┣ 📜 .gitignore   # Specifies intentionally untracked files to ignore
 ┣ 📜 LICENSE      # MIT License
 ┗ 📜 README.md    # This documentation file

```
## 🛠️ Requirements & Installation
To compile and run this game, you need a C compiler (gcc or clang) and the **Raylib** library installed on your system.
### macOS (Intel)
You can install Raylib using Homebrew:
```bash
brew install raylib

```
## 🚀 How to Run
 1. **Clone the repository:**
   ```bash
   git clone [https://github.com/Ana-Neves/FinalProject-Algorythm-and-Programming.git](https://github.com/Ana-Neves/FinalProject-Algorythm-and-Programming.git)
   cd FinalProject-Algorythm-and-Programming
   
   ```
 2. **Compile the game (macOS Intel example):**
   Run the following command in the terminal at the root of the project:
   ```bash
   clang src/main.c -o jogo -I/usr/local/include -L/usr/local/lib -lraylib -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL
   
   ```
   *(Note: The compilation command may vary depending on your Operating System and Raylib installation path. If using Windows or Linux, ensure you link the -lraylib flag correctly).*
 3. **Execute:**
   ```bash
   ./jogo
   
   ```
## 🎮 Controls
 * Left Arrow or A: Move platform left.
 * Right Arrow or D: Move platform right.
 * S: Save current game state.
 * ESC: Exit or return to the main menu.
   
## 👥 Authors
 * **Ana Caroline Neves** - *Computer Science Undergraduate at UFRGS*
 * **Helena Kambundi** - *[Collaborator's Title/Info]*
   
## 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.
```

