#include "stdafx.h"
#include "Model.h"

using namespace std;

Model::Model()
{
	m_nIndexSize = 0;
}

Model::~Model()
{
	deleteVBO();
}

bool Model::load(std::string objectPath, std::string texturePath)
{
	fstream in(objectPath, ios::in | ios::binary);

	if (!in) return false;

	vector<Vector3> vv3VertexBuffer;
	vector<Vector2> vv2TextureBuffer;
	vector<Vector3> vv3NormalBuffer;
	vector<Polygon> vplPolygonBuffer;

	string	id;
	char	slash;
	float	x, y, z;

	bool foundTexCoords{ false };
	bool foundNormals{ false };

	for (string line; getline(in, line);)
	{
		if (line.size() == 0) continue;

		stringstream lineparser(line);
		lineparser >> id;

		switch (parseID(id))
		{
		case VERTEX:
		{
			lineparser >> x >> y >> z;
			vv3VertexBuffer.emplace_back(x, y, z);
			break;
		}
		case TEXCOORD:
		{
			foundTexCoords = true;
			lineparser >> x >> y;
			vv2TextureBuffer.emplace_back(x, y);
			break;
		}
		case NORMAL:
		{
			foundNormals = true;
			lineparser >> x >> y >> z;
			vv3NormalBuffer.push_back(V3::normalize(Vector3(x, y, z)));
			break;
		}
		case POLYGON:
		{
			Polygon		plPolygon;
			ModelIndex	miIndices;
			while (lineparser >> miIndices.m_nVertexID)
			{
				--miIndices.m_nVertexID;
				if (foundTexCoords)
				{
					if (!(lineparser >> slash >> miIndices.m_nTextureID))
						break;
					--miIndices.m_nTextureID;
				}

				if (foundNormals)
				{
					if (!(lineparser >> slash >> miIndices.m_nNormalID))
						break;
					--miIndices.m_nNormalID;
				}
				plPolygon.m_vmiModelIndices.push_back(miIndices);
			}
			vplPolygonBuffer.push_back(plPolygon);
			break;
		}
		}
	}
	in.close();

	if (!texturePath.empty())
		m_ModelTexture.load(texturePath);

	m_bLoaded = createVBO(
		vv3VertexBuffer,
		vv2TextureBuffer,
		vv3NormalBuffer,
		vplPolygonBuffer,
		foundTexCoords, foundNormals
	);

	return m_bLoaded;
}

void Model::render()
{
	if (!m_bLoaded) return;
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
	m_ModelTexture.drawStart();

	glBindVertexArray(m_uVaoID);
	glDrawArrays(GL_TRIANGLES, 0, m_nIndexSize);

	m_ModelTexture.drawEnd();
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY_EXT);
}

void Model::kill()
{
	deleteVBO();
}

int Model::parseID(const std::string & id)
{
	if (id == "v")	return VERTEX;
	if (id == "vt") return TEXCOORD;
	if (id == "vn") return NORMAL;
	if (id == "f")	return POLYGON;
	return -1;
}

bool Model::createVBO(
	std::vector<Vector3>& vv3VertexBuffer,
	std::vector<Vector2>& vv2TextureBuffer,
	std::vector<Vector3>& vv3NormalBuffer,
	std::vector<Polygon>& vplPolygonBuffer,
	bool bFoundTextures, bool bFoundNormals)

{
	std::vector<Vertex> vvVertices;

	m_nIndexSize = 0;

	for (auto& plPolygon : vplPolygonBuffer) {

		for (auto& miVertexIndex : plPolygon.m_vmiModelIndices)
		{
			Vertex vVertex;
			vVertex.m_v3Vertex.x = vv3VertexBuffer[miVertexIndex.m_nVertexID].x;
			vVertex.m_v3Vertex.y = vv3VertexBuffer[miVertexIndex.m_nVertexID].y;
			vVertex.m_v3Vertex.z = vv3VertexBuffer[miVertexIndex.m_nVertexID].z;

			if (bFoundNormals)
			{
				vVertex.m_v3Normal.x = vv3NormalBuffer[miVertexIndex.m_nNormalID].x;
				vVertex.m_v3Normal.y = vv3NormalBuffer[miVertexIndex.m_nNormalID].y;
				vVertex.m_v3Normal.z = vv3NormalBuffer[miVertexIndex.m_nNormalID].z;
			}

			if (bFoundTextures)
			{
				vVertex.m_v2Texture.x = vv2TextureBuffer[miVertexIndex.m_nTextureID].x;
				vVertex.m_v2Texture.y = vv2TextureBuffer[miVertexIndex.m_nTextureID].y;
			}

			vvVertices.push_back(vVertex);
			m_nIndexSize++;
		}
	}

	GLenum ErrorCheckValue = glGetError();
	const size_t BufferSize = m_nIndexSize * sizeof(Vertex);
	const size_t VertexSize = sizeof(Vertex);

	glGenVertexArrays(1, &m_uVaoID);
	glBindVertexArray(m_uVaoID);

	glGenBuffers(1, &m_uVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_uVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, &vvVertices[0], GL_STATIC_DRAW);

	glVertexPointer(3, GL_FLOAT, VertexSize, NULL);
	glNormalPointer(GL_FLOAT, VertexSize, (void*)(sizeof(Vector3)));
	glTexCoordPointer(2, GL_FLOAT, VertexSize, (void*)(sizeof(Vector3) * 2));

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glEnableVertexAttribArray(0);

	ErrorCheckValue = glGetError();
	if (ErrorCheckValue != GL_NO_ERROR)
	{
		fprintf(
			stderr,
			"ERROR: Could not create a VBO: %s \n",
			gluErrorString(ErrorCheckValue)
		);

		return false;
	}
	return true;
}

void Model::deleteVBO()
{
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &m_uVertexBuffer);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &m_uVaoID);

	m_bLoaded = false;
}
