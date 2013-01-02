#include "rationalnumberarray.h"
#include "rationalnumber.h"
#include <stdlib.h>
#include <stdio.h>
namespace rnum{

void RationalNumberArray::resize(const unsigned int capacity) {
	// allocate memory
	RationalNumber* newdata = (RationalNumber*) realloc(data(),
			capacity * sizeof(RationalNumber));

	// validate newdata
	if (!newdata) {
		m_error = OUT_OF_MEMORY;
	} else {
		// resize
		m_data = newdata;
		m_capacity = capacity;
		m_size = capacity > m_size ? m_size : capacity;
		m_error = VALID;
	}
}
void RationalNumberArray::add(RationalNumber rn) {
	// resize if neccessary
	if (capacity() == size()) {
		resize(capacity() * 2);
	}
	if (capacity() > size()) {
		m_data[size()] = rn;
		m_size++;
		m_error = VALID;
	} else {
		// resize failed
		m_error = OUT_OF_MEMORY;
	}
}
void RationalNumberArray::set(RationalNumber rn, const unsigned int index) {
	// resize if neccessery
	 if (index >= capacity()) {
		 // resize with index
		 if(index >=capacity() * 2){
		 		resize(index);
		 } else {
			 // resize
			resize(capacity() * 2);
		 }
		// fill with RN { 0, 1 } and increment size
		// NOTE: only elements with position < index of 'rn' are initialized by {0, 1} !!
		for (unsigned int i = size(); i < index; i++) {
			RationalNumber r;
			m_data[i] = r;
			m_size++;
		}
		// set 'rn' at position 'index' in 'rna', increment size
		m_data[index] = rn;
		m_size++;
	} else {
		// set 'rn' at position 'index' in 'rna'
		m_data[index] = rn;
		m_error = VALID;
	}
}
RationalNumber RationalNumberArray::get(const unsigned int index) {
	if (index >= capacity()) {
		m_error = INVALID_INDEX;
		RationalNumber r;
		return r;
	}
	if (index >= size()) {
		RationalNumber *r = new RationalNumber(0, 1);
		return r;
	}
	m_error = VALID;
	return m_data[index];
}

void RationalNumberArray::remove(const unsigned int start,
		const unsigned int end) {
	unsigned int new_index = start;
	unsigned int index = end;
	for (; index < capacity(); index++) {
		m_data[new_index++] = m_data[index];
	}
	m_capacity = new_index;
	m_size = new_index;
}

void RationalNumberArray::catchOutOfMemory() {
	printf("out of memory!\n");
	// to do:
	// appropriate error handling
	m_error = VALID;
	printf("error adjusted!\n\n");
}
void RationalNumberArray::catchInvalidIndex() {
	printf("invalid index!\n");
	// to do:
	// appropriate error handling
	m_error = VALID;
	printf("error adjusted!\n\n");
}
void RationalNumberArray::catchInvalidArray() {
	printf("invalid array!\n");
	// to do:
	// appropriate error handling
	m_error = VALID;
	printf("error adjusted!\n\n");
}
void RationalNumberArray::handleError() {
	if (m_error != 0) {
		m_error_handler();
	} else {
		printf("no errors occured!\n\n");
	}
}
void RationalNumberArray::setErrorCallback(const ErrorHandler handler) {
	m_error_handler = handler;
}

// operators
RationalNumberArray& RationalNumberArray::operator=(RationalNumberArray& rna) {
	m_capacity = rna.capacity();
	m_size = rna.size();
	m_error = rna.error();
	m_error_handler = rna.errorHandler();
	m_data =
			((RationalNumber*) malloc(rna.capacity() * sizeof(RationalNumber)));
	for (unsigned int i = 0; i < rna.size(); i++) {
		m_data[i] = rna.data()[i];
	}
	return *this;
}

const RationalNumber& RationalNumberArray::operator[](int i) const {
	return m_data[i];
}

RationalNumber& RationalNumberArray::operator[](int i) {
	return m_data[i];
}

bool RationalNumberArray::operator==(RationalNumberArray& rna) {
	if (capacity() != rna.capacity() || size() == rna.size()
			|| error() == rna.error() || errorHandler() == rna.errorHandler()) {
		return false;
	}
	for(unsigned int i=0; i<capacity();i++){
		if(m_data[i] != rna.m_data[i]){
			return false;
		}
	}
	return true;
}
}
