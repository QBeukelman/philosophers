

<h1 align="center">
	Dining Philosophers Problem
</h1>

<br />


In Computer Science, the dining philosophers problem is an example often used in concurrent algorithm design to illustrate synchronization issues and techniques
for resolving them. The example is summerised as followes, and will serve as the rules of the program.

A round table is occupied by one or more philosophers. The center of the table holds a large bowl of spaghetti. The philosophers engage in a cycle of eating, thinking, and sleeping. While eating, they cannot think or sleep. While thinking, they cannot eat or sleep. And while sleeping, they cannot eat or think.

Forks, equal in number to the philosophers, are also present on the table. As it is inconvenient to serve and eat spaghetti with only one fork, each philosopher uses the fork on their right and left to eat, holding one in each hand. After finishing their meal, a philosopher returns their forks to the table and begins to sleep. Upon awakening, they resume thinking. The simulation comes to an end when a philosopher dies due to starvation, or all philosophers have eaten must_eat times. Communication between the philosophers is not allowed, and the philosophers are unaware of the imminent death of another philosopher.


### Problems

- **Deadlock** each of the philosophers pick up a fork, no one can eat, hence, a deadlock.

- **Starvation** if a philosopher is not able to eat within the time limit, the philosopher may die.


### Possible Solutions

1. Resource Hierarchy Solution &emsp; <-- used below
2. Arbitrator Solution
3. Chandy/Misra Solution


<br />


# Installation

To run this project, you will need to have a C compiler installed on your machine. Then, clone the repository and navigate to the project directory:

```bash
git clone https://github.com/QBeukelman/philosophers.git
cd philosophers
```

Finally, compile the program using the makefile:

```go
make
```

<br />


# Usage

```c
./philo 5  400 100 100  5
        +---|---|---|---|-- philo_nb
            +---|---|---|-- time_die
                +---|---|-- time_eat
                    +---|-- time_sleep
                        +-- must_eat (optional)
```

- `num_philosophers`: The number of philosophers at the table.
- `time_to_die`: The time in milliseconds after which a philosopher dies of starvation.
- `time_to_eat`: The time in milliseconds it takes for a philosopher to eat.
- `time_to_sleep`: The time in milliseconds it takes for a philosopher to sleep.
- `must_eat`: Optional argument. The number of times each philosopher must eat before the simulation ends. If not specified, the simulation runs until a philosopher dies or is interrupted.

<br />


# Performance

### CPU

Run top (table of processes) or htop to view the cpu to see which processes utilize CPU at that moment. It is useful to allow the philosophers to eat for a long time, giving us time to analyse the open process, use the below, or a similar input.

```bash
./philo 5 400 100 100 5
```

Open a seperate terminal and run


```bash
top
htop
```

<br />


# How it works

Each philosopher is represented by an instance of t_philo struct, and contains one fork, as pthread_mutex_t. Each t_philo contains a pointer to t_data, the environment variables.

For every philosopher a thread is created using pthread_create(), which accepts the ft_simulation_thread() function, representing the philosophers lifecycle, to run in each thread. The philosohpers lifecycle is shown below.

<pre>

                      │    time_die
                      │    400 ms
                      │
                      │
            ┌─────┐   │ │  time_think
Thinking    │     │   │ │  *   ms
            └─────┘   │ │
                      │
            ┌─────┐   │ │  time_sleep
Sleeping    │     │   │ │  100 ms
            └─────┘   │ │
                      │
            ┌─────┐   │ │  time_eat
Eating      │  P  │   │ │  100 ms
            └─────┘   │ │

            ┌─┐ ┌─┐   ┌─┐
            │F│ │F│   │1│  meal_count
            └─┘ └─┘   └─┘
</pre>

<br />

