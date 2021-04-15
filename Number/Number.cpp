#include "Number.h"

Number create_number(double num) {
    return Number(num);
}
double Number::operator+(Number num) { return this->a + num.a; }
double Number::operator-(Number num) { return this->a - num.a; }
double Number::operator/(Number num) { return this->a / num.a; }
double Number::operator*(Number num) { return this->a * num.a; }

void Number::set(double num) { this->a = num; }
double Number::get() { return this->a; }