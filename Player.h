#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// �v���C���[�L����
/// </summary>
class Player : public GameObject
{
public:
	Player(GameObject* scene);
	~Player();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	GameObject* sceneTop;
	bool prevSpaceKey;
	bool onGround;
	float Jump_P = 0.0f;

	int animType;//��
	int animFrame;//��
	int PictFlame;
	int flameCounter;


	enum State
	{
		S_WaIk = 0,
		S_Cry,
	};
	State state;

	void SetPosition(int x, int y);
};