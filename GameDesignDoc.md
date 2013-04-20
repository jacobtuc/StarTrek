# A Game of Chicken
##Overview
This game will be a top-down game that will be modeled after the classic game of chicken as is often used to model brinkmanship.
The basic premise of the game is quite simple: there are two cars. the two start a set distance away from each other on a relatively straight road. The driver of each car accelerates toward the other. The first person to swerve is called the chicken and has lost the game.
The challenge of the game is to decide whether or not you think the other driver will swerve as you get closer.

####Landcape
![alt text](http://octodex.github.com/usc-spring2013-csci102/Images/Landscape.png "Landscape")

##The Cars/Basic Gameplay
###Introduction
There will be two cars. One car will be controlled by the user and the other will be controlled by the computer. The user will be able to select his or her style of car from the options displayed below. The computer's car will be selected randomly from the cars not selected by the user.

####Possible Cars:
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/Car1.png "Car 1")
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/Car2.png "Car 2")
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/Car3.png "Car 3")
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/Car4.png "Car 4")
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/Car5.png "Car 5")

###Controls
The user will have three controls:
* Accelerate: this will increase the speed of the user controlled car progressively.
* Swerve: This will make the card swerve off the road to avoid a collision with the other vehicle
* Throw out the steering wheel: This signals to the computer player that the user has no way of swerving to avoid the collission. This was a common strategy used by the original players of chicken to indicate they are completely commited to continuing forward. This action will alter the computer's strategy as described below.

###Collisions
A collision will occur if neither the computer nor the user decides to swerve. A collision will result in points and the loss of one life. Each player will have three lives. The method for determining scoring is described in detail in the **Scoring** section.

###Computer Strategies
The computer will select from the following strategies:
* Randomly decide whether or not it is going to swerve
* 75% chance it will swerve
* 25% chance it will swerve
* Throw out the steering wheel (indicates it definitely won't swerve)
* 100% swerve: it definitely won't swerve, but does not signal its intent to the user
* Fake swerve: looks like it's going to swerve, but changes its mind
If the computer decides to swerve, it will swerve at different distances from the user's car so the user cannot predict at what point the computer will swerve if it does.

###Steering Wheel
As described above, either player will have the ability to throw out the steering wheel. The possible steering wheels are listed below:
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/SW1.png "Steering Wheel 1")
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/SW2.png "Steering Wheel 2")

##Interfering Objects/Twists
The game will include two objects that will interfere randomly.

###Falling Rocks
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/Boulder.png "Boulder")
The boulder will roll down the hill. If the player accelerates normally (continually holds the acceleration key), the boulder will collide with the user's car and result in the loss of one life.

###Tumbleweed
![alt text](http://octodex.github.com/usc-spring2013-csci102/game_jacobtuc/Images/TumbleWeed.png "Tumbleweed")
The tumbleweed will also appear randomly, and if the user fails to avoid it, it will blind the user (all visuals will disappear so the user will in effect be driving blind).

##Scoring
The player will begin with 100 points. If his or her points fall to zero, they have lost the game. The following will result in increases or loss of points:
* Collision with the computer controlled car: -25
* Swerve: -15
* Win (Don't swerve and computer does swerve): +50

1 life will be lost for the following:
* Collission with the boulder
* Both the computer and the player swerves
* Collission between the two cars

