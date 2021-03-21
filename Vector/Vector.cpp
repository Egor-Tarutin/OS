#include "pch.h"
#include "Vector.h"
#include <cmath>

Vector::Vector() {
	x = OS_1_lab_SL::Number(0);
	y = OS_1_lab_SL::Number(0);
}
Vector::Vector(OS_1_lab_SL::Number num1, OS_1_lab_SL::Number num2) {
	x = num1;
	y = num2;
}
void Vector::setX(OS_1_lab_SL::Number num) {
	x = num;
}
void Vector::setY(OS_1_lab_SL::Number num) {
	y = num;
}
OS_1_lab_SL::Number Vector::polar_R() {
	return sqrt(pow(x.get(), 2) + pow(y.get(), 2));
}
OS_1_lab_SL::Number Vector::polar_Phi() {
	return atan(y.get() / x.get());
}
Vector Vector::operator+(const Vector& vect) {
	return Vector(x + vect.x, y + vect.y);
}
OS_1_lab_SL::Number Vector::getX() { return x; }
OS_1_lab_SL::Number Vector::getY() { return y; }