#include <glew.h>
enum {elementBuffer, arrayBuffer, numBuffers};
class GLobject{
public:
	GLfloat* getVertices(){ return m_vertices; }
	GLfloat* getColor(){ return m_color; }
	GLushort* getIndices(){ return m_indices; }
	GLobject(GLfloat* v, GLfloat* c, GLushort* i);
	GLobject();
	~GLobject();

	GLint LoadObject(const char* filename);
	GLvoid renderArrays(GLenum mode, GLint first, GLsizei count);
	GLvoid renderElements(GLenum mode, GLsizei count, GLenum type, GLvoid* offset);
private:
	GLfloat* m_vertices; GLsizei m_vertices_size;
	GLfloat* m_color; GLsizei m_color_size;
	GLushort* m_indices; GLsizei m_indices_size;
	GLuint m_buffers[numBuffers];
protected:
};