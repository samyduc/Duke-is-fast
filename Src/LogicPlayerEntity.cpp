///=============================================================================
///
/// \file           LogicPlayerEntity.cpp
///
///
/// \author         Samy Duc, nobunaga.duc@gmail.com
///
/// \brief          Handle internal logic entity
///
///=============================================================================

#include "LogicPlayerEntity.hpp"
#include "IInput.hpp"
#include "IGraphic.hpp"
#include "CKernel.hpp"
#include <boost/lexical_cast.hpp>

// defined in CollisionBox
#define DEG_TO_RAD 0.017453f
#define RAD_TO_DEG 57.2957f
#define PI 3.1415926f
#define LOGIC_S 0.016666f //60 Hz

LogicPlayerEntity::LogicPlayerEntity(int id, std::string type) : LogicEntity(id, type)
{

}

LogicPlayerEntity::~LogicPlayerEntity()
{
}


bool LogicPlayerEntity::update()
{
	if(LogicEntity::update())
	{
		IInput *input = CKernel::input();

		m_move.setX(0.f);
		m_move.setY(0.f);

		if(input->isAction("move_forward"))
		{
			m_move.setY(m_move.Y() - 1*m_descriptor.velocity);
			m_action = "move_forward";
		}
		if(input->isAction("move_backward"))
		{
			m_move.setY(m_move.Y() + 1*m_descriptor.velocity);
			m_action = "move_backward";
		}
		if(input->isAction("move_straff_right"))
		{
			m_move.setX(m_move.X() + 1*m_descriptor.velocity);
			m_action = "move_straff_right";
		}
		if(input->isAction("move_straff_left"))
		{
			m_move.setX(m_move.X() - 1*m_descriptor.velocity);
			m_action = "move_straff_left";
		}
		if(m_move == Point2d<float>(0.f, 0.f))
		{
			m_action = "default";
		}

		Point2d<float> *mouse_position = CKernel::input()->getMousePosition();
		Point2d<float> player_position = CKernel::graphic()->getPosition(m_id);

		Point2d<float> compute_position = *mouse_position - player_position;

		float rotation = LogicEntity::getAngle(compute_position.X(), compute_position.Y());
		if(!(m_move.X() == 0.f && m_move.Y() == 0.f))
		{
			CKernel::graphic()->setMove(m_id, m_move, m_action, rotation*RAD_TO_DEG);
		}
		else if(rotation != 0)
		{
			CKernel::graphic()->setRotation(m_id, rotation*RAD_TO_DEG);
		}
	}


	return true;
}
