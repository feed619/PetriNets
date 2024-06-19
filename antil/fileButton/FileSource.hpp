#ifndef _FILE_SOURCE_
#define _FILE_SOURCE

#include "../pakage/init.hpp"
// #include "../buttons/Button.cpp"

class FileSource
{
	sf::RenderWindow *windowFile;
	// sf::Window *windowFile;

	sf::Image image_file;
	sf::Texture texture_file;
	sf::Sprite sprite_file;

	sf::Font font;
	sf::Text *text;
	std::string string_Text = "";
	int num = 0;
	Button *SaveButton;
	Button *ExitButton;
	Button *InputButton;
	Button *ExitWindow;
	Button *SecondSave;
	
	sf::Vector2f mou_poz;

	int width = 1201;//1000
	int height = 239;
	int fps = 30;

	void MousePosition();
	void upDateF();
	void DrawF();

	// draw and animate buttons
	void DrawAnimate();
	void DrawButtonsFile();
	void PositionMouse(sf::RenderWindow *window, Button *button, const int i);
	// methods of save ande exit nuttons
	void FunctionButtons(const int index_method);
	void ExitButtonMethod();
	void SaveButtonMethod();
	void InputButtonMethod();
	void ExitWindowButtonMethod();
	void TextMethod(sf::Event &event);
	/// SaveAtor and CheckAtor-
	void SaveAtor(std::string &string_path);
	void CheckAtor(std::string &string_path);

public:
	FileSource();
	~FileSource();
	std::string *str_path;

	void StartFileMethod(std::string &string_path);
};

#endif