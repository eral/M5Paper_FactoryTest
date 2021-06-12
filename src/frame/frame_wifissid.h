#ifndef _FRAME_WIFISSID_H_
#define _FRAME_WIFISSID_H_

#include "frame_base.h"
#include "../epdgui/epdgui.h"

class Frame_WifiSSID : public Frame_Base
{
public:
    Frame_WifiSSID(bool isHorizontal = false);
    ~Frame_WifiSSID();
    int run();
    int init(epdgui_args_vector_t &args);

private:
    EPDGUI_Textbox *inputbox;
    EPDGUI_Keyboard *keyboard;
    EPDGUI_Button *key_textclear;
};

#endif //_FRAME_WIFISSID_H_