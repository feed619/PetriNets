#include "MethodButtons.hpp"

void MethodButtons::MinusMethod(int &sizeMatrix)
{
    if (sizeMatrix > 1)
    {
        sizeMatrix -= 1;
    }
}

void MethodButtons::PlusMethod(int &sizeMatrix)
{
    if (sizeMatrix < 6)
    {
        sizeMatrix += 1;
    }
}

void MethodButtons::FileMethod(std::string &string_path)
{
    FileSource fileSource;
    fileSource.StartFileMethod(string_path);
}

void MethodButtons::HistoryMethod(std::string &string_path)
{
    History history;
    history.StartFileMethod(string_path);
}

void MethodButtons::ExitMethod(sf::Window &window)
{
    window.close();
}

std::vector<std::string> MethodButtons::FileSlae(std::string &path)
{
    std::vector<std::string> answer;
    int lines, columns;
    try
    {

        FileInfo read(path);
        columns = read.Read_Columns();
        lines = columns - 1;

        if (columns < 0)
        {
            answer.push_back("Error with file");
            return answer;
        }
        else
        {
            Slae Matrix(lines, columns);
            Matrix.ArrayFillingTxt(path);
            Matrix.GaussMethod();
            Matrix.MakeAnswer();
            Matrix.GetAnswer(answer);
            return answer;
        }
    }
    catch (...)
    {
        answer.push_back("Error with opening file");
        return answer;
    }
}

std::vector<std::string> MethodButtons::ManuallySlae(std::vector<std::vector<double>> &Matrix_of_numbers, int lines, const int columns)
{
    Slae Matrix(lines, columns);
    std::vector<std::string> answer;
    Matrix.ArrayFilling(Matrix_of_numbers);

    Matrix.GaussMethod();
    Matrix.MakeAnswer();
    Matrix.GetAnswer(answer);

    return answer;
}
