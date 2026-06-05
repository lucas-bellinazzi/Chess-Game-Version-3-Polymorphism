# C++ Chess Game (Version 3 - Polymorphism)

A terminal-based chess game written in **C++** that demonstrates object-oriented programming (OOP) principles, specifically **polymorphism** and inheritance. The game renders a visual chess board in the terminal using Unicode chess symbols and processes game moves through a custom algebraic move parser.

---

## Key Features

* **Polymorphic Architecture**: Chess pieces inherit from a common abstract base class (`Piece`), defining their movements dynamically.
* **Terminal Board Rendering**: Beautiful visual feedback using custom Unicode characters to represent the pieces on the board.
* **Special Chess Rules**:
  * **En Passant**: Supported with historical pawn-move verification.
  * **Castling**: Implemented for both King-side (Short Castle) and Queen-side (Long Castle).
  * **Check Detection stubs**: Groundwork for check validation.
* **Dual Execution Modes**:
  * **Interactive Mode**: Input moves turn-by-turn directly in the CLI.
  * **File Replay Mode**: Parse and replay chess games from recorded input files (e.g., `input.dat`).
* **Cross-Platform Compilation**: Supports both **Windows** (Command Prompt, PowerShell, Git Bash) and **Linux/macOS** through a single Makefile.

---

## Repository Structure

The project has been organized into clean directories separating interface/header declarations from implementation code:

```
├── include/                   # Header files (.h / .hpp)
│   ├── piece.h                # Abstract base class for chess pieces
│   ├── pawn.h                 # Pawn class header
│   ├── knight.h               # Knight class header
│   ├── bishop.h               # Bishop class header
│   ├── rook.h                 # Rook class header
│   ├── queen.h                # Queen class header
│   ├── king.h                 # King class header
│   ├── board.h                # Chess board management
│   ├── terminalPrint.hpp      # Terminal printing utility
│   ├── dataFileReader.hpp     # File parser helper
│   ├── abort.hpp              # Error handling helper
│   ├── myTypes.hpp            # Type definitions helper
│   └── numbers.hpp            # Number helper functions
├── src/                       # Source implementation files (.cpp)
│   ├── main.cpp               # Game controller and main loop
│   ├── pawn.cpp               # Pawn movement logic
│   ├── knight.cpp             # Knight movement logic
│   ├── bishop.cpp             # Bishop movement logic
│   ├── rook.cpp               # Rook movement logic
│   ├── queen.cpp              # Queen movement logic
│   ├── king.cpp               # King movement logic
│   └── board.cpp              # Board setup, moves, castling, and En Passant logic
├── input.dat                  # Sample move file
├── Makefile                   # Cross-platform Makefile
├── LICENSE                    # GPL-3.0 License details
└── README.md                  # This file
```

---

## Build & Compilation

To build and compile the application, you will need a C++ compiler (`g++` supporting C++11 or newer) and `make` installed on your machine.

### Windows (CMD, PowerShell, or Git Bash)
Open your terminal in the project directory and run:
```bash
make
```
This generates the `Chess.exe` executable.

### Linux / macOS
Open your terminal and run:
```bash
make
```
This generates the `Chess` executable.

### General Makefile Commands
* **Build Project**: `make` or `make all`
* **Clean Object Files**: `make clean`
* **Run Executable**: `make run`
* **Memory Check (Linux/macOS)**: `make valgrind` (runs Valgrind memory diagnostic tool)

---

## How to Run & Play

The application supports two play modes. You can configure which mode to use by modifying the `readType` variable inside [src/main.cpp](file:///c:/Users/lucas/Documents/LUCAS/Chess-Game-Version-3-Polymorphism/src/main.cpp#L26).

### 1. Interactive Mode (Default)
In [src/main.cpp](file:///c:/Users/lucas/Documents/LUCAS/Chess-Game-Version-3-Polymorphism/src/main.cpp#L26), verify the variable is set to:
```cpp
bool readType = viaTerminal;
```

**To compile and run**:
```bash
make clean
make
make run
```
Once launched, the board prints to the console, and players take turns entering moves when prompted:
```text
   a  b  c  d  e  f  g  h  
 ---------------------------
1| ♜  ♞  ♝  ♛  ♚  ♝  ♞  ♜ |1
2| ♟  ♟  ♟  ♟  ♟  ♟  ♟  ♟ |2
3| -  -  -  -  -  -  -  - |3
4| -  -  -  -  -  -  -  - |4
5| -  -  -  -  -  -  -  - |5
6| -  -  -  -  -  -  -  - |6
7| ♙  ♙  ♙  ♙  ♙  ♙  ♙  ♙ |7
8| ♖  Cap  ♔  ♕  ♔  ♔  ♘  ♖ |8  (Rendering depends on local terminal font/Unicode stubs)
 ---------------------------
   a  b  c  d  e  f  g  h  

White Team Move: e4
```
* Type `end` at any time to exit the game.

### 2. File Replay Mode
To replay a match recorded in a `.dat` file (such as `input.dat`):
1. In [src/main.cpp](file:///c:/Users/lucas/Documents/LUCAS/Chess-Game-Version-3-Polymorphism/src/main.cpp#L26), set the variable to:
   ```cpp
   bool readType = playFromFile;
   ```
2. Recompile the project:
   ```bash
   make clean
   make
   ```
3. Run the executable, passing the path to the move file as an argument:
   ```bash
   # Windows
   .\Chess.exe input.dat

   # Linux/macOS
   ./Chess input.dat
   ```

---

## Chess Move Notation Guide

The game expects moves in **standard English algebraic notation**. Since the internal parser decodes English abbreviations, make sure to use the letters specified in the table below:

| Piece | Symbol | Notation Prefix | Example Move | Description |
| :--- | :---: | :---: | :--- | :--- |
| **Pawn** | ♙ / ♟ | *None (lowercase col)* | `e4` | Pawn to e4 |
| **Knight** | ♘ / ♞ | **N** | `Nf3` | Knight to f3 |
| **Bishop** | ♗ / ♝ | **B** | `Bc4` | Bishop to c4 |
| **Rook** | ♖ / ♜ | **R** | `Rd1` | Rook to d1 |
| **Queen** | ♕ / ♛ | **Q** | `Qh5` | Queen to h5 |
| **King** | ♔ / ♚ | **K** | `Ke2` | King to e2 |

### Notation Examples
* **Basic movement**:
  * `e4`: Move pawn to `e4` square.
  * `Nf3`: Move knight to `f3`.
  * `Bc4`: Move bishop to `c4`.
* **Captures**:
  * `exd4`: Pawn on column `e` captures opponent piece on `d4`.
  * `Nxf3`: Knight captures opponent piece on `f3`.
* **Castling**:
  * King side (Short Castle): Move the King to the target square (e.g. `g1` / `g8` / file `g` row `1` or `8`).
  * Queen side (Long Castle): Move the King to the target square (e.g. `c1` / `c8` / file `c` row `1` or `8`).

> [!NOTE]
> When multiple pieces of the same type can move to the same square, the parser automatically attempts to move the first piece of that type. If that move is invalid under chess rules, it attempts the move with the second piece of that type.

---

## Technical Design: Polymorphism in Action

Each chess piece inherits from the `Piece` abstract class. Polymorphism is used to decouple the board execution flow from the individual rules of each piece:

```mermaid
classDiagram
    class Piece {
        <<abstract>>
        -movesCount: int
        -_row: int
        -_col: int
        -color: char
        +validateMove(final_row, final_col, board)* bool
        +toString()* string
    }
    class Pawn {
        +validateMove() bool
        +toString() string
    }
    class Knight {
        +validateMove() bool
        +toString() string
    }
    class Bishop {
        +validateMove() bool
        +toString() string
    }
    class Rook {
        +validateMove() bool
        +toString() string
    }
    class Queen {
        +validateMove() bool
        +toString() string
    }
    class King {
        +validateMove() bool
        +toString() string
    }
    
    Piece <|-- Pawn
    Piece <|-- Knight
    Piece <|-- Bishop
    Piece <|-- Rook
    Piece <|-- Queen
    Piece <|-- King
```

* **`validateMove`**: Implemented by each subclass to check if the target destination conforms to its move pattern (e.g., L-shape for `Knight`, straight lines for `Rook`, diagonals for `Bishop`).
* **`toString`**: Implemented by each subclass to output the correct Unicode character corresponding to the piece's type and team color.

---

## License

This project is licensed under the terms of the [GNU General Public License v3.0 (GPL-3.0)](LICENSE).
