#include <iostream>
#include "matrix.hpp"

int main(int argc, char const *argv[])
{

    float a[2][4] = {{1, 2, 3, 2}, {4, 5, 6, 2}};
    matrix m = matrix(a);
    std::cout << " m=\n";
    m.show();
    float b[5][5];
    matrix n = {{6, 5, 4}, {3, 2, 1}};
    std::cout << " n=\n";
    n.show();
    n = m;

    std::cout << " n=\n";
    n.show();
    matrix o = {{1, 2}, {2, 1}, {1, 1}};
    m = o;
    std::cout << " m=\n";
    m.show();
    std::cout << " n=\n";
    n.show();
    std::cout << " o=\n";
    o.show();
    matrix p = m * n;
    std::cout << " p=\n";
    p.show();
    return 0;
}
