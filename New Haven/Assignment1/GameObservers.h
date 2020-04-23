// Adapted from: https://www.bogotobogo.com/DesignPatterns/observer.php
// The above source uses code examples from the book "Design Patterns: Elements of Reusable Object-Oriented Software" by Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides.

#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

class Subject; 

class Observer
{
public:
    Observer() {};
    ~Observer() {};
    virtual void Update(Subject* theChangeSubject, string message) = 0;
};

class Subject
{
public:
    Subject() {};
    virtual ~Subject() {};
    virtual void Attach(Observer*);
    virtual void Detach(Observer*);
    virtual void Notify(string);
private:
    vector<Observer*> _observers;
};