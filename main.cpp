#include "Vector.h"
#include <iostream>
using namespace std;

void printVector(Vector v)
{
    cout << "(" << v.getX().get() << ", " << v.getY().get() << ")\n";
}

int main()
{
    Number n1 = 2, n2 = create_number(3), n3 = 4, n4 = 8;
    Vector v1(n1, n2), v2(n3, n4);

    cout << "\nn1: " << n1.get() << "\nn2: " << n2.get() << "\n";
    cout << "\nv1: ";
    printVector(v1);
    cout << "v2: ";
    printVector(v2);

    cout << '\n';
    cout << "n1 + n2 = " << n1 + n2 << "\n";
    cout << "n1 - n2 = " << n1 - n2 << "\n";
    cout << "n1 * n2 = " << n1 * n2 << "\n";
    cout << "n1 / n2 = " << n1 / n2 << "\n\n";

    cout << "v1 radius = " << v1.polar_R().get() << "\n";
    cout << "v2 angle = " << v2.polar_Phi().get() << "\n";
    cout << "v1 + v2: ";
    printVector(v1 + v2);
}
