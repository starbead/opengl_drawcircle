// assiagnment1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <vector>
#include "toys.h"

#define PI		3.14159265358979323846264338327950288

using namespace glm;
using namespace std;

void render(GLFWwindow* window);
void init();

int main(void)
{
	if (!glfwInit()) {
		exit(EXIT_FAILURE);
	}
#ifdef __APPLE__
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
	GLFWwindow* window = glfwCreateWindow(640, 480, "Starbead", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewInit();
	init();
	while (!glfwWindowShouldClose(window)) {
		render(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();
}

GLuint vertexBuffer = 0;
GLuint vertexArray = 0;
GLuint elementArray = 0;

vector<vec3> vertices;
vector<u32vec3> triangles;

Program prog;

float theta = 0.0;

void init() {
	prog.loadShaders("shader.vert", "shader.frag");

	vertices.push_back(vec3(0, 0, 0));
	for (int i = 0; i < 81; i++) {
		vertices.push_back(vec3(0.45*cos(theta), 0.6*sin(theta), 0));
		theta = theta + 0.025*PI;
	}

	for (int i = 0; i < 81; i++) {
		triangles.push_back(u32vec3(0, i + 1, i + 2));
	}

	glGenVertexArrays(1, &vertexArray);
	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(vec3), vertices.data(), GL_STATIC_DRAW);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, nullptr);

	glGenBuffers(1, &elementArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArray);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, triangles.size() * sizeof(u32vec3), triangles.data(), GL_STATIC_DRAW);
}

void render(GLFWwindow* window) {
	int width, height;

	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(prog.programID);

	glBindVertexArray(vertexArray);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementArray);

	glDrawElements(GL_TRIANGLES, triangles.size() * 3, GL_UNSIGNED_INT, 0);

	glfwSwapBuffers(window);
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.