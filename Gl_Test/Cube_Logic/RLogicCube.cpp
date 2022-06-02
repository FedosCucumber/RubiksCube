#include "RLogicCube.hpp"
#include <string>
#include <sstream>


 RLogicCube::RLogicCube() {
	cube.resize(6);

	cube[down] = 
	{
		{yellow, yellow, yellow},
		{yellow, yellow, yellow},
		{yellow, yellow, yellow}
	};

	cube[front] = 
	{
		{green, green, green},
		{green, green, green},
		{green, green, green},
	};

	cube[up] = {
		{white, white, white},
		{white, white, white},
		{white, white, white}
	};
	
	cube[right] = {
		{red, red, red},
		{red, red, red},
		{red, red, red}
	};

	cube[left] = 
	{
		{orange, orange, orange},
		{orange, orange, orange},
		{orange, orange, orange},
	};

	cube[back] = {
		{blue, blue, blue},
		{blue, blue, blue},
		{blue, blue, blue},
	};
}

void RLogicCube::rotate_matrix_clockwise(RLogicCube::side& _Matrx) {
	RLogicCube::side rotated(3, std::vector <short>(3));

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			rotated[j][2 - i] = _Matrx[i][j];
		}
	}

	_Matrx = std::move(rotated);
}

void RLogicCube::rotate_matrix_countclock(RLogicCube::side& _Matrx) {
	RLogicCube::side rotated(3, std::vector <short>(3));

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			rotated[j][i] = _Matrx[i][2 - j];
		}
	}

	_Matrx = std::move(rotated);
}

void RLogicCube::rotate_U() {
	std::vector <short> temp = cube[front][0];
	cube[front][0] = cube[right][0];
	std::swap(temp, cube[left][0]);
	std::swap(temp, cube[back][0]);
	std::swap(temp, cube[right][0]);


	rotate_matrix_clockwise(cube[up]);
}

void RLogicCube::rotate_cube_right() {
	RLogicCube::side temp = cube[up];
	cube[up] = cube[left];
	std::swap(temp, cube[right]);
	std::swap(temp, cube[down]);
	std::swap(temp, cube[left]);

	for (size_t i = 0; i < 6; ++i) {
		if (i != back)
			rotate_matrix_clockwise(cube[i]);
	}

	rotate_matrix_countclock(cube[back]);
}

void RLogicCube::rotate_cube_back() {
	RLogicCube::side temp = cube[up];
	cube[up] = cube[front];
	std::swap(temp, cube[back]);
	std::swap(temp, cube[down]);
	std::swap(temp, cube[front]);

	rotate_matrix_clockwise(cube[right]);
	rotate_matrix_countclock(cube[left]);

	std::reverse(cube[down].begin(), cube[down].end());
	std::reverse(cube[back].begin(), cube[back].end());

	for (size_t i = 0; i < 3; ++i) {
		std::reverse(cube[down][i].begin(), cube[down][i].end());
		std::reverse(cube[back][i].begin(), cube[back][i].end());
	}
}

void RLogicCube::print_cube() const {

	const char* color_codes[6];
	color_codes[red] = "\033[3;41;30m";
	color_codes[green] = "\033[3;42;30m";
	color_codes[yellow] = "\033[3;43;30m";
	color_codes[blue] = "\033[3;44;30m";
	color_codes[white] = "\33[3;47;30m";
	color_codes[orange] = "\33[3;101;30m";

	const char* default_color = "\033[0m";

	for (auto& arr : cube[up]) {
		std::cout << "      ";
		for (auto& val : arr) {
			std::cout << color_codes[val] << "  ";
		}
		std::cout << default_color;
		std::cout << "\n";
	}

	for (size_t i = 0; i < 3; ++i) {
		for (auto& val : cube[left][i])
			std::cout << color_codes[val] << "  ";
		for (auto& val : cube[front][i])
			std::cout << color_codes[val] << "  ";
		for (auto& val : cube[right][i])
			std::cout << color_codes[val] << "  ";
		for (auto& val : cube[back][i])
			std::cout << color_codes[val] << "  ";

		std::cout << default_color;
		std::cout << "\n";
	}

	for (auto& arr : cube[down]) {
		std::cout << "      ";
		for (auto& val : arr) {
			std::cout << color_codes[val] << "  ";
		}
		std::cout << default_color;
		std::cout << "\n";
	}
}

void RLogicCube::rotate(const std::string& _Move) {
	std::stringstream inp_moves(_Move);

	std::string cur_move;
	while (inp_moves >> cur_move) {
		if (cur_move[0] == 'U') {
			this->rotate_U();
			if (cur_move.size() > 1) {
				this->rotate_U();
				if (cur_move[1] == '\'')
					this->rotate_U();
			}
		}
		else if (cur_move[0] == 'D') {
			for (unsigned i = 0; i < 2; ++i)
				this->rotate_cube_back();

			this->rotate_U();
			if (cur_move.size() > 1) {
				this->rotate_U();
				if (cur_move[1] == '\'')
					this->rotate_U();
			}

			for (unsigned i = 0; i < 2; ++i)
				this->rotate_cube_back();
		}
		else if (cur_move[0] == 'L') {
			this->rotate_cube_right();

			this->rotate_U();
			if (cur_move.size() > 1) {
				this->rotate_U();
				if (cur_move[1] == '\'')
					this->rotate_U();
			}

			for (unsigned i = 0; i < 3; ++i)
				this->rotate_cube_right();
		}
		else if (cur_move[0] == 'R') {
			for (unsigned i = 0; i < 3; ++i)
				this->rotate_cube_right();

			this->rotate_U();
			if (cur_move.size() > 1) {
				this->rotate_U();
				if (cur_move[1] == '\'')
					this->rotate_U();
			}

			this->rotate_cube_right();
		}
		else if (cur_move[0] == 'B') {
			for (unsigned i = 0; i < 3; ++i)
				this->rotate_cube_back();

			this->rotate_U();
			if (cur_move.size() > 1) {
				this->rotate_U();
				if (cur_move[1] == '\'')
					this->rotate_U();
			}

			this->rotate_cube_back();
		}
		else if (cur_move[0] == 'F') {
			this->rotate_cube_back();

			this->rotate_U();
			if (cur_move.size() > 1) {
				this->rotate_U();
				if (cur_move[1] == '\'')
					this->rotate_U();
			}

			for (unsigned i = 0; i < 3; ++i)
				this->rotate_cube_back();
		}
		else if (cur_move == "<") {
			for (unsigned i = 0; i < 3; ++i)
				this->rotate_cube_right();
		}
		else if (cur_move == ">") {
			this->rotate_cube_right();
		}
		else if (cur_move == "^") {
			this->rotate_cube_back();
		}
		else if (cur_move == "v") {
			for (unsigned i = 0; i < 3; ++i)
				this->rotate_cube_back();
		}
	}
}

std::ostream& operator<<(std::ostream& _Otp, const RLogicCube& _Cube)
{
	for (auto& side : _Cube.cube)
		for (auto& arr : side)
			for (auto val : arr)
				_Otp.put(static_cast <short> (val));

	return _Otp;
}

std::istream& operator>>(std::istream& _Inp, RLogicCube& _Cube)
{
	for (auto& side : _Cube.cube)
		for (auto& arr : side)
			for (auto& val : arr)
				_Inp.get(reinterpret_cast <char&> (val));
	return _Inp;
}