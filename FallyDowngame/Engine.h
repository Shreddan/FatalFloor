#pragma once
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
	Engine();
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

	olc::Decal* man;
	olc::Decal* cloud;

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

	float cloudtimer = 0.f;
	float cloudrate = 4.f;
	float cloudspeed = 2.2f;

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

	//functions
	void retry(int& altitude, int& defAltitude, float& fFrameTime, float& timeSpace, int& nFrame, float& posX, float& posY, int& endloopcount, int& Hearts, float& px, float& py, int& level, int& gState, float& velX);
	void nextLvl(int& altitude, int& defAltitude, float& fFrameTime, float& timeSpace, int& nFrame, float& posX, float& posY, int& endloopcount, int& Hearts, float& px, float& py, int& level, int& gState, bool& endfin, bool& Complete, float& velX, float& cloudspeed, float& cloudrate);
	void detectCol(float posX, float posY, int& Hearts, int tOffset, std::vector<Clouds>& clouds);
	void Addcloud(float x, float y);
	void Movecloud(std::vector<Clouds>& cloud, float& cloudtimer, int altitude, float cloudrate, float cloudspeed);
	void Drawcloud(std::vector<Clouds>& cloud, olc::Sprite* cloudspr, olc::Decal* clouds);
	void Addpart(float x, float y);
	void Movepart(std::vector<Particles>& particles, int height);
	void Drawpart(std::vector<Particles>& particles);
	void endLoop(float& fFrameTime, float& fElapsedTime, int& nFrame, int nMaxFrames2, olc::Decal& manspr, int& endloopcount);
	void frameloop(float& fFrameTime, float& fElapsedTime, int& nFrame, int nMaxFrames, olc::Decal& manspr);
	void moveChar(float& posX, float& posY, float& velX, float Friction, float accelX, float maxSpeed, float fElapsedTime, float& fFrameTime, int& nFrame, int nMaxFrames, olc::Decal& manspr);
	void skyChange(int& altitude, float& timeSpace, float fElapsedTime, float& py, float& cloudtimer);

	//PGE Vitals
	bool OnUserCreate();
	bool OnUserUpdate(float fElapsedTime);



};