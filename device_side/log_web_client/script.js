var ws_logging;

var keepAliveTimer = 0;

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
        cancelKeepAlive();
    };

    keepAlive()
 }

function keepAlive() {
    if (ws_logging.readyState == WebSocket.OPEN) {
        ws_logging.send('keepalive');
    }

    keepAliveTimer = setTimeout(keepAlive, 20000);
}

function cancelKeepAlive() {
    if (keepAliveTimer) {
        clearTimeout(keepAliveTimer);
    }
}
