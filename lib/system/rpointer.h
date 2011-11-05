#ifndef _RPOINTER_H_
#define _RPOINTER_H_

namespace ice
{
template<class CType>
class RPointer {
private:
	CType *m_ptr;
	int *counter;
public:
	RPointer( RPointer<CType> *share ) : m_ptr( &((*share)->()) ) , m_counter( share->getCounter() )
	{
		++m_counter[0];
	}

	RPointer( RPointer<CType> &share ) : m_ptr( &(share->()) ) , m_counter( share.getCounter() )
	{
		++m_counter[0];
	}

	RPointer(CType *res) : m_ptr(res), m_counter(new int[1])
	{
		m_counter[0] = 1;
	}

	~RPointer()
	{
		if (m_ptr != NULL && m_counter != NULL)
		{
			--(*m_counter);
			if ((*m_counter) <= 0)
			{
				delete m_ptr;
				delete[] m_counter;
			}
			m_counter = NULL;
			m_ptr = NULL;
		}
	}

	CType &operator ->()
	{
		return *m_ptr;
	}

	int *getCounter()
	{
		return m_counter;
	}
};

template<class CType>
class RArrayPointer {
private:
	CType *m_ptr;
	int *counter;
public:
	RArrayPointer( RArrayPointer<CType> *share ) : m_ptr( &((*share)->()) ) , m_counter( share->getCounter() )
	{
		++m_counter[0];
	}

	RArrayPointer( RArrayPointer<CType> &share ) : m_ptr( &(share->()) ) , m_counter( share.getCounter() )
	{
		++m_counter[0];
	}

	RArrayPointer(CType *res) : m_ptr(res), m_counter(new int[1])
	{
		m_counter[0] = 1;
	}

	~RArrayPointer()
	{
		if (m_ptr != NULL && m_counter != NULL)
		{
			--(*m_counter);
			if ((*m_counter) <= 0)
			{
				delete[] m_ptr;
				delete[] m_counter;
			}
			m_counter = NULL;
			m_ptr = NULL;
		}
	}

	CType &operator ->()
	{
		return *m_ptr;
	}

	int *getCounter()
	{
		return m_counter;
	}
};
}

#endif

