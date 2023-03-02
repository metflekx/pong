#pong

###compile : 
>"g++ ./ball/ball.cpp ./racket/racket.cpp pong.cpp helpers.cpp
   -std=c++20 -lsdl2 -lsdl2_image "

###file structure : 
.
├── MANUAL.md
├── a.out
├── ball
│   ├── ball.cpp
│   └── ball.h
├── cmd.txt
├── helpers.cpp
├── helpers.h
├── pong.cpp
└── racket
    ├── racket.cpp
    └── racket.h

####how to play :
for player1 :'w' and 's' controls left racket.
for player2 : "up-arrow" and "down-arrow" controls right racket.
each time one of the players scores, you should press r to restart.
player who get the first 5 pts wins.

####leaks check:
leaks --atExit -- ./a.out
Process 73101: 0 leaks for 0 total leaked bytes.
