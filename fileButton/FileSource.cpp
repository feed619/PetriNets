#include "FileSource.hpp"
//-----------------------Constructor--------------------------------///
FileSource::FileSource()
{
    this->windowFile = new sf::RenderWindow(sf::VideoMode(this->width, this->height), "Open file", sf::Style::None);

    this->windowFile->setFramerateLimit(this->fps);
    this->windowFile->setKeyRepeatEnabled(false);
    this->image_file.loadFromFile("image/fileWindow/fileframe2.png");
    this->texture_file.loadFromImage(this->image_file);
    this->sprite_file.setTexture(this->texture_file);

    this->ExitButton = new Button(sf::Vector2f(954, 50), "image/fileWindow/buttons/exit.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png");
    this->SaveButton = new Button(sf::Vector2f(954, 130), "image/fileWindow/buttons/save.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png");
    this->InputButton = new Button(sf::Vector2f(175, 151), "image/fileWindow/buttons/inputnew.png", "image/fileWindow/buttons/inputshadownew.png", "image/fileWindow/buttons/inputshadownew.png");
    this->ExitWindow = new Button(sf::Vector2f(1152, 0), "image/frontPM/exitnew.png", "image/frontPM/shadow/shadowExitWindow.png", "image/frontPM/shadow/shadowExitWindow.png");
    this->SecondSave = new Button(sf::Vector2f(954, 130), "image/fileWindow/buttons/save3.png", "image/frontButton/shadow/shadow15.png", "image/frontButton/click/click15.png");

    this->font.loadFromFile("fileButton/font/qwe.ttf");
    this->text = new sf::Text(this->string_Text, font);
    this->text->setCharacterSize(50);
    this->text->setStyle(sf::Text::Italic);
    this->text->setPosition(sf::Vector2f(180, 140));
}
//-----------------------Destructor---------------------------------///
FileSource::~FileSource()
{
    delete this->windowFile;
    delete this->ExitButton;
    delete this->SaveButton;
    delete this->InputButton;
    // delete this->text;
}
//---------------------Start of FileSource-------------------------///
void FileSource::StartFileMethod(std::string &string_path)
{
    FileSource::SaveAtor(string_path);
    while (this->windowFile->isOpen())
    {
        FileSource::upDateF();
        FileSource::DrawF();
    }
    FileSource::CheckAtor(string_path);
}
//-----------------------Event-------------------------------------///
void FileSource::upDateF()
{
    sf::Event event;
    while (this->windowFile->pollEvent(event))
    {
        if (this->InputButton->TextPut == true)
            FileSource::TextMethod(event);
    }
}
//-----------------------Draw buttons-------------------------------///
void FileSource::DrawF()
{
    this->windowFile->clear();
    this->windowFile->draw(this->sprite_file);

    DrawButtonsFile();
    DrawAnimate();
    if (this->string_Text.length() < 27)
    {
        this->windowFile->draw(*this->text);
    }
    else
    {
        this->text->setString(this->string_Text.substr(this->string_Text.length() - 27, this->string_Text.length()));
        this->windowFile->draw(*this->text);
    }
    this->windowFile->display();
}
void FileSource::DrawButtonsFile()
{
    this->windowFile->draw(this->ExitButton->getSprite());
    this->windowFile->draw(this->InputButton->getSprite());
    this->windowFile->draw(this->ExitWindow->getSprite());
    if (this->SaveButton->Enabled == true)
        this->windowFile->draw(this->SaveButton->getSprite());
    else
        this->windowFile->draw(this->SecondSave->getSprite());
}
//-----------------------Vector of mouse position-------------------///
void FileSource::MousePosition()
{
    this->mou_poz.x = sf::Mouse::getPosition().x - this->windowFile->getPosition().x;
    this->mou_poz.y = sf::Mouse::getPosition().y - this->windowFile->getPosition().y;
}
//-----------------------Animate buttons----------------------------///
void FileSource::DrawAnimate()
{
    FileSource::MousePosition();

    if (this->ExitButton->getSprite().getGlobalBounds().contains(this->mou_poz))
    {
        this->windowFile->draw(ExitButton->getShadowSprite());
        FileSource::PositionMouse(this->windowFile, this->ExitButton, 1);
    }
    if (this->SaveButton->getSprite().getGlobalBounds().contains(this->mou_poz) and this->SaveButton->Enabled == true)
    {
        this->windowFile->draw(SaveButton->getShadowSprite());
        FileSource::PositionMouse(this->windowFile, this->SaveButton, 2);
    }
    if (this->InputButton->getSprite().getGlobalBounds().contains(this->mou_poz) and this->SaveButton->Enabled == true)
    {
        FileSource::PositionMouse(this->windowFile, this->InputButton, 3);
    }
    if (this->ExitWindow->getSprite().getGlobalBounds().contains(this->mou_poz) and this->ExitWindow->Enabled == true)
    {
        this->windowFile->draw(this->ExitWindow->getShadowSprite());
        FileSource::PositionMouse(this->windowFile, this->ExitWindow, 4);
    }
    if (this->InputButton->TextPut == true)
    {
        this->windowFile->draw(InputButton->getShadowSprite());
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and !this->InputButton->getSprite().getGlobalBounds().contains(this->mou_poz))
    {
        this->InputButton->TextPut = false;
    }

}
//-----------------------Click and shadow buttons-------------------///
void FileSource::PositionMouse(sf::RenderWindow *window, Button *button, const int i)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and !button->BTN_ACTIVE and button->Enabled == true)
    {
        window->draw(button->getSpriteShadow());
        button->BTN_ACTIVE = true;
        FileSource::FunctionButtons(i);
    }
    else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        button->BTN_ACTIVE = false;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        window->draw(button->getSpriteShadow());
    }
}
//----------------Methods of buttons after click -------------------///
void FileSource::ExitButtonMethod()
{
    if (this->SaveButton->Enabled == false)
    {
        this->SaveButton->Enabled = true;
    }
}
void FileSource::SaveButtonMethod()
{
    this->SaveButton->Enabled = false;
}
void FileSource::InputButtonMethod()
{
    if (this->InputButton->TextPut == false)
    {
        this->InputButton->TextPut = true;
    }
}
void FileSource::ExitWindowButtonMethod()
{
    this->windowFile->close();
}
//----------------Functions bittons --------------------------------///
void FileSource::FunctionButtons(const int index)
{
    switch (index)
    {
    case 1:
        FileSource::ExitButtonMethod();
        break;

    case 2:
        FileSource::SaveButtonMethod();
        break;
    case 3:
        FileSource::InputButtonMethod();
        break;
    case 4:
        FileSource::ExitWindowButtonMethod();
        break;
    }
}
//----------------text --------------------------------------------///
void FileSource::TextMethod(sf::Event &event)
{
    while (this->windowFile->pollEvent(event))
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Backspace))
        {
            if (this->string_Text.length() > 0)
            {
                this->string_Text.pop_back();
                this->text->setString(this->string_Text);
            }
        }
        else if (event.type == sf::Event::TextEntered)
        {
            this->string_Text += event.text.unicode;
            this->text->setString(this->string_Text);
        }
    }
}
//----------------SaveAtor and CheckAtor----------------------------------------///
void FileSource::SaveAtor(std::string &string_path)
{
    this->string_Text = string_path;
    this->text->setString(this->string_Text);
    if (string_path.length() > 0)
        FileSource::SaveButtonMethod();
}
void FileSource::CheckAtor(std::string &string_path)
{
    if (this->SaveButton->Enabled == false)
    {
        string_path = this->string_Text;
    }
    if (this->SaveButton->Enabled == true)
    {
        string_path = "";
    }
}