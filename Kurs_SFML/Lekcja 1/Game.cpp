#include "Game.h"

RenderWindow window(VideoMode(1280,720),"Mechanized Techno Explorer",Style::Fullscreen);

Game::Game(void)
{
	state = END;

	if(!font.loadFromFile("data/Mecha.ttf"))
	{
		MessageBox(NULL,"Font not found!","ERROR",NULL);
		return;
	}

	state = MENU;
}


Game::~Game(void)
{
}


void Game::runGame()
{
	while(state != END)
	{
		switch (state)
		{
		case GameState::MENU:
			menu();
			break;
		case GameState::GAME:
			//
			break;
		}
	}
}


void Game::menu()
{
	Text title("Mechanized Techno Explorer",font,80);
	title.setStyle(Text::Bold);

	title.setPosition(1280/2-title.getGlobalBounds().width/2,20);

	const int ile = 2;

	Text tekst[ile];

	string str[] = {"Play","Exit"};
	for(int i=0;i<ile;i++)
	{
		tekst[i].setFont(font);
		tekst[i].setCharacterSize(65);

		tekst[i].setString(str[i]);
		tekst[i].setPosition(1280/2-tekst[i].getGlobalBounds().width/2,250+i*120);
	}

	while(state == MENU)
	{
		Vector2f mouse(Mouse::getPosition());
		Event event;

		while(window.pollEvent(event))
		{
			//Wci�ni�cie ESC lub przycisk X
			if(event.type == Event::Closed || event.type == Event::KeyPressed &&
				event.key.code == Keyboard::Escape)
				state = END;
			
			//klikni�cie EXIT
			else if(tekst[1].getGlobalBounds().contains(mouse) &&
				event.type == Event::MouseButtonReleased && event.key.code == Mouse::Left)
			{
				state = END;
			}
		}
		for(int i=0;i<ile;i++)
			if(tekst[i].getGlobalBounds().contains(mouse))
				tekst[i].setColor(Color::Cyan);
			else tekst[i].setColor(Color::White);
		
		window.clear();
		
		window.draw(title);
		for(int i=0;i<ile;i++)
			window.draw(tekst[i]);

		window.display();
	}
}