/*
 * work.h
 *
 *  Created on: 16.10.2011
 *      Author: akin
 */

#ifndef WORK_H_
#define WORK_H_

#include <log/log>

namespace ice
{

class Work
{
protected:
	Log *log;
public:
	Work();
	virtual ~Work();

	void setLog( Log *clog );

	virtual bool begin() = 0;
	virtual void run() = 0;
	virtual void end() = 0;
};

} /* namespace ice */
#endif /* WORK_H_ */
