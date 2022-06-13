#include "scriptingUtil/gameplaypch.h"
#include "BulletController.h"

#include "Scenes.h"
#include "EnemyController.h"
#include "PlayerController.h"
#include "CrystalExplosion.h"

#include <components/ComponentTransform.h>

#include <modules/ModuleSceneManager.h>

Hachiko::Scripting::BulletController::BulletController(GameObject* game_object)
	: Script(game_object, "BulletController")
	, _collider_radius(2.0f)
{
}

void Hachiko::Scripting::BulletController::OnAwake()
{
}

void Hachiko::Scripting::BulletController::OnStart()
{
	// Spawn bullet (Passing the prefab can be improved)
	UID bullet_uid = 14999767472668584259;
	_bullets = SceneManagement::Instantiate(bullet_uid, game_object->scene_owner->GetRoot(), _max_bullets);

	_bullet_stats.reserve(_bullets.size());

	for (unsigned i = 0; i < _bullets.size(); i++)
	{
		GameObject* bullet = _bullets[i];
		bullet->SetActive(false);
		_bullet_stats[0] = BulletStats();
	}
	//bullet->GetTransform()->SetGlobalPosition(attack_origin_position);
	//bullet->GetComponent<BulletController>()->SetForward(forward);
	//bullet->GetComponent<BulletController>()->SetDamage(_combat_stats->_attack_power);
}

void Hachiko::Scripting::BulletController::OnUpdate()
{
	
	if (!game_object->IsActive())	return;

	for (unsigned i = 0; i < _bullets.size(); i++)
	{
		GameObject* bullet = _bullets[i];
		// Check if its time to destroy
		BulletStats& stats = _bullet_stats[i];
		if (stats.alive&& stats.lifetime <= 0)
		{
			//	Disable
			stats.alive = false;
			stats.lifetime = 0.f;
			bullet->SetActive(false);

			return;
		}
		else
		{
			// Move bullet forward
			ComponentTransform* bullet_transform = bullet->GetTransform();
			bullet_transform->SetGlobalPosition(stats.direction * stats.speed * Time::DeltaTime());
			// Check if it collides with an enemy
			if (CheckCollisions())
			{
				stats.alive = false;
				stats.lifetime = 0.f;
				bullet->SetActive(false);//	Disable
				return;
			}

			stats.lifetime -= Time::DeltaTime();
		}
	}	
}

bool Hachiko::Scripting::BulletController::CheckCollisions()
{
	// Enemy collisions
	GameObject* enemies = game_object->scene_owner->GetRoot()->GetFirstChildWithName("Enemies");
	if (!enemies)	return false;

	std::vector<GameObject*> enemies_children = enemies->children;
	ComponentTransform* transform = game_object->GetTransform();
	math::float4x4 inv_matrix = transform->GetGlobalMatrix().Transposed();

	for (int i = 0; i < enemies_children.size(); ++i)
	{
		if (enemies_children[i]->active && _collider_radius >= transform->GetGlobalPosition().Distance(enemies_children[i]->GetTransform()->GetGlobalPosition()))
		{
			float3 dir = enemies_children[i]->GetTransform()->GetGlobalPosition() - transform->GetGlobalPosition();
			EnemyController* enemy = enemies_children[i]->GetComponent<EnemyController>();
			if (enemy)
			{
				enemy->RegisterHit(_damage, dir);
			}
			return true;
		}
	}

	// Crystal collisions
	GameObject* crystals = game_object->scene_owner->GetRoot()->GetFirstChildWithName("Crystals");
	if (!crystals)	return false;

	std::vector<GameObject*> crystal_children = crystals->children;

	for (int i = 0; i < crystal_children.size(); ++i)
	{
		if (crystal_children[i]->active && _collider_radius >= transform->GetGlobalPosition().Distance(crystal_children[i]->GetTransform()->GetGlobalPosition()))
		{
			crystal_children[i]->GetComponent<CrystalExplosion>()->RegisterHit(_damage);
			return true;
		}
	}

	return false;
}

void Hachiko::Scripting::BulletController::SetDamage(int new_damage)
{
	_damage = new_damage;
}

void Hachiko::Scripting::BulletController::SetForward(float3 new_forward)
{
	_direction = new_forward;
}

void Hachiko::Scripting::BulletController::ShootBullet(ComponentTransform* emiter_transform)
{
	//bullet->GetTransform()->SetGlobalPosition(attack_origin_position);
	//bullet->GetComponent<BulletController>()->SetForward(forward);
	//bullet->GetComponent<BulletController>()->SetDamage(_combat_stats->_attack_power);
	//_emitter_transform

	for (unsigned i = 0; i < _bullets.size(); i++)
	{
		BulletStats& stats = _bullet_stats[i];
		if (!stats.alive)
		{
			continue;
		}
		// Reset stats
		stats = BulletStats();
		GameObject* bullet = _bullets[i];
		stats.alive = true;
		ComponentTransform* bullet_transform = bullet->GetTransform();
		float3 forward = emiter_transform->GetFront().Normalized();
		bullet_transform->SetGlobalPosition(emiter_transform->GetGlobalPosition());
	}
}