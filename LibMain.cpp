#include "LibMain.h"

std::string pathToMe; // This needs to be initialized from the initialization secttion of the LibMain class so it can be used in the standalone functions directly below
std::vector<std::string> menuNames = { "Show Song Chooser"};    // List of menu items

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
    if (m_smartview != nullptr) {
        std::string newSongs = getSongListFromGP();
        saucer::forget(m_smartview->eval<bool>("setSongList({})",newSongs));
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
    
    m_smartview = std::make_unique<saucer::simple_smartview<saucer::serializers::json>>();

    m_smartview->set_title("Basic Song Chooser");

    m_smartview->expose("selectSong", [&](int slot) {
        switchToSong(slot, 0);
        return slot;
    });

    m_smartview->expose("closeWindow", [&]() {
        m_smartview->close();
        return 0;
    });

    m_smartview->on<saucer::window_event::close>([&]() {
        isVisible = false;
        return false;
    });

    m_smartview->expose("getSongList", [&]() {
        return getSongListFromGP();
    });

    // m_smartview->embed(std::move(embedded::get_all_files()));
    // m_smartview->serve("index.html");
    m_smartview->embed_files(std::move(embedded::get_all_files()));
    m_smartview->serve_embedded("index.html");

    m_smartview->set_dev_tools(false);  // set to true to show Developer Tools with in your browser window for debugging the JavaScript
    m_smartview->show();
    m_smartview->run();

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