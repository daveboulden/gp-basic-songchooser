#pragma once
#include <gigperformer/sdk/GigPerformerAPI.h>

#include "libs/choc/gui/choc_WebView.h"
#include "libs/choc/gui/choc_DesktopWindow.h"
#include "libs/choc/gui/choc_MessageLoop.h"

// define an XML string describing your product
const std::string XMLProductDescription =   
     // Replace with your information            
    "<Library>" 
    "<Product Name=\"Basic Song Chooser\" Version=\"1.1.0\" BuildDate=\"06/09/2023\"></Product> "
    "<Description>Demo song chooser extension that uses a web based UI</Description>"
    "<ImagePath>/Path/To/ImageFile/foo.jpg</ImagePath>"
    "</Library>"; 

#define then


// This needs to be initialized from the initialization secttion of the LibMain class so it can be used in the standalone functions directly below
// Define your class here - it MUST be called LibMain and it must inherit from GigPerformerAPI

class LibMain : public gigperformer::sdk::GigPerformerAPI
{
private:
    std::unique_ptr<choc::ui::DesktopWindow> window;    // the global chooser window pointer   
    std::unique_ptr<choc::ui::WebView> webview;         // the global webview pointer   

    bool showingChooser = false;                        // used to indicate when we are opening a chooser window
    bool isVisible = false;                             // used to indicate when a song chooser window is open

protected:
    // These are for creating menu items in Gig Performer that can be used to trigger external functions provided by the extension developer
    int GetMenuCount() override;
    std::string GetMenuName(int index) override;
    void InvokeMenu(int itemIndex) override;

public:
    // These must be here but no need to do anything unless you want extra behavior
    LibMain(LibraryHandle handle) : GigPerformerAPI(handle)  { }
    virtual ~LibMain() {}

    
    /***************************************************************************************************
     * 
     *  Declare the chooser functions.
     * 
     ****************************************************************************************************/

    bool showChooser();
    void updateChooser();
    void initChooser();
    std::string getSongListFromGP();

    // Now, simply override the callback methods in which you are interested
    // and, in the Initialization method at the end of this class, 
    // call RegisterCallback for each of these methods

    
    /***************************************************************************************************
     * 
     *  The user has selected a new set list, refresh the contents of the chooser window.
     * 
     ****************************************************************************************************/

    void OnSetlistChanged(const std::string & newSetlistName) override {
        updateChooser();
    }


    /***************************************************************************************************
     * 
     *  Check if we are now in SetList mode and, if so, is it because we are trying to open the chooser.
     *  If we are, reset the indicator and open the chooser
     * 
     ****************************************************************************************************/

    void OnModeChanged(int mode) override {
        if ((mode == GP_SetlistMode) && (showingChooser == true)) {    
            showingChooser = false;                                 
            showChooser();                                          
        }
    }


    /***************************************************************************************************
     * 
     *  A widget value has changed. Check if it has the name "showBasicChooser".
     *  If it does, this is the panel button to open our chooser window, so start opening it.
     * 
     ****************************************************************************************************/

    void OnWidgetValueChanged(const std::string & widgetName, double newValue) override {
        if (widgetName == "showBasicChooser") {
            if (newValue == 1.0) {
                initChooser();
            }
        }
    }



    void Initialization() override {
        // Do any initialization that you need
            
        // .... your code here

              
        // Finally, register all the callbacks that you are going to actually use, i.e, the ones you declared above as override
        registerCallback("OnWidgetValueChanged");
        registerCallback("OnModeChanged");
        registerCallback("OnSetlistChanged");
        listenForWidget("showBasicChooser", true);           
           
        //consoleLog("path to library " + getPathToMe());  
    }

    // Generally don't touch this - simply define the constant 'XMLProductDescription' at the top of this file with an XML description of your product
    std::string GetProductDescription() override { // This MUST be defined in your class
        return XMLProductDescription;
    }

};