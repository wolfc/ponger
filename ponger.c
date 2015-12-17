#include <plugin.h>
#include <version.h>

static PurplePluginInfo info = {
    PURPLE_PLUGIN_MAGIC,
    PURPLE_MAJOR_VERSION,
    PURPLE_MINOR_VERSION,
    PURPLE_PLUGIN_STANDARD,
    NULL,
    0,
    NULL,
    PURPLE_PRIORITY_DEFAULT,

    "ponger",
    "Ponger",
    "0.1",

    "Ponger Plugin",
    "Your automated Ponger answering machine",
    "Carlo de Wolf <carlo@nerdnet.nl>",
    NULL,

    NULL, // load
    NULL, // unload
    NULL, // destroy

    NULL, // ui_info
    NULL, // extra_info
    NULL, // prefs_info
    NULL, // actions
    NULL, // reserved1
    NULL, // reserved2
    NULL, // reserved3
    NULL // reserved4
};

static void init_plugin(PurplePlugin *plugin) {
}

PURPLE_INIT_PLUGIN(ponger, init_plugin, info)
