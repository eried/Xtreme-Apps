#pragma once

#include "nfc_magic.h"
#include "nfc_magic_worker.h"

#include "lib/magic/common.h"
#include "lib/magic/types.h"
#include "lib/magic/classic_gen1.h"
#include "lib/magic/gen4.h"

#include <furi.h>
#include <gui/gui.h>
#include <gui/view_dispatcher.h>
#include <gui/scene_manager.h>
#include <notification/notification_messages.h>

#include <gui/modules/submenu.h>
#include <gui/modules/popup.h>
#include <gui/modules/loading.h>
#include <gui/modules/text_input.h>
#include <gui/modules/byte_input.h>
#include <gui/modules/widget.h>

#include <input/input.h>

#include "scenes/nfc_magic_scene.h"

#include <storage/storage.h>
#include <lib/toolbox/path.h>

#include <lib/nfc/nfc_device.h>
#include "nfc_magic_icons.h"

#include <assets_icons.h>

#define NFC_APP_FOLDER ANY_PATH("nfc")

enum NfcMagicCustomEvent {
    // Reserve first 100 events for button types and indexes, starting from 0
    NfcMagicCustomEventReserved = 100,

    NfcMagicCustomEventViewExit,
    NfcMagicCustomEventWorkerExit,
    NfcMagicCustomEventByteInputDone,
    NfcMagicCustomEventTextInputDone,
};

struct NfcMagicDevice {
    MagicType type;
    uint32_t cuid;
    uint8_t uid_len;
    uint32_t password;
};

struct NfcMagic {
    NfcMagicWorker* worker;
    ViewDispatcher* view_dispatcher;
    Gui* gui;
    NotificationApp* notifications;
    SceneManager* scene_manager;
    struct NfcMagicDevice* dev;
    NfcDevice* source_dev;

    uint32_t new_password;

    FuriString* text_box_store;

    // Common Views
    Submenu* submenu;
    Popup* popup;
    Loading* loading;
    TextInput* text_input;
    ByteInput* byte_input;
    Widget* widget;
};

typedef enum {
    NfcMagicViewMenu,
    NfcMagicViewPopup,
    NfcMagicViewLoading,
    NfcMagicViewTextInput,
    NfcMagicViewByteInput,
    NfcMagicViewWidget,
} NfcMagicView;

NfcMagic* nfc_magic_alloc();

void nfc_magic_text_store_set(NfcMagic* nfc_magic, const char* text, ...);

void nfc_magic_text_store_clear(NfcMagic* nfc_magic);

void nfc_magic_blink_start(NfcMagic* nfc_magic);

void nfc_magic_blink_stop(NfcMagic* nfc_magic);

void nfc_magic_show_loading_popup(void* context, bool show);
