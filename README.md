# Lego-Wreath
Get festive with this lego wreath
Wreath in action: https://youtube.com/shorts/zORu2V9RCKs?si=Z_5DbFAUw2vjMvO6

See .ino file for settings
Make sure your data pin and button pin are set correct.
Upload however many songs you want to a micro SD card for the MP3 Player. Change all names to 1, 2, 3, 4, 5... Change "10" on line 74 to however many songs you have.

I.E. you upload 5 songs, line 74 should be
randNumber = random(5) + 1;

Included Circuit Diagram is from my Stargate. For this project I only used 1 LED strip, connected to D8, and 1 speaker. SPK_1 to positive, SPK_2 to negative.

For operation of wreath:
Plug into power, either via USB-C or power brick.
If using power brick, turn rocker switch to on position.
Wait a couple seconds for everything to initiallize.
Press momentary button once to begin song and lights.
Press again to play a new song.
Lights will continue to twinkle after song is complete.
Press momentary button twice to turn off both sound and lights.


Required hardware:
D1 Mini Arduino Control Board:
https://a.co/d/0FfEbmH

MP3 Player:
https://a.co/d/3wRC83B

Speaker:
https://a.co/d/7q27jT4

Addressable LEDs:
https://a.co/d/27ul6Ua

Momentary Button:
https://a.co/d/7I6YXeD

Connectors to disconnect lights from control box:
https://a.co/d/2EUPSaQ

Power brick:
https://a.co/d/7k44QZJ

Wire:
https://a.co/d/aVZOO76

Rocker Power Switch:
https://a.co/d/eYaRlxe

Power Jack:
https://a.co/d/haANCTK
