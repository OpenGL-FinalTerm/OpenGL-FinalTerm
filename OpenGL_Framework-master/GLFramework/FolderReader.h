#pragma once

/* 
 * Original Coding Knowledge gotten from 'Vlad', https://stackoverflow.com/users/2970514/vlad
 * Code has been changed a lot to fit this Framework's possible needs. 
 */

class FolderReader {

	static WIN32_FIND_DATAA			m_DataFinder;
	static HANDLE					m_Handle;

public:

	static std::vector<std::string> readFolder(std::string path, std::string type);
	static std::vector<std::string> readFolder(std::string path);
	static std::vector<std::string> readFolder(std::string path, std::vector<std::string> supportedTypes);

private:
	static std::string findFirstFile();
	static std::string findNextFile();

	static void finder(std::string a);
	static std::vector<std::string> getFilenames();
};
