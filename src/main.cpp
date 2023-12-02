#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/configuration.h>
#include <swiftly/timers.h>

Configuration *config = nullptr;
Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;
Timers *timers = nullptr;

unsigned long long timerid; // credits to blu
int elapsedTime = 10; // credits to blu

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);
    g_playerManager = new PlayerManager();
    server = new Server();
    config = new Configuration();
    timers = new Timers();
}
 
void OnPluginStart()
{
}

void OnBombPlanted(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.plant.message"), config->Fetch<const char*>("c4events.prefix"), player->GetName());
    print("%s planted a bomb.\n", player->GetName()); // credits to blu
    print("UNIX Time: %llu\n", GetTime());
    elapsedTime = 10;
    timerid = timers->RegisterTimer(1000, TimerCallback);  
    print("Timer registered.\n");
    print("UNIX Time: %llu\n", GetTime()); //
}

void OnBombDefused(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, FetchTranslation("c4events.defuse.message"), config->Fetch<const char*>("c4events.prefix"), player->GetName());
}

void Timer() // credits to blu
{
    print("There are %02d players on the server.\n", g_playerManager->GetPlayers());
}

void TimerCallback() { // credits to blu
    g_playerManager->SendMsg(HUD_PRINTTALK, "Remaining time: %d seconds\n", elapsedTime);
    print("Remaining time: %d seconds\n", elapsedTime);
    print("UNIX Time: %llu\n", GetTime());
    elapsedTime--;  // decrement elapsedTime.
    if (elapsedTime == 0) {
        timers->DestroyTimer(timerid);
    }
}

const char *GetPluginName()
{
    return "C4 Events Messages";
}

void OnPluginStop()
{
    timers->UnregisterTimers();
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
    return "https://discord.gg/ESKNDx2CNB";
}