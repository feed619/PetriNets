
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <vector>
#include <math.h>
#include <fstream>

class Slae
{
private:
  bool notEq = false;
  bool Multi = false;
  const int Lines;
  double **Matrix;
  const int Columns;
  std::vector<std::string> ans;

  // Create dynamic matrix
  double **DynamicArray() const
  {
    double **matrix = new double *[this->Lines];
    for (int count = 0; count < this->Lines; count++)
      matrix[count] = new double[this->Columns];
    return matrix;
  }

  void OnceMakeAnswer()
  {
    for (int i = 1; i < this->Lines + 1; ++i)
    {
      this->Answer[this->Lines - i] = this->Matrix[this->Lines - i][this->Columns - 1];
      for (int j = 2; j <= i; j++)
      {
        this->Answer[this->Lines - i] = this->Answer[this->Lines - i] - this->Matrix[this->Lines - i][this->Columns - j] * this->Answer[this->Lines - j + 1];
      }
    }
  }

  void MultiMakeAnswer()
  {
    this->Multi = true;

    for (int i = 0; i < this->Lines; ++i)
    {
      if (this->Matrix[this->Lines - i - 1][this->Lines - i - 1] == 0)
        ans.push_back("X" + std::to_string(Lines - i));
      else
      {
        ans.push_back(std::to_string((int)this->Matrix[this->Lines - i - 1][this->Columns - 1]) + "-" + ans[i - 1]);
        for (int j = 2; j <= i; ++j)
        {
          ans[i] = ans[i] + "-" + ans[i - j];
        }
      }
    }
  }

public:
  double *Answer;
  Slae(int lines, const int columns) : Lines(lines), Columns(columns)
  {
    this->Matrix = DynamicArray();
    this->Answer = new double[lines + 1];
  };

  ~Slae()
  {
    for (int count = 0; count < this->Lines; count++)
    {
      delete[] this->Matrix[count];
    }
    delete[] this->Matrix;
    delete[] this->Answer;
  }

  // Geeters:
  int GetLines() const
  {
    double a = std::numeric_limits<double>::infinity();
    std::cout << (this->Matrix[1][2] == a);
    return this->Lines;
  }
  int GetColumns() const
  {
    return this->Columns;
  }
  // Filiing matrix:
  void ArrayFilling(std::vector<std::vector<double>> &Matrix_of_numbers) const
  {
    double **matrix = this->Matrix;
    const int lines = this->Lines;
    const int columns = this->Columns;

    for (int i = 0; i < lines; i++)
    {
      for (int j = 0; j < columns; j++)
      {
        matrix[i][j] = Matrix_of_numbers[i][j];
      }
    }
  }
  void ArrayFillingTxt(std::string name) const
  {
    double **matrix = this->Matrix;
    const int lines = this->Lines;
    const int columns = this->Columns;

    std::ifstream File;
    std::string TextLine;
    std::string strNumber;
    int number;
    File.open(name);
    for (int line = 0; line < lines; line++)
    {
      int n = 0;
      std::getline(File, TextLine);
      for (int i = 0; i < TextLine.length(); i++)
      {
        if (TextLine[i] == ' ')
        {
          if (strNumber.length() > 0)
          {
            matrix[line][n] = std::stod(strNumber);

            n += 1;
          }
          strNumber = "";
        }
        else
          strNumber += TextLine[i];
      }
      if (strNumber.length() > 0)
      {
        matrix[line][n] = std::stod(strNumber);
        strNumber = "";
      }
    }
    File.close();
  }
  // GausMethod
  void GaussMethod() const
  {
    double del;

    for (int m = 0; m < this->Lines; ++m)
    {
      for (int i = m; i < this->Lines; ++i)
      {
        del = this->Matrix[i][m];
        if (del == 0)
        {
          continue;
        }
        for (int j = m; j < this->Columns; ++j)
        {
          this->Matrix[i][j] = this->Matrix[i][j] / del;
          if (i > m)
            this->Matrix[i][j] = this->Matrix[i][j] - this->Matrix[m][j];
        }
      }
    }
  }
  // Create answer
  void MakeAnswer()
  {
    int Dioganals = 0;
    int Answer = 0;
    int notAns = 0;

    for (int i = 0; i < this->Lines; i++)
    {
      if (this->Matrix[i][i] == 0)
      {

        if (this->Matrix[i][Lines] != 0)
          this->notEq = true;
        notAns += 1;
      }
      if (this->Matrix[i][i] != this->Matrix[i][i] || this->Matrix[i][i] == 0)
      {
        Dioganals = 1;
        this->Matrix[i][i] = 0;
        if (this->Matrix[i][this->Columns - 1] != 0)
        {
          Answer = 1;
        }
      }
    }
    if (notAns)
    {
      this->notEq = true;
    }
    else if (Dioganals == 1 && Answer == 0)
    {
      MultiMakeAnswer();
    }
    else
      OnceMakeAnswer();
  }

  void GetAnswer(std::vector<std::string> &answer)
  {
    if (this->notEq)
    {
      answer.push_back("Not Answer");
    }
    else if (this->Multi)
    {
      for (int i = 0; i < this->Lines; i++)
      {
        answer.push_back("X" + std::to_string(i + 1) + " = " + this->ans[this->Lines - 1 - i]);
      }
    }
    else if (this->notEq)
    {
      answer.push_back("Not Answer");
    }
    else
    {
      for (int i = 0; i < this->Lines; i++)
      {
        std::string str_num = std::to_string(this->Answer[i]);
        str_num = str_num.substr(0, str_num.find(".") + 3);
        if (str_num[str_num.length() - 1] == '0')
        {
          if (str_num[str_num.length() - 2] == '0')
          {
            str_num = str_num.substr(0, str_num.length() - 3);
          }
          else
          {
            str_num = str_num.substr(0, str_num.length() - 1);
          }
        }
        answer.push_back("X" + std::to_string(i + 1) + " = " + str_num);
      }
    }
  }
};
