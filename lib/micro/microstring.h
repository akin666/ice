/*
 * microstring.h
 *
 *  Created on: 25.11.2011
 *      Author: akin
 */

#ifndef MICROSTRING_H_
#define MICROSTRING_H_

class MicroString
{
public:
	enum Type{
		ASCII = 0,
		UTF8,
		UTF16,
		UTF32,
		CHAR,
		WCHAR16,
		WCHAR32,
		END
	};

	typedef unsigned int MSSize;

	MSSize typeSize( Type type = ASCII ) const;
protected:
	MSSize datasize;
	char *data;
	Type dataType;
public:
	MicroString( Type type = ASCII );
	MicroString( const MicroString& other );
	MicroString( const char *other , Type type = ASCII );

	MicroString( int number , Type type = ASCII );
	MicroString( float number , Type type = ASCII);
	MicroString( double number , Type type = ASCII);
	MicroString( bool number , Type type = ASCII);

	virtual ~MicroString();

	char *CStr() const;
	Type type() const;
	MSSize size() const;
	void clear();

	bool operator < ( const MicroString& other ) const;
	bool operator > ( const MicroString& other ) const;
	bool operator ==( const MicroString& other ) const;
	MicroString& operator += ( const MicroString& other );
	const MicroString operator + ( const MicroString& other ) const;
	const MicroString& operator = ( const MicroString& other );
};

#endif /* MICROSTRING_H_ */
