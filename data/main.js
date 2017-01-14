(function() {
    function setState(onoff) {
        var req = new XMLHttpRequest();
        req.addEventListener("load", function(event) {

        });
        req.open('POST', '/api/switch');
        req.setRequestHeader("Content-type", "application/json");
        req.send(JSON.stringify({ state:  onoff ? 'on' : 'off' }));
    }
    document.addEventListener("DOMContentLoaded", function() {
        var ws = document.getElementById('ws1');
        ws.addEventListener('change', function(event) {
            var newState = event.target.checked;
            console.log(newState);
            setState(newState);
        });
        var req = new XMLHttpRequest();
        req.addEventListener('load', function(event) {
            console.log(this.responseText);
            var status = JSON.parse(this.responseText);
            console.log(status.state);
            ws.checked = (status.state == 'on');
        });
        req.open('GET', '/api/switch');
        req.send();
    });
})();