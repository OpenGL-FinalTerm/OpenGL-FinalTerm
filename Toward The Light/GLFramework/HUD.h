struct BMPImage
{
		int   width;
		int   height;
		char *data;
};

class Texture
{
public:
		BMPImage GetTextureInfo(char * ImageName);
		void LoadImage(char * ImageName, int ID);
		void SetActive(int ID);
		void SetRepeat();
		void SetClamp();
private:
		unsigned int g_textureID[10];
		BMPImage textureImage[10];
		int Active;
};
class HUD
{
public:
		void Begin();
		void End();
		int WinX, WinY; //The window size
};
