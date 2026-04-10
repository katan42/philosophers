*This project has been created as part of the 42 curriculum by ka-tan.*

# 🍽️ Philosophers

> *I never thought philosophy would be so deadly.*

This project focuses on the mandatory part of the subject:
building the **Dining Philosophers simulation** in **C** using **threads** and **mutexes**.  
It is basically a concurrency project where multiple philosophers compete for shared resources (forks) without causing **data races**, **deadlocks**, or incorrect timing.


---

## 📖 Description

The goal of **Philosophers** is to simulate philosophers sitting around a round table, where they repeatedly:
- 🍔 **eat** 
- 💤 **sleep**
- 💭 **think**

To eat, each philosopher needs **two forks**:
- one on the **left**
- one on the **right**

Since forks are shared resources, the challenge is not the actions themselves, but how to coordinate them safely.

This project teaches the fundamentals of:
- **multithreading**
- **mutex protection**
- **shared state management**
- **precise timing in milliseconds**
- **avoiding race conditions**
- **designing a simulation that stops correctly when a philosopher dies or when everyone has eaten enough**
---


---


---
## 🧠 Concepts 

###  Why ....
When several threads run at the same time, they may try to:
- read the same data
- write to the same data
- lock the same forks
- print at the same time
- update meal times at the same time

Without proper protection, this creates **race conditions**.
...

---

### Core concurrency ideas

#### 1. Threads
Each philosopher is a separate **thread** in the mandatory part. 
That means all philosophers run "at the same time" within one process and share the same memory space.

#### 2. Mutexes
A **mutex** is a lock used to protect shared resources.

In this project, mutexes are commonly used for:
- each **fork**
- shared simulation state such as **stop/death flags**
- synchronized **printing**
- shared counters like **meals eaten** or **last meal time**

Only one thread should hold a fork mutex at a time.

#### 3. Race conditions
A **race condition** happens when multiple threads access the same data without proper synchronization, and the final result depends on timing.

Example:
- one thread updates `last_meal`
- another thread checks whether the philosopher has died

If these happen without protection, the monitor may read stale or inconsistent data.

---

#### 4. Deadlock
A **deadlock** can happen if every philosopher picks up one fork and waits forever for the second fork.

A classic way to reduce this risk is to avoid making all philosophers lock forks in the exact same order.

For example:
- odd philosophers take left then right
- even philosophers take right then left

Or:
- delay some philosophers slightly at startup
- use a careful locking strategy

---

#### 5. Starvation
Even if deadlock is avoided, a philosopher may still **starve** if they never get both forks in time.

So the program must not only “run”, but also behave fairly enough under the subject rules.

---

#### 6. Time management
This project depends heavily on **accurate timestamps in milliseconds**.

You will usually need:
- a function to get the current time in ms using `gettimeofday`
- a custom sleep loop for better precision than raw `usleep`
- regular checks to stop the simulation as soon as death is detected

---

### A simple mental picture

Think of the table like this:

```text
 fork   philo   fork   philo   fork   philo
   \      |       /       |       /      |
         shared resources around one table
```

Every philosopher wants the same pattern:

```text
take fork -> take fork -> eat -> sleep -> think -> repeat
```

The difficulty is that neighbors share forks, so one philosopher’s action directly affects another.


### A simple mental picture



---

## 🛠️ Instructions

1. To Compile
```bash
make
```
2. Run
```bash
./philo 5 800 200 200
```
```bash
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]
```

3. Clean object files
```bash
make clean
```

4. Remove all generated files
```bash
make fclean
```

5. Rebuild from scratch
```bash
make re
```

---

## ▶️ Usage examples

### Basic test
```bash
./philo 5 800 200 200
```

This means:
- 5 philosophers
- a philosopher dies if they do not eat within 800 ms
- eating takes 200 ms
- sleeping takes 200 ms
- simulation stops only when someone dies

---

### Stop after everyone has eaten enough
```bash
./philo 5 800 200 200 3
```

This means the simulation should stop once **all philosophers** have eaten at least **3 times**.


## 📚 Resources

References used to understand the project topic:

- **Dining Philosophers Problem** - overview of the classic concurrency problem
	https://youtu.be/FYUi-u7UWgw?si=Zyj2PtbOu7kjfB73
- **Multithreading in C Programming** - understanding `pthread_create`, `pthread_join`, and shared memory
	https://youtu.be/ldJ8WGZVXZk?si=Pob4iJJDmuyovqW-
- **Multithreading vs Multiprocessing** - https://youtu.be/PgDaJEjlBuI?si=ZipVwPLfujuvr3WB
- **Concurrency vs Parallerism** - https://youtu.be/RlM9AfWf1WU?si=FHJ61dVyrrKsxj0q
- **Mutex lock** - understanding mutual exclusion and critical sections
	https://youtu.be/9axu8CUvOKY?si=10_3IHeio6AXwBdB
	
AI was used for:
- clarifying concepts such as **threads, mutexes, race conditions, deadlocks, and starvation**
- notebook LLM to review concepts and strengthened concepts in an interactive/podcast


---
## 🌱 Final thought

...
