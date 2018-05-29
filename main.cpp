#include <iostream>
#include "matrix.hpp"

int main(int argc, char const *argv[])
{

    float a[2][3] = {{1, 2, 3}, {2, 3, 5}};
    matrix m = matrix(a);
    m.show();
    return 0;
}
