#pragma once

#include <string>
#include <vector> 
#include <execution>
#include <utility>
#include <random>

namespace RSolver {

	template <class _RCube>
	unsigned metric(const _RCube& _Cube) {
		unsigned res = 0;
		for (auto& side : _Cube.cube) {
			auto center = side[1][1];
			for (auto& arr : side)
				for (auto& val : arr)
					res += val != center;
		}

		return res;
	}

	template <class _RCube>
	std::string shuffle(_RCube& _Cube) {
		std::vector <std::string> move_combos = {
		"R", "R2", "R'",
		"L", "L2", "L'",
		"F", "F2", "F'",
		"B", "B2", "B'",
		"U", "U2", "U'",
		"D", "D2", "D'",
		"^", ">", "<", "v"
		};

		std::random_device ran_dev;
		std::mt19937 random_engine(ran_dev());
		std::uniform_int_distribution <unsigned> distr(0, move_combos.size() - 1);

		std::string scram;
		for (size_t i = 0; i < 20; ++i) {
			scram.append(move_combos[distr(random_engine)]);
			scram.push_back(' ');
		}
		_Cube.rotate(scram);
		return scram;
	}




	template <class _RCube>
	std::pair <std::string, bool>  genetic_solution(const _RCube& _Cube)
	{
		std::vector <std::string> _Rotations = {
    // ������������ ���� ����� : ����� U, ������ � ������ �����
        "F' L' B' R' U' R U' B L F R U R' U",
    // ������������ ���� ����� : ����� U, ������ � ����� �����
        "F R B L U L' U B' R' F' L' U' L U'",
    // ������������ ���� ����� : ����� U, ������ ����� � ������ ������
        "U2 B U2 B' R2 F R' F' U2 F' U2 F R'",
    // ������������ ���� ����� : ����� U, ������ ����� � ������� �����
        "U2 R U2 R' F2 L F' L' U2 L' U2 L F'",
    // ������������ ���� ����� : ����� F, �������, ������, ������
        "U' B2 D2 L' F2 D2 B2 R' U'",
    // ������������ ���� ������� : ����� F, �������, ������ �����
        "U B2 D2 R F2 D2 B2 L U",
    // ����� U : ������ ���� < ->������ ����, ������ ������ ���� < ->������� ������ ����
        "D' R' D R2 U' R B2 L U' L' B2 U R2",
    // ����� U : ������ ���� < ->������ ����, ������ ������ ���� < ->����� ������ ����
        "D L D' L2 U L' B2 R' U R B2 U' L2",
    // ����� U : ������� ���� < ->������ ����, ������ ����� ���� < ->������� ������ ����
        "R' U L' U2 R U' L R' U L' U2 R U' L U'",
    // ����� U : ������� ���� < ->������ ����, ������ ������ ���� < ->������� ����� ����
        "L U' R U2 L' U R' L U' R U2 L' U R' U",
    // ������������ ���� ����� : ����� U, ������ ������, ������ ����� � ������� �����
        "F' U B U' F U B' U'",
    // ������������ ���� ����� : ����� U, ������ �����, ������ ������ � ������� ������
        "F U' B' U F' U' B U",
    // ������������ ���� ����� : ������ ����� ����� F, ������� ����� ����� F, ������� ����� ����� B
        "L' U2 L R' F2 R",
    // ������������ ���� ����� : ������� ����� ����� F, ������� ����� ����� B, ������ ����� ����� B
        "R' U2 R L' B2 L",
    //��������� � ���������� ������
			"^",
			">",
			"<",
			"v"
    }; 

		struct solution {
			_RCube Cube_;
			std::vector <unsigned> Moves_;
			unsigned quality_;
			bool operator< (const solution& _Right) const {
				return this->quality_ < _Right.quality_;
			}
		};

		std::random_device ran_dev;
		std::mt19937 random_engine(ran_dev());
		std::uniform_int_distribution <unsigned> distribution(0, _Rotations.size() - 1);

		std::vector <solution> population(50, { _Cube, {}, metric(_Cube)});

		std::cout << "Start cube:\n\n";
		_Cube.print_cube();

		while (population[0].quality_) {
			std::cout << "\nCurrent best\n";
			population[0].Cube_.print_cube();
			std::cout << "\n\n\n";

			std::vector <solution> next_population = population;
			for (size_t i = 0; i < 9; ++i) {
				for (solution sol : population) {
					sol.Moves_.push_back(distribution(ran_dev));
					sol.Cube_.rotate(_Rotations[sol.Moves_.back()]);
					sol.quality_ = metric(sol.Cube_);

					next_population.push_back(sol);
				}
			}

			for (solution& sol : next_population) {
					sol.Moves_.push_back(distribution(ran_dev));
					sol.Cube_.rotate(_Rotations[sol.Moves_.back()]);
					sol.quality_ = metric(sol.Cube_);
			}

			std::sort(next_population.begin(), next_population.end());
			population = std::vector <solution>(next_population.begin(), next_population.begin() + 50);
		}


		std::string ans;
		for (unsigned mov : population[0].Moves_)
			ans += _Rotations[mov] + " ";

		return { ans, true };
	}

	template <class _RCube>
	bool validate(const _RCube& _Cube)
	{
		unsigned short color_count[6];

		for (auto& side : _Cube.cube)
			for (auto& arr : side)
				for (auto& val : arr) 
				{
					if (val < 0 || val > 5)
						return false;
					++color_count[val];
				}

		for (auto cont : color_count) {
			if (cont != 9)
			{
				return false;
			}
		}
	}
}
