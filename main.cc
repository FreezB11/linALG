#include <iostream>
#include "./src/include/LinALG/matrix.h"


int main(){
    matrix<float> test(20,20);
    test.fill(1);
    test.print();

    matrix<float> neww = test.multiply(test);

    neww.print();

    return 0;
}