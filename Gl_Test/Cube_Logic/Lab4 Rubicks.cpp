#include <string>
#include <iostream>
#include <fstream>

#include "RCube.hpp"
#include "RSolver.hpp"

int main()
{
    RCube cube; 

    RSolver::shuffle(cube);

    std::cout << "Scramble is:\n" << "\n\n";

    cube.print_cube();

    std::cout << "\nBegin solving...\n";

    auto solution = RSolver::genetic_solution(cube);

    std::cout << "Solution is:\n" << solution.first << "\n\n";
     
    cube.rotate(solution.first);
    cube.print_cube();

    //RCube cube;
    //RSolver::shuffle(cube);

    //std::cout << "Created cube: \n\n";
    //cube.print_cube();

    //std::ofstream otp("C:\\Users\\fedor\\Desktop\\test.cube");
    //otp << cube;

    //otp.close();
    //
    //std::ifstream inp("C:\\Users\\fedor\\Desktop\\test.cube");
    //inp >> cube;

    //std::cout << "Cube from file: \n\n";
    //cube.print_cube();

    //
    //RCube cub;
    //cub = cube;
}
