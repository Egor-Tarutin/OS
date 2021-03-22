#include <iostream>
#include "../OS_lab_1_DLL/Vector.h"

int main() {
	OS_1_lab_SL::Number num1(6);
	OS_1_lab_SL::Number num2(5);
	OS_1_lab_SL::Number num3 = OS_1_lab_SL::create_number(10);
	std::cout << "Sum: " << num1 + num2 << " Sub: " << num1 - num2 
		<< " Mul: " << num1 * num2 << " Div: " << num1 / num2 << '\n';
	
	Vector vect(num1, num2);
	std::cout << "Polar is: " << vect.polar_R().get() << " " << vect.polar_Phi().get() << '\n';

	//vector_init(num1, num2);

	//set_coord_x(num1);
	//set_coord_y(num2);

	//std::cout << "Polar coord is: " << coord_R().get() << " " << coord_Phi().get() << '\n';


	return 0;
}