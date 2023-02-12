#include "Box.hpp"
#include "Game/MyMath/MyMath.h"
#include "Game/KeyInput/KeyInput.h"
#include <cmath>

Box::Box(std::shared_ptr<Camera> camera):
	Object(camera),
	kGravity(0.0f, -9.8f),
	mass(10.0f),
	miu(0.4f),
	spd(),
	accel()
{
	pos.Set(Vector2D(50.0f, 50.0f), Vector2D(100.0f, 100.0f));
}

void Box::Update() {
	if (KeyInput::Released(DIK_SPACE)) {
		spd = { 70.0f, 0.0f };
	}

	if (fabs(spd.x) > 0.01f || fabs(spd.y) > 0.01f) {
		float magnitude = miu * (-mass * kGravity.y);

		Vector2D direction;

		if (spd != 0.0f) {
			direction = MyMath::Normalize(spd) * -1.0f;
		}

		Vector2D frictionForce = magnitude * direction;

		accel = frictionForce / mass;

		if (fabs(accel.x) > fabs(spd.x)) {
			accel.x = -spd.x;
		}

		spd += accel * Camera::getDelta();
	}
	else {
		spd = { 0.0f,0.0f };
	}

	pos.worldPos += spd * Camera::getDelta();

	if (pos.worldPos.y < pos.getSize().y / 2.0f) {
		pos.worldPos.y = pos.getSize().y / 2.0f;
	}
}

void Box::Draw() {
	camera->DrawQuad(pos, whiteBox, 0);
}