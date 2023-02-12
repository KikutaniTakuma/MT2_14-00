#pragma once

#include "Game/Object/Object.h"

class Box : public Object {
public:
	Box() = delete;
	Box(std::shared_ptr<Camera> camera);

private:
	float mass;
	float miu;

	Vector2D spd;
	Vector2D accel;

	const Vector2D kGravity;

public:
	void Update() override;
	void Draw() override;
	inline void Reset() override {}
};