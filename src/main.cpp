#include <swiftly/swiftly.h>
#include <swiftly/server.h>
#include <swiftly/configuration.h>

Configuration *config = nullptr;
Server *server = nullptr;
PlayerManager *g_playerManager = nullptr;

void OnProgramLoad(const char *pluginName, const char *mainFilePath)
{
    Swiftly_Setup(pluginName, mainFilePath);
    g_playerManager = new PlayerManager();
    server = new Server();
    config = new Configuration();
}
 
void OnBombPlanted(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, "%s has planted the bomb!", player->GetName());
}

void OnBombDefused(Player *player, unsigned short site)
{
    g_playerManager->SendMsg(HUD_PRINTTALK, "%s has defused the bomb!", player->GetName());
}

void OnPluginStart()
{
}

void OnPluginStop()
{
}

const char *GetPluginWebsite()
{
    return "";
}

const char *GetPluginAuthor()
{
    return "Moongetsu";
}

const char *GetPluginVersion()
{
    return "1.0.0";
}

const char *GetPluginName()
{
    return "C4 Events Messages";
}