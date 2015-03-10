#include <iostream>
using namespace std;
#ifndef MOVIETREE_H
#define MOVIETREE_H

struct MovieNode{
    int ranking;
    string title;
    int year;
    int quantity;
    MovieNode * right;
    MovieNode * left;
    MovieNode * parent;
};

class MovieTree
{
    public:
        MovieTree();
        ~MovieTree();
        void printMovieInventory();
        void addMovieNode(int, string, int, int);
        MovieNode* searchMovieTree(string, MovieNode *);
        void rentMovie(string);
        void buildTree();
        void printMovie(MovieNode*);
        MovieNode *root;
        void restoreTree(MovieNode*);
        void deleteNode(MovieNode*);
        void countMovies(MovieNode*, int* );
        void deleteAll(MovieNode*);

    protected:
    private:
};

#endif // MOVIETREE_H