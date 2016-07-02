# Arduino House Lock.

This app sends commands to an internet connected Arduino with Wifi Shield to open or close a door.

Authentication is currently done through the Single Sign On System of The University of Texas at El Paso.

## Photographs

## Interface

Navigate to `/` to access the user list
`/doors` to access connected door lists.


## Instructions

1. When deploying this app, sign in with your UTEP Miners account.
2. Login to the production console by doing `rails c production`.
3. Give your user admin rights `User.first.admin = true`
4. Now you can modify access rights to the door.

## Arduino Code

Switch to branch `arduino-code` to see the Arduino sketch that is uploaded, change the values of your SSID to use.

### Logic

The app uses a status page located at `/doors/{door_id}/status`. Then a WifiClient on the Arduino connects to a Wi-Fi Network, navigates to the page and does a GET request. The results are then parsed and the tag `<status></status>` is searched for. A boolean value is given to state the current status of the lock. 

The WifiClient on the Arduino repeats the GET request every given interval.

## To Do

- [ ] Make system accessible without a miners account, another type of authentication, social media accounts?

Based on:
https://flowingdata.com/2014/12/11/how-to-download-and-use-online-data-with-arduino/
