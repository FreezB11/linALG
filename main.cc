#include <iostream>
#include "./src/include/LinALG/matrix.h"
#include "./src/include/LinALG/Solver/gaussian.h"


int main(){
    // matrix<float> test(20,20);
    // test.fill(1);
    // test.print();

    // matrix<float> neww = test.multiply(test);
    // neww.print();

    // // random unit test
    // matrix<float> randd(4,4);
    // randd.print();

    // gaussian elimination test
    matrix<float> gauss(3,4);
    vector<float> input = { 3, -2, 2, 9,
                            1, -2, 1, 5,
                            2, -1, -2, -1
                        };
    // for (int i = 0; i < 4; ++i) {
    //     for (int j = 0; j < 3; ++j) {
    //         gauss(i, j) = input[i * 3 + j];
    //     }
    // }
    gauss = gauss.fromARRAY(input);
    gauss.print();
    
    vector<float> ans = GaussianElimination(gauss);

    cout << "ans for gaussian elimination\n";
    for(auto answer : ans){
        cout << answer << " ";
    }
    cout << "\n";

    return 0;
}