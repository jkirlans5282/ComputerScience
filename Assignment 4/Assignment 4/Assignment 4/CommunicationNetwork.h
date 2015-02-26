#ifndef __Assignment_4__network__
#define __Assignment_4__network__

#include <stdio.h>
#include <string>

class queue
{
private:
    int qsize;
    int qhead;
    int qtail;
    int qed;
    std::string * qarray;
public:
    queue(int size);
    bool enqueue(std::string word);
    std::string dequeue();
    void sendQueue();
    void print();
};



#endif
