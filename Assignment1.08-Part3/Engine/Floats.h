#ifndef __Floats_H
#define __Floats_H
namespace Engine {
#define EPSILON 0.00001f
inline bool isNan(const float i_num) {
		if (i_num != i_num)
			return true;
		else
			return false;
	}
inline bool fEquals(const float i_num1, const float i_num2) {
	float absolute = fabsf(i_num1 - i_num2);
	if (absolute > EPSILON)
		return false;
	return true;
}
}
#endif//__Floats_H