#include <iostream>
#include <list>
#include "GameObservers.h"

using std::cout;
using std::endl;
using std:: list;

Observer::Observer() {};

Observer::~Observer()
{
	//To show order of destructor calls with polymorphism or not
	//cout << "in ~Observer" << endl;
};

Subject::Subject()
{
	_observers = new list<Observer*>;
};

Subject::~Subject()
{
	/*
	for (Observer* o : *_observers)
	{
		//Detach(o); //cannot do!
		if (o != nullptr)
		{
			delete o;
			o = nullptr;
		}
	}
	/**/
	delete _observers;
};

void Subject::Attach(Observer* o)
{
	_observers->push_back(o);
};

void Subject::Detach(Observer* o)
{
	_observers->remove(o);
	/*
	if (o != nullptr)
	{
		delete o;
		o = nullptr;
	}
	/**/
};

void Subject::Notify()
{
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); ++i)	//note: for loop initialization already handled with begin()
		(*i)->Update();
};