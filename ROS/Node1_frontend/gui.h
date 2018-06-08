#include <gtkmm.h>
#include "ros_talker.h"
#include <iostream>
enum ChargerStatus{
    
    CHARGING=1,
    FAULT=2,
    PREPARING=3,
    NOT_CONNECTED=4
            
    
    
};

class gui: public Gtk::Window{
    private:
        int seconds;
        void setImage();
    public:
    gui(int argc,char **argv);
    virtual ~gui();
    
    void updateStatus(std::string);
    void update_Image();
    
    protected:
        std::string firstImage;
        std::string secondImage;
        std::string statusString;
        Gtk::Button TurnOnButton;
        Gtk::Button TurnOffButton;
        Gtk::Grid Grid;
        Gtk::Image image;
        
        Gtk::Label status;
        void onClickedTurnOnButton();
        void onClickedTurnOffButton();
        bool onTimeOut();
        ChargerStatus charger;
        
};
extern ros_talker *talker_ptr;
extern gui *guiptr;
