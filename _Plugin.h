#pragma once

#include <Urho3D/Urho3D.h>

#ifdef URHO3D_STATIC
    #define PLUGIN_CORE_STEAMAUDIO_API
#else
    #if Plugin_Core_SteamAudio_EXPORT
        #define PLUGIN_CORE_STEAMAUDIO_API URHO3D_EXPORT_API
    #else
        #define PLUGIN_CORE_STEAMAUDIO_API URHO3D_IMPORT_API
    #endif
#endif
