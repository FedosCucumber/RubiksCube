#include "RCube.h"

#include <sstream>

static int CurFPS = 0;


const std::array <std::pair <float, glm::vec3>, 6> RCube::m_Rotations =
{
	std::make_pair <float, glm::vec3>(-PI / 2, glm::vec3(0.0f, 1.0f, 0.0f)), //up
	std::make_pair <float, glm::vec3>(-PI / 2, glm::vec3(0.0f, 0.0f, 1.0f)), //front
	std::make_pair <float, glm::vec3>(PI / 2, glm::vec3(1.0f, 0.0f, 0.0f)), //left
	std::make_pair <float, glm::vec3>(PI / 2, glm::vec3(0.0f, 0.0f, 1.0f)), //back
	std::make_pair <float, glm::vec3>(-PI / 2, glm::vec3(1.0f, 0.0f, 0.0f)), //right
	std::make_pair <float, glm::vec3>(PI / 2, glm::vec3(0.0f, 1.0f, 0.0f)), //down
};



RCube::RCube()
{
	//element_arr[16].cube.Unbind();
	//element_arr[16].cube = Cube("HvostFace.png");

	glm::mat4 trans_list[9] =
	{
		glm::translate(glm::mat4(1.0), glm::vec3(-100.0f, 0.0f, -100.0f)), //0
		glm::translate(glm::mat4(1.0), glm::vec3(0.0f,    0.0f, -100.0f)), //1
		glm::translate(glm::mat4(1.0), glm::vec3(100.0f,  0.0f, -100.0f)), //2

		glm::translate(glm::mat4(1.0), glm::vec3(-100.0f, 0.0f,  0.0f)),   //3
		glm::translate(glm::mat4(1.0), glm::vec3(0.0f,    0.0f,  0.0f)),   //4
		glm::translate(glm::mat4(1.0), glm::vec3(100.0f,  0.0f,  0.0f)),   //5

		glm::translate(glm::mat4(1.0), glm::vec3(-100.0f, 0.0f,  100.0f)), //6
		glm::translate(glm::mat4(1.0), glm::vec3(0.0f,    0.0f,  100.0f)), //7
		glm::translate(glm::mat4(1.0), glm::vec3(100.0f,  0.0f,  100.0f)), //8
	};


	glm::mat4 high = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, 100.0f, 0.0f));
	for (int i = 0; i < 9; i++)
	{
		element_arr[i].translation = trans_list[i] * high;
	}

	for (int i = 0; i < 9; i++)
	{
		element_arr[i + 9].translation = trans_list[i];
	}

	glm::mat4 low = glm::translate(glm::mat4(1.0), glm::vec3(0.0f, -100.0f, 0.0f));
	for (int i = 0; i < 9; i++)
	{
		element_arr[i + 18].translation = trans_list[i] * low;
	}


	cube = std::vector<side>(6, std::vector <std::vector <std::reference_wrapper<Element>>>(3, std::vector < std::reference_wrapper<Element> > (3, element_arr[0])));

	//up side init
	cube[up][0][0] = element_arr[0];
	cube[up][0][1] = element_arr[1];
	cube[up][0][2] = element_arr[2];

	cube[up][1][0] = element_arr[3];
	cube[up][1][1] = element_arr[4];
	cube[up][1][2] = element_arr[5];

	cube[up][2][0] = element_arr[6];
	cube[up][2][1] = element_arr[7];
	cube[up][2][2] = element_arr[8];

	//front side init
	cube[front][0][0] = element_arr[6];
	cube[front][0][1] = element_arr[7];
	cube[front][0][2] = element_arr[8];

	cube[front][1][0] = element_arr[15];
	cube[front][1][1] = element_arr[16];
	cube[front][1][2] = element_arr[17];

	cube[front][2][0] = element_arr[24];
	cube[front][2][1] = element_arr[25];
	cube[front][2][2] = element_arr[26];

	//left side init
	cube[left][0][0] = element_arr[0];
	cube[left][0][1] = element_arr[3];
	cube[left][0][2] = element_arr[6];

	cube[left][1][0] = element_arr[9];
	cube[left][1][1] = element_arr[12];
	cube[left][1][2] = element_arr[15];

	cube[left][2][0] = element_arr[18];
	cube[left][2][1] = element_arr[21];
	cube[left][2][2] = element_arr[24];

	//right side init
	cube[right][0][0] = element_arr[8];
	cube[right][0][1] = element_arr[5];
	cube[right][0][2] = element_arr[2];

	cube[right][1][0] = element_arr[17];
	cube[right][1][1] = element_arr[14];
	cube[right][1][2] = element_arr[11];

	cube[right][2][0] = element_arr[26];
	cube[right][2][1] = element_arr[23];
	cube[right][2][2] = element_arr[20];

	//back side init
	cube[back][0][0] = element_arr[2];
	cube[back][0][1] = element_arr[1];
	cube[back][0][2] = element_arr[0];

	cube[back][1][0] = element_arr[11];
	cube[back][1][1] = element_arr[10];
	cube[back][1][2] = element_arr[9];

	cube[back][2][0] = element_arr[20];
	cube[back][2][1] = element_arr[19];
	cube[back][2][2] = element_arr[18];

	//down side init
	cube[down][0][0] = element_arr[24];
	cube[down][0][1] = element_arr[25];
	cube[down][0][2] = element_arr[26];

	cube[down][1][0] = element_arr[21];
	cube[down][1][1] = element_arr[22];
	cube[down][1][2] = element_arr[23];

	cube[down][2][0] = element_arr[18];
	cube[down][2][1] = element_arr[19];
	cube[down][2][2] = element_arr[20];
}


void RCube::Update()
{
	
	if (m_MoveQu.empty())
		return;

	auto& [type, count] = m_MoveQu.front();
	
	switch (type)
	{
	case 10:
		m_MoveQu.pop();
		RotateCubeBack();
		return;
	case 11:
		m_MoveQu.pop();
		RotateCubeRight();
		return;
	case 12:
		m_MoveQu.pop();
		RotateCubeBack();
		RotateCubeBack();
		RotateCubeBack();
		return;
	case 13:
		m_MoveQu.pop();
		RotateCubeRight();
		RotateCubeRight();
		RotateCubeRight();
		return;
	default: 
		break;
	}

	if (CurFPS < count)
		CurFPS = count;

	auto& [deg, axis] = m_Rotations[type];

	for (auto& arr : cube[type])
		for (auto& val : arr)
			val.get().temp_rotation *= glm::rotate(glm::mat4(1.0f), deg / CurFPS, axis);

	--count;

	if (count == 0)
	{
		for (auto& arr : cube[type])
			for (auto& val : arr)
			{
				val.get().rotation = glm::rotate(glm::mat4(1.0f), deg, axis) * val.get().rotation;
				val.get().temp_rotation = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			}
		if (!count)
			m_MoveQu.pop();

		switch (type)
		{
		case up: RotateU(); break;
		case down: RotateD(); break;
		case left: RotateL(); break;
		case right: RotateR(); break;
		case front: RotateF(); break;
		case back: RotateB(); break;
		default: break;
		}

		CurFPS = 0;
	}
}

void RCube::Rotate(const std::string& _Moves, unsigned short _FPS)
{
	std::stringstream ss(_Moves);
	std::string _Move;
	while (ss >> _Move) {
		m_MoveQu.push({ m_MoveDict.find(_Move[0])->second, _FPS });

		if (_Move.size() > 1)
		{
			m_MoveQu.push(m_MoveQu.back());
			if (_Move[1] == '\'')
			{
				m_MoveQu.push(m_MoveQu.back());
			}
		}
	}
}



const std::unordered_map <char, unsigned short> RCube::m_MoveDict =
{
//  Cube rotations
	{'^', 10},
	{'>', 11},
	{'v', 12},
	{'<', 13},

//  Side rotations
	{'U', up},
	{'D', down},
	{'F', front},
	{'B', back},
	{'R', right},
	{'L', left}
};

void RCube::RotateU()
{	
	RotateMatrixClockWise(cube[up]);

	cube[back][0][0] = cube[up][0][2];
	cube[back][0][1] = cube[up][0][1];
	cube[back][0][2] = cube[up][0][0];

	cube[left][0][0] = cube[up][0][0];
	cube[left][0][1] = cube[up][1][0];
	cube[left][0][2] = cube[up][2][0];

	cube[front][0][0] = cube[up][2][0];
	cube[front][0][1] = cube[up][2][1];
	cube[front][0][2] = cube[up][2][2];

	cube[right][0][0] = cube[up][2][2];
	cube[right][0][1] = cube[up][1][2];
	cube[right][0][2] = cube[up][0][2];

}

void RCube::RotateD()
{
	RotateMatrixClockWise(cube[down]);

	cube[front][2][0] = cube[down][0][0];
	cube[front][2][1] = cube[down][0][1];
	cube[front][2][2] = cube[down][0][2];

	cube[right][2][0] = cube[down][0][2];
	cube[right][2][1] = cube[down][1][2];
	cube[right][2][2] = cube[down][2][2];

	cube[back][2][0] = cube[down][2][2];
	cube[back][2][1] = cube[down][2][1];
	cube[back][2][2] = cube[down][2][0];

	cube[left][2][0] = cube[down][2][0];
	cube[left][2][1] = cube[down][1][0];
	cube[left][2][2] = cube[down][0][0];
}

void RCube::RotateF()
{
	RotateMatrixClockWise(cube[front]);

	cube[up][2][0] = cube[front][0][0];
	cube[up][2][1] = cube[front][0][1];
	cube[up][2][2] = cube[front][0][2];

	cube[left][0][2] = cube[front][0][0];
	cube[left][1][2] = cube[front][1][0];
	cube[left][2][2] = cube[front][2][0];

	cube[right][0][0] = cube[front][0][2];
	cube[right][1][0] = cube[front][1][2];
	cube[right][2][0] = cube[front][2][2];

	cube[down][0][0] = cube[front][2][0];
	cube[down][0][1] = cube[front][2][1];
	cube[down][0][2] = cube[front][2][2];
}

void RCube::RotateB()
{
	RotateMatrixClockWise(cube[back]);

	cube[up][0][0] = cube[back][0][2];
	cube[up][0][1] = cube[back][0][1];
	cube[up][0][2] = cube[back][0][0];

	cube[right][0][2] = cube[back][0][0];
	cube[right][1][2] = cube[back][1][0];
	cube[right][2][2] = cube[back][2][0];

	cube[down][2][0] = cube[back][2][2];
	cube[down][2][1] = cube[back][2][1];
	cube[down][2][2] = cube[back][2][0];

	cube[left][0][0] = cube[back][0][2];
	cube[left][1][0] = cube[back][1][2];
	cube[left][2][0] = cube[back][2][2];
}

void RCube::RotateR()
{
	RotateMatrixClockWise(cube[right]);

	cube[up][0][2] = cube[right][0][2];
	cube[up][1][2] = cube[right][0][1];
	cube[up][2][2] = cube[right][0][0];

	cube[down][0][2] = cube[right][2][0];
	cube[down][1][2] = cube[right][2][1];
	cube[down][2][2] = cube[right][2][2];

	cube[back][0][0] = cube[right][0][2];
	cube[back][1][0] = cube[right][1][2];
	cube[back][2][0] = cube[right][2][2];

	cube[front][0][2] = cube[right][0][0];
	cube[front][1][2] = cube[right][1][0];
	cube[front][2][2] = cube[right][2][0];
}

void RCube::RotateL()
{
	RotateMatrixClockWise(cube[left]);

	cube[up][0][0] = cube[left][0][0];
	cube[up][1][0] = cube[left][0][1];
	cube[up][2][0] = cube[left][0][2];

	cube[front][0][0] = cube[left][0][2];
	cube[front][1][0] = cube[left][1][2];
	cube[front][2][0] = cube[left][2][2];

	cube[down][0][0] = cube[left][2][2];
	cube[down][1][0] = cube[left][2][1];
	cube[down][2][0] = cube[left][2][0];

	cube[back][0][2] = cube[left][0][0];
	cube[back][1][2] = cube[left][1][0];
	cube[back][2][2] = cube[left][2][0];
}

void RCube::RotateCubeBack()
{
	RCube::side temp = cube[up];
	cube[up] = cube[front];
	std::swap(temp, cube[back]);
	std::swap(temp, cube[down]);
	std::swap(temp, cube[front]);

	RotateMatrixClockWise(cube[right]);
	RotateMatrixContClockWise(cube[left]);

	std::reverse(cube[down].begin(), cube[down].end());
	std::reverse(cube[back].begin(), cube[back].end());

	for (size_t i = 0; i < 3; ++i) {
		std::reverse(cube[down][i].begin(), cube[down][i].end());
		std::reverse(cube[back][i].begin(), cube[back][i].end());
	}


	glm::mat4 rotate = glm::rotate(glm::mat4(1.0), -PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
	
	for (auto& elem : element_arr)
	{
		elem.rotation = rotate * elem.rotation;
	}
}

void RCube::RotateCubeRight() {
	RCube::side temp = cube[up];
	cube[up] = cube[left];
	std::swap(temp, cube[right]);
	std::swap(temp, cube[down]);
	std::swap(temp, cube[left]);

	for (size_t i = 0; i < 6; ++i) {
		if (i != back)
			RotateMatrixClockWise(cube[i]);
	}

	RotateMatrixContClockWise(cube[back]);

	glm::mat4 rotate = glm::rotate(glm::mat4(1.0), -PI / 2, glm::vec3(0.0f, 0.0f, 1.0f));

	for (auto& elem : element_arr)
	{
		elem.rotation = rotate * elem.rotation;
	}
}



void RCube::RotateMatrixClockWise(RCube::side& _Matrx) {
	RCube::side rotated = _Matrx;

	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			rotated[j][2 - i] = _Matrx[i][j];
		}
	}
	_Matrx = std::move(rotated);
}

void RCube::RotateMatrixContClockWise(RCube::side& _Matrx)
{
	RCube::side rotated = _Matrx;
	for (size_t i = 0; i < 3; ++i) {
		for (size_t j = 0; j < 3; ++j) {
			rotated[j][i] = _Matrx[i][2 - j];
		}
	}
	_Matrx = std::move(rotated);
}
