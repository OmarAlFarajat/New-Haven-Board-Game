#pragma once
#include <list>

using std::list;

class Observer
{
	/**
	* Abstract class for observers. Contains an instance of the model they are
	* observing. All classes that inherit from this class must define what they will
	* do when update() is invoked.
	*/
public:
	Subject* model;
	Observer();
	Observer(Subject* subject) : model(subject) {};
	virtual void update(int code) {};
	~Observer();
	//virtual ~Observer();		//to properly delete derived classes with dynamic members if using polymorphism
	virtual void Update() = 0;

protected:
	Observer();
};

class Subject
{
	/**
	 * Abstract class for subjects. In the Observer model, there is a one to many
	 * relationship between inheritors of this class and inheritors of the Observer
	 * class. The list _views_ contains all the observer objects to which this subject
	 * will be sharing information.
	 */
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify();
	Subject();
	~Subject();

private:
	list<Observer*>* _observers;
};

