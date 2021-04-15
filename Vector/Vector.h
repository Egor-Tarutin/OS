#pragma once
#include "../Number/Number.h"

class Vector {
	Number x, y;
public:
	 Vector();
	 Vector(Number num1, Number num2);
	 Number polar_R();
	 Number polar_Phi();
	 Vector operator+(const Vector& vect);
	 Number getX();
	 Number getY();
	 void setX(Number num);
	 void setY(Number num);
};