#define OLC_PGE_APPLICATION
#define OLC_PGEX_TRANSFORMED_VIEW_H
#include "Engine.h"

	//Original by zleapingbear & modified for my usage by Gorbit99
	/*void FillScrollableSprite(olc::Sprite *spr, olc::Sprite *target, int yOffset, int& altitude, int defAltitude, const int skyDiv)
	{
		yOffset = (int)(skyspr->height - height) / (float)defAltitude * (defAltitude - altitude) / skyDiv;
		memcpy(target->GetData(), spr->GetData() + yOffset * target->width * sizeof(uint32_t), target->height * target->width * sizeof(uint32_t));
	}*/

int main()
{
	Engine engine;
	if (engine.Construct(engine.width, engine.height, 1, 1))
	{
		engine.Start();
	}
	return 0;
}

