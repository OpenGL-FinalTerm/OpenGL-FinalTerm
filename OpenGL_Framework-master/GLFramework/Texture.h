#pragma once

class Texture
{
public:

	struct TextureInfo
	{
		GLubyte* getBytes() { return &(bytes[0]); }

		GLuint					uTextureIdx	{ 0 };
		bool					hasAlpha	{ false };
		std::vector<GLubyte>	bytes;
		int						height;
		int						width;
	};

private:

	static GLuint				m_uGlobalTexID;

	TextureInfo					m_Texture;
	GLboolean					m_bHasAlpha{ false };
	GLboolean					m_bImgLoaded{ false };

public:
	Texture();
	~Texture();

	void load(std::string path);

	void drawStart(bool usingEnv = true);
	void drawEnd();
};

