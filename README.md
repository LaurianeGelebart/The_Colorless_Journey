# The Colorless Journey - A Firefly Story
Created by Lauriane Gélébart - IMAC2 2023

Template from https://julesfouchy.github.io/Learn--OpenGL/

## The Projet 
This project is a semester-end assignment for engineering students in the IMAC program at ESIEE Paris, focusing on the subjects of OpenGL, image synthesis, and clean coding in C++.
The project is individual and serves as a practical application of the concepts learned in the mentioned subjects.

The main objective of this project is to develop a Boids visualization application that enables both the observation of boid behavior and interactive navigation within a 3D environment. The project allows for creative freedom in terms of visual design.
All objects and textures used in the project were created using Blender and Photoshop.

In this project, I have interpreted the concept as creating a paper-themed mode where colors have disappeared. Our protagonist, guided by fellow fireflies, possesses the power to bring back light and restore colors to this universe.

## Project Structure

The project's main content is located in the `projet` directory. This directory contains the following subdirectories:

- `shaders`: Contains the necessary OpenGL shaders used in the project.
- `programs`: Contains the programs used in the project.
- `cpp and hpp files`: Includes all the C++ and header files related to the project, including the main file.

In addition to the `projet` directory, the project's root directory contains the following files and directories:

- `Makefile`: The Makefile used for compiling and building the project.
- `assets`: Contains additional project assets.
  - `textures`: Stores textures used in the project.
  - `models`: Stores 3D models used in the project.

Please note that this is a simplified representation of the project structure and may not include all the files or directories present in your specific project.


## Setting up

### Creating a repository

First, create your own repository based on this one. If you are using GitHub you can use this repository as a template:

![image](https://user-images.githubusercontent.com/45451201/217287736-20058d69-f0ed-40ff-b4e5-cfd852e2ba82.png)

Otherwise simply create a repository on your own and copy-paste all the files in this repo to your new repo.

### Downloading your repository

Run this command inside the directory where you want to put this project:

```
git clone your_repo_url
```

### Compiling

If that is not already done, [install a compiler](https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/install-a-compiler/).

If that is not already done, [setup your IDE for C++ development](https://julesfouchy.github.io/Learn--Clean-Code-With-Cpp/lessons/ide/).

Once that is done, open the project folder in your IDE: it will detect the CMakeLists.txt file automatically and you can just run the project:
![image](https://user-images.githubusercontent.com/45451201/217290500-bd09bc81-861f-4da9-b3c6-fef5e28a83f6.png)
