#include "YinPad.h"

YinPad::YinPad()
{
    Initialize_Variables();
	Initialize_Window();
    Initialize_Background();
    Initialize_Sections();
}

YinPad::~YinPad()
{
	delete window;
}

void YinPad::Initialize_Window()
{
	videomode = VideoMode::getDesktopMode();
	window = new RenderWindow(videomode, "YinPad");
	window->setFramerateLimit(60);
	window->setVerticalSyncEnabled(1);
}

void YinPad::Initialize_Variables()
{
	window = nullptr;
    if (!this->font.loadFromFile("Fonts/PixeloidSans.ttf"))
    {
        std::cerr << "Error: Kon Font Niet Laden!" << std::endl;
    }
    CTRL_Pressed = false;
}

void YinPad::Initialize_Background()
{
    if (!this->Background_Shader.loadFromFile("Shaders/Background.frag", sf::Shader::Fragment))
    {
        std::cerr << "Error Loading Background Shader" << std::endl;
    }

    this->Background_Shader.setUniform("u_resolution", Vector2f(window->getSize()));

    this->Background.setSize(Vector2f(window->getSize()));
    this->Background.setFillColor(sf::Color::White);
}

void YinPad::Initialize_Sections()
{
    // Text
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(Color::TextColor);
    text.setString("");
    text.setPosition(Vector2f((window->getSize().x / 2), ((window->getSize().y / window->getSize().y) + (window->getSize().y / TextBox_Y))));

    // Text section
    TextWindow.setSize( Vector2f((window->getSize().x / 2),(window->getSize().y /2)) );
    TextWindow.setPosition(Vector2f((window->getSize().x / 2), ( (window->getSize().y / window->getSize().y) + (window->getSize().y / TextBox_Y))));
    TextWindow.setFillColor(Color::Yellow);
    TextWindow.setOutlineColor(Color::Black);

    // Horizontel Options Bar
    Options_Horizontal.setSize(Vector2f((window->getSize().x), (window->getSize().y / 30)));
    Options_Horizontal.setPosition(Vector2f((window->getSize().x / window->getSize().x), (window->getSize().y / window->getSize().y)));
    Options_Horizontal.setFillColor(Color::Yellow);
    Options_Horizontal.setOutlineColor(Color::Black);
    Options_Horizontal.setOutlineThickness(OutlineThickness_Options_H);

    // Vertical Options Bar
    //Options_Vertical.setSize(Vector2f((window->getSize().x / 2), (window->getSize().y / 2)));
    //Options_Vertical.setPosition(Vector2f((window->getSize().x / 2), (window->getSize().y / 2)));
    //Options_Vertical.setFillColor(Color::Green);
}

void YinPad::PollEvents()
{
    while (window->pollEvent(event))
    {
        switch (event.type)
        {
        case Event::Closed:
            window->close();
            break;

        case Event::KeyPressed:
            if (event.key.code == Keyboard::LControl)
            {
                CTRL_Pressed = true;
            }
            else if (CTRL_Pressed && event.key.code == Keyboard::S)
            {
                std::ofstream MyFile("Save.txt");
                MyFile << input_text;
                MyFile.close();
            }
            else if (event.key.code == Keyboard::Escape)
            {
                window->close();
            }
            else if (event.key.code == Keyboard::Backspace)
            {
                if (!input_text.empty())
                {
                    input_text.pop_back();
                    text.setString(input_text);
                }
            }
            else if (event.key.code == Keyboard::Enter)
            {
                input_text += '\n';
                text.setString(input_text);
            }
            break;

        case Event::TextEntered:
            if (event.text.unicode < 128 && event.text.unicode > 31)
            {
                input_text += static_cast<char>(event.text.unicode);
                
                size_t lastNewLine = input_text.find_last_of('\n');

                std::string lastLine;
                if (lastNewLine == std::string::npos)
                {
                    lastLine = input_text;
                }
                else
                {
                    lastLine = input_text.substr(lastNewLine + 1);
                }

                Text tempText(lastLine, font, text.getCharacterSize());

                if (tempText.getGlobalBounds().width >= (window->getSize().x - TextBox_Y))
                {
                    input_text += '\n';
                }
                
                text.setString(input_text);

            }
            break;
        }
    }
}

Vector2f YinPad::GetMousePos()
{
    mousePosWindow = Mouse::getPosition(*this->window);
    mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);

    return Vector2f(mousePosView);
}

const bool YinPad::Running()
{
	return this->window->isOpen();
}

void YinPad::Update()
{
    PollEvents();
    Background_Shader.setUniform("u_time", Clock_Shader.getElapsedTime().asSeconds());
    Background_Shader.setUniform("u_mouse", GetMousePos());
}

void YinPad::Render()
{
    window->clear();
    window->draw(Background, &Background_Shader);
    window->draw(TextWindow);
    window->draw(Options_Horizontal);
    window->draw(text);
    window->display();
}
