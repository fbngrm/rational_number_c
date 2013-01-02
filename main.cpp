/*
 Simple Unit Test for type RationalNumber
 */

#include <stdio.h>
#include <assert.h>
#include <iostream>
#include "rationalnumber.h"
#include "rationalnumberarray.h"
using namespace std;
using namespace rnum;

int main() {

	printf("Performing unit tests for RationalNumber...");
	fflush(stdout);

	/* Part 1 - RationalNumber data type */

	int i = 5, j = 4;
	RationalNumber nn(0, 0), a(1, 2), b(7, 3), c(2, 4), aa = a * i, bb = b / j,
			ia(i), ja = j, ac = i * a.toDouble();
	//RationalNumber ab = i*a; // no match
	RationalNumber d = a + c, e = d + d;
	RationalNumber f = a + b * c - d / e; // 7/6
	RationalNumber g = -f + RationalNumber(1, 1);
	RationalNumber h = RationalNumber(1, 2) += RationalNumber(3, 6);
	RationalNumber k = RationalNumber(3, 2) -= RationalNumber(3, 6);

	assert( a.isValid());
	assert( !(nn.isValid()));
	assert( nn.isNaN());
	assert( aa.nomi() == 5 && aa.deno() == 2);
	assert( bb.nomi() == 7 && bb.deno() == 12);
	assert( ia.nomi() == 5 && ia.deno() == 1);
	assert( ja.nomi() == 4 && ja.deno() == 1);
	assert( a==c);
	assert( c==a);
	assert( c!=b);
	assert( a<b);
	assert( a<=b);
	assert( a<=c);
	assert( aa==aa);
	assert( aa<=aa);
	assert( aa>=aa);
	assert( aa>=a);
	// add, sub, mult, div
	assert( d.nomi() == 1 && d.deno() == 1);
	assert( e.nomi() == 2 && e.deno() == 1);
	assert( f.nomi() == 7 && f.deno() == 6);
	// -, +
	assert( -f.nomi() == -7 && -f.deno() == -6);
	assert( +f.nomi() == 7 && +f.deno() == 6);
	assert( g.nomi() == 0 && g.deno() == 1);
	// +=, -=
	assert( h.nomi() == 1 && h.deno() == 1);
	assert( k.nomi() == 1 && k.deno() == 1);

	printf("RationalNumber test successful!\n");
	printf("Performing unit tests for RationalNumberArray...\n");
	printf("TESTING PARAMETER: %12u\n", 1);

	// test capacity, size & error_state
	RationalNumberArray rna(1);
	assert( rna.capacity() == 1);
	assert( rna.size() == 0);
	assert( rna.error() == 0);

	// resize
	rna.resize(10);
	assert( rna.capacity() == 10);
	assert( rna.size() == 0);
	assert( rna.error() == 0);
	// add
	rna.add(a);
	assert( rna.capacity() == 10);
	assert( rna.size() == 1);
	assert( rna.error() == 0);
	rna.add(a);
	rna.add(b);
	rna.add(RationalNumber(-6, 6));
	rna.add(RationalNumber(3, 6));

	// resize & cut
	rna.resize(4);
	assert( rna.capacity() == 4);
	assert( rna.size() == 4);
	assert( rna.error() == 0);
	// add with resize
	rna.add(a);
	assert( rna.capacity() == 8);
	assert( rna.size() == 5);
	assert( rna.error() == 0);
	rna.resize(5);

	// get
	assert( rna.get(0).nomi() == 1 && rna.get(0).deno() == 2);
	assert( rna.get(1).nomi() == 1 && rna.get(1).deno() == 2);
	assert( rna.get(2).nomi() == 7 && rna.get(2).deno() == 3);
	assert( rna.get(3).nomi() == -3 && rna.get(3).deno() == 3);
	assert( rna.get(4).nomi() == 1 && rna.get(4).deno() == 2);
	assert( rna.capacity() == 5);
	assert( rna.size() == 5);
	assert( rna.error() == 0);

	// set & get
	rna.set(a, 0);
	rna.set(b, 1);
	rna.set(RationalNumber(2, 4), 2);
	rna.set(RationalNumber(-3, 3), 3);
	rna.set(RationalNumber(3, -3), 4);
	assert( rna.get(0).nomi() == 1 && rna.get(0).deno() == 2);
	assert( rna.get(1).nomi() == 7 && rna.get(1).deno() == 3);
	assert( rna.get(2).nomi() == 1 && rna.get(2).deno() == 2);
	assert( rna.get(3).nomi() == -3 && rna.get(3).deno() == 3);
	assert( rna.get(4).nomi() == 3 && rna.get(4).deno() == -3);
	assert( rna.capacity() == 5);
	// handle error
	assert( rna.size() == 5);
	assert( rna.error() == 0);
	// set & resize
	rna.set(RationalNumber(), 5);
	assert( rna.get(5).nomi() == 0 && rna.get(5).deno() == 1);
	assert( rna.capacity() == 10);
	assert( rna.size() == 6);
	assert( rna.error() == 0);
	// set, enlarge & fill with {0, 1}
	rna.set(RationalNumber(-2, 1), 10);
	assert( rna.get(10).nomi() == -2 && rna.get(10).deno() == 1);
	assert( rna.capacity() == 20);
	assert( rna.size() == 11);
	assert( rna.error() == 0);

	// remove
	rna.remove((unsigned short int) 8, (unsigned short int)12);
	assert( rna.capacity() == 16);
	assert( rna.size() == 16);
	assert( rna.error() == 0);

	rna.remove((unsigned short int)5, (unsigned short int)16);
	assert( rna.capacity() == 5);
	assert( rna.size() == 5);
	assert( rna.error() == 0);
	// test remaining values
	assert( rna.get(0).nomi() == 1 && rna.get(0).deno() == 2);
	assert( rna.get(1).nomi() == 7 && rna.get(1).deno() == 3);
	assert( rna.get(2).nomi() == 1 && rna.get(2).deno() == 2);
	assert( rna.get(3).nomi() == -3 && rna.get(3).deno() == 3);
	assert( rna.get(4).nomi() == 3 && rna.get(4).deno() == -3);
/*
	// test error handler
	printf("%s\n", "TEST ERROR HANDLER - VALID:");
	rna.handleError();
	// test error handler
	printf("%s\n", "TEST ERROR HANDLER - INVALID_INDEX:");
	rna.setErrorCallback(catchInvalidIndex);
	// set invalid index
	rna.get(10);
	// handle INVALID_INDEX error
	rna.handleError();
	// test error handler
	printf("%s\n", "TEST ERROR HANDLER - OUT_OF_MEMORY:");
	rna.setErrorCallback(rna.catchOutOfMemory);
	// blow up - intel i3, 64-bit, 8 GB RAM
	// poduces warning
	rna.resize(1000000000000);
	// handle OUT_OF_MEMORY error
	rna.handleError();
	// free
*/
	printf("RationalNumberArray test successful!\n");
	return 0;
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
