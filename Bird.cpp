#include "Bird.h"
#include <assert.h>
#include"Camera.h"
Bird::Bird(GameObject* scene)
{
	hImage = LoadGraph("Assets/mob.png");
	assert(hImage > 0);
	transform_.position_.x = 800.0f;
	transform_.position_.y = 500.0f;
}

Bird::~Bird()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Bird::Update()
{
	transform_.position_.x -= 1.0f;
	sinAngle += 3.0f; //
	float sinValue = sinf(sinAngle * DX_PI_F / 180.0);
	transform_.position_.y = 500.0f + sinValue * 50.0f;
}

void Bird::Draw()
{
	

	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam ->GetValue();
	}
	DrawRectGraph(x, y, 0, 0, 64, 64, hImage, TRUE);
}

bool Bird::CollideCircle(float x, float y, float r)
{
	float myCenterX = transform_.position_.x + 32.0f;
	float myCenterY = transform_.position_.y + 32.0f;
	float myR = 24.0f;

	(myCenterX - x)* (myCenterY - y);

	float dx = myCenterX - x;
	float dy = myCenterY - y;
	if (sqrt(dx * dx + dy * dy) < (r + myR) * (r + myR))
		return true;
	return false;
}
