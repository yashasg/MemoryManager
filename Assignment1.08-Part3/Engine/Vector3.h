#ifndef VECTOR3_H
#define VECTOR3_H
#include<iostream>
#include"Assert\Assert.h"
#include "Floats.h"

namespace Engine{

	class Vector3{
	private:
		float m_x;
		float m_y;
		float m_z;
	public:
		inline float getX() const{
			return m_x;
		}
		inline float getY() const{
			return m_y;
		}
		inline float getZ() const{
			return m_z;
		}
		inline void setX(const float i_X){
			if (!isNan(i_X))
				m_x = i_X;
			else
				MessagedAssert(false, "Given X was a NaN");
		}
		inline void setY(const float i_Y){
			if (!isNan(i_Y))
			m_y = i_Y;
		}
		inline void setZ(const float i_Z){
			if (!isNan(i_Z))
			m_z = i_Z;
		}
		inline Vector3 getPosition() {
			return Vector3(m_x, m_y, m_z);
		}
		inline void setPosition(Vector3 i_newPosition) {
			if (isNan(i_newPosition.m_x) || isNan(i_newPosition.m_y) || isNan(i_newPosition.m_z)) {
				MessagedAssert(false, "One of the values is Nan");
			}
			m_x =  i_newPosition.m_x;
			m_y =  i_newPosition.m_y;
			m_z =  i_newPosition.m_z;
		}
		Vector3(){

		}
		Vector3(const float i_X, const float i_Y,const float i_Z){
			if (isNan(i_X) || isNan(i_Y) || isNan(i_Z)) {
				MessagedAssert(false, "One of the values is Nan");
			}
			else {
				m_x = i_X;
				m_y = i_Y;
				m_z = i_Z;
			}
		}
		//should be a member function
		inline void operator=(const Vector3& RHS)
		{
			if (isNan(RHS.m_x) || isNan(RHS.m_y) || isNan(RHS.m_z)) {
				MessagedAssert(false, "One of the values is Nan");
			}
			m_x = RHS.m_x;
			m_y = RHS.m_y;
			m_z = RHS.m_z;
		}

		inline bool operator==(const Vector3& RHS) const
		{
			if (!fEquals(m_x,RHS.m_x))
			{
				return false;
			}
			if (!fEquals(m_y, RHS.m_y))
			{
				return false;
			}
			if (!fEquals(m_z, RHS.m_z))
			{
				return false;
			}
			return true;
			/*if (m_x != RHS.m_x)
				return false;

			if (m_y != RHS.m_y)
				return false;

			if (m_z != RHS.m_z)
				return false;

			return true;*/
		}

		inline bool operator!=(const Vector3& RHS) const
		{
			if (!fEquals(m_x, RHS.m_x))
			{
				return false;
			}
			if (!fEquals(m_y, RHS.m_y))
			{
				return false;
			}
			if (!fEquals(m_z, RHS.m_z))
			{
				return false;
			}
			return true;
			/*
			if (m_x == RHS.m_x)
				return false;

			if (m_y == RHS.m_y)
				return false;

			if (m_z == RHS.m_z)
				return false;

			return true;*/
		}
		friend std::ostream& operator<<(std::ostream& out, const Vector3& vector);
		 Vector3 operator+(const Vector3& RHS) const;	//adding inline here  causes linker errors
		 Vector3 operator-(const Vector3& RHS)const;
		 Vector3 operator+=(const Vector3& RHS);
		 Vector3 operator-=(const Vector3& RHS);

	};
	//arithmetic operators
	inline Vector3 operator*(const Vector3& LHS, float RHS)  {
		if (isNan(LHS.getX()) || isNan(LHS.getY()) || isNan(LHS.getZ())) {
			MessagedAssert(false, "One of the values is Nan");
			return LHS;
		}
		return Vector3(RHS* LHS.getX(), RHS* LHS.getY(), RHS* LHS.getZ());
	}
	inline Vector3 operator*(float LHS, const Vector3& RHS)  {
		if (isNan(RHS.getX()) || isNan(RHS.getY()) || isNan(RHS.getZ())) {
			MessagedAssert(false, "One of the values is Nan");
			return RHS;
		}
		return Vector3(LHS* RHS.getX(), LHS* RHS.getY(), LHS* RHS.getZ());
	}

	inline Vector3 CROSS(const Vector3& LHS, const Vector3& RHS) {
		if (isNan(LHS.getX()) || isNan(LHS.getY()) || isNan(LHS.getZ()) || isNan(RHS.getX()) || isNan(RHS.getY()) || isNan(RHS.getZ())) {
			MessagedAssert(false, "One of the values is Nan");
			return LHS;
		}
		return Vector3(LHS.getY()*RHS.getZ() - LHS.getZ()*RHS.getY(), LHS.getZ()*RHS.getX() - LHS.getX()*RHS.getZ(), LHS.getX()*RHS.getY() - LHS.getY()*RHS.getX());
	}
	inline float DOT(const Vector3& LHS, const Vector3& RHS){
		if (isNan(LHS.getX()) || isNan(LHS.getY()) || isNan(LHS.getZ()) || isNan(RHS.getX()) || isNan(RHS.getY()) || isNan(RHS.getZ())) {
			MessagedAssert(false, "One of the values is Nan");
			return NULL;
		}
		return LHS.getX()*RHS.getX() + LHS.getY()*RHS.getY() + LHS.getZ()*RHS.getZ();
	}

			}
#endif //!VECTOR3_H