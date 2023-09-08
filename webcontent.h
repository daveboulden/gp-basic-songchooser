constexpr const auto html 
= R"xxx(
<!DOCTYPE html>
<html lang='en'>
    <head>
        <title>Basic Song Chooser</title>  
        <meta charset="utf-8">
        <style>
            html { 
                font-family: system-ui,-apple-system,"Segoe UI",Roboto,"Helvetica Neue",Arial,"Noto Sans","Liberation Sans",sans-serif,"Apple Color Emoji","Segoe UI Emoji","Segoe UI Symbol","Noto Color Emoji";
                overflow-y: scroll; 
                overflow-x: hidden; 
                height: 100%; 
                margin: 0;
                padding: 0; 
            }
            .header-top { 
                background: #111;
                position: fixed;
                z-index: 1;
                width: 100%;
                height: 90px;
                margin-top: -100px;
            }
            .header-content {
                display:flex;
                flex-direction: row;
                align-content: stretch;
            }
            .page-wrap, .header-wrap { 
                margin: 0 auto; 
                padding: 0 10px;
            }
            .page-wrap {
                margin-top: 100px;
            }
            body {
                height: 100%;
                margin: 0;
                padding: 0; 
                background: #222222;
            }
            #songlist {
                margin: 0 0 0 0;
                padding: 0;
            }
            #songlist li {
              font-size: 3em;
              font-weight: bold;
              background-color: #000000;
              color: #FFFFFF;
              padding: 0 0;
              text-transform: none;
              list-style: none;
              white-space: nowrap;
              margin-bottom: 8px;
              border-radius: 8px;
            }
            #songlist li span {
              text-transform:none;
              padding-left: 20px;
              color: #a15050;
              font-size: 0.8em;
            }
            #songlist li.selected {
                background-color: rgb(69, 69, 69);
                color: #fff;
            }
            #songlist li a {
                width:100%;
                height:1em;
                color: #bbb;
                display: inline-block;
                text-align: left;
                margin-right: 20px;
                border-radius: 8px;
                padding: 0px 16px 20px 16px;
                vertical-align: bottom;
                cursor: pointer;
            }
            #songlist li a:hover {
                color: #fff;
            }
            #list-title {
                color: #fff;
                font-size: 80px;
                line-height: 75px;
                font-family: system-ui,-apple-system,"Segoe UI",Roboto,"Helvetica Neue",Arial,"Noto Sans","Liberation Sans",sans-serif,"Apple Color Emoji","Segoe UI Emoji","Segoe UI Symbol","Noto Color Emoji";
                flex-grow: 1;
            }
            #close-window {
                float: right;
                font-weight: bold;
                font-size: 7em;
                line-height: 0.6em;
                color: #ffffff;
                background-color: #444444;
                padding: 0px 5px 22px 0px;
                cursor: pointer;
                display: block;
                margin-right: 0;
            }
        </style>
    </head>
    <body>
        <div id="main-container">
            <header class='header-top'>
                <div class='header-wrap'>
                    <div class='header-content align-bottom'>
                        <div id='list-title'>Basic Song Chooser</div>
                        <div id='close-window'>&times;</div>
                    </div>
                </div>        
            </header>
            <div id='top' class='page-wrap'>
                <ol id='songlist'></ol>            
            </div>
        </div>
        <script>
            (function() {
                var selSlot = 0;
                document.body.addEventListener('click', function(e) {
                    if (e.target.classList.contains('song-select')) {
                        document.querySelectorAll('.song-item').forEach(song => song.classList.remove('selected'));
                        e.target.parentElement.classList.add('selected');
                        selSlot = parseInt(e.target.dataset.slot, 10);

                        const result = selectSong(selSlot);
                    }
                    if (e.target.id == "close-window") {
                        const result = closeSongSelector();
                    }
                });
            })();
        </script>
        <script>
            getSongListFromGP().then ((result) => { document.querySelector('#songlist').innerHTML = result; });
        </script>
        <script>
            function setSongList(listHtml) {
                document.querySelector('#songlist').innerHTML = listHtml;
                return true;
            }
        </script>
    </body>
</html>
    )xxx";