#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


using namespace std;

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // set the version of openGL to use
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // set the version of openGL to use
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // set the profile of openGL to use

	GLFWwindow* window = glfwCreateWindow(800, 800, "openGL project", NULL, NULL); // create a window
	if (window == NULL) {
		cout << "Couldn't open window" << endl;
		glfwTerminate();
		return 0; 
	}
	glfwMakeContextCurrent(window); // use the window 
	gladLoadGL(); // load the openGL functions
	glViewport(0, 0, 800, 800); // set the viewport to be the entire window
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f); // set the color to clear the screen to
	glClear(GL_COLOR_BUFFER_BIT); // clear the screen to the color we set
	glfwSwapBuffers(window); // swap the buffer
	while (!glfwWindowShouldClose(window)) { // while the window is open
		glfwPollEvents(); // poll for events
	}
	glfwDestroyWindow(window); // destroy the window
	glfwTerminate(); // terminate the glfw
	cout << "done" << endl;
	return 0;
}