# Game - Programming Assignments Private Repository
### Student Information
  + Name: Jacob Tucker
  + USC Email: jacobtuc@usc.edu
  + USC ID: 8578893431 

### Game Information
  + Game Name: StarTrek
  + Game Description: Follw the adventures of the starship enterprise through three levels of challenges.
  + [Game Design Doc](NewGameDesignDoc.md)


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
echo "./StarTrek"
```
###Grader Testing Notes
##Skipping Levels
There is a menu called "Grading" in the menu bar with buttons to allow the grader to skip to any of the levels so all the "things" can be observed without having to beat each level.

##High Scores
There is a sample high scores list provided with 10 high scores listed. No more than 10 high scores will be stored, so if you beat any of the ones in the file (it's not difficult - most are really low), they will replace the lowest value in the file. The file is called HighScores.txt, but should never be edited manually. If the file is removed, a new file will be created the first time the game is played.
