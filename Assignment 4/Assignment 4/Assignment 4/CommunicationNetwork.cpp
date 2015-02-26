#include <iostream>
#include <string>
#include "CommunicationNetwork.h"

queue::queue (int size)
{
    qsize = size;
    qarray = new  std::string[ size ];
    qhead = 0;
    qtail = 0 ;
    qed = 0 ; //how many items are in queue.1
}
    bool queue::enqueue(std::string word)
{
    qarray[qtail] = word;
    qtail++;
    if(qtail-qhead>=qsize){ std::cout<< "queue is full"<<std::endl; return false;}
    qed++;
    std::cout<<"qed "<<qed<<std::endl;
    std::cout << "E " << word << std::endl;
    std::cout << "H " << qhead << std::endl;
    std::cout << "T " << qtail << std::endl;
    return true;
}
std::string queue::dequeue()
{
    if(qed==0){return "empty";}
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
void queue::sendQueue(){
    
}
