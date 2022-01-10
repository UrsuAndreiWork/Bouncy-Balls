// Bounce.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <stdlib.h>   
#include <time.h> 
using namespace std;
using namespace sf;
sf::RenderWindow window(sf::VideoMode(900, 700), "SFML works!");

class Scris {
	sf::Text text;
	int pozX, pozY;
	string scris;
public:
	Scris(sf::Font& fontulet, string s, int size, int x, int y, bool cul)
	{
		text.setFont(fontulet);
		scris = s;
		text.setString(scris);
		pozX = x;
		pozY = y;
		text.setCharacterSize(size);
		text.setPosition(x, y);
		if (cul == true)
			text.setFillColor(sf::Color::Green);
	}
	void afisare()
	{
		window.draw(text);
	}
	int getX()
	{
		return pozX;
	}
	int getY()
	{
		return pozY;
	}
	void afisarePozitii()
	{
		cout << "X: " << pozX << endl;
		cout << "Y: " << pozY << endl;
	}
	void setFont(sf::Font& fontulet)
	{
		text.setFont(fontulet);
	}
	void setScris(string s)
	{
		scris = s;
		text.setString(scris);
	}
	void setPozitii(int x, int y)
	{
		pozX = x;
		pozY = y;
	}
	sf::Text getText()
	{
		return text;
	}


};
class Muzica {
	sf::SoundBuffer buffer;
	sf::Sound soundNo;
	sf::Music musicPlay;
public:
	Muzica()
	{
		buffer.loadFromFile("sounds\\no.wav");
		soundNo.setBuffer(buffer);
		musicPlay.openFromFile("sounds\\muzica joc.wav");
	}

	sf::Sound getNoSound()
	{

		return soundNo;
	}
	void playSoundNo()
	{
		soundNo.play();
	}
	void playMusicGame()
	{
		musicPlay.play();
	}
	void stopMusic()
	{
		musicPlay.stop();
	}

};
//*Scris textScore(font,"Coins:",24,770,15,false);
class Background
{
	sf::Texture tex;
	sf::Sprite spr;

public:
	Background()
	{
		tex.loadFromFile("images/error.jpg");
	}
	void loadTexture(string texPath)
	{
		tex.loadFromFile(texPath);
		spr.setTexture(tex);
	}
	void setTextureNr(int nr)
	{
		if (nr == 0)
		{
			tex.loadFromFile("images/img1.jpg");
			spr.setTexture(tex);
		}
	}
	sf::Sprite getTexture()
	{
		return spr;
	}
};
class Minge
{
protected:
	sf::Texture tex;
	sf::Sprite spr;
	int xMinge = 0;
	int yMinge = 0;
	float acceleratie = 1;
	float bounce = 0;
	bool flight = 0;
	float copACC = 0;
	bool stop;
	float ricoseu = 0;
	bool directie = false;
public:
	
	Minge()
	{
		tex.loadFromFile("images/mingeSPR.png");
		spr.setTexture(tex);
		spr.setPosition(xMinge, yMinge);
		spr.setScale(0.05, 0.05);
	}
	sf::Sprite getSprite()
	{
		return spr;
	}
	float getAcceleratie()
	{
		return acceleratie;
	}
	void setAcceleratie(float acc)
	{
		acceleratie =  acc;
	}
	float getBounce()
	{
		return bounce;
	}
	void addBounce()
	{
		bounce = bounce + 0.2;
	}
	int getX()
	{
		return xMinge;
	}
	int getY()
	{
		return yMinge;
	}
	void setX(int x1)
	{
		xMinge = x1;
		spr.setPosition(xMinge, yMinge);
	}
	void setY(int y1)
	{
		yMinge = y1;
		spr.setPosition(xMinge, yMinge);
	}
	void setCoord(int x1, int y1)
	{
		xMinge = x1;
		yMinge = y1;
		spr.setPosition(xMinge, yMinge);
	}
	void resetGravitatie()
	{
		acceleratie = 1;
		bounce = 0;
		flight = 0;
		copACC = 0;
		ricoseu = 0;
		stop = false;
	}
	void Gravitatie()
	{
		
	
		if (stop == false)
			//* scade mingea pana ajunge jos (inaltimea + inaltimea mingii)
			if (yMinge < 700 - 1290 * 0.05 - acceleratie + 1 && flight == false)
			{
				yMinge = yMinge + acceleratie;
				acceleratie = acceleratie + 0.4;
				spr.setPosition(xMinge, yMinge);
			}
		//* urca mingea pana acceleratia devine 0
			else if (flight == true) {
				if (acceleratie > 1)
				{
					yMinge = yMinge - acceleratie;
					acceleratie = acceleratie - (0.5 + bounce);
					spr.setPosition(xMinge, yMinge);
				}
				else {
					flight = false;
				}
			}
		//*mereu cand atinge pamantul,creste bounce si o ia in sus
			else {
				acceleratie = acceleratie - 0.1;
				bounce = bounce + 0.2;
				if (ricoseu > 0)
				{
					ricoseu = ricoseu - 0.5;
					ricoseu = ricoseu - (0.2 + bounce);
				}
				//*cout <<"bounce:" << bounce << endl;
				//*cout <<"acceleratie:" << acceleratie << " " << copACC << " " << round(acceleratie * 1000) / 1000 << endl;
				flight = true;


				if (round(acceleratie * 1000) / 1000 < 1)
				{
					stop = true;
					flight = false;
					acceleratie = 1;
					bounce = 0;

				}
				//* se opreste cand acceleratie e constanta
				if (round(acceleratie * 1000) / 1000 == round(copACC * 1000) / 1000)
				{
					stop = true;
					flight = false;
					acceleratie = 1;
					bounce = 0;
				}

				copACC = acceleratie;

			}
		if (stop == true && ricoseu > 0)
		{
			ricoseu = ricoseu - 0.07;
		}
		else if (stop == true) { ricoseu = 0; }

	}
	void setFligt(bool fl)
	{
		flight = fl;
	}
	void setRicoseu(float ric)
	{
		ricoseu = ric;
	}
	float getRicoseu()
	{
		return ricoseu;
	}
	bool getStateDirectie()
	{
		return directie;
	}
	void setStateDirectie(bool dir)
	{
		directie = dir;
	}

};

class Trambulina : public Minge
{

	sf::Texture tex;
	sf::Sprite spr;
	int xTrambulina = 0;
	int yTrambulina = 0;

public:
	Trambulina()
	{ 
		tex.loadFromFile("images/TrampSPR.png");
		spr.setTexture(tex);
		spr.setPosition(xTrambulina, yTrambulina);
		
	}
	sf::Sprite getSprite()
	{
		return spr;
	}
	int getX()
	{
		return xTrambulina;
	}
	int getY()
	{
		return yTrambulina;
	}
	void setX(int x1)
	{
		xTrambulina = x1;
		spr.setPosition(xTrambulina, yTrambulina);
	}
	void setY(int y1)
	{
		yTrambulina = y1;
		spr.setPosition(xTrambulina, yTrambulina);
	}
	void setCoord(int x1, int y1)
	{
		xTrambulina = x1;
		yTrambulina = y1;
		spr.setPosition(xTrambulina, yTrambulina);
	}


};

Trambulina trambulina;
Background bgr;
Minge minge;
vector<Minge> mingi;
int main()
{
	int var=0;
	Minge mingeJ;
	mingeJ.setX(100);
	int i, j;
	srand(time(NULL)); int NRandom;
	mingi.push_back(minge);
	mingi.push_back(mingeJ);
	bgr.setTextureNr(0);
	window.setFramerateLimit(60);
	Event event;
    // run the program as long as the window is open
    while (window.isOpen())
    {   
		sf::Vector2i position = sf::Mouse::getPosition(window);
		window.draw(bgr.getTexture());
		window.draw(trambulina.getSprite());
		//*pune conditia pentru toate mingile

		//*creez mingi
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right) == true)
		{
			NRandom = rand() % 150 + 1;
			mingi.push_back(minge);
			mingi[mingi.size()-1].setX(position.x + NRandom);
			mingi[mingi.size()-1].setY(position.y - NRandom);
		}

	
		for (i = 0; i < mingi.size(); i++)
		{
			
			if ((position.x >= mingi[i].getX()) && (position.x <= mingi[i].getX() + round(1290 * 0.05)) && (position.y >= mingi[i].getY()) && (position.y <= mingi[i].getY() + round(1290 * 0.05)) && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true))
			{

				mingi[i].setY(position.y - 30);
				mingi[i].setX(position.x - 30);
				//*cout << "pozitie X:" << position.x << " position Y:" << position.y << endl;
				//*cout << "minge X:" << minge.getX() << " minge Y:" << minge.getY() << endl;

				mingi[i].resetGravitatie();
			}
			else
			{
				mingi[i].Gravitatie();
			}
		}
		int k = 0;

		//* nu merge
		for (i = 0; i < mingi.size(); i++)
		{
			for (j = 0; j < mingi.size(); j++)
			{
				if (i != j)
				{
					//* sa nu fie unite
					if ((mingi[i].getX() == mingi[j].getX()) && mingi[i].getY()==mingi[j].getY() && mingi[i].getAcceleratie()==mingi[j].getAcceleratie() && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false))
					{
						mingi[i].setX( mingi[i].getX() + round(1290 * 0.05)+ NRandom%10);
						
					}



					if ( (  abs(mingi[i].getX() - mingi[j].getX()) <round(1290 * 0.05) ) ==true)
					{
						
						if ( (abs(mingi[i].getY() - mingi[j].getY()) < round(1290 * 0.05)) == true )

						{
                                //*aici isi schimba directia la contact cu alta minge
							
							if (mingi[i].getAcceleratie() >= mingi[j].getAcceleratie())
							{
								mingi[i].setFligt(true);
								if ((mingi[i].getX() - mingi[j].getX())>=0)
								{   
									mingi[i].setRicoseu((mingi[i].getAcceleratie()-mingi[j].getAcceleratie())/2+0.1);
									mingi[i].setStateDirectie(false);
									mingi[j].setRicoseu(mingi[j].getAcceleratie() + mingi[i].getAcceleratie()/2+0.1);
									mingi[j].setStateDirectie(true);
	
								}
								else {
									
									mingi[i].setRicoseu((mingi[i].getAcceleratie() - mingi[j].getAcceleratie())/2+0.1);
									mingi[i].setStateDirectie(true);
									mingi[j].setRicoseu(mingi[j].getAcceleratie() + mingi[i].getAcceleratie()/2+0.1);
									mingi[j].setStateDirectie(false);
								}

								
							}
						}
					}
				}
			}
		}
		//* sa scada la bounce
		for (i = 0; i < mingi.size(); i++)
		{
			if (mingi[i].getRicoseu()>0)
			{
				if (mingi[i].getStateDirectie() == false)
				{
					mingi[i].setX(mingi[i].getX() + mingi[i].getRicoseu());
				}
				else { mingi[i].setX(mingi[i].getX() - mingi[i].getRicoseu()); }

			}

              window.draw(mingi[i].getSprite());
		}
		if ((position.x >= trambulina.getX()) && (position.x <= trambulina.getX() + 181) && (position.y >= trambulina.getY()) && (position.y <= trambulina.getY() + 80) && (sf::Mouse::isButtonPressed(sf::Mouse::Left) == true))
		{
			trambulina.setY(position.y - 40);
			trambulina.setX(position.x - 90);
		}


			window.display();
			window.clear();
		


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }



    }

    return 0;
}

