/*
 * DIOLocker.h
 *
 *  Created on: 6.3.2011
 *      Author: akin
 */

#ifndef DIOLOCKER_H_
#define DIOLOCKER_H_

namespace ice
{
	class DIO;

	class DIOLocker {
	private:
		DIO *ptr;
	public:
		DIOLocker( DIO &dio );
		virtual ~DIOLocker();
	};
}

#endif /* DIOLOCKER_H_ */
