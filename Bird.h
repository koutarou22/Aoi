#pragma once
#include "Engine/GameObject.h"

/// <summary>
/// íπÅiìGÅj
/// </summary>
class Bird : public GameObject
{
public:
	Bird(GameObject* scene);
	~Bird();
	void Update() override;
	void Draw() override;

	 bool CollideCircle(float x, float y, float r);
private:
	float sinAngle;
	int hImage;
};
