///Okno menu 
/**
* Plik w ktorym zostalo zaimplementowane okno menu wraz z przejsciami na kolejny level
*/
#include <SFML/Graphics.hpp>
#include "MainMenu.h"
#include <fstream>
#include "Poziom1.h"
#include <windows.h>
#include <SFML/Audio.hpp>

using namespace std;
using namespace sf;

int width = 1100;
int height = 825;


///Funkcja Main
/**
* W funkcji main sa zawarte
* Wielkorotne petle while oraz if.
* Funkcje tworzace okno
* Instrukcje okreslajaca ilosc klatek na sekunde
* Stworzenie obiekyu klasy MainMenu
* Wskaznik na obiekt klasy
* Instrukcje pozwalajace na dodanie dzwieku, sciezki oraz dzwiekowej
* Implementacja wygladu tla "menu", tla "opcji", tla "o grze"
* Petla ktora jest uruchomiona tylko kiedy jestesmy w menu
* Stworzenie eventu
* Sprawdzanie czy event dziala i wlacza okno
* Zamkniecie eventu
* Petla sprawdzajaca czy przycisk jest nacisniety
* Petla sprawdzajaca ktory przycisk jest nacisniety
* Funkcja zwracajaca to jaka opcja zostala wybrana
* Petla sprawdzajaca ktory przyciskt zostal nacisniety
* Szesc peti ktora sprawdza wartosc jaka zwraca funkcja. Zaleznie od tego jaka wartosc sczyta kontunuje dzialanie funkcji kub ja zatrzymuje
* Instrukcja wlaczajaca muzyke kiedy poziom sie uruchamia ++
* @param[in] <x> zmienna okreslajaca czy gra dziala poprzez przypisanie do niej odpowiedniej artosci po zakonczeniu poziomu pozyywnie oraz niegatywnie.
**/
void main()
{
	RenderWindow MENU(VideoMode(width, height), "Menu", Style::Default); // tworzy okno 
	MENU.setFramerateLimit(60);  // set to jest od ilosci klatek na sekunde
	MainMenu mainMenu(MENU.getSize().x, MENU.getSize().y);  ///tworzymy obiekt klasy MainManu
	Poziom1* poziom1 = new Poziom1(); /// wskaznik na obiekt klasy 
	SoundBuffer buffer; // od dzwieku 
	buffer.loadFromFile("Audio/menuAudio.wav"); //dodoanie sciezki d dzwieku 
	Sound sound;
	sound.setBuffer(buffer);
	sound.play(); //granie 

	//tlo menu
	RectangleShape tloMenu;
	tloMenu.setSize(Vector2f(width, height));  // wielkosc planszy 
	Texture mainTlo;  //
	mainTlo.loadFromFile("Textury/background.jpg");
	tloMenu.setTexture(&mainTlo);
	//tlo opcji 
	RectangleShape tloOpcje;
	tloOpcje.setSize(Vector2f(width, height));
	Texture opcjeTlo;
	opcjeTlo.loadFromFile("Textury/background3.jpg");
	tloOpcje.setTexture(&opcjeTlo);
	//tlo o grze
	RectangleShape tloOGrze;
	tloOGrze.setSize(Vector2f(width, height));
	Texture oGrzeTlo;
	oGrzeTlo.loadFromFile("Textury/background4.jpg");
	tloOGrze.setTexture(&oGrzeTlo);



	while (MENU.isOpen()) ///funkcja dzije sie tylko kiedy jestesmy w mennu
	{
		Event menuEvent; 
		while (MENU.pollEvent(menuEvent))
		{
			if (menuEvent.type == Event::Closed)
			{
				MENU.close();
			}
			if (menuEvent.type == Event::KeyPressed) /// jesli przycisk zostal nacisniety 
			{
				if (menuEvent.key.code == Keyboard::Up) ///sprawdza czy przyciskt w gore lub w dol zostalk nacisniety lub esc
				{
					mainMenu.MoveUp();
					break;
				}
				if (menuEvent.key.code == Keyboard::Down)
				{
					mainMenu.MoveDown();
					break;
				}
				if (menuEvent.key.code == Keyboard::Return)
				{
					int x = mainMenu.MainMenuPressed();		
					if (x == 0)
					{
						sound.stop();

						if (poziom1->Start() == -1)
						{
							continue;
						}

						else
						{
							break;
						}

					}
					sound.play();
					if (x == 1)
					{
						RenderWindow Options(VideoMode(width, height), "Opcje");
						while (Options.isOpen())
						{
							Event aevent;
							while (Options.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									Options.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										Options.close();
									}
								}
							}
							Options.clear();
							Options.draw(tloOpcje);
							Options.display();
						}
					}
					if (x == 2)
					{
						RenderWindow About(VideoMode(width, height), "O grze");
						while (About.isOpen())
						{
							Event aevent;
							while (About.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									About.close();
								}
								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										About.close();
									}
								}
							}
							About.clear();
							About.draw(tloOGrze);
							About.display();

						}
					}
					if (x == 3)
					{
						MENU.close();
						break;
					}
				}
			}
			MENU.clear();
			MENU.draw(tloMenu);
			mainMenu.draw(MENU);
			MENU.display();
		}
	}
}