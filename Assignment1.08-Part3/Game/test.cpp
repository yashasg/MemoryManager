#include<iostream>
#include<assert.h>
using namespace std;
#include "Vector3.h"
#include "Assert\Assert.h"
using namespace Engine;

int mainxx(void){

	Vector3 v1(1.0,1.0,1.0), v2(2.0,2.0,2.0);
	MessagedAssert(v1 == v2, "OMG THIS IS RIGHT");

	//addition
	cout << v1 + v1;
	//minus
	cout << v1 - v1;
	//multiplication
	cout << v1*2.0f;
	cout << 2.0f * v1;
	//+=
	v1 += v1;
	cout <<v1;
	//-=
	v1 -= v1;
	cout << v1;
	//==
	v1 = v2;
	if (v1 == v2)
		cout << "They are equal\n";
	else if (v1 != v2)
		cout << "They are not equal";

	//CROSS
	cout << CROSS(v1, v1);

	//dot
	cout << DOT(v1, v1);
	//checking if isNan works
	float x = NAN;
	Vector3 v_nan(x, x, x);
	
	//checking if fEquals works
	Vector3 v_equals1(1.001f, 1.001f, 1.001f), v_equals2(1.0001f, 1.0001f, 1.0001f);
	if (v_equals1 == v_equals2) {
		cout << "My fEquals doest work";
	}
	else {
		cout << "Fequals works";
	}
	getchar();

	return 0;
}