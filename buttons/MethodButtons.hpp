#ifndef _METHOD_
#define _METHOD_

#include "../pakage/init.hpp"
#include "../fileButton/FileSource.cpp"
#include "../history/history.cpp"

#include "../slay/Slae.h"
#include "../slay/File.h"

class MethodButtons
{
public:
	MethodButtons() = default;
	~MethodButtons() = default;

	void MinusMethod(int &sizeMatrix);
	void PlusMethod(int &sizeMatrix);
	void FileMethod(std::string &string_path);
	void HistoryMethod(std::string &string_path);
	void ExitMethod(sf::Window &window);

	std::vector<std::string> FileSlae(std::string& path);
	std::vector<std::string> ManuallySlae(std::vector<std::vector<double>>& Matrix_of_numbers,int lines, const int columns);


};

#endif