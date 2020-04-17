// Adapted from: https://www.bogotobogo.com/DesignPatterns/observer.php
// The above source uses code examples from the book "Design Patterns: Elements of Reusable Object-Oriented Software" by Erich Gamma, Richard Helm, Ralph Johnson, John Vlissides.

#include "GameObservers.h"

void Subject::Attach(Observer* o)
{
    _observers.push_back(o);
}

void Subject::Detach(Observer* o)
{
    int count = _observers.size();
    int i;

    for (i = 0; i < count; i++) {
        if (_observers[i] == o)
            break;
    }
    if (i < count)
        _observers.erase(_observers.begin() + i);

}

void Subject::Notify()
{
    int count = _observers.size();

    for (int i = 0; i < count; i++)
        (_observers[i])->Update(this);
}