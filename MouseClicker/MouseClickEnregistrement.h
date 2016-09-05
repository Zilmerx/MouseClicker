#pragma once

#include <iostream>
#include <vector>
#include <conio.h> // getch
#include <ctype.h> // toupper
#include <thread>
#include <chrono>
#include <string>

#include "MouseClicker.h"

#define PRECISIONLENT std::chrono::milliseconds(3)
#define PRECISION std::chrono::milliseconds(1)
#define PRECISIONRAPIDE std::chrono::microseconds(1)

class MouseClickEnregistrement
{
	MouseClicker mouse;

	std::vector<MousePoint> ptList;
	std::chrono::nanoseconds duree;

	bool continuer;

public:

	MouseClickEnregistrement(size_t MaxNbPoints = 15000) :
		duree{ 0 }
	{
		ptList.reserve(MaxNbPoints);
	}




	void Menu()
	{
		SetState("");

		continuer = true;

		char c;

		while (continuer)
		{
			c = toupper(readKey());

			std::cout << std::endl;

			switch (c)
			{
				case 'F':
				{
					MenuClear();
				}
				break;

				case 'C':
				{
					MenuExecuterLent();
				}
				break;

				case 'X':
				{
					MenuExecuter();
				}
				break;

				case 'Z':
				{
					MenuExecuterRapide();
				}
				break;

				case 'R':
				{
					MenuEnregistrer();
				}
				break;

				case 'T':
				{
					MenuRandEnregistrer();
				}
				break;

				case 'U':
				{
					MenuEnregistrerClick();
				}
				break;

				case 'Q':
				{
					MenuTerminer();
				}
				break;

				case 'O':
				{
					MenuRetirerDebut();
				}
				break;

				case 'P':
				{
					MenuRetirerFin();
				}
				break;
			}
		}
	}

private:

	void SetState(std::string state)
	{
		system("cls");

		std::cout
			<< "Q pour arrêter le programme" << std::endl
			<< std::endl
			<< "R pour enregister" << std::endl
			<< "T pour enregister avec une variation random" << std::endl
			<< "U pour enregister les clicks seulement" << std::endl
			<< std::endl
			<< "C pour executer lentement" << std::endl
			<< "X pour executer" << std::endl
			<< "Z pour executer rapidement" << std::endl
			<< std::endl
			<< "F pour reinitialiser l'enregistrement" << std::endl
			<< "O pour retirer un temps en secondes au debut de l'enregistrement" << std::endl
			<< "P pour retirer un temps en secondes a la fin de l'enregistrement" << std::endl
			<< std::endl
			<< "-----------------------------------------" << std::endl
			<< "ENREGISTREMENT COURANT" << std::endl
			<< "-----------------------------------------" << std::endl
			<< "Duree : " << std::chrono::duration_cast<std::chrono::milliseconds>(duree).count() << " ms" << std::endl
			<< "Nb pts: " << ptList.size() << std::endl
			<< std::endl
			<< "-----------------------------------------" << std::endl
			<< "ETAT : " << state << std::endl
			<< "-----------------------------------------" << std::endl;
	}

	void MenuClear()
	{
		Clear();
		SetState("Liste videe");
	}

	void MenuExecuterLent()
	{
		SetState("Execution lente");

		for (auto pt : ptList)
		{
			mouse.Reproduce(pt);
			std::this_thread::sleep_for(PRECISIONLENT);
		}

		SetState("Execution terminee");
	}

	void MenuExecuter()
	{
		SetState("Execution");

		for(auto pt : ptList)
		{
			mouse.Reproduce(pt);
			std::this_thread::sleep_for(PRECISION);
		}

		SetState("Execution terminee");
	}

	void MenuExecuterRapide()
	{
		SetState("Execution rapide");

		for (auto pt : ptList)
		{
			mouse.Reproduce(pt);
			std::this_thread::sleep_for(PRECISIONRAPIDE);
		}

		SetState("Execution terminee");
	}

	void MenuEnregistrer()
	{
		SetState("Debut de l'enregistrement");
		auto debut = std::chrono::steady_clock::now();

		while (_kbhit() == 0)
		{
			AddPoint();
			std::this_thread::sleep_for(PRECISION);
		}
		_getch();

		duree = std::chrono::steady_clock::now() - debut;
		SetState("Fin de l'enregistrement");
	}

	void MenuRandEnregistrer()
	{
		SetState("Debut de l'enregistrement random");
		auto debut = std::chrono::steady_clock::now();

		while (_kbhit() == 0)
		{
			AddRandPoint();
			std::this_thread::sleep_for(PRECISION);
		}
		_getch();

		duree = std::chrono::steady_clock::now() - debut;
		SetState("Fin de l'enregistrement random");
	}

	void MenuEnregistrerClick()
	{
		SetState("Debut de l'enregistrement des clicks");
		auto debut = std::chrono::steady_clock::now();

		while (_kbhit() == 0)
		{
			MousePoint pt = mouse.GetMousePosition();
			if (pt.leftClick)
			{
				ptList.push_back(pt);
				std::this_thread::sleep_for(PRECISION);
			}
		}
		_getch();

		duree = std::chrono::steady_clock::now() - debut;
		SetState("Fin de l'enregistrement des clicks");
	}

	void MenuTerminer()
	{
		SetState("Termine");
		continuer = false;
	}

	void MenuRetirerDebut()
	{
		std::cout << "Combien de secondes ?" << std::endl;

		std::string temps;

		std::cin >> temps;

		int secs = std::atoi(temps.c_str());

		if (secs >= 0)
		{
			std::chrono::seconds time{ secs };
			if (time < duree)
			{
				size_t nbPointsAEffacer = (std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() * ptList.size()) / duree.count();
				ptList.erase(ptList.begin(), ptList.begin() + nbPointsAEffacer);
				duree -= time;
			}
		}

		SetState("Retire " + std::to_string(secs) + " secondes au debut");
	}

	void MenuRetirerFin()
	{
		std::cout << "Combien de secondes ?" << std::endl;

		std::string temps;

		std::cin >> temps;

		int secs = std::atoi(temps.c_str());

		if (secs >= 0)
		{
			std::chrono::seconds time{ secs };
			if (time < duree)
			{
				size_t nbPointsAEffacer = (std::chrono::duration_cast<std::chrono::nanoseconds>(time).count() * ptList.size()) / duree.count();
				ptList.erase(ptList.end() - nbPointsAEffacer, ptList.end());
				duree -= time;
			}
		}

		SetState("Retire " + std::to_string(secs) + " secondes a la fin");
	}



	void AddPoint()
	{
		ptList.push_back(mouse.GetMousePosition());
	}

	void AddRandPoint()
	{
		ptList.push_back(mouse.GetRandMousePosition(10));
	}

	void Clear()
	{
		duree = std::chrono::nanoseconds(0);
		ptList.clear();
	}

	int readKey() const
	{
		int c = 0;

		do
		{
			if (_kbhit())
			{
				c = _getch();
			}
		} while (c == 224 || c == 0); // _getch() retourne (0 ou 224), puis la valeur de la touche du clavier. Nous n'avons pas besoin de la premiere information.

		return c;
	}
};


