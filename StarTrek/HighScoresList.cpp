#include "HighScoresList.h"

HighScoresList::HighScoresList()
{
    size_ = 0;
    head_ = NULL;
    readFile();
}

bool HighScoresList::insert(std::string name, int score)
{
    std::cout << "Inserting..." << std::endl;
    if (head_ == NULL) //This is the first item
    {
        head_ = new Item;
        head_->name_ = name;
        head_->score_ = score;
        head_->next_ = NULL;
        size_ = 1;
        std::cout << "Inserted head" << std::endl;
        return true;
    }

    Item* conductor = head_;
    Item* previous = head_;
    while(conductor != NULL)
    {
        if(conductor->score_ >= score)
        {
            if (conductor != head_)
                previous = previous->next_;
            conductor = conductor->next_;
        } else {
            previous->next_ = new Item;
            previous->next_->name_ = name;
            previous->next_->score_ = score;
            previous->next_->next_ = conductor;
            if (size_ == 10)
                removeLastItem();
            else
                size_++;
            return true;
        }
    }

    if (size_ < 10)
    {
        previous->next_ = new Item;
        previous = previous->next_;
        previous->name_ = name;
        previous->score_ = score;
        previous->next_ = NULL;
        size_++;
        std::cout << "Inserted " << previous->score_ << std::endl;
        return true;
    }
    std::cout << "Did not insert" << std::endl;
    return false;
}

void HighScoresList::printFile()
{
    std::cout << "Printing file" << std::endl;
    std::ofstream myfile("HighScores.txt");

    Item* conductor = head_;
    while (conductor != NULL)
    {
        std::cout << "  Printing " << conductor->name_ << " " << conductor->score_ << std::endl;
        myfile << "\"" << conductor->name_ << "\" " << conductor->score_ << "\n";
        conductor = conductor->next_;
    }
    std::cout << "File printed" << std::endl;
}

void HighScoresList::readFile()
{
    std::ifstream myfile("HighScores.txt");
    if (myfile.is_open())
    {
        while(!myfile.eof())
        {
            std::string trash;
            //char* trash;
            getline(myfile,trash,'"');
            //myfile.getline(trash,1,"\"");
            std::string nm;
            //char* nm;
            getline(myfile,nm,'"');
            //myfile.getline(nm,1000,"\"");
            int score;
            myfile >> score;
            insert(std::string(nm),score);
            std::cout << "Name: " << nm << " Score: " << score << std::endl;
        }
    }
}

int HighScoresList::size()
{
    return size_;
}

std::string HighScoresList::at(int index, int& score)
{
    if (index > size_-1)
    {
        score = -99;
        return "";
    }
    Item* conductor = head_;
    for (int n = 0; n < index; n++)
    {
        conductor = conductor->next_;
    }
    score = conductor->score_;
    return conductor->name_;
}

void HighScoresList::removeLastItem()
{
    Item* conductor = head_;
    Item* previous = head_;
    for (int n = 0; n < size_; n++)
    {
        if (n != 0)
            previous = previous->next_;
        conductor = conductor->next_;
    }
    delete conductor;
    previous->next_ = NULL;
}
