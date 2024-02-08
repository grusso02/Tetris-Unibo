# Progetto 2023/2024 - Tetris

### Membri del gruppo

    mattia.mercuriali2@studio.unibo.it
    luca.marangon2@studio.unibo.it
    gabriele.russo11@studio.unibo.it

This project is a simple and classic implementation of the famous ASCII Tetris game, made using the C++ programming languagen and ncurses library.

# Requirements

  * g++
  * Make
  * cmake 3.0 or newer
  * Ncurses library

## Installed Ncurses

Linux
```
sudo apt-get install libncurses5-dev libncursesw5-dev
```
MacOS
```
brew install ncurses
```

# Compilation

The code can be compiled using the script build.sh in the root dir.

```
./build.sh
```

# Execution

To start the game:

```
./run.sh
```

# Menu command

You can navigate through menu items using the up and down arrow keys and spacebar to select.
'Play' to start the game.
'Scores' to view the top 10 scores.
'Exit' to close the game.

# Game command

Use the arrow keys to move and rotate the Tetromino.<br>
Press KEY_RIGHT to move right.<br>
Press KEY_LEFT to move left.<br>
Press KEY_UP to rotate.<br>
Press SPACEBAR to make the Tetromino fall to the floor.<br>
Press 'E' to exit the game.
