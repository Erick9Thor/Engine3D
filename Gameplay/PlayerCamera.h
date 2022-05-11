#pragma once

#include <scripting/Script.h>

namespace Hachiko
{
class GameObject;
namespace Scripting
{
class PlayerController;
class PlayerCamera : public Script
{
	SERIALIZATION_METHODS(false)

public:
	PlayerCamera(GameObject* game_object);
	~PlayerCamera() override = default;

	void OnAwake() override;
	void OnStart() override;
	void OnUpdate() override;

private:
	float2 MoveCameraWithMouse();
	void ScrollWheelZoom(float3* cam_pos);

private:
	SERIALIZE_FIELD(math::float3, _relative_position_to_player);
	SERIALIZE_FIELD(GameObject*, _player);
	SERIALIZE_FIELD(float, _follow_delay);

	math::float3 _look_ahead;
	float _dynamic_delay;
	PlayerController* _player_ctrl;
};
} // namespace Scripting
} // namespace Hachiko