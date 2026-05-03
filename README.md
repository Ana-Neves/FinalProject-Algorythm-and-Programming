# Nebulosa Smasher 🌌🔨

## Project Description
**Nebulosa Smasher** is an arcade game inspired by the classic *Brick Breaker* genre, developed as the final project for the Algorithms and Programming course at UFRGS. Set in a deep-space mining scenario, the player controls a mining vessel that utilizes plasma pulses to fragment stellar debris and collect valuable minerals in distant asteroid belts.

The interface was designed with a "Quiet Luxury" space aesthetic, employing a palette of deep blues and earthy oranges to represent advanced technology and mineral resources.

## Mission
The player's mission is to clear the sector of debris before it compromises the ship's hull integrity. This project aims to apply advanced concepts of **Modularization in C**, data structures for collision management, and game state logic including Menu, Gameplay, and Game Over screens.

---

## Project Organization
To ensure academic efficiency and transparency, our team adopted the following tools and collaborative methods:

*   **GitHub**: Version control and hosting for source code and documentation.
*   **Lunacy**: Used for creating high-fidelity wireframes and defining the visual identity.
*   **Adobe Color**: Used for planning the "Nebulosa" color palette to ensure visual harmony.
*   **Discord**: Regular meetings to align strategies and discuss project progress.
*   **VS Code (Live Share)**: Facilitated real-time collaborative coding and code reviews.

---

## Project Structure

### 1. Visual Documentation
*   **Wireframe**: Located in `/docs`, it presents the 800x600 pixel layout with the 15x25 matrix arrangement.
*   **Game Map**: A logical diagram representing the occupancy of debris in space.

### 2. Visual Identity (Nebulosa Palette)
*   **Deep Space**: `#101126` (Background)
*   **Plasma Pulse**: `#0460D9` (Ball and HUD)
*   **Rare Minerals**: `#A4431F` (Ship and Special Bricks)
*   **Common Debris**: `#7A89A0` (Standard Bricks)

---

## Data Structure (Preview)
The game utilizes C structures to manage the global state:

*   **Ship (Nave)**: Stores the initial X position and dimensions (100x20 px).
*   **Pulse (Ball)**: Manages velocity vectors and collision radius (16x16 px).
*   **Debris Matrix**: An `int[15][25]` matrix where each value represents the mineral type and its resistance.

---

## How to Use

### Prerequisites
*   GCC Compiler.
*   **RayLib** library installed.

### Configuration Steps
1.  **Clone the Repository**
    ```bash
    git clone https://github.com/Ana-Neves/FinalProject-Algorythm-and-Programming.git
    cd FinalProject-Algorythm-and-Programming
    ```
2.  **Compilation**
    (Compilation instructions will be added upon completion of the `Makefile`).

---

## Contributors

*   **Ana Caroline Rodrigues Neves** — *Developer & Designer*
    *   [GitHub](https://github.com/Ana-Neves)
*   **[PARTNER NAME]** — *Developer*
    *   [GitHub](link)

---

## Conclusion
This project represents the effort to apply low-level programming logic to create an interactive and visually cohesive experience. **Nebulosa Smasher** is not just a gamePeço desculpas pela confusão! Ocorreu um erro técnico que gerou várias repetições do texto. Limpei tudo para você.


### License
This project is under the **MIT** license.
