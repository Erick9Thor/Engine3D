#include "scriptingUtil/gameplaypch.h"
#include "EnemyBulletController.h"

#include "Scenes.h"
#include "EnemyController.h"
#include "PlayerController.h"
#include "CrystalExplosion.h"

Hachiko::Scripting::EnemyBulletController::EnemyBulletController(Hachiko::GameObject* game_object)
	: Script(game_object, "EnemyBulletController")
	, _move_speed(0.5f)
	, _direction(1.0f, 1.0f, 1.0f)
	, _lifetime(2.0f)
	, _collider_radius(2.0f)
	, _damage(1)
{
}

void Hachiko::Scripting::EnemyBulletController::OnAwake()
{
}

void Hachiko::Scripting::EnemyBulletController::OnUpdate()
{
	if (!game_object->IsActive())	return;

	math::float3 current_position = game_object->GetComponent<ComponentTransform>()->GetGlobalPosition();
	const math::float3 delta_pos = _direction * _move_speed;

	// Check if its time to destroy
	if (_lifetime <= 0)
	{
		//	Disable
		game_object->SetActive(false);
		SceneManagement::Destroy(game_object);
	}
	else
	{
		// Move bullet forward
		current_position += delta_pos;
		game_object->GetComponent<ComponentTransform>()->SetGlobalPosition(current_position);
		// Check if it collides with an enemy
		if (CheckCollisions())
		{
			//	If it hits enemy bullets is destroyed
			SceneManagement::Destroy(game_object);
		}

		_lifetime -= Time::DeltaTime();
	}
}

bool Hachiko::Scripting::EnemyBulletController::CheckCollisions()
{
	ComponentTransform* transform = game_object->GetTransform();

	if (_player->active && _collider_radius >= transform->GetGlobalPosition().Distance(_player->GetTransform()->GetGlobalPosition()))
	{
		float3 dir = _player->GetTransform()->GetGlobalPosition() - transform->GetGlobalPosition();
		_player->GetComponent<PlayerController>()->RegisterHit(_damage, false, dir);
		return true;
	}

	return false;
}

void Hachiko::Scripting::EnemyBulletController::SetTarget(GameObject* player)
{
	_player = player;
}

void Hachiko::Scripting::EnemyBulletController::SetDamage(int new_damage)
{
	_damage = new_damage;
}

void Hachiko::Scripting::EnemyBulletController::SetForward(float3 new_forward)
{
	_direction = new_forward;
}
