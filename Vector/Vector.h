#pragma once
#include "../OS_1_lab_SL/Number.h"

#ifdef OS_LAB_1_DLL_EXPORTS
#define OS_LAB_1_DLL_API __declspec(dllexport)
#else
#define OS_LAB_1_DLL_API __declspec(dllimport)
#endif

extern "C" OS_LAB_1_DLL_API class Vector {
	OS_1_lab_SL::Number x, y;
public:
	OS_LAB_1_DLL_API Vector();
	OS_LAB_1_DLL_API Vector(OS_1_lab_SL::Number num1, OS_1_lab_SL::Number num2);
	OS_LAB_1_DLL_API OS_1_lab_SL::Number polar_R();
	OS_LAB_1_DLL_API OS_1_lab_SL::Number polar_Phi();
	OS_LAB_1_DLL_API Vector operator+(const Vector& vect);
	OS_LAB_1_DLL_API OS_1_lab_SL::Number getX();
	OS_LAB_1_DLL_API OS_1_lab_SL::Number getY();
	OS_LAB_1_DLL_API void setX(OS_1_lab_SL::Number num);
	OS_LAB_1_DLL_API void setY(OS_1_lab_SL::Number num);
};