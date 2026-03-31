*This project has been created as part of the 42 curriculum by ansimonn*

# Content

### 1. [Description](#description)

### 2. [Instructions](#instructions)

### 3. [Resources](#resources)

# Description

This project is centered around Edsger Dijkstra's "Dining philosophers problem".
In this problem, a given number n of philosophers is sitting at a round table with
n plates of spaghetti in front of them. N forks are placed between each one of them.
Every single philosopher has 3 actions to do in an infinite cycle that ends if the start
of his last meal is too far in the past. In these cycles, a philosopher takes the forks
on his right and on his left to eat his spaghetti for a given amount of time, then he
needs to sleep for another given amount of time before thinking. 

If at any given point in the simulation a philosopher hasn't started eating since the
starvation time given in the program's arguments, the simulation ends immediately. That
means a philosopher can die while he is sleeping or even eating depending on the situation.

The program must be executed with 4 or 5 arguments if the user wants or not to specify a
maximum number of meals before the simulation ends. The arguments are in the following order:


- nb_philos : the number of philosophers we want to have for this simulation


- time_to_die : the maximum amount of time a philosopher can spend without dying of starvation


- time_to_eat : the time a philosopher spends eating


- time_to_sleep : the time a philosopher spends sleeping


- (optional) nb_meals : the program will end by itself when every philosopher reaches this
specific number of meals if specified

# Instructions

To compile all the files needed you must use the `make` command. It will create object
files directly into the `obj` folder and compile them to get your `philo` binary at the
root of the project.

From there you only need to execute it by executing the following command:

`$> ./philo nb_philos time_to_die time_to_eat time_to_sleep [nb_meals]`

You can use the `make clean` command to delete all .o files in the obj folder, or the `make fclean` to also
delete the `philo` binary.

The `make re` command will execute the `make fclean` command, and then recreate every object files and
the `philo` binary.

# Resources

I chose not to use AI as I usually do, because I prefer to look for all the resources I need
by my own, so my references websites are here:

- https://franckh.developpez.com/tutoriels/posix/pthreads/#LI


- https://wormav.github.io/42_eval/Cursus/Philosophers/index.html


- https://medium.com/@ruinadd/philosophers-42-guide-the-dining-philosophers-problem-893a24bc0fe2
