# ECE759Project

## Programs:
  * randMatrix.c
    * ./randMatrix.exe r c
    *   input: row and col size
    *   output: random matrix of row x col, output to crtMatrix.txt
  * mvMatrix.c
    * ./mvMatrix r c mov
    *  input: row size, col size, amount of moves to make
    *  output: multiple matricies to the same file movingMatrix.txt
    *  **BE VERY CAREFUL ON SIZE OF MATRIX AND AMOUNT OF MOVEMENT, THIS CODE IS NOT OPTIMIZED FOR MEMORY!**
* input_file.c
    * ./gen_file SIZE numCreatures
    *   input: dimension of one side of the board and number of creatures
    *   output: characteristics of all creatures written to same file
* check.c
    * ./gen_file SIZE numCreatures
    *   input: dimension of one side of the board and number of creatures
    *   output: characteristics of all creatures written to same file
* movement.c
    * ./move SIZE numCreatures
    *  input: dimension of one side of the board and number of creatures
    *  outut: new characteristics of all creatures written to a file
      


HOW TO RUN JAVA CODE
    *  Compile: javac *.java     
    *  variables need to set:  in CreatureComponent.java, line 17 SIZE,line 18 COL, line 19 ROW
    *                          in CreatureViewer.java, line 13 WIDTH,line 14 HEIGHT   
    *  Usage: java CreatureViewer 
    *  input: image files written by c program
    *  outut: void
