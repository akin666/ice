/*
 * component.h
 *
 *  Created on: 14.10.2011
 *      Author: akin
 *
 *      Without aspect oriented programming, this class causes a bit of trouble
 *      especially, if you forget to add _one_ finish() call to the end of the
 *      execution of your component.
 *      If the component is single-threaded, make sure that start() calls finish
 *      at the end! If it is multi-threaded, you just some magical way, must make
 *      sure that it gets called.
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <set>

namespace ice
{

class Entity;
class ComponentNode;

class Component
{
protected:
	static unsigned int sm_id;
	static unsigned int getNewId();

	unsigned int id;
	std::string name;
	unsigned int priority;

	bool concurrent;

	std::set<std::string> dependencies;
	ComponentNode *componentNode;

	void addDependency( std::string dependency );
	void setPriority( unsigned int prio );
public:
	Component( std::string name , bool concurrent = false);
	virtual ~Component();

	void setComponentNode( ComponentNode *cn );

	// get string identifier of the component
	std::string getName() const;

	// get integer identifier of the component
	// decided on runtime!
	unsigned int getId() const;

	// Figure out if this component can be before the linked component
	virtual bool before( Component& component );

	// Generate list of components dependencies
	virtual void getDependencyList( std::set<std::string>& list );

	bool isConcurrent();

	// Return components priority
	unsigned int getPriority();

	// Attach / Detach an entity to the component.
	virtual void attach( Entity& entity ) = 0;
	virtual void detach( Entity& entity ) = 0;

	// Start can be blocking, if the component wants to go singlethreaded.
	// on multithreaded situation, it should start work packages, but not block.
	// Once all computing is done, finish() has to be called.
	virtual void start();

	// finish should be called, once the thread/all the stuff the component is doing
	// is done. Not before! Applies to singlethreaded mode too!.
	void finish();
};

} /* namespace ice */
#endif /* COMPONENT_H_ */
