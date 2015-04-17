#ifndef HASHTABLE_H
#define HASHTABLE_H

struct Movie{
    std::string title;
    int year;
    Movie *next;

    Movie(){};

    Movie(std::string in_title, int in_year)
    {
        title = in_title;
        year = in_year;
    }

};

class HashTable
{
    public:
        HashTable(int);
        ~HashTable();
        void insertMovie(std::string in_title);
        Movie* findMovie(std::string in_title, int *index);
        void deleteMovie(std::string in_title);
        void printInventory();
    protected:
    private:
        Movie *hashTable;
};

#endif // HASHTABLE_H
