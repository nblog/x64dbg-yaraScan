#include "plugin.h"


#include "x64dbgYaraScan.h"



#include "../third_party/strutil/strutil.h"


enum : uint32_t {
    MENU_ABOUT = 20220414,

    MENU_YARA_MEM_MAP,
};




static bool yarascan(int argc, char** argv)
{
    if (3 > argc) {

        x64dbgYaraScan::infos_msg(fmt::format(

            "\n\n" "YARA rule matching by scanning memory, PE(.rdata)" "\n\n"

            "find within module: " "\n"
            "  yarascan module, ntdll.dll, crypto_signatures.yar" "\n\n"
             
            "find within memory region: " "\n"
            "  yarascan range, 0, crypto_signatures.yar" "\n\n"

            "find within memory length: " "\n"
            "  yarascan memory, 0x401000, 0x1000, crypto_signatures.yar" "\n\n"

        ));

        return true;
    }


    x64dbgYaraScan::cls_yarascan scan;

    if (0 == std::string(argv[1]).compare("memory"))
        scan.begin("memory", { argv[2], argv[3] }, { argv[4] });

    if (0 == std::string(argv[1]).compare("range"))
        scan.begin("range", { argv[2] }, { argv[3] });

    if (0 == std::string(argv[1]).compare("module"))
        scan.begin("module", { argv[2] }, { argv[3] });

    return true;
}



PLUG_EXPORT void CBMENUENTRY(CBTYPE cbType, PLUG_CB_MENUENTRY* info)
{
    switch (info->hEntry)
    {
    case MENU_ABOUT: {
        x64dbgYaraScan::show_msg(fmt::format(
            "{}  v{}\n\n"
            "{:->16}\n{}\n\n",

            PLUGIN_NAME, PLUGIN_VERSION,
            "",
            u8"Yara Rule Scan Tool."
        ));
        break;
    }
    case MENU_YARA_MEM_MAP: {

        bool isOk = x64dbgYaraScan::cls_yarascan().begin(
            "range", 
            { x64dbgYaraScan::ptr_t(Script::Gui::MemMap::SelectionGetStart()) },
            { glob::glob((x64dbgYaraScan::current_dir() / "rules" / "*.yar").string()) }
        );

        x64dbgYaraScan::infos_msg(
            fmt::format("scan completed.")
        );
    } break;
    default:
        break;
    }

}








//Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct)
{

    if (!_plugin_registercommand(pluginHandle, "yarascan", yarascan, true))
        _plugin_logputs("[" PLUGIN_NAME "] Error registering the 'yarascan' command!");



    return true; //Return false to cancel loading the plugin.
}

//Deinitialize your plugin data here.
void pluginStop()
{
}

//Do GUI/Menu related things here.
void pluginSetup()
{
    _plugin_menuaddentry(hMenu, MENU_ABOUT, "&About");
    _plugin_menuaddentry(hMenuMemmap, MENU_YARA_MEM_MAP, "&Scan Select Item");

}
