#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include "OpenglGameLoop.hpp"

int main(void)
{
	OpenGL_Engine::OpenGLGameLoop OLoop;
	OLoop.Run();
}