#include "Vector.h"
#include <cmath>

Vector::Vector() {
	x = Number(0);
	y = Number(0);
}
Vector::Vector(Number num1, Number num2) {
	x = num1;
	y = num2;
}
void Vector::setX(Number num) {
	x = num;
}
void Vector::setY(Number num) {
	y = num;
}
Number Vector::polar_R() {
	return sqrt(pow(x.get(), 2) + pow(y.get(), 2));
}
Number Vector::polar_Phi() {
	return atan(y.get() / x.get());
}
Vector Vector::operator+(const Vector& vect) {
	return Vector(x + vect.x, y + vect.y);
}
Number Vector::getX() { return x; }
Number Vector::getY() { return y; }