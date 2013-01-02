#ifndef RATIONALNUMBERARRAY_H_
#define RATIONALNUMBERARRAY_H_

#include "rationalnumber.h"
#include <stdlib.h>
namespace rnum{

class RationalNumberArray {

public:
	// constructor
	RationalNumberArray(unsigned int capacity)
		: m_capacity(capacity), m_size(0), m_error(0), m_error_handler(0), m_data(
					(RationalNumber*) malloc(10 * sizeof(RationalNumber)))
	{}
	// default
	RationalNumberArray() {
		m_capacity = 10;
		m_size = 0;
		m_error = 0;
		m_error_handler = 0;
		m_data = (RationalNumber*) malloc(10 * sizeof(RationalNumber));
	}
	// copy constructor
	RationalNumberArray(const RationalNumberArray& rna)
		: m_capacity(rna.capacity()), m_size(rna.size()), m_error(rna.error()),
		  m_error_handler(rna.errorHandler()),
		  m_data((RationalNumber*) malloc(rna.capacity() * sizeof(RationalNumber)))
		{
			for(unsigned int i=0; i<rna.size(); i++){
				m_data[i] = rna.data()[i];
			}
		}

	// desructor
	~RationalNumberArray() {
		free (m_data);
	}

	// declare type ErrorHandler as function pointer
	typedef void (*ErrorHandler)();

	// accessors
	unsigned int capacity() const {
		return m_capacity;
	}
	unsigned int size() const {
		return m_size;
	}
	unsigned int error() const {
		return m_error;
	}
	ErrorHandler errorHandler() const {
		return m_error_handler;
	}
	RationalNumber* data() const {
		return m_data;
	}
	// mutators
	unsigned int capacity() {
		return m_capacity;
	}
	unsigned int size() {
		return m_size;
	}
	unsigned int error() {
		return m_error;
	}
	ErrorHandler errorHandler(){
		return m_error_handler;
	}
	RationalNumber* data() {
		return m_data;
	}

	void resize(const unsigned int capacity);
	void add(RationalNumber rn);
	void set(RationalNumber rn, const unsigned int index);
	RationalNumber get(const unsigned int index);
	void remove(const unsigned int start, const unsigned int end);
	void catchOutOfMemory();
	void catchInvalidIndex();
	void catchInvalidArray();
	void handleError();
	void setErrorCallback(const ErrorHandler handler);
	RationalNumberArray& operator=(RationalNumberArray& rna);
	const RationalNumber& operator[](int i) const;
	RationalNumber& operator[](int i);


private:
	// member variables
	unsigned int m_capacity, m_size, m_error;
    // error callback function
    ErrorHandler m_error_handler;
    // array
	RationalNumber* m_data;
	enum Errors {
		VALID, INVALID_ARRAY_OBJECT, INVALID_INDEX, OUT_OF_MEMORY
	};
	bool operator==(RationalNumberArray& rna);
};

}

#endif /* RATIONALNUMBERARRAY_H_ */
