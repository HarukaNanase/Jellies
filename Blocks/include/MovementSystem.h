#pragma once
#include "System.h"
/*!
 * \class MovementSystem
 *
 * \brief The system responsible for LERP of objects between two positions over time.
 *
 */
class MovementSystem : public System
{

private:
public:
	virtual void Initialize() override;
	virtual void Update(float _deltaTime) override;
	virtual void Destroy() override;

};

