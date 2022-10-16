#pragma once
#include <scripting/Script.h>

namespace Hachiko
{

	class GameObject;
	class ComponentAudioSource;

	namespace Scripting
	{

		class AudioManager : public Script
		{

			SERIALIZATION_METHODS(false)

		public:
			AudioManager(Hachiko::GameObject* game_object);
			~AudioManager() override = default;

			void OnAwake() override;
			void OnStart() override;
			void OnUpdate() override;

			void RegisterCombat();
			void UnregisterCombat();

			void RegisterGaunlet();
			void UnregisterGaunlet();

			void Restart();
			void SetLevel(unsigned level);

			void PlaySpawnWorm();
		private:
			bool updated = false;
			bool _in_combat = false;
			bool _in_gaunlet = false;
			unsigned _level = 0;
			int _enemies_in_combat = 0;
			ComponentAudioSource* _audio_source = nullptr;

			void StopMusic();
			void SetCombat();
			void SetNavigation();
			const wchar_t* GetPlayMusicEventName(unsigned level);
			const wchar_t* GetStopMusicEventName(unsigned level);
			
		};
	} // namespace Scripting
} // namespace Hachiko


