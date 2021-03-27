#include "Engine.h"

Engine::Engine()
{
	sAppName = "Fatal Floor";
}

void Engine::retry(int& altitude, int& defAltitude, float& fFrameTime, float& timeSpace, int& nFrame, float& posX, float& posY, int& endloopcount, int& Hearts, float& px, float& py, int& level, int& gState, float& velX)
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

void Engine::nextLvl(int& altitude, int& defAltitude, float& fFrameTime, float& timeSpace, int& nFrame, float& posX, float& posY, int& endloopcount, int& Hearts, float& px, float& py, int& level, int& gState, bool& endfin, bool& Complete, float& velX, float& cloudspeed, float& cloudrate)
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

	cloudspeed += 0.2f;
	cloudrate -= 0.2f;

	Addcloud(rand() % width, height + 35);

	for (int i = 0; i < clouds.size(); i++)
	{
		clouds[i].cY = height + rand() % cloudspr->height + 40;
	}

	gState = Game;
}

void Engine::detectCol(float posX, float posY, int& Hearts, int tOffset, std::vector<Clouds>& clouds)
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

void Engine::Addcloud(float x, float y)
{
	Clouds c;
	c.cX = x;
	c.cY = y;
	clouds.emplace_back(c);
}

void Engine::Movecloud(std::vector<Clouds>& cloud, float& cloudtimer, int altitude, float cloudrate, float cloudspeed)
{
	for (int i = 0; i < cloud.size(); i++)
	{

		if (cloud[i].cY < 0 - (cloudspr->height + 40))
		{
			cloud[i].cX = rand() % width - cloudspr->width / 2;
			cloud[i].cY = height + rand() % cloudspr->height + 40;
			cloud[i].onScreen = false;
			cloud[i].doesDamage = true;
			cloudtimer = 0;

		}
		else
		{
			cloud[i].onScreen = true;
			cloud[i].cY -= cloudspeed;
		}
	}
}

void Engine::Drawcloud(std::vector<Clouds>& cloud, olc::Sprite* cloudspr, olc::Decal* clouds)
{
	for (auto& c : cloud)
	{
		if (c.onScreen)
		{
			if (c.cX > 0 && c.cX <= width + cloudspr->width / 2 && c.cY < height + (cloudspr->height + 40))
			{
				DrawDecal(olc::vf2d(c.cX, c.cY), clouds);
			}
		}

	}
}

void Engine::Addpart(float x, float y)
{
	Particles p;
	p.partX = x;
	p.partY = y;
	p.partCol = olc::Pixel(rand() % 255, rand() % 255, rand() % 255);

	particles.emplace_back(p);
}

void Engine::Movepart(std::vector<Particles>& particles, int height)
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

void Engine::Drawpart(std::vector<Particles>& particles)
{
	for (auto& p : particles)
	{
		Draw(p.partX, p.partY, p.partCol);
	}
}

void Engine::endLoop(float& fFrameTime, float& fElapsedTime, int& nFrame, int nMaxFrames2, olc::Decal& manspr, int& endloopcount)
{
	fFrameTime += fElapsedTime;
	if (fFrameTime >= 1.f)
	{
		fFrameTime -= 1.f;
		nFrame++; nFrame %= nMaxFrames2;
	}

	if (nFrame == 0 && endfin == false)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(0, 37), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 1 && endfin == false)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(48, 37), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 2 && endfin == false)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(96, 37), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 3 && endfin == false)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(144, 37), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 4 && endfin == false)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(192, 37), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
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

void Engine::frameloop(float& fFrameTime, float& fElapsedTime, int& nFrame, int nMaxFrames, olc::Decal& manspr)
{
	fFrameTime += fElapsedTime;
	if (fFrameTime >= 0.040f)
	{
		fFrameTime -= 0.040f;
		nFrame++; nFrame %= nMaxFrames;
	}

	if (nFrame == 0)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(0, 0), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 1)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(48, 0), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 2)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(96, 0), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 3)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(144, 0), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 4)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(96, 0), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 5)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(192, 0), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}
	else if (nFrame == 6)
	{
		DrawPartialDecal(olc::vi2d(posX, posY), &manspr, olc::vf2d(48, 0), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
	}

}

void Engine::moveChar(float& posX, float& posY, float& velX, float Friction, float accelX, float maxSpeed, float fElapsedTime, float& fFrameTime, int& nFrame, int nMaxFrames, olc::Decal& manspr)
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

void Engine::skyChange(int& altitude, float& timeSpace, float fElapsedTime, float& py, float& cloudtimer)
{

	if (altitude > 0)
	{

		//FillScrollableSprite(skyspr, GetDrawTarget(), py, altitude, defAltitude, skyDiv);
		timeSpace += fElapsedTime;
		if (timeSpace >= 0.25f)
		{
			altitude--;
			timeSpace = 0;
			cloudtimer++;
		}

	}
	else
	{
		//FillScrollableSprite(skyspr, GetDrawTarget(), py, altitude, defAltitude, skyDiv);
		if (posY < 550)
		{
			SetPixelMode(olc::Pixel::ALPHA);
			frameloop(fFrameTime, fElapsedTime, nFrame, nMaxFrames, *man);
			SetPixelMode(olc::Pixel::NORMAL);
			posY += 3.0f;
		}
		else
		{
			SetPixelMode(olc::Pixel::ALPHA);
			endLoop(fFrameTime, fElapsedTime, nFrame, nMaxFrames, *man, endloopcount);
			SetPixelMode(olc::Pixel::NORMAL);
		}

	}

}

bool Engine::OnUserCreate()
{
	srand(time(NULL));
	manspr = new olc::Sprite("fally boi.png");
	skyspr = new olc::Sprite("sky.png");
	cloudspr = new olc::Sprite("Cloud.png");

	man = new olc::Decal(manspr);
	cloud = new olc::Decal(cloudspr);

	for (int j = 0; j < 100; j++)
	{
		Addpart(rand() % width - 40, rand() % height);
	}
	Addcloud(rand() % width, height + 35);
	Addcloud(rand() % width, height + 30);



	return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
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
			Clear(olc::BLUE);
			if (Hearts > 0)
			{
				skyChange(altitude, timeSpace, fElapsedTime, py, cloudtimer);
				Drawpart(particles);
				Movepart(particles, height);
				if (altitude > 20 && cloudtimer >= cloudrate)
				{
					SetPixelMode(olc::Pixel::ALPHA);
					Drawcloud(clouds, cloudspr, cloud);
					Movecloud(clouds, cloudtimer, altitude, cloudrate, cloudspeed);
					SetPixelMode(olc::Pixel::NORMAL);
				}
				SetPixelMode(olc::Pixel::ALPHA);
				moveChar(posX, posY, velX, Friction, accelX, maxSpeed, fElapsedTime, fFrameTime, nFrame, nMaxFrames, *man);
				SetPixelMode(olc::Pixel::NORMAL);
				DrawString(80, 30, "Altitude : " + std::to_string(altitude) + "m", olc::WHITE, 2U);
				DrawString(1000, 30, "Hearts : " + std::to_string(Hearts), olc::WHITE, 2U);
				detectCol(posX, posY, Hearts, tOffset, clouds);

				if (endfin)
				{
					SetPixelMode(olc::Pixel::ALPHA);
					DrawPartialDecal(olc::vi2d(posX, posY), man, olc::vf2d(192, 37), olc::vf2d(48, 37), olc::vf2d(2.f, 2.f));
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
							nextLvl(altitude, defAltitude, fFrameTime, timeSpace, nFrame, posX, posY, endloopcount, Hearts, px, py, level, gState, endfin, Complete, velX, cloudspeed, cloudrate);
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

