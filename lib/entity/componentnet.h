/*
 * componentnet.h
 *
 *  Created on: 19.10.2011
 *      Author: akin
 */

#ifndef COMPONENTNET_H_
#define COMPONENTNET_H_

#include "component"
#include <deque>
#include <map>
#include "componentnode.h"
#include <datatypes/common.h>

namespace ice
{

class ComponentNet
{
public:
	unsigned int time;
protected:
	std::deque<ComponentNode*> roots;
	std::deque<ComponentNode*> nodes;
	std::map<std::string,ComponentNode*> nodes_str;

	void removeFromRoot( ComponentNode *node );
	void addToRoot( ComponentNode *node );
public:
	ComponentNet();
	virtual ~ComponentNet();

	void add( Component *component );
	void addNoSort( Component *component );
	void sort();

	void resetTime( Time time );

	void getRoot( std::deque<ComponentNode*>& root );
};

} /* namespace ice */
#endif /* COMPONENTNET_H_ */
