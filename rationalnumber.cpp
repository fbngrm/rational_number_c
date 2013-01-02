#include "rationalnumber.h"
#include <iostream>
namespace rnum {

// implement function isValid
bool RationalNumber::isValid() const {
	return deno() != 0;
}

// implement function isNaN
bool RationalNumber::isNaN() const {
	return deno() == 0;
}

// operator overloading
RationalNumber& RationalNumber::operator=(const RationalNumber& other) {
	if (other.isNaN())
		return *this;

	m_nomi = other.nomi();
	m_deno = other.deno();
	normalize();
	return *this;
}

// call by value
RationalNumber RationalNumber::operator+() const {
	RationalNumber r(+nomi(), +deno());
	r.normalize();
	return r;
}

// call by value
RationalNumber RationalNumber::operator-() const {
	RationalNumber r(-nomi(), deno());
	r.normalize();
	return r;
}

// call by reference
RationalNumber& RationalNumber::operator+=(const RationalNumber& other) {
	if (other.isNaN())
		return *this;

	m_nomi = nomi() * other.deno() + other.nomi() * deno();
	m_deno *= other.deno();
	normalize();
	return *this;
}

// call by reference
RationalNumber& RationalNumber::operator-=(const RationalNumber& other) {
	if (other.isNaN())
		return *this;

	m_nomi = nomi() * other.deno() - other.nomi() * deno();
	m_deno *= other.deno();
	normalize();
	return *this;
}

// call by value - non-member function
RationalNumber operator+(const RationalNumber& one, const RationalNumber& two) {
	if (one.isNaN() || two.isNaN()) {
		RationalNumber r;
		return r;
	}

	RationalNumber r(one.nomi() * two.deno() + two.nomi() * one.deno(),
			one.deno() * two.deno());
	r.normalize();
	return r;
}

// call by value - non-member function
RationalNumber operator-(const RationalNumber& one, const RationalNumber& two) {
	if (one.isNaN() || two.isNaN()) {
		RationalNumber r;
		return r;
	}
	RationalNumber r(one.nomi() * two.deno() - two.nomi() * one.deno(),
			one.deno() * two.deno());
	r.normalize();
	return r;
}

// call by value
RationalNumber RationalNumber::operator-(const RationalNumber& other) const {
	if (other.isNaN())
		return RationalNumber(*this);

	RationalNumber r(*this);
	r -= other;
	r.normalize();
	return r;
}

// call by value
RationalNumber RationalNumber::operator+(const RationalNumber& other) const {
	if (other.isNaN())
		return RationalNumber(*this);
	/*
	 RationalNumber result(nomi() * other.deno() + other.nomi() * deno(),
	 deno() * other.deno());
	 return result;
	 */
	RationalNumber r(*this);
	r += other;
	r.normalize();
	return r;
}

// call by reference
RationalNumber& RationalNumber::operator*=(const RationalNumber& other) {
	if (other.isNaN())
		return *this;

	m_nomi *= other.nomi();
	m_deno *= other.deno();
	normalize();
	return *this;
}

// call by reference
RationalNumber& RationalNumber::operator/=(const RationalNumber& other) {
	if (other.isNaN())
		return *this;

	m_nomi *= other.deno();
	m_deno *= other.nomi();
	normalize();
	return *this;
}

// call by value - non-member function
RationalNumber operator*(const RationalNumber& one, const RationalNumber& two) {
	if (one.isNaN() || two.isNaN()) {
		RationalNumber r;
		return r;
	}
	RationalNumber r(one.nomi() * two.nomi(), one.deno() * two.deno());
	return r;
}

// call by value - non-member function
RationalNumber operator/(const RationalNumber& one, const RationalNumber& two) {
	if (one.isNaN() || two.isNaN()) {
		RationalNumber r;
		return r;
	}
	RationalNumber r(one.nomi() * two.deno(), one.deno() * two.nomi());
	return r;
}

// call by value
RationalNumber RationalNumber::operator*(const RationalNumber& other) const {
	if (other.isNaN())
		return RationalNumber(*this);

	RationalNumber r(*this);
	r *= other;
	r.normalize();
	return r;
}

RationalNumber RationalNumber::operator/(const RationalNumber& other) const {
	if (other.isNaN())
		return RationalNumber(*this);

	RationalNumber r(*this);
	r /= other;
	r.normalize();
	return r;
}

RationalNumber RationalNumber::operator*(const int i) const {
	RationalNumber ri(i);
	RationalNumber rr(*this);
	rr *= ri;
	rr.normalize();
	return rr;
}
RationalNumber RationalNumber::operator/(const int i) const {
	RationalNumber ri(i);
	RationalNumber rr(*this);
	rr /= ri;
	rr.normalize();
	return rr;
}

RationalNumber operator*(const int i, RationalNumber& rn) {
	RationalNumber ri(i);
	ri *= rn;
	ri.normalize();
	return ri;
}

RationalNumber operator/(const int i, RationalNumber& rn) {
	RationalNumber ri(i);
	ri /= rn;
	ri.normalize();
	return ri;
}

bool RationalNumber::operator==(const RationalNumber& other) const {
	if (other.isNaN())
		return false;

	signed short int a1 = nomi() * other.deno();
	signed short int b1 = deno() * other.deno();

	signed short int a2 = other.nomi() * deno();
	signed short int b2 = other.deno() * deno();

	return (a1 == a2 && b1 == b2);
}

bool RationalNumber::operator!=(const RationalNumber& other) const {
	if (other.isNaN())
		return false;
	return !(*this == other);
}

bool RationalNumber::operator<(const RationalNumber& other) const {
	if (other.isNaN())
		return false;
	return ((nomi() * other.deno()) * (deno() * other.deno()))
			< ((other.nomi() * deno()) * (other.deno() * deno()));
}

bool RationalNumber::operator>(const RationalNumber& other) const {
	if (other.isNaN())
		return false;
	return ((nomi() * other.deno()) * (deno() * other.deno()))
			> ((other.nomi() * deno()) * (other.deno() * deno()));
}

bool RationalNumber::operator<=(const RationalNumber& other) const {
	if (other.isNaN())
		return false;
	return *this < other || *this == other;
}

bool RationalNumber::operator>=(const RationalNumber& other) const {
	if (other.isNaN())
		return false;
	return *this > other || *this == other;
}

bool RationalNumber::operator&&(const RationalNumber& other) const {
	if (other.isNaN())
		return false;
	return nomi() > 0 && other.nomi() > 0;
}

bool RationalNumber::operator||(const RationalNumber& other) const {
	if (other.isNaN())
		return nomi() > 0;
	return nomi() > 0 || other.nomi() > 0;
}

bool RationalNumber::operator!() const {
	return nomi() == 0;
}

std::ostream& operator<<(std::ostream& lhs, RationalNumber& rhs){
	lhs << "(" << rhs.nomi() << ", " << rhs.deno() << ")";
	return lhs;
}


void RationalNumber::normalize() {
	// get gdc
	unsigned short int gcd = euclid(nomi(), deno());
	// normalize with gdc
	m_nomi /= gcd;
	m_deno /= gcd;
}

// implementation of the euclidian algorithm to calculate the greatest common divisor
unsigned short int RationalNumber::euclid(unsigned short int n1,
		unsigned short int n2) {
	if (n1 < n2) {
		unsigned short int t = n1;
		n1 = n2;
		n2 = t;
	}
	if (n2 == 0) {
		return n1;
	}
	// recursion
	return euclid(n2, n1 % n2);
}
double RationalNumber::toDouble() const {
	return nomi() / deno();
}
}

