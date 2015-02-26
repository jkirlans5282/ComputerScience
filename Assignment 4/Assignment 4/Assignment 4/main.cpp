//
//  main.cpp
//  Assignment 4
//
//  Created by Jacob Kirlan-Stout on 2/18/15.
//  Copyright (c) 2015 Jacob Kirlan-Stout. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <random>
#include "CommunicationNetwork.h"
#include <sstream>
struct node
{
    std::string name = "";
    std::string value = "";
    node * next;
    node * prev;
};

node * addcity(node * head, std::string prev, std::string name)
{
    node * current = head;
    do
    {
        if (current->next == 0)
        {
            node * add = new node;
            add->next = 0;
            add->name = name;
            add->value = "";
            current->next = add;
            add->prev = current;
            break;
        }
        if (current->name == prev)
        {
            node * add = new node;
            add->next = current->next;
            add->name = name;
            add->value = "";
            (current->next)->prev = add;
            current->next = add;
            add->prev = current;
            break;
        }
        current = current->next;
    } while (true);
    
    return head;
}

node * delcity(node * head, std::string city)
{
    node * current = head;
    do
    {
        if ((current->next)->name == city)
        {
            ((current->next)->next)->prev = current;
            current->next = (current->next)->next;
            break;
        }
        current = current->next;
    } while (true);
    
    return head;
}

void print (node * current)
{
    std::cout << current->name << " -> ";
    if (current->next != 0)
    {
        print(current->next);
    }
    if (current->name == "HEAD")
    {
        std::cout << "0" << std::endl;
        std::cout << "==================" << std::endl;
    }
}

node * build(node * head)
{
    std::string citylist[11] = {"HEAD", "Los Angeles", "Phoenix", "Denver", "Dallas", "St.	Louis", "Chicago", "Atlanta", "Washington, D.C.", "New York", "Boston"};
    
    for (int i = 1; i < 11; i++)
    {
        head = addcity(head, citylist[i-1], citylist[i]);
    }
    
    print(head);
    
    return head;
}

void pass (node * current, std::string message)
{
    std::cout << (*current).name << " recieved " << message << std::endl;
    if ((*current).next != 0)
    {
        pass((*current).next, message);
    }
}

node * clear(node * head)
{
    head->next = 0;
    return head;
}

void quit()
{
    exit(0);
}

int main(int argc, const char * argv[])
{
    node * head = new node;
    head->name = "HEAD";
    head->value = "";
    head->next = 0;
    
    int size = 5;
    
    queue q(size);
    
    int current = 0;
    
    while (true)
    {
        std::cout << "======Main Menu======" << std::endl;
        std::cout << "1. Build Network" << std::endl;
        std::cout << "2. Print Network Path" << std::endl;
        std::cout << "3. Enqueue" << std::endl;
        std::cout << "4. Dequeue" << std::endl;
        std::cout << "5. Print Queue" << std::endl;
        std::cout << "6. Send Entire Network" <<std::endl;
        std::cout << "7. Quit" << std::endl;
        
        int selection;
        std::cin >> selection;
        std::cout << std::endl;
        
        std::string cityName = "";
        std::string previousName = "";
        
        std::string message[100];
        std::ifstream inFile(argv[1]);
        std::string messageString="A liger it's pretty much my favorite animal. It's like a lion and a tiger mixed - bred for its skills in magic. Elephants are pretty cool too. Hippos are just weird.";
        getline(inFile, messageString);
        
        std::istringstream iss(messageString);
        int i = 0;
        do{
            std::string sub;
            iss >> sub;
            message[i] = sub;
            i++;
        }while(iss);
        
        
        
        switch (selection){
            case 1:
            {
                head = build(head);
                break;
            }
            case 2:
            {
                print(head);
                break;
            }
            case 3:
            {
                q.enqueue(message[current]);
                current++;
                break;
            }
            case 4:
            {
                std::string word = q.dequeue();
                if(!word.compare("empty")){std::cout<<"empty"<<std::endl;}
                else{pass(head, word);}
                break;
            }
            case 5:
            {
                q.print();
                break;
            }
            case 7:
            {
                return 0;
                break;
            }
        }
    }
}
