
/*
g++ hello_world_node.cpp -o hello_world_node -I/opt/ros/kinetic/include -L/opt/ros/kinetic/lib -lroscpp -lrosconsole -lrostime

*/



#include <gtkmm.h>
#include "gui.h"
#include "ros_talker.h"
#include <thread>
// Standard C++ entry point
int argc_;
char ** argv_;
   
ros_talker *talker_ptr;
gui *guiptr;
int Main(int argc,char **argv)
{
    
  

}

void runUi(){
 Gtk::Main app(argc_,argv_);  
    gui ab(argc_,argv_);
    guiptr=&ab;
    Gtk::Main::run(*guiptr);  
}
void runRos(){
       ros_talker speaker(argc_,argv_);
      
talker_ptr=&speaker;   
   talker_ptr->publish_data("Grid-scape"); 
}
int main(int argc, char** argv) {
   argc_=argc;
    argv_=argv;
    std::thread guiThread(runUi);
    std::thread rosThread(runRos);
    
    guiThread.join();
    rosThread.join();
    
   // runUi();
    //while(1);
    //runRos();
return 0;
}
