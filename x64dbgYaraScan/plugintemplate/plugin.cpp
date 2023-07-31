#include "plugin.h"


#include "x64dbgYaraScan.h"



enum : uint32_t {
    MENU_ABOUT = 20230403,

    MENU_YARA_DIALOG,
};


PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{

    switch (info->hEntry)
    {
    case MENU_ABOUT: {
        auto about = String::Format(
            "{0}  {1}\n\n{2}",
            PLUGIN_NAME, "v0.2.1",
            u8"Yara Rule Scan Tool.");

        x64dbgYaraScan::rtcmsgbox(about);
        break;
    }
    case MENU_YARA_DIALOG: {
        if (!DbgIsDebugging()) {
            x64dbgYaraScan::rtcmsgbox("Please start a debug session first.");
            break;
        }

        x64dbgYaraScan::YaraDialog::ShowAsyn();
		break;
	}
    default:
        break;
    }

}



//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{
    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
    auto icon = x64dbgYaraScan::icon();
    ICONDATA icondata{ icon.data(), icon.size() };
    _plugin_menuseticon(hMenu, &icondata);

    _plugin_menuaddentry(hMenu, MENU_ABOUT, "&About");
    _plugin_menuaddentry(hMenu, MENU_YARA_DIALOG, "&Yara Scan");
}
