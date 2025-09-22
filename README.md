# Computer-Graphics-Lab

This repository contains my personal experiments and practice code while learning **Computer Graphics**, following the [LearnOpenGL](https://learnopengl.com/) tutorials and related resources.  
The goal is to explore rendering techniques, practice modern OpenGL, and build a deeper understanding of computer graphics concepts.

---

## Project Overview
- A collection of test programs and experiments in **OpenGL**.
- Code follows along with **LearnOpenGL** and extends into custom experiments.
- Serves as a sandbox for learning and exploration in **Computer Graphics**.

---

## Libraries & Tools
This project makes use of the following libraries:
- **OpenGL 3.3** (Core Profile)
- **GLFW** – window & input management
- **GLAD** – OpenGL function loader
- **GLM** – mathematics library for graphics (vectors, matrices, transformations)
- (additional libraries may be added as experiments grow)

---

## Build & Run
To build and run the examples:

```bash
# Clone the repository
git clone https://github.com/danierumr/Computer-Graphics-Lab.git
cd Computer-Graphics-Lab

# (Example for Linux / Mac, with CMake)
mkdir build && cd build
cmake ..
make
./YourExecutable
