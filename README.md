# Generic-Genetic-Algorithm
This is just a C++ implementation of a Generic Genetic Algorithm. Implemented a Singleton Class with all the information about the simulated population. 

Runs with an arbitrary mathematical function and finds its maximum using variable mutation rate. It also has a graphical user interface (GUI) that shows each generation as the algorithm runs. The big red dot is the best fit individual and the green ones are his children, the function itself is shown in the background.

![Demonstrational GIF](https://github.com/Guerreiroo/Generic-Genetic-Algorithm/blob/main/demo/demo.gif "Algorithm demonstration")

The program can also render some useful plots showing the population progress through the generations.

![Fitness Evolution Plot](https://github.com/Guerreiroo/Generic-Genetic-Algorithm/blob/main/demo/fitness.png "Fitness Evolution Plot")
![Mutation Rate Evolution Plot](https://github.com/Guerreiroo/Generic-Genetic-Algorithm/blob/main/demo/mutationRate.png "Mutation Rate Evolution Plot")

# How to run it

First, you're gonna need to install GLUT and GNUPLOT. In Ubuntu, you just need to run:

```bash
sudo apt-get install freeglut3 freeglut3-dev binutils-gold gnuplot -y
```

After this, you can compile and run it with:

```bash
mkdir build && cd build && mkdir data plots
cmake ..
make
./Genetic_Algorithm <gui|nogui>
```

## Settings

You can enable/disable the GUI in source/main.cpp by altering the runTextMode variable.

```cpp
const bool runTextMode = false;
```

You can also change some general settings about the population in header/genetic_algorithm.hpp

```cpp
constexpr size_t POP_SIZE = 10;        // The size of the population
constexpr float MUTATION_RATE = 0.2f;  // Starting mutation rate
```

Lastly, you can create your own function to be maximized by the algorithm by changing the Population::EvaluateGene() function in source/genetic_algorithm.cpp. The default function is the following:

```cpp
// benchmark function
FitType Population::EvaluateGene(Gene x) {
    return ((2.0f * cos(0.039f * x) + 5.0f * sin(0.05f * x) + 0.5f * cos(0.01f * x) + 10.0f * sin(0.07f * x) + 5.0f * sin(0.1f * x) + 5.0f * sin(0.035f * x)) * 10.0f + 500.0f);
}
```

## Running in windows 10 with WSL 2

I'd recommend using VcXsrv, you're going to need to create a firewall inbound rule allowing TCP communication through port 6000 (on the windows side) and fix some X11 forwarding issues (on the WSL 2 side). There's a nice tutorial [here](https://stackoverflow.com/questions/61110603/how-to-set-up-working-x11-forwarding-on-wsl2).


