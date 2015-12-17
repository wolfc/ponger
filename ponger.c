#include <conversation.h>
#include <plugin.h>
#include <version.h>

#include <string.h>

#define REPLY "Please state the nature of your emergency."

static void received_any_msg(PurpleAccount *account, char *sender, char *message, PurpleConversation *conv, PurpleMessageFlags flags) {
    if (!strstr(message, "ping"))
        return;

    if (purple_conversation_get_type(conv) == PURPLE_CONV_TYPE_CHAT) {
        purple_conv_chat_send(purple_conversation_get_chat_data(conv), REPLY);
    } else {
        purple_conv_im_send(purple_conversation_get_im_data(conv), REPLY);
    }
}

static gboolean plugin_load(PurplePlugin *plugin) {
    void *conv_handle = purple_conversations_get_handle();
    purple_signal_connect(conv_handle, "received-im-msg", plugin, PURPLE_CALLBACK(received_any_msg), NULL);
    purple_signal_connect(conv_handle, "received-chat-msg", plugin, PURPLE_CALLBACK(received_any_msg), NULL);
    return TRUE;
}

static gboolean plugin_unload(PurplePlugin *plugin) {
    void *conv_handle = purple_conversations_get_handle();
    purple_signal_disconnect(conv_handle, "received-im-msg", plugin, PURPLE_CALLBACK(received_any_msg));
    purple_signal_disconnect(conv_handle, "received-chat-msg", plugin, PURPLE_CALLBACK(received_any_msg));
    return TRUE;
}

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

    plugin_load, // load
    plugin_unload, // unload
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
