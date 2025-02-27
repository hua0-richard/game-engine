#include <raylib.h>
#include <string_view>
#include <vector>


class SoundManager{
    public:

    SoundManager();
    ~SoundManager();

    void PlaySound();
    void SetVolume();
    void StopSound();

    private:
    std::vector<Sound> soundEffects;
};