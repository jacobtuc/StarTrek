# Game - Programming Assignments Private Repository
### Student Information
  + Name: Jacob Tucker
  + USC Email: jacobtuc@usc.edu
  + USC ID: 8578893431 

### Game Information
  + Game Name: Chicken
  + Game Description: First person to swerve is the chicken
  + [Game Design Doc](GameDesignDoc.md)


### Compile & Run Instructions
The grader should use the following procedure to compile and run the code:
```shell
#Compile Instructions
echo "qmake -project"
echo "qmake"
echo "make"
#Doxygen Instructions
echo "doxygen -g config.txt"
echo "doxygen config.txt"
#Command to run
echo "./game_jacobtuc"
```
###Grader Testing Notes
There is a widget built in to force the objects that decide whether to move randomly to move including the boulder, tumbleweed, and police car. There is also an option to force the computer car to swerve. The widget can be accessed by clicking View->Grading Tools in the menu bar of the main window.
