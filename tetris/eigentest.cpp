#include <iostream>
#include <Eigen/Dense>
 
// using Eigen::MatrixXd;
 
int main()
{
    Eigen::MatrixXd m(2,2);
    m(0,0) = 3;
    m(1,0) = 2.5;
    m(0,1) = -1;
    m(1,1) = m(1,0) + m(0,1);
    std::cout << m << std::endl;

    Eigen::MatrixXd m2(2,2);
    m2 << 1, 2, 3, 4;

    std::cout << "manual print:\n";
    std::cout << "size: " << m2.size() << "\n";
    std::cout << "m2[0][1]: " << m2(0,1) << "\n";
    // for (uint r = 0; r < m2.size(); r++){
    //     for (uint c = 0; c < m2[r].size(); c++)
    // }    
    auto m3 = m2 * m;
    std::cout << "m2: " << m2 << "\n";
    std::cout << m3 << "\n";
}