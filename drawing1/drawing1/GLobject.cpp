#include "GLobject.h"
#include <iostream>
#include <fstream>


GLobject::GLobject(GLfloat* v, GLfloat* c, GLushort* i){
	m_vertices = new GLfloat(*v);
	m_color = new GLfloat(*c);
	m_indices = new GLushort(*i);
//	glGenBuffers(numBuffers, m_buffers);
}
GLobject::GLobject(){
//	glGenBuffers(numBuffers, m_buffers);
};

GLobject::~GLobject(){
	delete m_vertices;
	delete m_color;
	delete m_indices;
}
int GLobject::LoadObject(const char* filename){
	/*reading data*/
	int i;
	char* buffer = new char[64];
	std::fstream ifs;
	GLfloat* vertices = new GLfloat[256]; int vertices_len = 0;
	GLfloat* color = new GLfloat[256]; int color_len = 0;
	GLshort* indices = new GLshort[256]; int indices_len = 0;
	ifs.open(filename, std::fstream::in);
	for (i = 0; i < 256 && ifs.peek() != '/'&& ifs.peek() >=0; i++){
		ifs.get(buffer, 64, ',');
		vertices[i] = strtof(buffer, NULL);
		ifs.ignore();
	}
	vertices_len = i;
	if (ifs.peek() == '/')
		ifs.ignore();

	for (i = 0; i < 256 && ifs.peek() != '/'&& ifs.peek() >=0; i++){
		ifs.get(buffer, 64, ',');
		color[i] = strtof(buffer, NULL);
		ifs.ignore();
	}
	color_len = i;
	if (ifs.peek() == '/')
		ifs.ignore();
	char peek = ifs.peek();
	for (i = 0; i < 256 && ifs.peek() != '/' && ifs.peek() >=0; i++){
		ifs.get(buffer, 64, ',');
		indices[i] = strtol(buffer, NULL, 16);
		ifs.ignore();
	}
	indices_len = i;
	ifs.close();

	/*initialising the object*/
	m_vertices = new GLfloat[vertices_len]; m_vertices_len = vertices_len;
	memcpy_s(m_vertices, vertices_len*sizeof(GLfloat), vertices, vertices_len*sizeof(GLfloat)); 
	m_color = new GLfloat[color_len];m_color_len = color_len;
	memcpy_s(m_color, color_len*sizeof(GLfloat), color, color_len*sizeof(GLfloat));
	m_indices = new GLushort[indices_len]; m_indices_len = indices_len;
	memcpy_s(m_indices, indices_len*sizeof(GLushort), indices, indices_len*sizeof(GLushort));

	/*cleaning up*/
	delete vertices;
	delete color;
	delete indices;
	return 0;
}

GLvoid renderElements(GLenum mode, GLsizei count, GLenum type, GLvoid* offset){
	glDrawElements(mode, count, type, offset);
}

GLvoid renderArrays(GLenum mode, GLint first, GLsizei count){
	glDrawArrays(mode, first, count);
}