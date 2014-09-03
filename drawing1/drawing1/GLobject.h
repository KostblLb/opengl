#include <glew.h>
// enum {elementBuffer, arrayBuffer, numBuffers};
class GLobject{
public:
	GLfloat* getVertices(){ return m_vertices; }
	GLfloat* getColor(){ return m_color; }
	GLushort* getIndices(){ return m_indices; }
	GLsizei getIndicesSize(){ return m_indices_len*sizeof(GLushort); }
	GLsizei getVerticesSize(){ return m_vertices_len*sizeof(GLfloat); }
	GLsizei getColorSize(){ return m_color_len*sizeof(GLfloat); }
	GLobject(GLfloat* v, GLfloat* c, GLushort* i);
	GLobject();
	~GLobject();

	GLint LoadObject(const char* filename);
	GLvoid renderArrays(GLenum mode, GLint first, GLsizei count);
	GLvoid renderElements(GLenum mode, GLsizei count, GLenum type, GLvoid* offset);
private:
	GLfloat* m_vertices; GLsizei m_vertices_len;
	GLfloat* m_color; GLsizei m_color_len;
	GLushort* m_indices; GLsizei m_indices_len;
	//	GLuint m_buffers[numBuffers];
protected:
};