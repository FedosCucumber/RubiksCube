# Rubick's Cube

This project is a simulation of a Rubik's cube 
 that was made a pet-project based on a university assignment. 
## Overview
The logical aspect of simulating and solving a cube was made using only c++ STl. Logicaly, the cube is represented as six matrices, each representing a side of a cube. Cube can be randomly shuffled and solved using a "genetic"-like algorithm. Visualy, cube is composed of 27 textured cubes (faces of me and my buddy were used for the texture just to show off). I Tried abstracting most of the raw OpenGl code into dedicated classes such as VertexBuffer, IndexBuffer, Rendrer etc. 
## Solver
Cube can be solved using an algorithm that ususe a population/mutation approach. A function, that counts the amount of stickers with different colour from the center sticker of a side is used as a metric.  A set of common combinations that are optimal for the used metric is used to apply random mutations on cubes until one of them is solved. While solving, a text representation of the current best variat is displayed in the console. After it a string with moves that will solve the initial cube is returned. On run, program uses both a console terminal to convey text data and a separate window to show the model. 

## Building
Project was made using visual studio. .sln file is included in the repository, hence to build you may use the visual studio tools to compile and change the code. The binaries can be found inside the repository. Note: binaries should not be downloaded withtout the whole project or used outside of the folder because of the various dependencies.  

There is a compiled .exe package for windows x64 with all the necessary files in the release section. An imgui.ini file may  be created on use. 
## Usage
The application provides a simple UI. 
![Alt Text](https://media.giphy.com/media/uUa6O8723yDMjQEeRO/giphy.gif) 
## Technologies used
The visual part of the project was made using OpenGL and various libs based on it: 
- C++ STL as the core structure of the project
- OpenGL Extension Wrangler Library (GLEW) for handling OpenGL itself
- OpenGL Mathematics (glm) was used for calculating projections, rotations, moves etc.
- OpenGL Shading Language (GLSL) was used, surpisingly, for making shaders
- Dear ImGui (ImGui) was used to create the UI 
- stb_image was used for working with textures 
## Notes
The file structure of the project leaves a lot ot be desired. Make using CMake is the way to go? Creating projects in visual studio seems a little bit "toy-ish"? Dunno. I am happy to accept any advice on the topic of file organization and using other techologies for project assembly to my email.
## License
[MIT](https://choosealicense.com/licenses/mit/)
