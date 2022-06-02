#pragma once

#include <vector>
#include <iostream>
#include <string>

class RLogicCube {
public:
	
	enum side_dir {
		up = 0,
		left = 2,
		right = 4,
		front = 1,
		back = 3,
		down = 5
	};

	enum color {
		white = 0,
		red = 4,
		green = 1,
		blue = 3,
		orange = 2,
		yellow = 5

	};

	using side = std::vector <std::vector <short>>;

	std::vector <side> cube;

	RLogicCube();

	void print_cube() const;

	void rotate(const std::string&);

	friend std::ostream& operator<<(std::ostream& _Otp, const RLogicCube& _Cube);
	friend std::istream& operator>>(std::istream& _Inp, RLogicCube& _Cube);
private:
	void rotate_U();
	
	void rotate_cube_right();
	void rotate_cube_back();

	void rotate_matrix_clockwise(RLogicCube::side&);
	void rotate_matrix_countclock(RLogicCube::side&);
};