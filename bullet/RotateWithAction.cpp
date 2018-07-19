#include "RotateWithAction.h"

RotateWithAction::RotateWithAction(void)
{
	
}

RotateWithAction::~RotateWithAction(void)
{
}

RotateWithAction * RotateWithAction::create(double duration)
{
	auto act = new RotateWithAction();
	act->initWithDuration(duration);
	return act;
}

void RotateWithAction::update(float t)
{
	Vec2 firstToward = Vec2(1, 0);
	auto aa = getOriginalTarget();
	lastPosition = thisPosition;
	thisPosition = aa->getPosition();

	Vec2 direction = thisPosition - lastPosition;

	if (direction.x == 0 && direction.y == 0) {
		return;
	}
	//a*b/|a*b|
	auto a = direction;
	auto b = firstToward;
	double cos_theta = (a.x*b.x + a.y*b.y) / (sqrt(a.x*a.x + a.y*a.y)* sqrt(b.x*b.x + b.y*b.y));
	double theta = acos(cos_theta);
	double p;
	if (direction.y > firstToward.y) {
		p = -theta * 180 / 3.14;
	}
	else {
		p = theta * 180 / 3.14;
	}
	aa->setRotation(p);
}

void RotateWithAction::startWithTarget(Node * target)
{
	CCActionInterval::startWithTarget(target);
	lastPosition = target->getPosition();
	thisPosition = lastPosition;
}









