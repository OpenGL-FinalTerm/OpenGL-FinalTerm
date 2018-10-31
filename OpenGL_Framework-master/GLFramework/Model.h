#pragma once
#include "LinearMath.h"
#include "Texture.h"

class Model
{
	struct Vertex
	{
		Vector3 m_v3Vertex;
		Vector3 m_v3Normal;
		Vector2 m_v2Texture;
	};

	struct ModelIndex
	{
		unsigned int m_nVertexID;
		unsigned int m_nNormalID;
		unsigned int m_nTextureID;
	};

	struct Polygon
	{
		unsigned int				m_nMaterialID{ 0 };
		std::vector<ModelIndex>		m_vmiModelIndices;
	};

public:
	Model();
	~Model();

	bool load(std::string objectPath, std::string texturePath = "");
	void render();
	void kill();

private:
	int parseID(const std::string& id);
	bool createVBO(
		std::vector<Vector3>&	m_Vv3VertexBuffer,
		std::vector<Vector2>&	m_Vv2TextureBuffer,
		std::vector<Vector3>&	m_Vv3NormalBuffer,
		std::vector<Polygon>&	m_VplPolygonBuffer,
		bool bFoundTextures, bool bFoundNormals);
	void deleteVBO();


private:
	enum { VERTEX, NORMAL, TEXCOORD, POLYGON };
	bool					m_bLoaded	{ false };
	int						m_nIndexSize;
	GLuint					m_uVaoID;
	GLuint					m_uVertexBuffer;
	Texture					m_ModelTexture;
};