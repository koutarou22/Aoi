#include "Player.h"
#include <DxLib.h>
#include <assert.h>
#include"Camera.h"
#include"Stone.h"
#include "Bird.h"
#include "Field.h"

namespace
{
	const float MOVE_SPEED = 4.0f;
	const float GROUND = 580.0f;
	const float JUMP_HEIGHT =  64.0f * 4.0f;
	const float GRAVITY = 9.8f / 60.0f;

};
Player::Player(GameObject* parent) : GameObject(sceneTop)
{
	hImage = LoadGraph("Assets/aoi.png");
	assert(hImage > 0);
	transform_.position_.x = 100.0f;
	transform_.position_.y = GROUND;
	onGround = true;
	flameCounter = 0;
	animType = 0;
	animFrame = 0;
	state = 0;
	/*cameraX = 50;*/
}

Player::~Player()
{
	if (hImage > 0)
	{
		DeleteGraph(hImage);
	}
}

void Player::Update()
{
	Field* pField = GetParent()->FindGameObject<Field>();

	if (state == S_Cry)
	{
		flameCounter++;
		if (flameCounter);
	}

	if (CheckHitKey(KEY_INPUT_D))
	{
		transform_.position_.x += MOVE_SPEED;
		if (++flameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 4;//if文を使わない最適解
			flameCounter = 0;
		}
	}
	else if (CheckHitKey(KEY_INPUT_A))
	{
		transform_.position_.x -= MOVE_SPEED;	
		if (++flameCounter >= 8)
		{
			animFrame = (animFrame + 1) % 4;//if文を使わない最適解
			flameCounter = 0;
		}

	}
	else
	{
		animFrame = 0;
		flameCounter = 0;
	}


	if (CheckHitKey(KEY_INPUT_SPACE))
	{
		PictFlame = 80;

		animFrame = (animFrame + 1) % 4;
		if (prevSpaceKey == false)
		{
			if (onGround)
			{
               Jump_P  = -sqrtf(2 * GRAVITY * JUMP_HEIGHT);
			   onGround = false;
			}	
		}
		prevSpaceKey = true;
	}
	else
	{
		prevSpaceKey = false;
	}
	
	

	//-------------------+++加速のプログラムは基礎の基礎+++-------------------

	Jump_P += GRAVITY; //速度 += 加速度
	transform_.position_.y += Jump_P; //座標 += 速度

	if (pField != nullptr)
	{
           int pushR = pField->CollisionDown(transform_.position_.x + 50, transform_.position_.y + 63);
	       int pushL = pField->CollisionDown(transform_.position_.x + 14, transform_.position_.y + 63);
	       int push = max(pushR, pushL);

	    if (push >= 1)
	    {
		   transform_.position_.y -= push;
	   	   Jump_P = 0.0f;
		   onGround = true;

	    }
		else
		{
			onGround = false;
		}
	}
	
	//if (transform_.position_.y >= GROUND)//地面についたら速度を元に戻す、戻さないと貫通する恐れあり
	//{
	//	transform_.position_.y = GROUND;
	//	Jump_P = 0.0f;
	//	onGround = true;
	//}

	//------------------------------------------------------------------------------------------

	if (CheckHitKey(KEY_INPUT_M))
	{
		Stone * st = Instantiate<Stone>(GetParent());
		st->SetPosition(transform_.position_);
	}

	Bird* pBird = GetParent()->FindGameObject<Bird>();
	if (pBird != nullptr)
	{
		if (pBird->CollideCircle(transform_.position_.x + 32.0f, transform_.position_.y + 32.0f, 20.0f))
		{
			transform_.position_.y = 0;
			animType = 4;
			animFrame = 0;
			state = S_Cry;
		}
	}
	//カメラ位置の調整
	Camera* cam = GetParent()->FindGameObject<Camera>();

	int x = (int)transform_.position_.x - cam->GetValue();

	if (x > 400)
	{

		x = 400;
	   cam->SetValue((int)transform_.position_.x - x);

	}
	

}

void Player::Draw()
{
	int x = (int)transform_.position_.x;
	int y = (int)transform_.position_.y;
	Camera* cam = GetParent()->FindGameObject<Camera>();
	if (cam != nullptr)
	{
		x -= cam->GetValue();
	}
	DrawRectGraph(x , y , animFrame*64, animType*64, 64, 64, hImage, TRUE);
}

void Player::Setposition(int x, int y)
{
}
