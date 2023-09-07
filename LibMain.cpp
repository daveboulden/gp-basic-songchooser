#include "LibMain.h"
#include "webcontent.h"
#include <iostream>

std::string pathToMe; // This needs to be initialized from the initialization secttion of the LibMain class so it can be used in the standalone functions directly below
std::vector<std::string> menuNames = { "Show Song Chooser"};    // List of menu items



    //choc::ui::DesktopWindow window ({ 100, 100, 800, 600 });


int LibMain::GetMenuCount() {
    return menuNames.size();
}

std::string  LibMain::GetMenuName(int index) {
    std::string text;
    if (index >= 0 && index < menuNames.size())
        text =  menuNames[index];
         
    return text;      
}


/***************************************************************************************************
 *
 *  If no pre-existing =Song chooser window is open: 
 *  Set indicator to show we want to open the Chooser Window once we are in SetList mode.
 *  Tell GP to swicth to SetList mode.
 * 
 ****************************************************************************************************/

void LibMain::initChooser() {
    if (!isVisible) {               // don't try to open a new one if an existing one is already open
        showingChooser = true;      // set indicator that we are opening the Chooser Window once we are in SetList mode
        switchToSetlistView();      // Switch GP to SetList mode    
    }
}


/***************************************************************************************************
 * 
 *  Get a list of the songs in the current setlist from GP.
 *  Formulate it into the require <LI> tags and return the string of pre-built HTML.
 *  Based upon code by originally written by @rank13
 * 
 ****************************************************************************************************/

std::string LibMain::getSongListFromGP () {
    std::string songList = "";
    std::string thisSong;
    std::string thisArtist;

    for (int i = 0; i < getSongCount(); ++i) {
        thisSong = getSongName(i);
        thisArtist = getArtistName(i);
        songList += "<li class='song-item' data-song-artist='" + thisSong + " | " + thisArtist + "'><a class='song-select' data-slot='" +
                    std::to_string(i) + "'>" + thisSong + " - " + thisArtist + "</a></li>";
    }

    return songList;
}


/***************************************************************************************************
 * 
 *  Send a refreshed list of songs to the exposed function in the embedded HTML page.
 * 
 ****************************************************************************************************/

void LibMain::updateChooser() {
    if (window != nullptr) {
        std::string newSongs = getSongListFromGP();
        // saucer::forget(m_smartview->eval<bool>("setSongList({})",newSongs));
    }
}


/***************************************************************************************************
 * 
 *  Instantiate and populate a new chooser window.
 * 
 ****************************************************************************************************/

bool LibMain::showChooser() {
    isVisible = true;
    showingChooser = false;

    choc::ui::setWindowsDPIAwareness(); // For Windows, we need to tell the OS we're high-DPI-aware

    choc::ui::Bounds winsize = { 100, 100, 1080, 720 };
    window = std::make_unique<choc::ui::DesktopWindow>(winsize);

    window->setWindowTitle ("Basic Song Chooser");
    window->setResizable (true);
    window->centreWithSize (1080, 720);
    window->setMinimumSize (300, 300);
    window->setMaximumSize (1500, 1200);
    window->windowClosed = [&] { 
        isVisible = false;
        choc::messageloop::stop(); 
    };

    choc::ui::WebView::Options wvopts = {false, false};

    choc::ui::WebView webview(wvopts);

    window->setContent (webview.getViewHandle());

    webview.bind ("getSongListFromGP", [&] (const choc::value::ValueView& args) -> choc::value::Value {
        std::string message = getSongListFromGP();
        return choc::value::createString (message);
    });

    webview.bind ("closeSongSelector", [&] (const choc::value::ValueView&) -> choc::value::Value {
        window->setVisible(false);
        window.reset();
        return {};
    });

    webview.bind ("selectSong", [&] (const choc::value::ValueView& args) -> choc::value::Value {
        scriptLog(choc::json::toString (args), true);

        int slot = args[0].getInt32();
        switchToSong(slot, 0);
        
        scriptLog(std::to_string(slot), true);

        return {};
    });

    webview.setHTML (html);



    window->toFront();
    choc::messageloop::run();

    return 0;
}


/***************************************************************************************************
 * 
 *  The "Show Chooser" menu item has been selected, so start opening a new chooser window.
 * 
 ****************************************************************************************************/

void LibMain::InvokeMenu(int index) {
    if (index >= 0 && index < menuNames.size()) {
        switch (index) {
            case 0:
                initChooser();
                break;
                           
            default:
                break;   
        }
    }
}

namespace gigperformer {
    namespace sdk {
        GigPerformerAPI *CreateGPExtension(LibraryHandle handle) {
            return new LibMain(handle);
        }
    } // namespace sdk
} // namespace gigperformer