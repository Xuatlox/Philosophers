*This project has been created as part of the 42 curriculum by ansimonn*

# Content

### 1. [Description](#description)

### 2. [Instructions](#instructions)

### 3. [Resources](#resources)

# Description

## Presentation

## Bonus features

In the bonus part I chose to add enemies to the game that will be represented as "X" on
the .ber map descriptor. They will try to chase the player to get him to be stuck somehow.

But the player can deal with them once he has collected every collectible on the map.
Once he gets all of them, he will unlock his final form, allowing him to beat enemies on
his way. The enemies will flee from the player once he gets to this point of the game
because, well, they don't want to face this and die.

# Instructions

To compile all the file needed you must use the `make` or `make bonus` command, whether you want
or not the bonus version. It will create object files directly into the `obj` or `bonus_obj` folder and
compile them to get your `so_long` binary at the root of the project.

From there you only need to execute it by executing the following command:

`$> ./so_long map.ber`

You can use the `make clean` command to delete all .o files in the obj folder, or the `make fclean` to also
delete the `so_long` binary.

The `make re` command will execute the `make fclean` command, and then recreate every object files and
the `so_long` binary.

# Resources

I chose not to use AI as I usually do, because I prefer to look for all the resources I need
by my own, so my references websites are here:

- https://franckh.developpez.com/tutoriels/posix/pthreads/#LI


- 
