#include "frame_wifissid.h"
#include "frame_wifipassword.h"


void key_ssidclear_cb(epdgui_args_vector_t &args)
{
    ((EPDGUI_Textbox*)(args[0]))->SetText("");
}


Frame_WifiSSID::Frame_WifiSSID(bool isHorizontal) : Frame_Base()
{
    _frame_name = "Frame_WifiSSID";
    uint8_t language = GetLanguage();
    if(isHorizontal)
    {
        inputbox = new EPDGUI_Textbox(84, 25, 712, 250);
        if(language == LANGUAGE_JA)
            key_textclear = new EPDGUI_Button("削除", 804, 25, 72, 120);
        else if(language == LANGUAGE_ZH)
            key_textclear = new EPDGUI_Button("清除", 804, 25, 72, 120);
        else
            key_textclear = new EPDGUI_Button("CLR", 804, 25, 72, 120);
    }
    else
    {
        const uint16_t kKeyBaseY = 176;
        inputbox = new EPDGUI_Textbox(4, 100, 532, 60);
        if(language == LANGUAGE_JA)
            key_textclear = new EPDGUI_Button("削除", 4, kKeyBaseY, 260, 52);
        else if(language == LANGUAGE_ZH)
            key_textclear = new EPDGUI_Button("清除", 4, kKeyBaseY, 260, 52);
        else
            key_textclear = new EPDGUI_Button("CLR", 4, kKeyBaseY, 260, 52);
    }
    
    inputbox->SetTextMargin(8, 15, 8, 8);
    inputbox->SetState(EPDGUI_Textbox::EVENT_PRESSED);

    keyboard = new EPDGUI_Keyboard(isHorizontal, EPDGUI_Keyboard::STYLE_INPUTMODE_NEEDCONFIRM);
    
    key_textclear->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, (void*)inputbox);
    key_textclear->Bind(EPDGUI_Button::EVENT_RELEASED, key_ssidclear_cb);

    if(language == LANGUAGE_JA)
    {
        exitbtn("WLAN");
        _canvas_title->drawString("パスワード", 270, 34);
    }
    else if(language == LANGUAGE_ZH)
    {
        exitbtn("无线局域网", 200);
        _canvas_title->drawString("密码", 270, 34);
    }
    else
    {
        exitbtn("WLAN");
        _canvas_title->drawString("SSID", 270, 34);
    }
    
    _key_exit->AddArgs(EPDGUI_Button::EVENT_RELEASED, 0, (void*)(&_is_run));
    _key_exit->Bind(EPDGUI_Button::EVENT_RELEASED, &Frame_Base::exit_cb);
}

Frame_WifiSSID::~Frame_WifiSSID()
{
    delete inputbox;
    delete keyboard;
    delete key_textclear;
}

int Frame_WifiSSID::init(epdgui_args_vector_t &args)
{
    _is_run = 1;
    M5.EPD.Clear();
    _canvas_title->pushCanvas(0, 8, UPDATE_MODE_NONE);
    EPDGUI_AddObject(inputbox);
    EPDGUI_AddObject(keyboard);
    EPDGUI_AddObject(_key_exit);
    EPDGUI_AddObject(key_textclear);
    return 6;
}

int Frame_WifiSSID::run(void)
{
    String data = keyboard->getData();
    if(data.indexOf("\n") >= 0)
    {
        String *ssid = new String(inputbox->GetText());
        EPDGUI_AddFrameArg("Frame_WifiScan", 0, NULL);        
        EPDGUI_AddFrameArg("Frame_WifiScan", 1, ssid);        
        inputbox->SetText("");
        EPDGUI_PopFrame();
        Frame_Base *frame = EPDGUI_GetFrame("Frame_WifiPassword");
        if(frame == NULL)
        {
            frame = new Frame_WifiPassword(false);
            EPDGUI_AddFrame("Frame_WifiPassword", frame);
        }
        EPDGUI_PushFrame(frame);
        _is_run = 0;
        return 0;
    }
    inputbox->AddText(data);
    return 1;
}
