

#include <iostream>
#ifndef RATIONALNUMBER_H_
#define RATIONALNUMBER_H_

namespace rnum {
class RationalNumber {
public:
	// constructors
	RationalNumber() :
			m_nomi(0), m_deno(1) {
	}
	RationalNumber(signed short int i) :
			m_nomi(i), m_deno(1) {
	}
	RationalNumber(signed short int nomi, signed short int deno) :
			m_nomi(nomi), m_deno(deno) {
	}
	RationalNumber(RationalNumber* that) :
			m_nomi(that->nomi()), m_deno(that->deno()) {
	}

	// mutators
	signed short int nomi() {
		return m_nomi;
	}
	signed short int deno() {
		return m_deno;
	}

	// accessors
	signed short int nomi() const {
		return m_nomi;
	}
	signed short int deno() const {
		return m_deno;
	}

	// methods
	bool isValid() const;
	bool isNaN() const;
	void normalize();
	unsigned short int euclid(unsigned short int deno, unsigned short int nomi);
	double toDouble() const;
	// operator overloading
	RationalNumber& operator=(const RationalNumber& other);
	RationalNumber operator+() const;
	RationalNumber operator-() const;
	RationalNumber& operator+=(const RationalNumber& other);
	RationalNumber& operator-=(const RationalNumber& other);
	RationalNumber operator+(const RationalNumber& other) const;
	RationalNumber operator-(const RationalNumber& other) const;
	RationalNumber& operator*=(const RationalNumber& other);
	RationalNumber& operator/=(const RationalNumber& other);
	RationalNumber operator*(const RationalNumber& other) const;
	RationalNumber operator/(const RationalNumber& other) const;
	bool operator==(const RationalNumber& other) const;
	bool operator!=(const RationalNumber& other) const;
	bool operator<(const RationalNumber& other) const;
	bool operator>(const RationalNumber& other) const;
	bool operator<=(const RationalNumber& other) const;
	bool operator>=(const RationalNumber& other) const;
	bool operator&&(const RationalNumber& other) const;
	bool operator||(const RationalNumber& other) const;
	RationalNumber operator*(const int i) const;
	RationalNumber operator/(const int i) const;
	bool operator!() const;

private:
	// member variables
	signed short int m_nomi, m_deno;
};
RationalNumber operator*(const int i, RationalNumber& rn);
}
#endif /* RATIONALNUMBER_H_ */
