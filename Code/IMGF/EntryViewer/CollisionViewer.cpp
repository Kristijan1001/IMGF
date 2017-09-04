#include <Windows.h>
#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif
#include "GL/glew.h"
#include "GL/wglew.h"
#include "CollisionViewer.h"
#include "IMGF.h"
#include "EntryViewerManager.h"
#include "Format/COL/COLEntry.h"
#include "Static/Math.h"
#include "Static/String.h"
#include "Static/File.h"
#include "Static/Input.h"
#include "Static/Debug.h"
#include "Type/Vector/Vec3f.h"
#include <vector>
//#include <GL/freeglut.h>
//#include <GL/glut.h>
//#include <GL/freeglut.h>
//#include "Shader.h"
#include <include/GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32 1
#define GLFW_EXPOSE_NATIVE_WGL 1
#include <include/GLFW/glfw3native.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include "OGLFT.h"
//#define STB_TRUETYPE_IMPLEMENTATION
//#include "stb_truetype.h"
#include "freetype-gl.h"
#include "mat4.h"
#include "shader.h"
#include "vertex-buffer.h"
#include "Format/COL/COLFormat.h"
#include <fstream>
#include <unordered_map>

using namespace std;
using namespace bxcf;
using namespace bxgi;
using namespace imgf;

#define GL_CLAMP_TO_EDGE 0x812F

struct Character;

//OGLFT::Monochrome*			face;
Vec3f					vecCameraPosition;
//Vec3f					vecCameraLookAtPosition;
Vec3f					vecCameraRotation;
Vec2f					g_vecLastMousePosition = { 0.0f, 0.0f };
bool						g_bLeftMouseButtonDown = false;
unordered_map<int, bool>	g_umapKeysDown;
float32 angle = 0;
float32 fOrbitAngle = 0.0; // degrees
FT_Bitmap g_FontTest1;
GLuint ProgramObject_3DScene; // for 3D Scene
GLuint ProgramObject; // for text rendering
GLuint VAO, VBO;
unordered_map<char, Character> Characters;
bool g_bText2DStuffLoaded = false;
FT_Face g_face;
GLuint vertexShader, fragmentShader;
GLuint vertexShader2, fragmentShader2;



GLuint shader;
vertex_buffer_t *buffer;
mat4   model, view, projection;

typedef struct {
	float32 x, y, z;    // position
	float32 s, t;       // texture
	float32 r, g, b, a; // color
} vertex_t;



void add_text(vertex_buffer_t * buffer, texture_font_t * font,
	wchar_t * text, vec4 * color, vec2 * pen)
{
	size_t i;
	float32 r = color->red, g = color->green, b = color->blue, a = color->alpha;
	for (i = 0; i<wcslen(text); ++i)
	{
		texture_glyph_t *glyph = texture_font_get_glyph(font, text[i]);
		if (glyph != NULL)
		{
			float32 kerning = 0.0f;
			if (i > 0)
			{
				kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
			}
			pen->x += kerning;
			int x0 = (int)(pen->x + glyph->offset_x);
			int y0 = (int)(pen->y + glyph->offset_y);
			int x1 = (int)(x0 + glyph->width);
			int y1 = (int)(y0 - glyph->height);
			float32 s0 = glyph->s0;
			float32 t0 = glyph->t0;
			float32 s1 = glyph->s1;
			float32 t1 = glyph->t1;
			GLuint indices[6] = { 0, 1, 2, 0, 2, 3 };
			vertex_t vertices[4] = { { (float32)x0, (float32)y0, (float32)0, s0, t0, r, g, b, a },
			{ (float32)x0, (float32)y1, (float32)0, s0, t1, r, g, b, a },
			{ (float32)x1, (float32)y1, (float32)0, s1, t1, r, g, b, a },
			{ (float32)x1, (float32)y0, (float32)0, s1, t0, r, g, b, a } };
			vertex_buffer_push_back(buffer, vertices, 4, indices, 6);
			pen->x += glyph->advance_x;
		}
	}
}

void						perspectiveGL(GLdouble fovY, GLdouble aspect, GLdouble zNear, GLdouble zFar)
{
	const GLdouble pi = 3.1415926535897932384626433832795;
	GLdouble fW, fH;

	//fH = tan( (fovY / 2) / 180 * pi ) * zNear;
	fH = tan(fovY / 360 * pi) * zNear;
	fW = fH * aspect;

	glFrustum(-fW, fW, -fH, fH, zNear, zFar);
}

/*
void				gluLookAt(GLdouble eyex, GLdouble eyey, GLdouble eyez, GLdouble centerx,
GLdouble centery, GLdouble centerz, GLdouble upx, GLdouble upy,
GLdouble upz)
{
float32 forward[3], side[3], up[3];
GLfloat m[4][4];

forward[0] = centerx - eyex;
forward[1] = centery - eyey;
forward[2] = centerz - eyez;

up[0] = upx;
up[1] = upy;
up[2] = upz;

normalize(forward);

// Side = forward x up
cross(forward, up, side);
normalize(side);

// Recompute up as: up = side x forward
cross(side, forward, up);

__gluMakeIdentityf(&m[0][0]);
m[0][0] = side[0];
m[1][0] = side[1];
m[2][0] = side[2];

m[0][1] = up[0];
m[1][1] = up[1];
m[2][1] = up[2];

m[0][2] = -forward[0];
m[1][2] = -forward[1];
m[2][2] = -forward[2];

glMultMatrixf(&m[0][0]);
glTranslated(-eyex, -eyey, -eyez);
}
*/

class SolidSphere
{
protected:
	vector<GLfloat> vertices;
	vector<GLfloat> normals;
	vector<GLfloat> texcoords;
	vector<GLushort> indices;

public:
	SolidSphere(float32 radius, unsigned int rings, unsigned int sectors)
	{
		float32 const R = 1.0f / (float32)(rings - 1);
		float32 const S = 1.0f / (float32)(sectors - 1);
		int r, s;

		vertices.resize(rings * sectors * 3);
		normals.resize(rings * sectors * 3);
		texcoords.resize(rings * sectors * 2);
		vector<GLfloat>::iterator v = vertices.begin();
		vector<GLfloat>::iterator n = normals.begin();
		vector<GLfloat>::iterator t = texcoords.begin();
		for (r = 0; r < (int32)rings; r++) for (s = 0; s < (int32)sectors; s++) {
			float32 const y = (float32)sin((float32)-M_PI_2 + (float32)M_PI * (float32)r * R);
			float32 const x = (float32)cos(2.0f * (float32)M_PI * (float32)s * S) * sin((float32)M_PI * (float32)r * R);
			float32 const z = (float32)sin(2.0f * (float32)M_PI * (float32)s * S) * sin((float32)M_PI * (float32)r * R);

			*t++ = s*S;
			*t++ = r*R;

			*v++ = x * radius;
			*v++ = y * radius;
			*v++ = z * radius;

			*n++ = x;
			*n++ = y;
			*n++ = z;
		}

		indices.resize(rings * sectors * 4);
		vector<GLushort>::iterator i = indices.begin();
		for (r = 0; r < (int32)rings - 1; r++) for (s = 0; s < (int32)sectors - 1; s++) {
			*i++ = r * sectors + s;
			*i++ = r * sectors + (s + 1);
			*i++ = (r + 1) * sectors + (s + 1);
			*i++ = (r + 1) * sectors + s;
		}
	}

	void draw(GLfloat x, GLfloat y, GLfloat z)
	{
		//glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslatef(x, y, z);

		glEnableClientState(GL_VERTEX_ARRAY);
		//glEnableClientState(GL_NORMAL_ARRAY);
		//glEnableClientState(GL_TEXTURE_COORD_ARRAY);

		glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
		//glNormalPointer(GL_FLOAT, 0, &normals[0]);
		//glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
		glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
		glPopMatrix();

		//glEnableClientState(GL_VERTEX_ARRAY);
		//glDisableClientState(GL_NORMAL_ARRAY);
		//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
};

struct Character {
	GLuint     TextureID;  // ID handle of the glyph texture
	signed int Size[2];    // Size of glyph
	signed int Bearing[2]; // Offset from baseline to left/top of glyph
	GLuint     Advance;    // Offset to advance to next glyph
};

uint32 getFileLength(ifstream& file)
{
	if (!file.good()) return 0;

	streampos pos = file.tellg();
	file.seekg(0, ios::end);
	streampos len = file.tellg();
	file.seekg(ios::beg);

	return (uint32)len;
}

int loadshader(char* filename, GLchar** ShaderSource, uint32* len)
{
	ifstream file;
	file.open(filename, ios::in); // opens as ASCII!
	if (!file) return -1;

	*len = getFileLength(file);

	if (len == 0) return -2;   // Error: Empty File 

	*ShaderSource = (GLchar*) new char[(*len) + 1];
	if (*ShaderSource == 0) return -3;   // can't reserve memory

	// len isn't always strlen cause some characters are stripped in ascii read...
	// it is important to 0-terminate the real length later, len is just max possible value... 
	//*ShaderSource[*len] = 0;

	unsigned int i = 0;
	while (file.good())
	{
		*ShaderSource[i] = file.get();       // get character from file.
		if (!file.eof())
			i++;
	}

	*ShaderSource[i] = 0;  // 0-terminate it at the correct position

	file.close();

	return 0; // No Error
}

void unloadshader(GLubyte** ShaderSource)
{
	if (*ShaderSource != 0)
		delete[] * ShaderSource;
	*ShaderSource = 0;
}

void						RenderText(string text, GLfloat x, GLfloat y, GLfloat scale, vector<uint8> color)
{
	// Activate corresponding render state	
	//s.Use();
	//glUniform3f(glGetUniformLocation(s.Program, "textColor"), color.x, color.y, color.z);

	if (color.size() == 0)
	{
		color = { 0, 0, 0 };
	}

	//glUseProgram(ProgramObject);
	//if (glGetError()) Input::showMessage("glUseProgram error", "Error");

	GLint iLocation = glGetUniformLocation(ProgramObject, "textColor");
	if (glGetError()) Input::showMessage("glGetUniformLocation error", "Error");

	//glUniform3f(glGetUniformLocation(ProgramObject, "textColor"), color[0], color[1], color[2]);
	glUniform3f(iLocation, 0.9f, 0.1f, 0.1f);
	if (glGetError()) Input::showMessage("glUniform3f error", "Error");

	glActiveTexture(GL_TEXTURE0);
	if (glGetError()) Input::showMessage("glActiveTexture error", "Error");

	glBindVertexArray(VAO);
	if (glGetError()) Input::showMessage("glBindVertexArray error", "Error");

	// Iterate through all characters
	string::const_iterator c;
	for (c = text.begin(); c != text.end(); c++)
	{
		Character ch = Characters[*c];

		GLfloat xpos = x + ch.Bearing[0] * scale;
		GLfloat ypos = y - (ch.Size[1] - ch.Bearing[1]) * scale;

		GLfloat w = ch.Size[0] * scale;
		GLfloat h = ch.Size[1] * scale;
		// Update VBO for each character
		GLfloat vertices[6][4] = {
			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos, ypos, 0.0, 1.0 },
			{ xpos + w, ypos, 1.0, 1.0 },

			{ xpos, ypos + h, 0.0, 0.0 },
			{ xpos + w, ypos, 1.0, 1.0 },
			{ xpos + w, ypos + h, 1.0, 0.0 }
		};
		// Render glyph texture over quad
		glBindTexture(GL_TEXTURE_2D, ch.TextureID);
		// Update content of VBO memory
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		// Render quad
		glDrawArrays(GL_TRIANGLES, 0, 6);
		// Now advance cursors for next glyph (note that advance is number of 1/64 pixels)
		x += (ch.Advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void						custom_fbsize_callback(GLFWwindow* window, int width, int height)
{
	/* use system width,height */
	glViewport(0, 0, width, height);

	/* use custom width,height */
	//glViewport(0, 0, <CUSTOM_WIDTH>, <CUSTOM_HEIGHT>);

	glm::mat4 projection2 = glm::ortho(0.0f, static_cast<GLfloat>(width), 0.0f, static_cast<GLfloat>(height));
	//shader.Use();
	glUniformMatrix4fv(glGetUniformLocation(ProgramObject_3DScene, "projection"), 1, GL_FALSE, glm::value_ptr(projection2));

	mat4_set_orthographic(&projection, 0.0f, (float32)width, 0.0f, (float32)height, -1.0f, 1.0f);
}

void						handleKeypress(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		g_umapKeysDown[key] = true;
		break;
	case GLFW_RELEASE:
		//g_umapKeysDown[key] = false;
		g_umapKeysDown.erase(key);
		break;
	}
}
void						handleCursorMove(GLFWwindow* window, double xpos, double ypos)
{
	if (!g_bLeftMouseButtonDown)
	{
		return;
	}

	Vec2f vecNewPosition = Vec2f((float32)xpos, (float32)ypos);
	if (g_vecLastMousePosition.x != 0.0f && g_vecLastMousePosition.y != 0.0f)
	{
		const Vec2f vecCursorMoveMultiplier = { 0.3f, 0.3f };
		Vec2f vecPositionDifference = Vec2f(vecNewPosition.x - g_vecLastMousePosition.x, vecNewPosition.y - g_vecLastMousePosition.y);
		vecCameraRotation.z += Math::convertDegreesToRadians(vecPositionDifference.x * vecCursorMoveMultiplier.x);
		vecCameraRotation.x += Math::convertDegreesToRadians(vecPositionDifference.y * vecCursorMoveMultiplier.y);
	}

	g_vecLastMousePosition = vecNewPosition;
}
void						handleCursorButton(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1)
	{
		switch (action)
		{
		case GLFW_PRESS:
			g_bLeftMouseButtonDown = true;
			break;
		case GLFW_RELEASE:
			g_bLeftMouseButtonDown = false;
			g_vecLastMousePosition = { 0.0f, 0.0f };
			break;
		}
	}
}
void						handleScrollInput(GLFWwindow * 	window, double dXOffset, double dYOffset)
{
	float32 fMouseWheelScrollMultiplier = 5.0f;
	CollisionViewer *pCollisionViewer = getIMGF()->getEntryViewerManager()->getCollisionViewer();
	pCollisionViewer->zoomCamera((float32)-dYOffset * fMouseWheelScrollMultiplier);
}

CollisionViewer::CollisionViewer(void) :
	m_bWindowIsOpening(false),
	m_bEntryIsChanging(false),
	m_pCOLFile(nullptr),
	m_uiLastKeyProcessTime(0)
{
	m_pFTLibrary = new FT_Library;
}
CollisionViewer::~CollisionViewer(void)
{
	for (SolidSphere *pSolidSphere : m_vecCollisionSpheresGL)
	{
		delete pSolidSphere;
	}
	m_vecCollisionSpheresGL.clear();
	
	delete m_pFTLibrary;
}

void						CollisionViewer::init(void)
{
	// GLFW (not GLEW) should be initiailized when the thread has started, as GLFW will be shutdown (via glfwTerminate) when the window closes.
	// GLEW (not GLFW) must be initialized after the GLFW window has been created, rather than here.
}
void						CollisionViewer::uninit(void)
{

}

void						CollisionViewer::initGLFW(void)
{
	glfwInit();
}
void						CollisionViewer::initGLEW(void)
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		Input::showMessage("Failed to load GLEW library.", "Library Load Failed", MB_OK);
	}
}

void						CollisionViewer::reset(void)
{
	if(m_pCOLFile != nullptr)
	{
		delete m_pCOLFile;
	}
}

void						CollisionViewer::applyWindowTitle(void)
{
	//glutSetWindowTitle(strWindowTitle.c_str());
	glfwSetWindowTitle(getWindow(), getWindowTitle().c_str());
}

void						CollisionViewer::moveCamera(uint8 ucAxisIndex, bool bPositivePositionChange, float32 fMoveDistance)
{
	if (!bPositivePositionChange)
	{
		fMoveDistance = -fMoveDistance;
	}

	switch (ucAxisIndex)
	{
	case 0:
	{
		float32 fAngleRad = vecCameraRotation.z;
		vecCameraPosition = Math::getPositionInFrontOfPosition(vecCameraPosition, fAngleRad, fMoveDistance);
		//vecCameraLookAtPosition = Math::getPositionInFrontOfPosition(vecCameraLookAtPosition, fAngleRad, fPositionChange);
		break;
	}
	case 1:
	{
		float32 fAngleRad = Math::convertDegreesToRadians(90.0f) + vecCameraRotation.z;
		vecCameraPosition = Math::getPositionInFrontOfPosition(vecCameraPosition, fAngleRad, fMoveDistance);
		//vecCameraLookAtPosition = Math::getPositionInFrontOfPosition(vecCameraLookAtPosition, fAngleRad, fPositionChange);
		break;
	}
	case 2:
		vecCameraPosition.z += fMoveDistance;
		//vecCameraLookAtPosition.z += fPositionChange;
		break;
	}

	//vecCameraRotation.z = Math::getAngleBetweenPoints(vecCameraPosition, vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f);
}
void						CollisionViewer::zoomCamera(float32 fMoveDistance)
{
	float32 fXAngle = vecCameraRotation.x + Math::convertDegreesToRadians(90.0f);
	float32 fZAngle = vecCameraRotation.z + Math::convertDegreesToRadians(90.0f);
	Vec3f vecCameraPositionOffset = Math::getCartesianFromSpherical(fMoveDistance, fXAngle, fZAngle);
	vecCameraPositionOffset.z = -vecCameraPositionOffset.z;
	vecCameraPosition = vecCameraPosition + vecCameraPositionOffset;
}

void						CollisionViewer::openWindow(void)
{
	/*
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Collision Viewer");
	*/

	GLFWwindow* window = glfwCreateWindow(1200, 675, "Collision Viewer", NULL, NULL);
	setWindow(window);

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(getWindow(), custom_fbsize_callback);
}
void						CollisionViewer::closeWindow(void)
{
	glfwDestroyWindow(getWindow());
}

void						CollisionViewer::processWindow(void)
{
	while (!glfwWindowShouldClose(getWindow()))
	{
		// Loop until the user closes the window
		if (isWindowOpen())
		{
			// Render
			bool bMinimized = IsIconic(glfwGetWin32Window(getWindow())) || glGetError() != GL_NO_ERROR; // IsIconic returns true once while the rendering function's won't work. so skip first render occurrence.
			if (!isEntryChanging() && !bMinimized)
			{
				processKeys();
				render();
			}

			// Swap front and back buffers
			glfwSwapBuffers(getWindow());

			//render2DText();

			//glFinish();

			

			// Poll for and process events
			glfwPollEvents();
		}
	}
	glfwTerminate();
	setWindowIsOpen(false);
}

DWORD WINAPI				CollisionViewer::onThreadStarted_CollisionViewer(LPVOID lpParam)
{

	CollisionViewer *pCollisionViewer = (CollisionViewer*)lpParam;
	pCollisionViewer->onThreadStarted();
	return 0;
}

void						CollisionViewer::onThreadStarted(void)
{
	initGLFW();

	openWindow();
	applyWindowTitle();
	
	initGLEW();

	glfwSetKeyCallback(getWindow(), handleKeypress);
	glfwSetCursorPosCallback(getWindow(), handleCursorMove);
	glfwSetMouseButtonCallback(getWindow(), handleCursorButton);
	glfwSetScrollCallback(getWindow(), handleScrollInput);
	
	glClearColor(1.0, 0.5, 0.0, 0.5);

	//glScissor(300, 0, 500, 500);

	int w, h;
	glfwGetWindowSize(getWindow(), &w, &h);

	//face = new OGLFT::Monochrome("arial.ttf", 24);

	glViewport(0, 0, w, h);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_uiLastKeyProcessTime = GetTickCount();


	/*
	initTextStuff();



	mat4_set_orthographic(&projection, 0, w, 0, h, -1, 1);

	size_t i;
	texture_font_t *font = 0;
	texture_atlas_t *atlas = texture_atlas_new(512, 512, 1);
	const char * filename = "C:\\Users\\James\\Documents\\Visual Studio 2013\\Projects\\IMG-Factory\\Debug\\arial.ttf"; // todo - 6x absolute file paths in this .cpp file
	wchar_t *text = L"A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
	buffer = vertex_buffer_new("vertex:3f,tex_coord:2f,color:4f");
	vec2 pen = { { 5, 400 } };
	vec4 black = { { 0, 0, 0, 1 } };
	for (i = 7; i < 27; ++i)
	{
		font = texture_font_new_from_file(atlas, i, filename);
		pen.x = 5;
		pen.y -= font->height;
		texture_font_load_glyphs(font, text);
		add_text(buffer, font, text, &black, &pen);
		texture_font_delete(font);
	}
	glBindTexture(GL_TEXTURE_2D, atlas->id);

	shader = shader_load("shaders/v3f-t2f-c4f.vert",
		"shaders/v3f-t2f-c4f.frag");
	mat4_set_identity(&projection);
	mat4_set_identity(&model);
	mat4_set_identity(&view);
	*/




	setWindowIsOpen(true);
	setWindowIsOpening(false);

	//init3DSceneShader();
	processWindow();
}

void						CollisionViewer::init3DSceneShader(void)
{
	vertexShader2 = glCreateShader(GL_VERTEX_SHADER);
	if (glGetError()) Input::showMessage("glCreateShader v", "Error");
	fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	if (glGetError()) Input::showMessage("glCreateShader f", "Error");

	string strVertexShadersFilePath = "C:\\Users\\James\\Documents\\Visual Studio 2013\\Projects\\IMG-Factory\\Debug\\vertex-shaders-2.glsl";
	uint32 uiFileSize1 = File::getFileSize(strVertexShadersFilePath);
	const GLchar *vertexShaderChars;// = new GLchar[uiFileSize1 + 1];
	uint32 iLen1 = 0;
	//loadshader((char*)strVertexShadersFilePath.c_str(), &vertexShaderChars, &iLen1);
	string strData1 = File::getFileContent(strVertexShadersFilePath, false);
	vertexShaderChars = strData1.c_str();
	GLchar const* files1[] = { strData1.c_str() };
	GLint lengths1[] = { (int32)strData1.size() };

	string strFragmentShadersFilePath = "C:\\Users\\James\\Documents\\Visual Studio 2013\\Projects\\IMG-Factory\\Debug\\fragment-shaders-2.glsl";
	uint32 uiFileSize2 = File::getFileSize(strFragmentShadersFilePath);
	const GLchar *fragmentShaderChars;// = new GLchar[uiFileSize2 + 1];
	uint32 iLen2 = 0;
	//loadshader((char*)strFragmentShadersFilePath.c_str(), &fragmentShaderChars, &iLen2);
	string strData2 = File::getFileContent(strFragmentShadersFilePath, false);
	fragmentShaderChars = strData2.c_str();
	GLchar const* files2[] = { strData2.c_str() };
	GLint lengths2[] = { (int32)strData2.size() };

	GLint uiLengths1 = uiFileSize2;
	glShaderSource(vertexShader2, 1, files1, lengths1);
	if (glGetError()) Input::showMessage("glShaderSource v", "Error");
	glShaderSource(fragmentShader2, 1, files2, lengths2);
	if (glGetError()) Input::showMessage("glShaderSource f", "Error");
	//glShaderSourceARB

	//delete[] vertexShaderChars;
	//delete[] fragmentShaderChars;

	glCompileShader(vertexShader2);
	if (glGetError()) Input::showMessage("glCompileShader v 3d", "Error");
	glCompileShader(fragmentShader2);
	if (glGetError()) Input::showMessage("glCompileShader f", "Error");

	GLint compiled;

	glGetShaderiv(vertexShader2, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		Input::showMessage("glGetShaderiv compile error v", "Error");
	}

	glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &compiled);
	if (!compiled)
	{
		Input::showMessage("glGetShaderiv compile error f", "Error");
	}

	// link shader
	ProgramObject_3DScene = glCreateProgram();
	if (glGetError()) Input::showMessage("glCreateProgram error", "Error");

	glAttachShader(ProgramObject_3DScene, vertexShader2);
	if (glGetError()) Input::showMessage("glAttachShader v error", "Error");
	glAttachShader(ProgramObject_3DScene, fragmentShader2);
	if (glGetError()) Input::showMessage("glAttachShader f error", "Error");

	glLinkProgram(ProgramObject_3DScene);
	if (glGetError()) Input::showMessage("glLinkProgram error", "Error");

	GLint linked;
	glGetProgramiv(ProgramObject_3DScene, GL_LINK_STATUS, &linked);
	if (!linked)
	{
		Input::showMessage("glGetProgramiv link error", "Error");
	}

	// use program
	glUseProgram(ProgramObject_3DScene);
	if (glGetError()) Input::showMessage("glUseProgram error", "Error");
}
void						CollisionViewer::initTextStuff(void)
{
	FT_Error iError = FT_Init_FreeType(m_pFTLibrary);
	if (!iError)
	{
		iError = FT_New_Face(*m_pFTLibrary, "C:\\Users\\James\\Documents\\Visual Studio 2013\\Projects\\IMG-Factory\\Debug\\arial.ttf", 0, &g_face);
		if (iError == FT_Err_Unknown_File_Format)
		{
			//... the font file could be opened and read, but it appears
			//	... that its font format is unsupported
			int a;
			a = 1;
		}
		else if (iError)
		{
			//... another error code means that the font file could not
			//	... be opened or read, or that it is broken...
			int a;
			a = 1;
		}
		else
		{
			iError = FT_Set_Pixel_Sizes(g_face, 0, 48);
			if (!iError)
			{
				return;

				///*
				//g_FontTest1 = face->glyph->bitmap;

				glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

				for (GLubyte c = 0; c < 128; c++)
				{
				// Load character glyph
				if (FT_Load_Char(g_face, c, FT_LOAD_RENDER))
				{
				//cout << "ERROR::FREETYTPE: Failed to load Glyph" << endl;
				Input::showMessage("failed to load char", "Error");
				continue;
				}

				// Generate texture
				GLuint texture;
				glGenTextures(1, &texture);
				glBindTexture(GL_TEXTURE_2D, texture);
				glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				g_face->glyph->bitmap.width,
				g_face->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				g_face->glyph->bitmap.buffer
				);
				// Set texture options
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				// Now store character for later use
				Character character = {
				texture,
				(int32)g_face->glyph->bitmap.width, (int32)g_face->glyph->bitmap.rows,
				g_face->glyph->bitmap_left, g_face->glyph->bitmap_top,
				(GLuint)g_face->glyph->advance.x
				};
				Characters.insert(pair<char, Character>(c, character));
				}



				vertexShader = glCreateShader(GL_VERTEX_SHADER);
				if (glGetError()) Input::showMessage("glCreateShader v", "Error");
				fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
				if (glGetError()) Input::showMessage("glCreateShader f", "Error");

				string strVertexShadersFilePath = "C:\\Users\\James\\Documents\\Visual Studio 2013\\Projects\\IMG-Factory\\Debug\\vertex-shaders.glsl";
				uint32 uiFileSize1 = File::getFileSize(strVertexShadersFilePath);
				const GLchar *vertexShaderChars;// = new GLchar[uiFileSize1 + 1];
				uint32 iLen1 = 0;
				//loadshader((char*)strVertexShadersFilePath.c_str(), &vertexShaderChars, &iLen1);
				string strData1 = File::getFileContent(strVertexShadersFilePath, false);
				vertexShaderChars = strData1.c_str();
				GLchar const* files1[] = { strData1.c_str() };
				GLint lengths1[] = { (int32)strData1.size() };

				string strFragmentShadersFilePath = "C:\\Users\\James\\Documents\\Visual Studio 2013\\Projects\\IMG-Factory\\Debug\\fragment-shaders.glsl";
				uint32 uiFileSize2 = File::getFileSize(strFragmentShadersFilePath);
				const GLchar *fragmentShaderChars;// = new GLchar[uiFileSize2 + 1];
				uint32 iLen2 = 0;
				//loadshader((char*)strFragmentShadersFilePath.c_str(), &fragmentShaderChars, &iLen2);
				string strData2 = File::getFileContent(strFragmentShadersFilePath, false);
				fragmentShaderChars = strData2.c_str();
				GLchar const* files2[] = { strData2.c_str() };
				GLint lengths2[] = { (int32)strData2.size() };

				GLint uiLengths1 = uiFileSize2;
				glShaderSource(vertexShader, 1, files1, lengths1);
				if (glGetError()) Input::showMessage("glShaderSource v", "Error");
				glShaderSource(fragmentShader, 1, files2, lengths2);
				if (glGetError()) Input::showMessage("glShaderSource f", "Error");
				//glShaderSourceARB

				//delete[] vertexShaderChars;
				//delete[] fragmentShaderChars;

				glCompileShader(vertexShader);
				if (glGetError()) Input::showMessage("glCompileShader v text", "Error");
				glCompileShader(fragmentShader);
				if (glGetError()) Input::showMessage("glCompileShader f", "Error");

				GLint compiled;

				glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &compiled);
				if (!compiled)
				{
				Input::showMessage("glGetShaderiv compile error v", "Error");
				}

				glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &compiled);
				if (!compiled)
				{
				Input::showMessage("glGetShaderiv compile error f", "Error");
				}

				// link shader
				ProgramObject = glCreateProgram();
				if (glGetError()) Input::showMessage("glCreateProgram error", "Error");

				glAttachShader(ProgramObject, vertexShader);
				if (glGetError()) Input::showMessage("glAttachShader v error", "Error");
				glAttachShader(ProgramObject, fragmentShader);
				if (glGetError()) Input::showMessage("glAttachShader f error", "Error");

				glLinkProgram(ProgramObject);
				if (glGetError()) Input::showMessage("glLinkProgram error", "Error");

				GLint linked;
				glGetProgramiv(ProgramObject, GL_LINK_STATUS, &linked);
				if (!linked)
				{
				Input::showMessage("glGetProgramiv link error", "Error");
				}

				// use program
				glUseProgram(ProgramObject);
				if (glGetError()) Input::showMessage("glUseProgram error", "Error");







				// should this go here or in render() function?
				glGenVertexArrays(1, &VAO);
				if (glGetError()) Input::showMessage("glGenVertexArrays error", "Error");

				glGenBuffers(1, &VBO);
				if (glGetError()) Input::showMessage("glGenBuffers", "Error");

				glBindVertexArray(VAO);
				if (glGetError()) Input::showMessage("glBindVertexArray", "Error");

				glBindBuffer(GL_ARRAY_BUFFER, VBO);
				if (glGetError()) Input::showMessage("glBindBuffer", "Error");

				glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
				if (glGetError()) Input::showMessage("glBufferData", "Error");

				glEnableVertexAttribArray(0);
				if (glGetError()) Input::showMessage("glEnableVertexAttribArray", "Error");

				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
				if (glGetError()) Input::showMessage("glVertexAttribPointer error", "Error");

				glBindBuffer(GL_ARRAY_BUFFER, 0);
				if (glGetError()) Input::showMessage("glBindBuffer error", "Error");

				glBindVertexArray(0);
				if (glGetError()) Input::showMessage("glBindVertexArray error", "Error");
				//*/

				g_bText2DStuffLoaded = true;
			}
		}

		//FT_Done_Face(g_face);
	}

	//FT_Done_FreeType(library);
}

void						CollisionViewer::loadThreadAndWindow(void)
{
	setWindowIsOpening(true);

	uint32 uiThreadId;
	HANDLE hThread = CreateThread(NULL, 0, &onThreadStarted_CollisionViewer, this, 0, &uiThreadId);
	setThread(hThread);

	/*
	char fakeParam[] = "";
	char *fakeargv[] = { fakeParam, NULL };
	int fakeargc = 1;

	glutInit(&fakeargc, fakeargv);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION);
	openWindow();

	glutDisplayFunc(render);
	glutKeyboardFunc(glutKeyboardInputCallback);
	glutSpecialFunc(glutSpecialInputCallback);

	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	*/
}
void						CollisionViewer::unloadThreadAndWindow(void)
{
	SuspendThread(getThread());

	closeWindow();

	setWindowIsOpen(false);

	HANDLE hThread = getThread();
	setThread(0);
	TerminateThread(hThread, 0);
}

void						CollisionViewer::prepareRenderData(void)
{
	// active COL entry
	COLFormat *pCOLFile = getCOLFile();
	if (pCOLFile->getEntryCount() == 0)
	{
		return;
	}
	uint32 uiCOLEntryIndex = 0;
	COLEntry *pCOLEntry = pCOLFile->getEntryByIndex(uiCOLEntryIndex);
	setActiveCOLEntry(pCOLEntry);

	// camera
	Vec3f vecCameraLookAtPosition = { 0.0f, 0.0f, 0.0f };

	TBounds& bounds = pCOLEntry->getBoundingObjects();
	Vec3f vecDistances = bounds.m_vecMax - bounds.m_vecMin;

	float32 fHighestDistance = vecDistances.x > vecDistances.y ? vecDistances.x : vecDistances.y;
	fHighestDistance = vecDistances.z > fHighestDistance ? vecDistances.z : fHighestDistance;
	float32 fDistanceMultiplier = 2.0f;

	vecCameraPosition = { 0.0f, 0.0f, 2.0f };
	vecCameraPosition = Math::getPositionInFrontOfPosition(vecCameraPosition, 45.0f, fHighestDistance * fDistanceMultiplier);
	vecCameraRotation = { 0.0f, 0.0f, Math::getAngleBetweenPoints(vecCameraPosition, vecCameraLookAtPosition) + Math::convertDegreesToRadians(90.0f) };

	//glDisableClientState(GL_VERTEX_ARRAY);

	// collision spheres data
	if (isWindowOpen())
	{
		SuspendThread(getThread());
	}

	uint32 i = 0;
	for (SolidSphere *pSolidSphere : m_vecCollisionSpheresGL)
	{
		delete pSolidSphere;
		m_vecCollisionSpheresGL[i] = nullptr;
		i++;
	}
	m_vecCollisionSpheresGL.clear();

	for (TSphere& collisionSphere : pCOLEntry->getCollisionSpheres())
	{
		SolidSphere *pSolidSphere = new SolidSphere(collisionSphere.m_fRadius, 100, 100);
		m_vecCollisionSpheresGL.push_back(pSolidSphere);
	}

	if (isWindowOpen())
	{
		ResumeThread(getThread());
	}
}

void						CollisionViewer::processKeys(void)
{
	bool bControlKey = (GetKeyState(VK_CONTROL) & 0x8000) == 0x8000;
	bool bShiftKey = (GetKeyState(VK_SHIFT) & 0x8000) == 0x8000;

	float32 fMoveDistancePerSecond = 5.0f;
	float32 fShiftKeyMultiplier = 10.0f;

	if (bShiftKey)
	{
		fMoveDistancePerSecond *= fShiftKeyMultiplier;
	}

	uint32 uiTimeNow = GetTickCount();
	uint32 uiTimeDifference = uiTimeNow - m_uiLastKeyProcessTime;
	m_uiLastKeyProcessTime = uiTimeNow;

	float32 fElapsedPercentOfSecond = ((float32)uiTimeDifference) / 1000.0f;
	float32 fMoveDistance = fElapsedPercentOfSecond * fMoveDistancePerSecond;

	for (auto it : g_umapKeysDown)
	{
		int iKey = it.first;

		switch (iKey)
		{
		case GLFW_KEY_UP:
		case 'W':
			if (bControlKey)
			{
				moveCamera(2, true, fMoveDistance);
			}
			else
			{
				moveCamera(1, false, fMoveDistance);
			}
			break;
		case GLFW_KEY_DOWN:
		case 'S':
			if (bControlKey)
			{
				moveCamera(2, false, fMoveDistance);
			}
			else
			{
				moveCamera(1, true, fMoveDistance);
			}
			break;
		case GLFW_KEY_LEFT:
		case 'A':
			moveCamera(0, false, fMoveDistance);
			break;
		case GLFW_KEY_RIGHT:
		case 'D':
			moveCamera(0, true, fMoveDistance);
			break;
		case GLFW_KEY_KP_ADD:
			zoomCamera(-fMoveDistance);
			break;
		case GLFW_KEY_KP_SUBTRACT:
			zoomCamera(fMoveDistance);
			break;
		}
	}
}

void						CollisionViewer::render(void)
{
	/*
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	vector<uint8> a = { 0, 255, 0 };
	//RenderText("This is sample text", 25.0f, 25.0f, 1.0f, a);
	RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 1.0f, a);

	glDisable(GL_BLEND);

	return;
	*/

	//if (glGetError()) Input::showMessage("test1 error", "Error");

	//glScissor(0, 0, 100, 100);
	//glEnable(GL_SCISSOR_TEST);

	prepare2DRender();
	if (glGetError()) Input::showMessage("test1.5 error", "Error"); 
	renderBackground();

	if (glGetError()) Input::showMessage("test2 error", "Error");

	prepare3DRender();
	renderCamera();
	renderAxis();
	renderBoundingSphere();
	renderBoundingCuboid();
	renderCollisionObjects();

	if (glGetError()) Input::showMessage("test3 error", "Error");

	prepare2DRender();
	if (glGetError()) Input::showMessage("test3.5 error", "Error");
	render2DObjects();

	if (glGetError()) Input::showMessage("test4 error", "Error");

	//glDisable(GL_SCISSOR_TEST);
}

void						CollisionViewer::prepare2DRender(void)
{
	//glUseProgram(ProgramObject);
	//if (glGetError()) Input::showMessage("glUseProgram error", "Error");

	int w, h;
	glfwGetWindowSize(getWindow(), &w, &h);

	glScissor(200, 200, 100, 100);

	glMatrixMode(GL_PROJECTION);
	if (glGetError()) Input::showMessage("prepare2DRender glMatrixMode 1 error", "Error");

	//glPushMatrix();
	//int yaz = glGetError();
	//if (yaz) Input::showMessage("prepare2DRender glPushMatrix error", "Error");

	glLoadIdentity();
	if (glGetError()) Input::showMessage("prepare2DRender glLoadIdentity 1 error", "Error");

	//glOrtho(-vecBackgroundBox.x / 2, vecBackgroundBox.x / 2, vecBackgroundBox.y / 2, -vecBackgroundBox.y / 2, -1.0, 10.0);
	//glOrtho(0.0, w, h, 0.0, -1.0, 10.0);
	glOrtho(-w / 2, w / 2, h / 2, -h / 2, -1.0, 1.0);
	if (glGetError()) Input::showMessage("prepare2DRender glOrtho error", "Error");

	glMatrixMode(GL_MODELVIEW);
	if (glGetError()) Input::showMessage("prepare2DRender glMatrixMode 2 error", "Error");

	//glPushMatrix();
	glLoadIdentity();
	if (glGetError()) Input::showMessage("prepare2DRender glLoadIdentity 2 error", "Error");

	glDisable(GL_CULL_FACE);
	if (glGetError()) Input::showMessage("prepare2DRender glDisable(GL_CULL_FACE) error", "Error");

	//glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	if (glGetError()) Input::showMessage("prepare2DRender glClear(GL_DEPTH_BUFFER_BIT)", "Error");
}
void						CollisionViewer::prepare3DRender(void)
{
	//glUseProgram(ProgramObject_3DScene);
	//if (glGetError()) Input::showMessage("glUseProgram error", "Error");

	int w, h;
	glfwGetWindowSize(getWindow(), &w, &h);
	const float64 ar = ((float64)w) / ((float64)h);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(60.0, ar, 0.1, 100.0);
	//gluPerspective(50.0, 1.0, 1.0, 50.0);
	perspectiveGL(45.0, ar, 1.0, 1500.0);

	//glLoadMatrixf(fData);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_DEPTH_BUFFER_BIT);
}

void						CollisionViewer::renderBackground(void)
{
	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	if (glGetError()) Input::showMessage("BG glDepthMask error", "Error");
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	if (glGetError()) Input::showMessage("BG glDisable error", "Error");

	int w, h;
	glfwGetWindowSize(getWindow(), &w, &h);

	// background gradient
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	//if (glGetError()) Input::showMessage("BG glBegin error", "Error");
	Vec2f vecBackgroundArea((float32)w, (float32)h);
	vector<Vec2f> vecBackgroundPoints = {
		{ -vecBackgroundArea.x / 2, -vecBackgroundArea.y / 2 },
		{ vecBackgroundArea.x / 2, -vecBackgroundArea.y / 2 },
		{ vecBackgroundArea.x / 2, vecBackgroundArea.y / 2 },
		{ -vecBackgroundArea.x / 2, vecBackgroundArea.y / 2 }
	};
	//if (glGetError()) Input::showMessage("BG glShadeModel error", "Error");
	uint32 i = 0;
	glColor3ub(120, 120, 120);
	//if (glGetError()) Input::showMessage("BG glColor3ub 1 error", "Error");
	for (auto vecVertex : vecBackgroundPoints)
	{
		if (i == 2)
		{
			glColor3ub(73, 73, 73);
			//if (glGetError()) Input::showMessage("BG glColor3ub 2 error", "Error");
		}

		glVertex2f(vecVertex.x, vecVertex.y);
		//if (glGetError()) Input::showMessage("BG glVertex2f error", "Error");

		i++;
	}
	glEnd();
	//int a = glGetError();
	//if (a) Input::showMessage("BG glEnd error", "Error");

	glEnable(GL_DEPTH_TEST);
	if (glGetError()) Input::showMessage("BG glEnable error", "Error");
	glDepthMask(GL_TRUE);  // enable writes to Z-Buffer
	if (glGetError()) Input::showMessage("BG glDepthMask error", "Error");
}

void						CollisionViewer::renderCamera(void)
{
	// camera rotation
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.x), 1.0f, 0.0f, 0.0f); // Rotate our camera on the x-axis (looking up and down)
	glRotatef(Math::convertRadiansToDegrees(vecCameraRotation.z), 0.0f, 1.0f, 0.0f); // Rotate our camera on the y-axis (looking left and right)

	// camera position
	glTranslatef(-vecCameraPosition.x, -vecCameraPosition.z, -vecCameraPosition.y);
}
void						CollisionViewer::renderCollisionObjects(void)
{
	glColor3ub(255, 255, 255);

	renderCollisionMeshes();
	renderCollisionCuboids();
	renderCollisionSpheres();
}

void						CollisionViewer::renderAxis(void)
{
	glBegin(GL_LINE_STRIP);
	glColor3ub(255, 0, 0);
	glVertex3f(-5000.0f, 0.0f, 0.0f);
	glVertex3f(5000.0f, 0.0f, 0.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 255, 0);
	glVertex3f(0.0f, 0.0f, -5000.0f);
	glVertex3f(0.0f, 0.0f, 5000.0f);
	glEnd();

	glBegin(GL_LINE_STRIP);
	glColor3ub(0, 0, 255);
	glVertex3f(0.0f, -5000.0f, 0.0f);
	glVertex3f(0.0f, 5000.0f, 0.0f);
	glEnd();
}
void						CollisionViewer::renderBoundingSphere(void)
{
	COLEntry *pCOLEntry = getActiveCOLEntry();

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 0, 255);
	for (uint32 i = 0, j = 360, step = 1; i < j; i += step)
	{
		Vec3f vecPosition = Math::getCartesianFromSpherical(pCOLEntry->getBoundingObjects().m_fRadius, Math::convertDegreesToRadians((float32)i), Math::convertDegreesToRadians(0.0f));
		vecPosition = vecPosition + pCOLEntry->getBoundingObjects().m_vecCenter;
		glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		//Debugger::log("m_fRadius: " + String::toString(pCOLEntry->getBoundingObjects().m_fRadius) + ", vecPosition: " + String::toString(vecPosition.x) + ", " + String::toString(vecPosition.y) + ", " + String::toString(vecPosition.z));
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 0, 255);
	for (uint32 i = 0, j = 360, step = 1; i < j; i += step)
	{
		Vec3f vecPosition = Math::getCartesianFromSpherical(pCOLEntry->getBoundingObjects().m_fRadius, Math::convertDegreesToRadians(90.0f), Math::convertDegreesToRadians((float32)i));
		vecPosition = vecPosition + pCOLEntry->getBoundingObjects().m_vecCenter;
		glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		//Debugger::log("m_fRadius: " + String::toString(pCOLEntry->getBoundingObjects().m_fRadius) + ", vecPosition: " + String::toString(vecPosition.x) + ", " + String::toString(vecPosition.y) + ", " + String::toString(vecPosition.z));
	}
	glEnd();

	glBegin(GL_LINE_LOOP);
	glColor3ub(255, 0, 255);
	for (uint32 i = 0, j = 360, step = 1; i < j; i += step)
	{
		Vec3f vecPosition = Math::getCartesianFromSpherical(pCOLEntry->getBoundingObjects().m_fRadius, Math::convertDegreesToRadians((float32)i), Math::convertDegreesToRadians(90.0f));
		vecPosition = vecPosition + pCOLEntry->getBoundingObjects().m_vecCenter;
		glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		//Debugger::log("m_fRadius: " + String::toString(pCOLEntry->getBoundingObjects().m_fRadius) + ", vecPosition: " + String::toString(vecPosition.x) + ", " + String::toString(vecPosition.y) + ", " + String::toString(vecPosition.z));
	}
	glEnd();
}
void						CollisionViewer::renderBoundingCuboid(void)
{
	COLEntry *pCOLEntry = getActiveCOLEntry();

	glColor3ub(0, 255, 255);
	vector<Vec3f> vecVertices = Math::getCuboidFaceVerticesAsQuads(pCOLEntry->getBoundingObjects().m_vecMin, pCOLEntry->getBoundingObjects().m_vecMax);
	for (uint32 i = 0; i < vecVertices.size(); i += 4)
	{
		if ((i % 4) == 0)
		{
			glBegin(GL_LINE_LOOP);
		}
		for (uint32 i2 = 0; i2 < 4; i2++)
		{
			Vec3f& vecPosition = vecVertices[i + i2];
			glVertex3f(vecPosition.x, vecPosition.z, vecPosition.y);
		}
		if ((i % 4) == 0)
		{
			glEnd();
		}
	}
}

void						CollisionViewer::renderCollisionMeshes(void)
{
	COLEntry *pCOLEntry = getActiveCOLEntry();

	// draw collision mesh faces & vertices
	glBegin(GL_TRIANGLES);
	glColor3ub(255, 0, 0);
	for (TFace& face : pCOLEntry->getCollisionMeshFaces())
	{
		TVertex& vecVector1 = pCOLEntry->getCollisionMeshVertices()[face.m_uiA];
		TVertex& vecVector2 = pCOLEntry->getCollisionMeshVertices()[face.m_uiB];
		TVertex& vecVector3 = pCOLEntry->getCollisionMeshVertices()[face.m_uiC];
		//Debugger::log("vecVector1: " + String::toString(vecVector1.x) + ", " + String::toString(vecVector1.y) + ", " + String::toString(vecVector1.z));
		//Debugger::log("vecVector2: " + String::toString(vecVector2.x) + ", " + String::toString(vecVector2.y) + ", " + String::toString(vecVector2.z));
		//Debugger::log("vecVector3: " + String::toString(vecVector3.x) + ", " + String::toString(vecVector3.y) + ", " + String::toString(vecVector3.z));
		glVertex3f(vecVector1.x, vecVector1.z, vecVector1.y);
		glVertex3f(vecVector2.x, vecVector2.z, vecVector2.y);
		glVertex3f(vecVector3.x, vecVector3.z, vecVector3.y);
	}
	glEnd();
}

void						CollisionViewer::renderCollisionCuboids(void)
{
	COLEntry *pCOLEntry = getActiveCOLEntry();

	glBegin(GL_QUADS);
	//glColor3ub(255, 0, 0);

	//Debugger::log("collisionBox.m_min: " + String::toString(collisionBox.m_min.x) + ", " + String::toString(collisionBox.m_min.y) + ", " + String::toString(collisionBox.m_min.z));
	//Debugger::log("collisionBox.m_max: " + String::toString(collisionBox.m_max.x) + ", " + String::toString(collisionBox.m_max.y) + ", " + String::toString(collisionBox.m_max.z));
	uint32 i = 0;
	int i2 = 0;
	int colors[6][3] = {
		{ 255, 0, 0 },
		{ 0, 255, 0 },
		{ 0, 0, 255 },
		{ 255, 255, 0 },
		{ 255, 128, 0 },
		{ 50, 50, 50 }
	};
	for (TBox& collisionBox : pCOLEntry->getCollisionBoxes())
	{
		vector<Vec3f> vecVertices = Math::getCuboidFaceVerticesAsQuads(collisionBox.m_min, collisionBox.m_max);
		i = 0;
		i2 = 0;
		for (auto vecVertex : vecVertices)
		{
			//Debugger::log("vecVertex: " + String::toString(vecVertex.x) + ", " + String::toString(vecVertex.y) + ", " + String::toString(vecVertex.z));
			if ((i % 4) == 0)
			{
				glColor3ub(colors[i2][0], colors[i2][1], colors[i2][2]);
				i2++;
			}
			if ((i % 4) == 3)
			{
				//Debugger::log("--");
			}
			glVertex3f(vecVertex.x, vecVertex.z, vecVertex.y);
			i++;
		}
		//Debugger::log("------------------------------");
	}
	glEnd();
}
void						CollisionViewer::renderCollisionSpheres(void)
{
	COLEntry *pCOLEntry = getActiveCOLEntry();

	// draw collision spheres
	uint32 i2 = 0;
	for (TSphere& collisionSphere : pCOLEntry->getCollisionSpheres())
	{
		//glColor3ub(colors[i2][0], colors[i2][1], colors[i2][2]);

		//glPushMatrix();
		//glTranslatef(collisionSphere.m_vecCenter.x, collisionSphere.m_vecCenter.z, collisionSphere.m_vecCenter.y); 
		//gluSphere(gluNewQuadric(), collisionSphere.m_fRadius, 100, 100);
		if (!isEntryChanging() && i2 < m_vecCollisionSpheresGL.size() && m_vecCollisionSpheresGL[i2] != nullptr)
		{
			m_vecCollisionSpheresGL[i2]->draw(collisionSphere.m_vecCenter.x, collisionSphere.m_vecCenter.z, collisionSphere.m_vecCenter.y);
		}
		//glPopMatrix();

		i2++;
	}
}
void						CollisionViewer::render2DObjects(void)
{
	static int f = 0;
	glDepthMask(GL_FALSE);  // disable writes to Z-Buffer
	int aa = glGetError();
	if (aa)
	{
		Input::showMessage("glDepthMask error", "Error");
		int h;
		h = 0;
	}
	glDisable(GL_DEPTH_TEST);  // disable depth-testing
	if (glGetError()) Input::showMessage("glDisable error", "Error");
	f++;

	renderLeftPanelBackground();
	if (glGetError()) Input::showMessage("AAA error", "Error");
	renderBottomPanelBackground();
	if (glGetError()) Input::showMessage("AAB error", "Error");
	renderPanelLineSeparators();
	if (glGetError()) Input::showMessage("AAC error", "Error");



	//g_FontTest1
	if (glGetError()) Input::showMessage("AA error", "Error");
	glEnable(GL_BLEND);
	if (glGetError()) Input::showMessage("glEnable error", "Error");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	if (glGetError()) Input::showMessage("glBlendFunc error", "Error");
	


	/*
	GLfloat fProjectionMatrix[16];
	glGetFloatv(GL_PROJECTION_MATRIX, fProjectionMatrix);
	if (glGetError()) Input::showMessage("glGetFloatv 1 error", "Error");

	GLfloat fModelViewMatrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, fModelViewMatrix);
	if (glGetError()) Input::showMessage("glGetFloatv 2 error", "Error");

	GLint iLocation1 = glGetUniformLocation(ProgramObject, "projection");
	if (glGetError()) Input::showMessage("glGetUniformLocation 1 error", "Error");

	GLint iLocation2 = glGetUniformLocation(ProgramObject, "modelview");
	if (glGetError()) Input::showMessage("glGetUniformLocation 2 error", "Error");

	glUniformMatrix3fv(iLocation1, 1, GL_FALSE, fProjectionMatrix);
	if (glGetError()) Input::showMessage("glUniformMatrix3fv 1 error", "Error");

	glUniformMatrix3fv(iLocation2, 1, GL_FALSE, fModelViewMatrix);
	if (glGetError()) Input::showMessage("glUniformMatrix3fv 2 error", "Error");
	*/

	//glUniform(glGetUniformLocation(ProgramObject, "textColor"), color[0], color[1], color[2]);
	//glUniform3f(glGetUniformLocation(ProgramObject, "textColor"), 0.0, 1.0, 0.0);
	//if (glGetError()) Input::showMessage("glUniform3f error", "Error");

	static uint32 iRed = 0;
	iRed++;
	if (iRed > 255)
		iRed = 0;
	//GLint iLocation1 = glGetUniformLocation(ProgramObject, "red");
	//glUniform1f(iLocation1, ((float32)iRed) / 255.0f);

	
	if (g_bText2DStuffLoaded)
	{
		

		//glm::mat4 projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

		vector<uint8> a = { 0, 255, 0 };
		RenderText("This is sample text", 25.0f, 25.0f, 1.0f, a);
		RenderText("(C) LearnOpenGL.com", 540.0f, 570.0f, 1.0f, a);
	}
	

	
	//face->draw(10.0, 10.0, "Here is some text");



	/*
	stbtt_bakedchar cdata[96];
	memset(&cdata, 'z', 95);
	memcpy((&cdata) + 95, 0, 1);
	string strFontData = File::getFileContent("arial.ttf");
	uint8 *pPixelsOut = nullptr;
	stbtt_BakeFontBitmap((const uint8*)strFontData.c_str(), stbtt_GetFontOffsetForIndex((const uint8*)strFontData.c_str(), 0), 32, pPixelsOut, 512, 512, 32, 96, cdata);
	*/

	//glClearColor(1.0, 0.5, 0.0, 0.5);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*
	 glUseProgram( shader );
    {
        glUniform1i( glGetUniformLocation( shader, "texture" ),
                     0 );
        glUniformMatrix4fv( glGetUniformLocation( shader, "model" ),
                            1, 0, model.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "view" ),
                            1, 0, view.data);
        glUniformMatrix4fv( glGetUniformLocation( shader, "projection" ),
                            1, 0, projection.data);
        vertex_buffer_render( buffer, GL_TRIANGLES );
    }
	*/

	glDisable(GL_BLEND);




	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);  // enable writes to Z-Buffer
}
void						CollisionViewer::render2DText(void)
{
	HWND hwnd = glfwGetWin32Window(getWindow());
	HDC hdc = GetDC(hwnd);
	
	/*
	PAINTSTRUCT ps;
	ZeroMemory(&ps, sizeof(ps));
	ps.hdc = hdc;
	ps.fErase = false;
	ps.rcPaint = { 0, 0, 500, 500 };
	ps.fRestore = false;
	ps.fIncUpdate = false;
	hdc = BeginPaint(hwnd, &ps);
	*/

	if (hdc == NULL)
	{
		Input::showMessage("GetDC() failed", "Error", MB_OK);
	}

	HFONT hFont = CreateFont(16, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Verdana"));
	HGDIOBJ old = SelectObject(hdc, hFont);

	RECT rect;
	SetTextColor(hdc, RGB(0, 0, 0));
	SetBkMode(hdc, TRANSPARENT);
	rect.left = 10;
	rect.top = 10;
	rect.right = 8000;
	rect.bottom = 8000;
	DrawText(hdc, String::convertStdStringToStdWString("Test").c_str(), String::convertStdStringToStdWString("Test").length(), &rect, DT_NOPREFIX);

	//EndPaint(hwnd, &ps);
}
void						CollisionViewer::renderLeftPanelBackground(void)
{
	int w, h;
	glfwGetWindowSize(getWindow(), &w, &h);

	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	Vec2f vecBackgroundArea((float32)w, (float32)h);
	vector<Vec2f> vecBackgroundPoints = {
		{ -vecBackgroundArea.x / 2,						-vecBackgroundArea.y / 2 },
		{ (-vecBackgroundArea.x / 2) + 200.0f + 7.5f,	-vecBackgroundArea.y / 2 },
		{ (-vecBackgroundArea.x / 2) + 200.0f + 7.5f,	vecBackgroundArea.y / 2 },
		{ -vecBackgroundArea.x / 2,						vecBackgroundArea.y / 2 }
	};
	uint32 i = 0;
	glColor3ub(120, 120, 120);
	for (auto vecVertex : vecBackgroundPoints)
	{
		if (i == 2)
		{
			glColor3ub(73, 73, 73);
		}

		glVertex2f(vecVertex.x, vecVertex.y);

		i++;
	}
	glEnd();
}
void						CollisionViewer::renderBottomPanelBackground(void)
{
	int w, h;
	glfwGetWindowSize(getWindow(), &w, &h);

	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	Vec2f vecBackgroundArea((float32)w, (float32)h);
	vector<Vec2f> vecBackgroundPoints = {
		{ vecBackgroundArea.x / 2,				(vecBackgroundArea.y / 2) - 150.0f },
		{ (-vecBackgroundArea.x / 2) + 200.0f,	(vecBackgroundArea.y / 2) - 150.0f },
		{ (-vecBackgroundArea.x / 2) + 200.0f,	vecBackgroundArea.y / 2 },
		{ vecBackgroundArea.x / 2,				vecBackgroundArea.y / 2 }
	};
	uint32 i = 0;
	float32 fInterpolateRatio = ((vecBackgroundArea.y - 150.0f) / vecBackgroundArea.y);
	uint8 ucColour1 = (uint8)((uint8)120 - (fInterpolateRatio * ((float32)(120 - 73))));
	glColor3ub(ucColour1, ucColour1, ucColour1);
	for (auto vecVertex : vecBackgroundPoints)
	{
		if (i == 2)
		{
			glColor3ub(73, 73, 73);
		}

		glVertex2f(vecVertex.x, vecVertex.y);

		i++;
	}
	glEnd();
}
void						CollisionViewer::renderPanelLineSeparators(void)
{
	int w, h;
	glfwGetWindowSize(getWindow(), &w, &h);

	// line separators
	glBegin(GL_QUADS);
	glColor3ub(0, 0, 0);
	Vec2f vecBackgroundArea2((float32)w, (float32)h);
	vector<Vec2f> vecLineSeparatorsPoints = {
		// horizontal line - below add/remove buttons
		{ -vecBackgroundArea2.x / 2,						(-vecBackgroundArea2.y / 2) + 50.0f },
		{ (-vecBackgroundArea2.x / 2) + 200.0f + 7.5f,	(-vecBackgroundArea2.y / 2) + 50.0f },
		{ (-vecBackgroundArea2.x / 2) + 200.0f + 7.5f,	(-vecBackgroundArea2.y / 2) + 50.0f + 7.5f },
		{ -vecBackgroundArea2.x / 2,						(-vecBackgroundArea2.y / 2) + 50.0f + 7.5f },

		// vertical line - attached to right side of left panel
		{ (-vecBackgroundArea2.x / 2) + 200,				-vecBackgroundArea2.y / 2 },
		{ (-vecBackgroundArea2.x / 2) + 200.0f + 7.5f,	-vecBackgroundArea2.y / 2 },
		{ (-vecBackgroundArea2.x / 2) + 200.0f + 7.5f,	vecBackgroundArea2.y / 2 },
		{ (-vecBackgroundArea2.x / 2) + 200.0f,			vecBackgroundArea2.y / 2 },

		// horizontal line - below 3d area
		{ (-vecBackgroundArea2.x / 2) + 200.0f + 7.5f,	(vecBackgroundArea2.y / 2) - 150.0f },
		{ vecBackgroundArea2.x / 2,						(vecBackgroundArea2.y / 2) - 150.0f},
		{ vecBackgroundArea2.x / 2,						(vecBackgroundArea2.y / 2) - 150.0f + 7.5f },
		{ (-vecBackgroundArea2.x / 2) + 200.0f + 7.5f,	(vecBackgroundArea2.y / 2) - 150.0f + 7.5f }
	};
	for (auto vecVertex : vecLineSeparatorsPoints)
	{
		glVertex2f(vecVertex.x, vecVertex.y);
	}
	glEnd();
}