
#ifndef ICE_EXCEPTION_H_
#define ICE_EXCEPTION_H_

#include <exception>
#include <string>

namespace ice
{
	class Exception: public ::std::exception
	{
	protected:
		std::string message;
	public:
		Exception(std::string msg);
		Exception(const Exception& other);
		virtual ~Exception() throw();

		virtual std::string getMessage();
	};
}

#endif /* EXCEPTION_H_ */
