#ifndef HIGHSCORESLIST_H
#define HIGHSCORESLIST_H

#include <string>
#include <iostream>
#include <fstream>

/**A struct to hold a name and a score. This is
* used to implement the HighScoresList class.
* @author Jacob Tucker*/
struct Item {
    std::string name_;
    int score_;
    Item* next_;
};

/**This is a priority queue that stores the high scores. It
* will only hold ten at a time and will remove the lowest score
* when there are 11 scores in the list. Printing to and reading
* from the high scores file is also done from this class.
* @author Jacob Tucker*/
class HighScoresList {
public:
    /**Default constructor*/
    HighScoresList();
    /**Inserts a score into the list if it is large enough.
    * @return True if the score was placed in the list. False otherwise.*/
    bool insert(std::string name,int score);
    /**Prints the list of high scores to the high scores file*/
    void printFile();
    /**Reads the file where high scores are stored if it exists.
    * Every score in the file will be inserted into the list. This
    * does not clear the list first, so anything in the file will be
    * added to what's already in the list if it has already been created.*/
    void readFile();
    /**Returns the size of the list*/
    int size();
    /**Returns the name at the given location
    * @param index The index of the score to be retrieved
    * @param score A reference to the integer where you want the player's score stored*/
    std::string at(int index, int& score);

private:
    int size_;
    Item* head_;
    void removeLastItem();
};

#endif
