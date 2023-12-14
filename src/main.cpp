#include <swiftly/swiftly.h>
#include <swiftly/gameevents.h>
#include <swiftly/server.h>
#include <swiftly/configuration.h>
#include <swiftly/timers.h>

Configuration *config = nullptr;
Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Timers *timers = nullptr;

unsigned long long timerid; // credits to blu
int elapsedTime = 10;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);
    g_playerManager = new PlayerManager();
    server = new Server();
    config = new Configuration();
    timers = new Timers();
}

void TimerCallback() { // credits to blu (made some modifications)
    if (elapsedTime == 30) {
        g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.secondschat.message"), elapsedTime);
    }

    if (elapsedTime == 20) {
        g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.secondschat.message"), elapsedTime);
    }

    if (elapsedTime == 10) {
        g_playerManager->SendMsg(HUD_PRINTCENTER, FetchTranslation("c4events.countdown.message"), elapsedTime);
    }

    elapsedTime--;

    if (elapsedTime == 0) {
        timers->DestroyTimer(timerid);
    }
} //

void OnBombPlanted(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.plant.message"), player->GetName());
    elapsedTime = server->cvars->GetConvarInt("mp_c4timer");
    timerid = timers->RegisterTimer(1000, TimerCallback);  
}

void OnBombDefused(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.defuse.message"), player->GetName());
}

void OnPluginStart()
{

}

void OnPluginStop()
{

}

const char *GetPluginName()
{
    return "C4 Events Messages";
}

const char *GetPluginAuthor()
{
    return "Moongetsu, blu";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginWebsite()
{
    return "https://github.com/moongetsu/swiftly_c4events";
}
