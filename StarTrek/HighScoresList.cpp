#include "HighScoresList.h"

HighScoresList::HighScoresList()
{
    size_ = 0;
    head_ = NULL;
    readFile();
}

bool HighScoresList::insert(std::string name, int score)
{
    if (name.compare("") == 0)
    {
        return false;
    }

    if (head_ == NULL) //This is the first item
    {
        head_ = new Item;
        head_->name_ = name;
        head_->score_ = score;
        head_->next_ = NULL;
        size_ = 1;
        return true;
    }

    Item* temp = new Item;
    temp->name_ = name;
    temp->score_ = score;
    temp->next_ = NULL;

    Item* last = head_;
    Item* previous;
    if (last->score_ <= temp->score_)
    {
        temp->next_ = head_;
        head_ = temp;
        return true;
    }

    last = last->next_;
    previous = head_;
    bool found = false;
    while (last != NULL)
    {
        if (last->score_ <= temp->score_)
        {
            previous->next_ = temp;
            temp->next_ = last;
            found = true;
            break;
        }

        previous = previous->next_;
        last = last->next_;
    }//End while

    bool lastItem = false;
    if (!found) {
        previous->next_ = temp;
        lastItem = true;
    }

    size_++;

    if (size_ > 10)
    {
        removeLastItem();
        if (lastItem)
            return false;
    }
    return true;
    /*
    std::cout << "Moving through list" << std::endl;
    Item* conductor = head_;
    Item* previous = head_;
    while(conductor != NULL)
    {
        if(conductor->score_ >= score)
        {
            std::cout << "Score: " << conductor->score_ << std::endl;
            if (conductor != head_)
                previous = previous->next_;
            conductor = conductor->next_;
        } else {
            Item* newNode = new Item;
            newNode->name_ = name;
            newNode->score_ = score;
            newNode->next_ = conductor;
            previous->next_ = newNode;
            if (size_ == 10)
                removeLastItem();
            else
                size_++;
            return true;
        }
    }

    std::cout << "Adding at end of list" << std::endl;
    if (size_ < 10)
    {
        Item* newNode = new Item;
        newNode->name_ = name;
        newNode->score_ = score;
        newNode->next_ = NULL;
        previous->next_ = newNode;
        size_++;
        std::cout << "Inserted " << previous->score_ << std::endl;
        return true;
    }
    std::cout << "Did not insert" << std::endl;
    return false; */
}

void HighScoresList::printFile()
{
    std::ofstream myfile("HighScores.txt");

    Item* conductor = head_;
    while (conductor != NULL)
    {
        myfile << "\"" << conductor->name_ << "\" " << conductor->score_ << "\n";
        conductor = conductor->next_;
    }
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
    if (conductor == NULL)
        return;
    if (conductor->next_ == NULL)
        return;
    if (conductor->next_->next_ == NULL)
        return;

    while (conductor->next_->next_ != NULL)
        conductor = conductor->next_;
    Item* temp = conductor->next_;
    conductor->next_ = NULL;
    delete temp;
    size_--;
    /*
    Item* conductor = head_;
    Item* previous = head_;
    for (int n = 0; n < size_; n++)
    {
        if (n != 0)
            previous = previous->next_;
        conductor = conductor->next_;
    }
    delete conductor;
    previous->next_ = NULL; */
}
