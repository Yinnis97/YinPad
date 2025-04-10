#pragma once

#include <iostream>
#include <string.h>
#include <fstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Options.h"

using namespace sf;

#define TextBox_Y 20
#define TextColor Black
#define OutlineThickness_Options_H 3.0

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

		// Shapes
		RectangleShape Background;
		RectangleShape TextWindow;
		RectangleShape Options_Horizontal;
		RectangleShape Options_Vertical;

		// Variables
		std::string input_text;
		Text text;
		bool CTRL_Pressed;

		// Saving and Loading

		// Shader
		Shader Background_Shader;
		Clock Clock_Shader;

	public:

		YinPad();
		~YinPad();

		void Initialize_Window();
		void Initialize_Variables();
		void Initialize_Background();
		void Initialize_Sections();

		void PollEvents();

		Vector2f GetMousePos();
		const bool Running();

		void Update();
		void Render();
};

