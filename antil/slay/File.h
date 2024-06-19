#include <iostream>
#include <string>
#include <fstream>

struct FileInfo
{
  std::ifstream File;
  std::string Text;

  FileInfo(std::string name)
  {
    File.open(name);
  }

  ~FileInfo()
  {
    File.close();
  }

  int Read_Columns()
  {
    std::string TextLine;
    std::string strNumber;
    int columns = 0;

    std::getline(File, TextLine);
    for (int i = 0; i < TextLine.length(); i++)
    {
      if (TextLine[i] == ' ')
      {
        if (strNumber.length() > 0)
        {
          columns += 1;
        }
        strNumber = "";
      }
      else
        strNumber += TextLine[i];
    }
    if (strNumber.length() > 0)
    {
      columns += 1;
    }
    return columns;
  }
};
