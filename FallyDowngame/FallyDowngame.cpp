#define OLC_PGE_APPLICATION
#include "includes.h"

struct Particles
{
	float partX = 0;
	float partY = 0;
	olc::Pixel partCol;

};

struct Clouds
{
	float cX = 0;
	float cY = 0;
	bool doesDamage = true;
	bool onScreen = false;
};

class Engine : public olc::PixelGameEngine
{
public:
	Engine()
	{
		sAppName = "Fatal Floor";
	}

	enum state
	{
		MainMenu,
		Game,
		Pause
	};

	int gState = MainMenu;


	olc::Sprite* manspr;
	olc::Sprite* skyspr;
	olc::Sprite* cloudspr;

	std::vector<Clouds> clouds;
	std::vector<Particles> particles;

	const int width = 1200;
	const int height = width * 9 / 16;
	const int nMaxFrames = 6;
	const int nMaxFrames2 = 4;
	const int skyDiv = 4;

	float px = 0;
	float py = 0;

	bool endfin = false;

	int cloudtimer;

	int defAltitude = 200;
	int altitude = defAltitude;

	float fFrameTime = 0;
	float timeSpace = 0;
	int nFrame = 0;
	
	float posX = 480;
	float posY = 60;

	float velX = 0;

	int endloopcount = 0;

	int Hearts = 3;

	int level = 1;


	const float accelX = 1.f;
	const float Friction = 0.5f;
	const float maxSpeed = 3.f;

	const int tOffset = 20;



	bool Complete = false;

	
	void retry(int& altitude, int& defAltitude, float& fFrameTime, float& timeSpace, int& nFrame, float& posX, float& posY, int& endloopcount, int& Hearts, float& px, float& py, int& level, int& gState, float& velX)
	{
		altitude = defAltitude;
		fFrameTime = 0;
		timeSpace = 0;
		nFrame = 0;
		posX = 480;
		posY = 60;

		endloopcount = 0;

		Hearts = 3;

		px = 0;
		py = 0;

		posX = 480;
		posY = 60;

		velX = 0.f;

		for (int i = 0; i < clouds.size(); i++)
		{
			clouds[i].cY = height + rand() % cloudspr->height + 40;
		}


		gState = Game;
	}

	void nextLvl(int& altitude, int& defAltitude, float& fFrameTime, float& timeSpace, int& nFrame, float& posX, float& posY, int& endloopcount, int& Hearts, float& px, float& py, int& level, int& gState, bool& endfin, bool& Complete, float& velX)
	{
		Complete = false;
		endfin = false;
		defAltitude += 100;
		altitude = defAltitude;

		fFrameTime = 0;
		timeSpace = 0;
		nFrame = 0;
		posX = 480;
		posY = 60;

		endloopcount = 0;

		Hearts = 3;

		px = 0;
		py = 0;

		posX = 480;
		posY = 60;

		velX = 0.f;

		level++;

		
		Addcloud(rand() % width, height + 35);

		for (int i = 0; i < clouds.size(); i++)
		{
			clouds[i].cY = height + rand() % cloudspr->height + 40;
		}

		gState = Game;
	}

	//Collision detection
	void detectCol(float posX, float posY, int& Hearts, int tOffset, std::vector<Clouds>& clouds)
	{
		for (int i = 0; i < clouds.size(); i++)
		{
			if (altitude > 20)
			{
				if (clouds[i].doesDamage == true)
				{
					if (posX < clouds[i].cX + (cloudspr->width - tOffset) && posX + (manspr->width / 5) > clouds[i].cX && posY < clouds[i].cY + (cloudspr->height - tOffset) && posY + (manspr->height / 2) > clouds[i].cY)
					{
						//std::cout << "Collision Detected!" << std::endl;
						clouds[i].doesDamage = false;
						Hearts--;
						//std::cout << clouds[i].doesDamage << std::endl;
					}
				}
			}
			
		}
	}

	//Cloud Functions
	void Addcloud(float x, float y)
	{
		Clouds c;
		c.cX = x;
		c.cY = y;
		clouds.emplace_back(c);
	}
	void Movecloud(std::vector<Clouds>& cloud, int& cloudtimer, int altitude)
	{
		for (int i = 0; i < cloud.size(); i++)
		{
			if (cloud[i].cY < 0 - (cloudspr->height + 40))
			{
				cloud[i].cX = rand() % width - cloudspr->width / 2;
				cloud[i].cY = height + rand()% cloudspr->height + 40;
				cloud[i].onScreen = false;
				cloud[i].doesDamage = true;
				
			}
			else
			{
				cloud[i].onScreen = true;
				cloud[i].cY -= 3.f;
			}


		}
	}
	void Drawcloud(std::vector<Clouds>& cloud, olc::Sprite* cloudspr)
	{
		for (auto& c : cloud)
		{
			if (c.onScreen)
			{
				if (c.cX > 0 && c.cX <= width + cloudspr->width / 2 && c.cY < height + (cloudspr->height + 40))
				{
					DrawSprite(c.cX, c.cY, cloudspr);
				}
			}
			
		}
	}


	//Particle Functions
	void Addpart(float x, float y)
	{
		Particles p;
		p.partX = x;
		p.partY = y;
		p.partCol = olc::Pixel(rand() % 255, rand() % 255, rand() % 255);
		
		particles.emplace_back(p);
	}
	void Movepart(std::vector<Particles>& particles, int height)
	{
		for (int i = 0; i < particles.size(); i++)
		{
			if (particles[i].partY < 0)
			{
				particles[i].partY = rand() % height;
				particles[i].partX = rand() % width - 60;
			}
			else
			{
				particles[i].partY -= 2.f;
			}
		
			
		}
	}
	void Drawpart(std::vector<Particles>& particles)
	{
		for (auto& p : particles)
		{
			Draw(p.partX, p.partY, p.partCol);
		}
	}


	//Original by zleapingbear & modified for my usage by Gorbit99
	void FillScrollableSprite(olc::Sprite *spr, olc::Sprite *target, int yOffset, int& altitude, int defAltitude, const int skyDiv)
	{
		yOffset = (int)(skyspr->height - height) / (float)defAltitude * (defAltitude - altitude) / skyDiv;
		memcpy(target->GetData(), spr->GetData() + yOffset * target->width * sizeof(uint32_t), target->height * target->width * sizeof(uint32_t));
	}


	//Frame loops
	void endLoop(float& fFrameTime, float& fElapsedTime, int& nFrame, int nMaxFrames2, olc::Sprite& manspr, int& endloopcount)
	{
		fFrameTime += fElapsedTime;
		if (fFrameTime >= 1.f)
		{
			fFrameTime -= 1.f;
			nFrame++; nFrame %= nMaxFrames2;
		}

		if (nFrame == 0 && endfin == false)
		{
			DrawPartialSprite(posX, posY, &manspr, 0, 37, 48, 37, 2U);
		}
		else if (nFrame == 1 && endfin == false)
		{
			DrawPartialSprite(posX, posY, &manspr, 48, 37, 48, 37, 2U);
		}
		else if (nFrame == 2 && endfin == false)
		{
			DrawPartialSprite(posX, posY, &manspr, 96, 37, 48, 37, 2U);
		}
		else if (nFrame == 3 && endfin == false)
		{
			DrawPartialSprite(posX, posY, &manspr, 144, 37, 48, 37, 2U);
		}
		else if (nFrame == 4 && endfin == false)
		{
			DrawPartialSprite(posX, posY, &manspr, 192, 37, 48, 37, 2U);
			if (endloopcount == 1)
			{
				endfin = true;
			}
			else
			{
				endloopcount++;
			}
			
		}
	}
	void frameloop(float& fFrameTime, float& fElapsedTime, int& nFrame, int nMaxFrames, olc::Sprite& manspr) 
	{
		fFrameTime += fElapsedTime;
		if (fFrameTime >= 0.040f)
		{
			fFrameTime -= 0.040f;
			nFrame++; nFrame %= nMaxFrames;
		}

		if (nFrame == 0)
		{
			DrawPartialSprite(posX, posY, &manspr, 0, 0, 48, 37, 2U);
		}
		else if (nFrame == 1)
		{
			DrawPartialSprite(posX, posY, &manspr, 48, 0, 48, 37, 2U);
		}
		else if (nFrame == 2)
		{
			DrawPartialSprite(posX, posY, &manspr, 96, 0, 48, 37, 2U);
		}
		else if (nFrame == 3)
		{
			DrawPartialSprite(posX, posY, &manspr, 144, 0, 48, 37, 2U);
		}
		else if (nFrame == 4)
		{
			DrawPartialSprite(posX, posY, &manspr, 96, 0, 48, 37, 2U);
		}
		else if (nFrame == 5)
		{
			DrawPartialSprite(posX, posY, &manspr, 192, 0, 48, 37, 2U);
		}
		else if (nFrame == 6)
		{
			DrawPartialSprite(posX, posY, &manspr, 48, 0, 48, 37, 2U);
		}
		
	}

	//Character Input
	void moveChar(float& posX, float& posY, float& velX, float Friction,  float accelX, float maxSpeed, float fElapsedTime, float& fFrameTime, int& nFrame, int nMaxFrames, olc::Sprite& manspr)
	{
		if (altitude > 0)
		{
			if (GetKey(olc::RIGHT).bPressed && posX <= width)
			{
				velX += accelX + 0.1f;
			}
			else if (GetKey(olc::LEFT).bPressed && posX > -2)
			{
				velX -= accelX + 0.1f;
			}
			else
			{
				if (velX > maxSpeed)
				{
					velX = maxSpeed;
				}
				else if (velX < 0 - maxSpeed)
				{
					velX = 0 - maxSpeed;
				}

				if (velX < 0)
				{
					velX + (Friction * 2);
				}
				if (velX > 0)
				{
					velX - (Friction * 2);
				}

				
			}
			

			if (posX > width - 64)
			{
				posX = width - 64;
				velX = 0.f;
			}
			else if (posX < 0)
			{
				posX = 0;
				velX = 0.f;
			}
			frameloop(fFrameTime, fElapsedTime, nFrame, nMaxFrames, manspr);
			posX += velX;
		}
		
		
		
	}

	//Sky Stuff
	void skyChange(int& altitude, float& timeSpace, float fElapsedTime, float& py)
	{
		
		if (altitude > 0)
		{
			
			FillScrollableSprite(skyspr, GetDrawTarget(), py, altitude, defAltitude, skyDiv);
			timeSpace += fElapsedTime;
			if (timeSpace >= 0.25f)
			{
				altitude--;
				timeSpace = 0;
			}
			
		}
		else
		{
			FillScrollableSprite(skyspr, GetDrawTarget(), py, altitude, defAltitude, skyDiv);
			if (posY < 550)
			{
				SetPixelMode(olc::Pixel::ALPHA);
				frameloop(fFrameTime, fElapsedTime, nFrame, nMaxFrames, *manspr);
				SetPixelMode(olc::Pixel::NORMAL);
				posY += 3.0f;
			}
			else
			{
				SetPixelMode(olc::Pixel::ALPHA);
				endLoop(fFrameTime, fElapsedTime, nFrame, nMaxFrames, *manspr, endloopcount);
				SetPixelMode(olc::Pixel::NORMAL);
			}
			
		}
		
	}

	
	

	bool OnUserCreate()
	{
		srand(time(NULL));
		manspr = new olc::Sprite("fally boi.png");
		skyspr = new olc::Sprite("sky.png");
		cloudspr = new olc::Sprite("Cloud.png");

		for (int j = 0; j < 100; j++)
		{
			Addpart(rand() % width - 40, rand() % height);
		}
		Addcloud(rand() % width, height + 35);
		Addcloud(rand() % width, height + 30);

		
		
		return true;
	}
	bool OnUserUpdate(float fElapsedTime)
	{

		switch (gState)
		{
			case MainMenu:
			{
				Clear(olc::BLUE);
				DrawString(380, 50, "Fatal Floor", olc::WHITE, 5U);
				//Start Button
				

				if (GetMouseX() > 485 && GetMouseX() < 685 && GetMouseY() > 280 && GetMouseY() < 340 && gState != Game)
				{
					FillRect(483, 278, 205, 65, olc::VERY_DARK_GREY);
					if (GetMouse(0).bPressed)
					{
						gState = Game;
					}
					
				}
				FillRect(485, 280, 200, 60, olc::GREY);
				DrawString(520, 300, "Start", olc::WHITE, 3U);


				break;
			}
			case Game:
			{
				if (Hearts > 0)
				{
					skyChange(altitude, timeSpace, fElapsedTime, py);
					Drawpart(particles);
					Movepart(particles, height);
					if (altitude > 20)
					{
						SetPixelMode(olc::Pixel::ALPHA);
						Drawcloud(clouds, cloudspr);
						Movecloud(clouds, cloudtimer, altitude);
						SetPixelMode(olc::Pixel::NORMAL);
					}
					SetPixelMode(olc::Pixel::ALPHA);
					moveChar(posX, posY, velX, Friction, accelX, maxSpeed, fElapsedTime, fFrameTime, nFrame, nMaxFrames, *manspr);
					SetPixelMode(olc::Pixel::NORMAL);
					DrawString(80, 30, "Altitude : " + std::to_string(altitude) + "m", olc::WHITE, 2U);
					DrawString(1000, 30, "Hearts : " + std::to_string(Hearts), olc::WHITE, 2U);
					detectCol(posX, posY, Hearts, tOffset, clouds);

					if (endfin)
					{
						SetPixelMode(olc::Pixel::ALPHA);
						DrawPartialSprite(posX, posY, manspr, 192, 37, 48, 37, 2U);
						SetPixelMode(olc::Pixel::NORMAL);
						Complete = true;
					}

					if (Complete)
					{
						DrawString(300, 240, "LEVEL COMPLETE!", olc::DARK_GREEN, 6U);
						FillRect(500, 340, 120, 50, olc::GREEN);
						DrawString(520, 360, "Next", olc::WHITE, 2U);

						if (GetMouseX() > 480 && GetMouseX() < 600 && GetMouseY() > 350 && GetMouseY() < 400)
						{
							if (GetMouse(0).bPressed)
							{
								nextLvl(altitude, defAltitude, fFrameTime, timeSpace, nFrame, posX, posY, endloopcount, Hearts, px, py, level, gState, endfin, Complete, velX);
							}

						}
					}

				}
				else
				{
					Clear(olc::BLACK);
					DrawString(390, 250, "GAME OVER", olc::RED, 6U);
					FillRect(510, 350, 120, 50, olc::GREEN);
					DrawString(530, 370, "Retry?", olc::WHITE, 2U);
					if (GetMouseX() > 480 && GetMouseX() < 600 && GetMouseY() > 350 && GetMouseY() < 400)
					{
						if (GetMouse(0).bPressed)
						{
							retry(altitude, defAltitude, fFrameTime, timeSpace, nFrame, posX, posY, endloopcount, Hearts, px, py, level, gState, velX);
						}
					}
				}

				break;

			}
			
			
				
		}
		
		

		return true;
	}

};

int main()
{
	Engine engine;
	if (engine.Construct(engine.width, engine.height, 1, 1))
	{
		engine.Start();
	}
	return 0;

}

