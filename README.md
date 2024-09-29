# 42 Philosophers Project

![example of execution](https://github.com/shexweeknd/blob/blob/main/42-cursus-Philosophers/42-cursus-Philosophers-din.png)

This is a project for the 42 cursus that focuses on the dining philosophers problem. The goal of this project is to implement a solution to the problem using multithreading and synchronization techniques while writing a `C` program.

## Table of Contents

- [42 Philosophers Project](#42-philosophers-project)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Installation](#installation)
  - [Usage](#usage)
  - [Contributing](#contributing)
  - [License](#license)

## Introduction

The dining philosophers problem is a classic synchronization problem in computer science. It involves a group of philosophers sitting around a table, where each philosopher alternates between thinking and eating. The problem arises when each philosopher requires two forks to eat, but there are only a limited number of forks available.

In this project, we aim to solve this problem by implementing a solution using threads and mutex locks.

## Installation

Before any installation, make sure you are unsing an LTS stable Linux version that compiles C programs with `cc` compiler. If not, proceed with the following command on your terminal in order to install `cc` compiler:

`sudo apt install cc`

To install and run the philosophers project, follow these steps:

1. Clone the repository:
```sh
git clone https://github.com/shexweeknd/42-cursus-Philosophers.git
```

2. Navigate to the project directory:
```sh
cd 42-cursus-Philosophers/philo
```

3. Compile the project with the command:
```sh
make
```

4. Run the program:
```sh
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

## Usage

![example of execution](https://github.com/shexweeknd/blob/blob/main/42-cursus-Philosophers/42-cursus-Philosophers-eg.png)

Once the program is running, the philosophers will start their dining process. The program will output the actions of each philosopher, such as when they start eating, finish eating, start sleeping, etc. The program will terminate when a philosopher dies or when all philosophers have eaten the required number of times.

## Contributing

Contributions to the philosophers project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

![42](https://github.com/shexweeknd/blob/blob/main/42-cursus-Philosophers/42-cursus-Philosophers-42-logo.png)

This project is from 42 School Common Core Cursurs. I do not owe individually any of the concept mentionned above. Instead I owe the provided code in the repository.

Licensed under the [MIT License](LICENSE).
