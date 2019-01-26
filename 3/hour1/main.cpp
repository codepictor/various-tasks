#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
//#include <iostream>


enum State
{
	state1,
	state2,
	state3
};

enum Result {
	result1,
	result2,
	result3
};



int main(int argc, const char** argv)
{
	State state = state1;
	Result result = result1;

	cv::VideoCapture cap(0); // open the video file for reading
	if (!cap.isOpened())
	{
		return 0;
	}

	sf::RenderWindow window(sf::VideoMode(800, 600), "RenderWindow");
	cv::Mat frameRGB, frameRGBA;
	sf::Image image;
	sf::Texture cameraTexture;
	sf::Texture resultTexture;
	sf::Event event;
	sf::Sprite sprite;
	tgui::Gui gui(window);
	std::string tempStr;

	tgui::Button::Ptr loading = tgui::Button::create();
	loading->setPosition(tgui::bindWidth(gui) * 0.15, tgui::bindHeight(gui) * 0.825);
	loading->setSize(tgui::bindWidth(gui) * 0.7, tgui::bindHeight(gui) * 0.15);

	int percent = 0;
	bool isCursorOn = false;

	tgui::Button::Ptr beginTest = tgui::Button::create();
	beginTest->setPosition(tgui::bindWidth(gui) * 0.15, tgui::bindHeight(gui) * 0.825);
	beginTest->setSize(tgui::bindWidth(gui) * 0.7, tgui::bindHeight(gui) * 0.15);
	beginTest->setText("Press this button, please");
	gui.add(beginTest);

	beginTest->connect("MouseEntered", [&]() { isCursorOn = true; });
	beginTest->connect("MouseLeft", [&]() { isCursorOn = false; });
	beginTest->connect("pressed", [&]() { state = state2; });

	while (window.isOpen())
	{
		window.clear();

		switch (state)
		{
			case state1:
				cap >> frameRGB;
				if (frameRGB.empty())
				{
					break;
				}

				cv::cvtColor(frameRGB, frameRGBA, cv::COLOR_BGR2RGBA);
				image.create(frameRGBA.cols, frameRGBA.rows, frameRGBA.ptr());
				if (!cameraTexture.loadFromImage(image))
				{
					break;
				}

				sprite.setTexture(cameraTexture);
				//sprite.setPosition(10.0, 10.0);
				window.draw(sprite);
				gui.draw();
				break;

			case state2:
				percent += 1;
				if (percent >= 200)
				{
					percent += 50;
				}

				if (percent >= 1000)
				{
					state = state3;
				}

				tempStr = "Analyzing your photo " + std::to_string(percent / 10);
				window.draw(sprite);
				loading->setText(tempStr.c_str());

				gui.add(loading);
				gui.draw();
				break;

			case state3:
				switch (result)
				{
					case result1:
						resultTexture.loadFromFile("../bin/data/risovach_ru.jpg");
						break;
					case result2:
						resultTexture.loadFromFile("../bin/data/risovach_ru_1.jpg");
						break;
					case result3:
						resultTexture.loadFromFile("../bin/data/risovach_ru_2.jpg");
						break;
				}
				sprite.setTexture(resultTexture);
				window.draw(sprite);
				break;
		}

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::Closed:
					window.close();
					break;

				case sf::Event::MouseButtonPressed:
					if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && isCursorOn)
					{
						state = state2;
						result = result3;
					}
					if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && isCursorOn)
					{
						state = state2;
						result = result2;
					}
					break;
			}

			gui.handleEvent(event);
			window.display();
		}
	}

	return 0;
}
