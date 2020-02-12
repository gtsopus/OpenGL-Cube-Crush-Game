# OpenGL-Cube-Crush-Game (VraXaPsa)

![](/Screenshots/1.PNG)

VraXaPsa is a 3D OpenGL game developed as a project for Computer Graphics and Interactive Systems, an undergraduate course in Computer Science and Engineering Department, University of Ioannina (2019). It is a candy/jewel crush like game using the rules of a classic rock-paper-scissors game with a twist.

## Installation

The game requires OpenGL,g++ and make in order to be properly installed.
Additionally it requires freeglut3 which is installed by using:
>sudo apt-get install freeglut3 freeglut3-dev

## Rules/How to play
Rock destroys scissors. Paper destroys rock. Scissors destroy paper.

![](/Screenshots/2.PNG)


To begin, press right click and click start from the menu. Click one cube to "select" it and then click a neighbouring cube to exchange them. 
Using the arrow keys, the user can view the board from different angles.
* If there is a triplet of colored cubes in a row, they get destroyed and you get points.
* If there is a bomb next to the triplet, you lose 30 points.
* When a cube is destroyed it gets filled by a blank (black) cube.
* If you exhange a blank cube and a textured cube (paper/scissors/rock) and there is a "weaker" textured cube next to it, it gets destroyed.
* If there is a textured cube triplet: 
  * All cubes except "stronger" cubes get destroyed in 1 cube radius.
  * All "weaker" textured cubes get destroyed in 3 cube radius.
  
  
![](/Screenshots/3.PNG)
  
## Credits
stb_image.h library used is made by:

https://github.com/nothings/stb/blob/master/stb_image.h
