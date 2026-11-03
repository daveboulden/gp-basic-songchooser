constexpr const auto html 
= R"xxx(
<!DOCTYPE html>
<html lang='en'>
    <head>
        <title>Basic Song Chooser</title>
        <meta charset="utf-8">
        <link href="https://fonts.googleapis.com/css2?family=Montserrat:wght@300;500;600;700&display=swap" rel="stylesheet">
        <style>
            * { box-sizing: border-box; }
            html, body {
                margin: 0;
                padding: 0;
                height: 100%;
                background: #0b0b0b;
                color: #f2f2f2;
                font-family: Montserrat, system-ui, -apple-system, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
                -webkit-font-smoothing: antialiased;
            }
            html { overflow-y: scroll; overflow-x: hidden; }
            .header-top {
                position: fixed;
                top: 0; left: 0; right: 0;
                z-index: 1;
                height: 92px;
                background: #0b0b0b;
                display: flex;
                align-items: center;
                justify-content: space-between;
                gap: 14px;
                padding: 16px 8px 16px 16px;
            }
            #list-title {
                font-size: 40px;
                font-weight: 300;
                letter-spacing: -.01em;
                line-height: 1;
                white-space: nowrap;
            }
            #list-title b { color: #e5202a; font-weight: 700; }
            #close-window {
                width: 60px;
                height: 60px;
                flex-shrink: 0;
                border-radius: 14px;
                background: #3a3a3a;
                border: 1px solid #4a4a4a;
                display: flex;
                align-items: center;
                justify-content: center;
                font-size: 34px;
                font-weight: 300;
                color: #f2f2f2;
                cursor: pointer;
                user-select: none;
            }
            #close-window:active { background: #4a4a4a; }
            .page-wrap {
                padding: 92px 8px 24px;
            }
            #songlist {
                margin: 0;
                padding: 0;
                list-style: none;
                border-top: 1px solid #222;
            }
            #songlist li {
                list-style: none;
                border-bottom: 1px solid #1e1e1e;
            }
            #songlist li a {
                height: 66px;
                display: flex;
                align-items: center;
                gap: 14px;
                padding: 0 16px;
                white-space: nowrap;
                overflow: hidden;
                cursor: pointer;
                user-select: none;
                -webkit-tap-highlight-color: transparent;
            }
            #songlist li a > span { pointer-events: none; }
            .song-name   { font-size: 28px; font-weight: 700; color: #d8d8d8; text-transform: uppercase; }
            .song-artist { font-size: 24px; font-weight: 600; color: #7d7d7d; }
            .song-key    { font-size: 22px; font-weight: 300; color: #9a9a9a; }
            #songlist li a:hover .song-name { color: #fff; }
            #songlist li.selected a { background: #1f1f1f; }
            #songlist li.selected .song-name   { color: #fff; }
            #songlist li.selected .song-artist { color: #bdbdbd; }
            #songlist li.selected .song-key    { color: #e5202a; }
        </style>
    </head>
    <body>
        <div id="main-container">
            <header class='header-top'>
                <div id='list-title'><b>Basic</b>SongChooser</div>
                <div id='close-window'>&times;</div>
            </header>
            <div id='top' class='page-wrap'>
                <ol id='songlist'></ol>
            </div>
        </div>
        <script>
            (function() {
                var selSlot = 0;
                document.body.addEventListener('click', function(e) {
                    const link = e.target.closest('.song-select');
                    if (link) {
                        document.querySelectorAll('.song-item').forEach(song => song.classList.remove('selected'));
                        link.parentElement.classList.add('selected');
                        selSlot = parseInt(link.dataset.slot, 10);
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
