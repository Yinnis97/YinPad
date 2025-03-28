#pragma once

#include <iostream>
#include <string.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

using namespace sf;

class YinPad
{
	private:

		RenderWindow* window;
		Event event;
		VideoMode videomode;
		Font font;

		// Mouse Positions
		Vector2i mousePosWindow;
		Vector2f mousePosView;

		// Variables
		RectangleShape Background;
		std::string input_text;
		Text text;
		bool CTRL_Pressed;

		// Saving and Loading
		FILE file;

		// Shader
		Shader Background_Shader;
		Clock Clock_Shader;

	public:

		YinPad();
		~YinPad();

		void Initialize_Window();
		void Initialize_Variables();
		void Initialize_Background();

		void PollEvents();

		const bool Running();

		void Update();
		void Render();
};

