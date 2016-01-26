#include "Vector3.h"
namespace Engine{
	Vector3 Vector3::operator + (const Vector3& RHS) const {
		return Vector3(this->m_x + RHS.getX(), this->m_y + RHS.getY(), this->m_z + RHS.getZ());
	}	
	Vector3 Vector3::operator - (const Vector3& RHS) const{
		return Vector3(this->m_x - RHS.getX(), this->m_y - RHS.getY(), this->m_z - RHS.getZ());
	}

	Vector3 Vector3::operator += (const Vector3& RHS) {
		return Vector3(this->m_x+= RHS.getX(), this->m_y += RHS.getY(), this->m_z += RHS.getZ());
	}
	Vector3 Vector3::operator -=(const Vector3& RHS) {
		return Vector3(this->m_x -= RHS.getX(), this->m_y -= RHS.getY(), this->m_z -= RHS.getZ());

	}
 std::ostream& operator<<(std::ostream& out, const Vector3& vector){
	 out << vector.getX() << " ," << vector.getY() << " ," << vector.getZ();
	 return out;
	}

}
