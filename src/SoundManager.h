
#include <string>
#include <unordered_map>

#include "soloud.h"
#include "soloud_wav.h"

using namespace std;
using namespace SoLoud;

namespace engine {

	class SoundManager {

	public:
		SoundManager();
		Soloud soloud;
		SoLoud::Wav boom;
		void Startup(void);
		void Shutdown(void);
		void LoadSound(const string& name, const string& path);
		void PlaySound(const string& name);

		unordered_map<string, Wav> soundMap;

	};

}