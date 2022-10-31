
namespace Hachiko::Sounds
{
	// Wwise Events
	// Player
	constexpr const wchar_t* FOOTSTEP = L"Play_Footstep";
	constexpr const wchar_t* MELEE_ATTACK = L"Play_MeleeAttack";
	constexpr const wchar_t* RANGED_ATTACK = L"Play_RangedAttack";
	constexpr const wchar_t* DASH = L"Play_Dash";
	constexpr const wchar_t* LOADING_AMMO = L"Play_LoadingAmmo";
	constexpr const wchar_t* SHOOT_NO_AMMO = L"Play_ShootNoAmmo";
	constexpr const wchar_t* RECEIVE_DAMAGE = L"Play_ReceiveDamage";
	constexpr const wchar_t* PARASITE_PICKUP = L"Play_ParasitePickUp";

	// Enemy
	constexpr const wchar_t* BEETLE_ATTACK = L"Play_BeetleAttack";
	constexpr const wchar_t* BEETLE_DEATH = L"Play_BeetleDeath";
	constexpr const wchar_t* WORM_SPAWN = L"Play_WormSpawn";
	constexpr const wchar_t* WORM_ROAR = L"Play_WormRoar";
	constexpr const wchar_t* WORM_ATTACK = L"Play_WormAttack";
	constexpr const wchar_t* WORM_HIDE = L"Play_WormHide";
	constexpr const wchar_t* WORM_DEATH = L"Play_WormDeath";

	// Gauntlet
	constexpr const wchar_t* GAUNTLET_START = L"Play_WormSpawn";
	constexpr const wchar_t* GAUNTLET_NEXT_ROUND = L"Play_WormRoar";
	constexpr const wchar_t* GAUNTLET_COMPLETE = L"Play_WormDeath";

	// Checkpoint
	constexpr const wchar_t* CHECKPOINT_ACTIVATE = L"Play_Dash";

	// Enviroment
	constexpr const wchar_t* CRYSTAL = L"Play_Crystal";
	constexpr const wchar_t* PLAY_WIND = L"Play_Wind";
	constexpr const wchar_t* STOP_WIND = L"Stop_Wind";
	constexpr const wchar_t* PLAY_PEBBLE = L"Play_Pebble";
	constexpr const wchar_t* STOP_PEBBLE = L"Stop_Pebble";
	constexpr const wchar_t* PLAY_LASER = L"Play_Laser";
	constexpr const wchar_t* PLAY_LASER_HIT = L"Play_Laser_Hit";
	constexpr const wchar_t* PLAY_SPLASH = L"Play_Splash";

	// Background Music
	// TODO: Rename this events in wwise
	constexpr const wchar_t* PLAY_BACKGROUND_MUSIC_LVL1 = L"Play_Navigation";
	constexpr const wchar_t* PLAY_BACKGROUND_MUSIC_LVL2 = L"Play_Navigation";
	constexpr const wchar_t* PLAY_BACKGROUND_MUSIC_BOSS = L"Play_Navigation";
	constexpr const wchar_t* STOP_BACKGROUND_MUSIC_LVL1 = L"Stop_Navigation";
	constexpr const wchar_t* STOP_BACKGROUND_MUSIC_LVL2 = L"Stop_Navigation";
	constexpr const wchar_t* STOP_BACKGROUND_MUSIC_BOSS = L"Stop_Navigation";
	constexpr const wchar_t* PLAY_DEAD_MUSIC = L"Play_GameOver";

	constexpr const wchar_t* PLAY_COMBAT_MUSIC = L"Play_Combat"; // Deprecated
	constexpr const wchar_t* STOP_COMBAT_MUSIC = L"Stop_Combat"; // Deprecated

	//UI
	constexpr const wchar_t* CLICK = L"Play_UIClick";
	constexpr const wchar_t* HOVER = L"Play_UIHover";
	constexpr const wchar_t* INTRO_CINEMATIC = L"Play_IntroCinematic";

	// Wwise RTPC
	// Enemy
	constexpr const wchar_t* ENEMY_AWARE = L"EnemyAware";

	// Wwise Switch
	// Footsteps
	constexpr const wchar_t* SWITCH_GROUP_FOOTSTEPS = L"Footsteps";
	constexpr const wchar_t* SWITCH_STATE_FOOTSTEPS_GRAVEL = L"Gravel";
	constexpr const wchar_t* SWITCH_STATE_FOOTSTEPS_STANDARD = L"Standard";
} // namespace Hachiko::Sounds