var ws_logging;

var keepAliveTimer = null;

function init() {
    ws_logging = new WebSocket("ws://192.168.1.141:80");

    ws_logging.onopen = function() {
        console.log("ws connected");
    };

    ws_logging.onmessage = function (evt) {
        try {
            var received_msg = evt.data;
            console.log("ws message: " + received_msg);
            loggingArea = document.getElementById("loggingArea")
            loggingArea.value += received_msg
            loggingArea.scrollTop = loggingArea.scrollHeight;
        } catch (error) {
            console.error(error);
        }
    };

    ws_logging.onclose = function() {
       console.log("ws connection closed...");
       keepAliveTimer = null
    };

    keepAlive()
 }

function keepAlive() {
    console.log("timer fired")
    if (ws_logging.readyState == WebSocket.OPEN) {
        ws_logging.send('');
    }

    keepAliveTimer = setTimeout(keepAlive, 20000);
}
