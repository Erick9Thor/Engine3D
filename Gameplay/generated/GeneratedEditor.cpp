#include "scriptingUtil/gameplaypch.h"
#include "AudioManager.h"
#include "BackToMainMenu.h"
#include "BulletController.h"
#include "CrystalExplosion.h"
#include "DynamicCamera.h"
#include "EnemyBulletController.h"
#include "EnemyController.h"
#include "FancyLights.h"
#include "MainMenuManager.h"
#include "PlayerCamera.h"
#include "PlayerController.h"
#include "PlayerSoundManager.h"
#include "RoomTeleporter.h"
#include "Stats.h"


void Hachiko::Scripting::AudioManager::OnEditor()
{
}

void Hachiko::Scripting::BackToMainMenu::OnEditor()
{
	Editor::Show<ComponentButton>("Button Back", "ComponentButton*", _button_back);
}

void Hachiko::Scripting::BulletController::OnEditor()
{
	Editor::Show("Move Speed", _move_speed);
	Editor::Show("Lifetime", _lifetime);
	Editor::Show("Collider Radius", _collider_radius);
}

void Hachiko::Scripting::CrystalExplosion::OnEditor()
{
	Editor::Show("Player", _player);
	Editor::Show("Explosion Crystal", _explosion_crystal);
	Editor::Show("Static Crystal", _static_crystal);
	Editor::Show("Crashing Index", _crashing_index);
	Editor::Show("Detecting Radius", _detecting_radius);
	Editor::Show("Explosion Radius", _explosion_radius);
	Editor::Show("Explosive Crystal", _explosive_crystal);
}

void Hachiko::Scripting::DynamicCamera::OnEditor()
{
	Editor::Show("Start Point", _start_point);
	Editor::Show("End Point", _end_point);
	Editor::Show("Speed", _speed);
	Editor::Show("Lerp Position", _lerp_position);
}

void Hachiko::Scripting::EnemyBulletController::OnEditor()
{
	Editor::Show("Move Speed", _move_speed);
	Editor::Show("Lifetime", _lifetime);
	Editor::Show("Collider Radius", _collider_radius);
}

void Hachiko::Scripting::EnemyController::OnEditor()
{
	Editor::Show("Aggro Range", _aggro_range);
	Editor::Show("Attack Range", _attack_range);
	Editor::Show("Spawn Pos", _spawn_pos);
	Editor::Show("Spawn Is Initial", _spawn_is_initial);
	Editor::Show("Player", _player);
	Editor::Show("Enemy Body", _enemy_body);
	Editor::Show("Parasite", _parasite);
	Editor::Show("Attack Animation Duration", _attack_animation_duration);
	Editor::Show("Attack Animation Timer", _attack_animation_timer);
	Editor::Show("Is Ranged Attack", _is_ranged_attack);
}

void Hachiko::Scripting::FancyLights::OnEditor()
{
	Editor::Show("Rotate On Y", _rotate_on_y);
	Editor::Show("Angle", _angle);
}

void Hachiko::Scripting::MainMenuManager::OnEditor()
{
	Editor::Show("State Changed", _state_changed);
	Editor::Show("Main Background", _main_background);
	Editor::Show("Button Background", _button_background);
	Editor::Show<ComponentButton>("Button Play", "ComponentButton*", _button_play);
	Editor::Show<ComponentButton>("Button Quit", "ComponentButton*", _button_quit);
	Editor::Show<ComponentButton>("Button Settings", "ComponentButton*", _button_settings);
	Editor::Show<ComponentButton>("Button Credits", "ComponentButton*", _button_credits);
	Editor::Show("Settings", _settings);
	Editor::Show("Credits", _credits);
	Editor::Show<ComponentButton>("Button Back", "ComponentButton*", _button_back);
}

void Hachiko::Scripting::PlayerCamera::OnEditor()
{
	Editor::Show("Relative Position To Player", _relative_position_to_player);
	Editor::Show("Player", _player);
	Editor::Show("Follow Delay", _follow_delay);
}

void Hachiko::Scripting::PlayerController::OnEditor()
{
	Editor::Show("Attack Indicator", _attack_indicator);
	Editor::Show("Goal", _goal);
	Editor::Show("Dash Duration", _dash_duration);
	Editor::Show("Dash Distance", _dash_distance);
	Editor::Show("Dash Cooldown", _dash_cooldown);
	Editor::Show("Max Dash Charges", _max_dash_charges);
	Editor::Show("Attack Duration", _attack_duration);
	Editor::Show("Attack Duration Distance", _attack_duration_distance);
	Editor::Show("Rotation Duration", _rotation_duration);
	Editor::Show("Hp Cell 1", _hp_cell_1);
	Editor::Show("Hp Cell 2", _hp_cell_2);
	Editor::Show("Hp Cell 3", _hp_cell_3);
	Editor::Show("Hp Cell 4", _hp_cell_4);
	Editor::Show("Camera", _camera);
	Editor::Show("Ui Damage", _ui_damage);
}

void Hachiko::Scripting::PlayerSoundManager::OnEditor()
{
	Editor::Show<ComponentAudioSource>("Audio Source", "ComponentAudioSource*", _audio_source);
	Editor::Show("Step Frequency", _step_frequency);
	Editor::Show("Melee Frequency", _melee_frequency);
	Editor::Show("Ranged Frequency", _ranged_frequency);
	Editor::Show("Timer", _timer);
}

void Hachiko::Scripting::RoomTeleporter::OnEditor()
{
	Editor::Show("Player", _player);
	Editor::Show("Room Portal", _room_portal);
	Editor::Show("Outdoor Portal", _outdoor_portal);
	Editor::Show("Trigger Distance", _trigger_distance);
	Editor::Show<ComponentImage>("Fade Image", "ComponentImage*", _fade_image);
	Editor::Show("Fade Duration", _fade_duration);
	Editor::Show("Blackout Duration", _blackout_duration);
}

void Hachiko::Scripting::Stats::OnEditor()
{
	Editor::Show("Attack Power", _attack_power);
	Editor::Show("Attack Cd", _attack_cd);
	Editor::Show("Attack Range", _attack_range);
	Editor::Show("Move Speed", _move_speed);
	Editor::Show("Max Hp", _max_hp);
}