#include "stdafx.h"
#include "Texture.h"
#include <atlimage.h>

GLuint Texture::m_uGlobalTexID{ 0 };

std::vector<GLubyte> getImageBits(CImage* img);

Texture::Texture()
{
}

Texture::~Texture()
{
}

void Texture::load(std::string path)
{
	CImage cimg;
	cimg.Load(path.c_str());

	glBindTexture(GL_TEXTURE_2D, m_uGlobalTexID);

	int bitsPerPixel = cimg.GetBPP() / 8;
	bool hasAlpha = bitsPerPixel == 4;

	m_Texture.uTextureIdx = m_uGlobalTexID;
	m_Texture.hasAlpha = hasAlpha;
	m_Texture.bytes = getImageBits(&cimg);

	m_Texture.height = cimg.GetHeight();
	m_Texture.width = cimg.GetWidth();

	GLenum format = GL_BGR_EXT;
	if (hasAlpha) format = GL_BGRA_EXT;

	glTexImage2D(GL_TEXTURE_2D, 0, bitsPerPixel, cimg.GetWidth(), cimg.GetHeight(), 0, format, GL_UNSIGNED_BYTE, m_Texture.getBytes());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_LINEAR);

	m_uGlobalTexID++;
	m_bImgLoaded = true;
}

void Texture::drawStart(bool usingEnv)
{
	if (!m_bImgLoaded)
		return;
	glEnable(GL_TEXTURE_2D);
	if (usingEnv)
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	if (m_Texture.hasAlpha)
	{
		glGetBooleanv(GL_BLEND, &m_bHasAlpha);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);
	}

	glBindTexture(GL_TEXTURE_2D, m_Texture.uTextureIdx);
}

void Texture::drawEnd()
{
	if (!m_bImgLoaded)
		return;
	glDisable(GL_TEXTURE_2D);
}

std::vector<GLubyte> getImageBits(CImage* cimg)
{
	std::vector<GLubyte> image_bits;
	BITMAP bmp;
	GetObject(*cimg, sizeof(BITMAP), &bmp);
	BITMAPINFOHEADER bmih{ 0 };
	bmih.biSize = sizeof(BITMAPINFOHEADER);
	bmih.biWidth = bmp.bmWidth;
	bmih.biHeight = bmp.bmHeight;
	bmih.biPlanes = 1;
	bmih.biBitCount = cimg->GetBPP();
	bmih.biCompression = (BI_RGB);

	HDC hdc = GetDC(NULL);
	GetDIBits(hdc, *cimg, 0, bmp.bmHeight, NULL, (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	image_bits.resize(bmih.biSizeImage);
	GetDIBits(hdc, *cimg, 0, bmp.bmHeight, &(image_bits[0]), (LPBITMAPINFO)&bmih, DIB_RGB_COLORS);
	ReleaseDC(NULL, hdc);
	return image_bits;
}
