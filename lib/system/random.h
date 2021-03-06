/*
 * random.h
 *
 *  Created on: 3.4.2010
 *      Author: akin
 */

#ifndef ICE_RANDOM_H_
#define ICE_RANDOM_H_

namespace ice
{
	class Random
	{
	protected:
		static Random *sm_singleton;
	public:
		Random();
		virtual ~Random();

		float getFloat();
		unsigned char getUChar();
		char getChar();
		int getInt();

		static Random& get();
	};
}

#endif /* RANDOM_H_ */
