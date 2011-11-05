/*
 * componentnode.h
 *
 *  Created on: 22.10.2011
 *      Author: akin
 */

#ifndef COMPONENTNODE_H_
#define COMPONENTNODE_H_

#include <deque>
#include <threadpool/tque>
#define NODE_NULL 0

namespace ice
{

class Component;

class ComponentNode
{
protected:
	Component& current;
	TQue<ComponentNode*> *finishQueu;

	unsigned int endTime;
	bool running;
public:
	ComponentNode( Component *component );
	ComponentNode( ComponentNode& other );
	virtual ~ComponentNode();

	std::deque<ComponentNode *> dependencies;
	std::deque<ComponentNode *> childs;
	unsigned int time;

	Component& getComponent();
	bool isRunning();

	void componentStart( TQue<ComponentNode*>& target , unsigned int start , unsigned int end );
	void componentFinished();
};

} /* namespace ice */
#endif /* COMPONENTNODE_H_ */
