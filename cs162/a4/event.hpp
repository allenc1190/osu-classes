#ifndef event_hpp
#define event_hpp

#include <iostream>
#include <ctime>
#include <vector>

using namespace std;

class Event{
    private:
    string message;
    char type;

    public:
    Event();
    ~Event();
    void set_type(char e);
    char get_type();
    virtual string get_message();
    virtual void print_message();
};

#endif