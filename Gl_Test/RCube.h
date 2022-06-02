#pragma once
#include <string>
#include <array>
#include <vector>
#include <functional>
#include <queue>
#include <algorithm>
#include <unordered_map>

#include "Cube.h"
#include "Cube_Logic/RLogicCube.hpp"

class RCube
{
private:
    RLogicCube m_LCube;

    struct Element
    {
        Cube cube = Cube("HvostFace.png");
        glm::mat4 translation;
        glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), PI * 2, glm::vec3(0.0f, 0.0f, 1.0f));
        glm::mat4 temp_rotation = glm::rotate(glm::mat4(1.0f), PI * 2, glm::vec3(0.0f, 0.0f, 1.0f));


        glm::mat4 GetRotation() const { return temp_rotation * rotation; }
        const glm::mat4& GetTranslation() const { return translation; }
        
        glm::mat4 GetModel() const { return temp_rotation * rotation * translation; }
    };

    enum side_dir {
        up = 0,
        left = 2,
        right = 4,
        front = 1,
        back = 3,
        down = 5
    };

    using side = std::vector <std::vector <std::reference_wrapper<Element>>>;

    std::array <Element, 27> element_arr;

    std::vector <side> cube;

    unsigned short m_TurnFlag[6];

    const static std::array <std::pair <float, glm::vec3>, 6> m_Rotations;

    const static std::array <std::pair <float, glm::vec3>, 6> m_CubeRotations;


    std::queue <std::pair <short, unsigned short>> m_MoveQu;

    const static std::unordered_map <char, unsigned short> m_MoveDict;

    void RotateU();
    void RotateD();
    void RotateF();
    void RotateB();
    void RotateR();
    void RotateL();

    void RotateCubeBack();
    void RotateCubeRight();

    void RotateMatrixClockWise(RCube::side& _Matrx);
    void RotateMatrixContClockWise(RCube::side& _Matrx);
public:
    RCube();

    void Update();

    void Rotate(const std::string& _Move, unsigned short _FPS);

    void SetLogicCube(const RLogicCube& _Cube) { m_LCube = _Cube; }
    RLogicCube& GetLogicCube() { return m_LCube; };


    std::array <Element, 27> & GetCube() { return element_arr; };
};