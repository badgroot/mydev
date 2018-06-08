#include "gui.h"
gui::gui(int argc, char** argv)
{ this->set_title("Grid-scape");
    this->set_border_width(10);
    TurnOnButton.add_label("Turn on");
    TurnOnButton.signal_clicked().connect(sigc::mem_fun(*this,&gui::onClickedTurnOnButton));
    TurnOffButton.add_label("Turn Off");
    TurnOffButton.signal_clicked().connect(sigc::mem_fun(*this,&gui::onClickedTurnOffButton));
    Grid.add(TurnOnButton);
    Grid.add(TurnOffButton);
    firstImage="1.jpeg";
   secondImage="2.jpg";
    image.set(firstImage);
    status.set_text("Please wait ..");
    Grid.add(status);
    Grid.add(image);
    Glib::signal_timeout().connect( sigc::mem_fun(*this, &gui::onTimeOut), 1000 );
    Grid.show_all();
    add(Grid);
  charger=ChargerStatus::FAULT; 
  seconds=0; 
    
   
   

}
gui::~gui(){

}
void gui::onClickedTurnOffButton(){
    std::cout<<"signal catch onClickedTurnOffButton"<<std::endl;
    image.set(firstImage);
    if(!talker_ptr->get_publish_data_flag()){
    talker_ptr->clear_publish_data_flag();
    talker_ptr->setString("onClickedTurnOffButton");
    talker_ptr->set_publish_data_flag();
    }

}
void gui::onClickedTurnOnButton(){
    std::cout<<"signal catch onClickedTurnOnButton"<<std::endl;
    image.set(secondImage);
    if(!talker_ptr->get_publish_data_flag()){
    talker_ptr->clear_publish_data_flag();

    talker_ptr->setString("onClickedTurnOnButton");
    talker_ptr->set_publish_data_flag();
    }
    
}
void gui::setImage(){
   
}
bool gui::onTimeOut(){
   
    char text[50];
    sprintf(text,"seconds : %d",++seconds);
    charger=ChargerStatus::CHARGING;
    status.set_text(text);
    updateStatus("AB");
    return true;
}
void gui::updateStatus(std::string){
    update_Image();
}
    void gui::update_Image(){
        switch(charger)
        {case ChargerStatus::CHARGING :
            std::cout<<"status charging"<<std::endl;
            break;
            case ChargerStatus::FAULT :
                std::cout<<"status faults"<<std::endl;
                break;
            case ChargerStatus::NOT_CONNECTED :
                std::cout<<"charger Not Connected";
             break;
            case ChargerStatus::PREPARING:
                std::cout<<"Charger preparing"<<std::endl;
         break;
            default:
                std::cout<<"Not implemented"<<std::endl;
        }
        
    }