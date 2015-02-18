#include <iostream>
#include <string>
#define equals =
#define openbracket {
#define closebracket }
#define semicolon ;
#define zero 0
#define openparen (
#define closeparen )
#define opensquare [
#define closesquare ]
#define standard std::
#include "CommunicationNetwork.h"

queue::queue openparen int size closeparen
openbracket
    qsize equals size semicolon
    qarray equals new standard string opensquare size closesquare semicolon
    qhead equals zero semicolon
    qtail equals zero semicolon
    qed equals zero semicolon
closebracket
bool queue::enqueue(std::string word)
{
    qarray[qtail] = word;
    qtail++;
    qtail = qtail%qsize;
    qed++;
    std::cout << "E " << word << std::endl;
    std::cout << "H " << qhead << std::endl;
    std::cout << "T " << qtail << std::endl;
    return true;
}
std::string queue::dequeue()
{
    std::string word = qarray[qhead];
    qhead++;
    qhead = qhead%qsize;
    qed--;
    return word;
}
void queue::print()
{
    int i = qtail;
    while (true)
    {
        std::cout << qarray[i] << std::endl;
        i++;
        i = i%qsize;
        if(i == qhead)
        {
            break;
        }
    }
}