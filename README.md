Terminal_Game
=============

Repo for our ECE 2524 final group project. Members: Carlos Folgar, Dharik Patel,Daniel Al-Abdrabbuh, and Kevin Lee

This is an ASCII dodging game using the framework 'ncurses', where the player moves left or right to doge falling ASCII characters.The player
is the "X" and tries to dodge the falling "#". 
* The player is given five lives and collects points as time ticks by. 
* The game gets progressively harder.

In addition to this, we have provided a version of the game without ncurses to show our early prototype and to show everyone the benefits of using ncurses.

INSTALLATION
=============

On ubuntu, please install ncurses before running the program. It's easy to do:

sudo apt-get install build-essential libncurses5-dev
