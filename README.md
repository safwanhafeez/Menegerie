# Menegerie

This project is a Match-3 game developed using the Simple and Fast Multimedia Library (SFML) and basic C++ programming constructs such as structures, pointers, and arrays. The game does not utilize Object-Oriented Programming (OOP) principles, highlighting a more fundamental approach to C++ programming.
## Installation

Install SFML from https://www.sfml-dev.org/download.php.
Following are the commands for compiling

```bash
  g++ -c main.cpp
```
If you installed SFML to a non-standard path, you'll need to tell the linker where to find the SFML libraries (.so files):
```bash
  g++ -c main.cpp -I<sfml-install-path>/include
```
Binding the include files
```bash
  g++ main.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
If you installed SFML to a non-standard path, you'll need to tell the linker where to find the SFML libraries (.so files):
```bash
  g++ main.o -o sfml-app -L<sfml-install-path>/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
```
Finally you can run the executable application
```bash
  ./sfml-app
```
## Screenshot

![Main Menu](https://i.imgur.com/4HXD6QI.png)

![Options](https://i.imgur.com/cAujd2E.png)

![Game Screen](https://i.imgur.com/1f9nNKR.png)
