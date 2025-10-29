#include "_Plugin.h"

#include "SteamAudio.h"
#include "SteamSoundListener.h"
#include "SteamSoundMesh.h"
#include "SteamSoundSource.h"

#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Engine/EngineDefs.h>
#include <Urho3D/Plugins/PluginApplication.h>

using namespace Urho3D;

namespace
{

void RegisterPluginObjects(PluginApplication& plugin)
{
    plugin.RegisterObject<SteamSoundListener>();
    plugin.RegisterObject<SteamSoundMesh>();
    plugin.RegisterObject<SteamSoundSource>();

    Context* context = plugin.GetContext();
    auto steamAudio = context->RegisterSubsystem<SteamAudio>();
    auto engine = context->GetSubsystem<Engine>();
    steamAudio->SetMode(engine->GetParameter(EP_SOUND_MIX_RATE).GetInt(),
        static_cast<SpeakerMode>(engine->GetParameter(EP_SOUND_MODE).GetInt()));
}

void UnregisterPluginObjects(PluginApplication& plugin)
{
    plugin.GetContext()->RemoveSubsystem<SteamAudio>();
}

} // namespace

URHO3D_DEFINE_PLUGIN_MAIN_SIMPLE(RegisterPluginObjects, UnregisterPluginObjects);
