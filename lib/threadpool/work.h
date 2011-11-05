/*
 * work.h
 *
 *  Created on: 16.10.2011
 *      Author: akin
 */

#ifndef WORK_H_
#define WORK_H_

#include <log/clientlog.h>

namespace ice
{

class Work
{
protected:
	ClientLog *log;
public:
	Work();
	virtual ~Work();

	void setLog( ClientLog *clog );

	virtual bool begin() = 0;
	virtual void run() = 0;
	virtual void end() = 0;
};

} /* namespace ice */
#endif /* WORK_H_ */
