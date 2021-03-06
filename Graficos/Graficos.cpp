 // Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\gtx\transform.hpp"
#include "glm\glm.hpp"

#include <iostream>

#include "Vertice.h"
#include "Shader.h"
#include "Modelo.h"

#include <math.h>

using namespace std;

GLfloat red, green, blue;
GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;

Modelo *figura;
Modelo *cuadrado;

Shader *shader;

void actualizar()
{

}

void dibujar()
{
	
	figura->dibujar(GL_POLYGON);
	cuadrado->dibujar(GL_POLYGON);
	
}

void inicializarFigura()
{
	figura = new Modelo();
	Vertice v1 =
	{ vec4(-1.0f, 0.5f, 0.0f,1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v2 =
	{ vec4(0.0f, -0.5f, 0.0f,1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v3 =
	{ vec4(1.0f, 0.5f, 0.0f,1.0f), vec4(1.0f, 0.0f, 0.0f, 1.0f) };

	figura->vertices.push_back(v1);
	figura->vertices.push_back(v2);
	figura->vertices.push_back(v3);

}


void inicializarCuadrado()
{

	cuadrado = new Modelo();
Vertice v1 =
{ vec4(-0.5f, 0.5f, 0.0f,1.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f) };
Vertice v2 =
{ vec4(0.5f, 0.5f, 0.0f,1.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f) };
Vertice v3 =
{ vec4(0.5f, -0.5f, 0.0f,1.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f) };
Vertice v4 =
{ vec4(-0.5f, -0.5f, 0.0f,1.0f), vec4(0.0f, 1.0f, 0.0f, 0.0f) };

cuadrado->vertices.push_back(v1);
cuadrado->vertices.push_back(v2);
cuadrado->vertices.push_back(v3);
cuadrado->vertices.push_back(v4);
}


int main()
{
	//Declaración de Ventana
	GLFWwindow *window;
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 768;

	//Inicialización de GLFW
	if (!glfwInit())
	{
		//Si no se inicia bien termina la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicialización de la ventana
	window = glfwCreateWindow(ancho, alto, "Gráficos", NULL, NULL);

	//Verificación de creación de ventana
	if (!window)
	{
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}


	//Establecer "windows" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;

	//Inicializar GLEW
	GLenum glewError = glewInit();

	//Verificar si GLEW se inicializo bien
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL:" << version << endl;

	red = green = blue = 0.75f;

	inicializarCuadrado();
	inicializarFigura();
	

	//Crear instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");
	transformacionesID = glGetUniformLocation(shader->getID(), "transformaciones");

	//Desenlazar shader
	shader->desenlazarShader();

	figura->shader = shader;
	figura->inicializarVertexArray(posicionID, colorID);

	cuadrado->shader = shader;
	cuadrado->inicializarVertexArray(posicionID, colorID);



	//Crear un vertex array
	
	

	//Crear vertex buffer
	
	//De aqui en adelante se trabaja con este buffer


	//Llenar el buffer
	

	//Habilitar el atributo solo en el vertex array en uso
	glEnableVertexAttribArray(posicionID);

	//Especificar a OpenGL como usar la memoria con ese atributo
	glVertexAttribPointer(posicionID, 3, GL_FLOAT,
		GL_FALSE, sizeof(Vertice), 0);


	//Soltarlos
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);

	
	//Ciclo de Dibujo
	while (!glfwWindowShouldClose(window))
	{
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(red, green, blue, 1);

		//Limpiar pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de Dibujo
		actualizar();
		dibujar();

		//Intercambio de Buffers
		glfwSwapBuffers(window);
		//Buscar nueva señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

