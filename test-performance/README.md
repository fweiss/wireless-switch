commit #

When it was running, it would periodically be unresponsive from a browser.
After some investigation with browser and HTTP client tools, root cause was unclear
Hypothesis: cpu. modem, radio going to sleep, networking error

Added a status LED GPIO5, Olimex pin 11

Case A: LED shows WiFi.status() == WL_CONNECTED
Observation: LED was mostly on, but would go off for a few seconds, repeatedly, but no clear pattern.
Sometimse would go off when requests were made, but also spontaneously.
With ARC, observed requests would be ~250 ms mostly but sometime 2-4 sec.

Started jmeter
Timing GET request on /api/switch
case A: 300ms 10 times
Observed: odd sawtooth in throughput metrics
throughput avg 41

case B: 500ms
about the same
Hypothesis: the stair step throughtput is an integration of a square wave of response time
Need to isolate the response time
Weird thing in jmeter, can ony see average response, not the whole range.

response time
usually ~250 ms, but then random spikes to 5 sec or even 9.
this is just /api/switch, no spiffs
voltage is steady 3.370 during outages

upgrade board sdk from 2.2.0 to 2.3.0
works without a hitch
avg response 218 ms

but overnight, the POST takes 10 sec


