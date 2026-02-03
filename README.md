*This project has been created as part of the 42 curriculum by tstelken.*

# Philosophers

## Description

This project implements the **Dining Philosophers Problem** using threads and mutexes in C. The goal is to learn how to handle **concurrency**, **synchronization**, and **timing** correctly while avoiding race conditions, deadlocks, and starvation.

Each philosopher is a thread that alternates between eating, sleeping, and thinking while competing for shared forks. The simulation stops when a philosopher dies or when all philosophers have eaten a required number of times.

## Instructions

### Compile

```bash
make
```

### Run

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [must_eat]
```

Example:

```bash
./philo 4 410 200 200 2
```

## Resources

* Linux manual pages (`pthread`, `gettimeofday`, `usleep`)
* Dean Ruina: "The Dining Philosophers Problem" (Medium)
* Jamshidbek Ergashev: "Philosophers, 42 Schoool Project" (YouTube)
* Oceano: "The dinig Philosophers in C: threads, race conditions and deadlocks" (YouTube)
* AI tools were used for debugging and understanding concurrency issues. All implementation and final decisions were made by the author.
