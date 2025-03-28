#include "YinPad.h"

YinPad::YinPad()
{
    Initialize_Variables();
	Initialize_Window();
    Initialize_Background();
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
    text.setFont(font);
    
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
                std::ofstream MyFile("Save.cpp");
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
                text.setFillColor(Color::White);
                text.setString(input_text);
            }
            break;
        }
    }
}

const bool YinPad::Running()
{
	return this->window->isOpen();
}

void YinPad::Update()
{
    PollEvents();
    Background_Shader.setUniform("u_time", Clock_Shader.getElapsedTime().asSeconds());
}

void YinPad::Render()
{
    window->clear();
    window->draw(Background, &Background_Shader);
    window->draw(text);
    window->display();
}
