#pragma once

namespace OS_1_lab_SL {
	class Number {
		double a;
	public:
		Number() {}
		Number(double val) : a(val) {}
		double operator+(Number num);
		double operator-(Number num);
		double operator*(Number num);
		double operator/(Number num);

		void set(double a);
		double get();
	};

	//double first = 0;
	//double second = 1;

	Number create_number(double num);
}
