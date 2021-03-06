#pragma once

#include "nsbxcf.h"
#include "nsbxgi.h"
#include "nsimgf.h"
#include "GUI/Editor/Base/Tab/EditorTab.h"
#include "Type/Vector/Vec3f.h"
#include "3D/OpenGL/OpenGL.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <stack>

class imgf::ModelEditorTab : public imgf::EditorTab
{
public:
	ModelEditorTab(void);
	
	bool						init(bool bIsNewFile);

	void						initLayer(void);

	void						bindEvents(void);
	void						unbindEvents(void);

	void						onMouseWheelMove2(int16 iRotationDistance);
	void						onProcess(void);

	bool						unserializeFile(void);
	void						onFileLoaded(void);

	void						setFileInfoText(void);
	void						updateEntryCountText(void);

	void						render_Type1(void);

	void						render(void);
	void						render3D(void);
	void						renderCamera(void);
	void						renderAxis(void);
	void						renderModel(void);
	void						renderFrame(uint32 uiFrameIndex, bxgi::RWSection_Frame *pFrame, bool bIsParentFrame);

	void						zoomCamera(float32 fRadius);
	glm::vec3					getCameraRotation(void);
	float32						getCameraZRotation(void); // result is in radians

	void						setDFFFile(bxgi::DFFFormat *pDFFFile) { m_pDFFFile = pDFFFile; }
	bxgi::DFFFormat*			getDFFFile(void) { return m_pDFFFile; }

	void						onResizeWindow(bxcf::Vec2i& vecSizeChange);
	
protected:
	void						storeControls(void);

private:



	void						createGLContext(void);
	void						prepareScene(void);
	void						reshape(void);
	void						drawScene(void);
	void						destroyScene(void);

	void						prepareShaders(void);
	void						prepareAxis(void);
	void						prepareMeshes(void);
	void						prepareTextures(void);
	void						prepareGLStates(void);
	void						prepareShaderData(void);
	void						prepareFBO(void);
	void						prepareCamera(void);
	
	void						updateCameraMatrix(void);

private:
	bxcf::OpenGL				m_gl;

	bxgi::DFFFormat*			m_pDFFFile;
	bxgi::TXDFormat*			m_pTXDFile;
	bool						m_bInitialized;
	bool						m_bPanningCamera;
	bool						m_bInitializing;

	glm::vec3					m_vecCameraPosition;
	glm::vec3					m_vecCameraRotation;

	GLuint						m_program;
	GLuint						m_program2;
	GLuint*						textureIDs; // todo - prefix
	std::unordered_map<std::string, GLuint>		textureIndices; // todo - prefix // GLuint: gl texture id
	std::unordered_map<std::string, uint32>		m_umapGeometryIndexByTextureNameLower;

	std::vector<GLuint>			m_pGeometryVertexPositionBuffers;	// GLuint: gl buffer id
	std::vector<GLuint>			m_pGeometryVertexNormalBuffers;		// GLuint: gl buffer id
	std::vector<GLuint>			m_pGeometryTexturePositionBuffers;	// GLuint: gl buffer id
	std::vector<std::vector<GLuint>>	m_pBinMeshDataIndexBuffers;	// GLuint: gl buffer id

	std::vector<std::vector<GLuint>>	m_pGeometryVertexArrayBuffers;		// GLuint: gl vertex array buffer id

	//GLuint*						m_pGeometryVertexPositionBuffers;	// GLuint: gl buffer id

	std::vector<const char*>					m_pVertexPositionBuffer;
	std::vector<const char*>					m_pVertexNormalBuffer;
	std::vector<const char*>					m_pTextureCoordinateBuffer;
	std::vector<std::vector<const char*>>		m_pDataIndexBuffer;

	std::stack<glm::mat4>		m_matProjectionMatrix;
	std::stack<glm::mat4>		m_stkModels;
	glm::mat4					m_matCamera;
	//glm::mat4					m_matModelViewProjectionMatrix;

	bxcf::Vec2u					m_vecRenderSize;

	GLuint						axisBuffer;
	GLuint						axisIndexBuffer;
	GLuint						fb;
	GLuint						color_tex;
	GLuint						depth_rb;
	GLuint						m_vboID;
	GLuint						m_vboColours;
	GLuint						m_iboID;
};