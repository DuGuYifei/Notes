---
title: SDL2 SpyHunter
date: 2022-09-15 04:03:03
tags:
 - SDL2
 - game remake
categories:
 - Game
description:
  <img src="https://duguyifei.github.io/blog/SDL2-SpyHunter/spyhunter.jpg">
  <a herf="https://github.com/DuGuYifei/SDL2_SpyHunter">代码：https://github.com/DuGuYifei/SDL2_SpyHunter</a><br />
  Spy Hunter is a classic 1983 vehicular combat arcade game where you play as a spy behind the wheels of an armed sports car. <br />
  Player control the car. There are normal cars which can be attacked but shouldn't be attacked. There are enemies can be attacked. There are enemies can attack player.
---

# Spy Hunter

![](SDL2-SpyHunter/spyhunter.jpg)

代码：https://github.com/DuGuYifei/SDL2_SpyHunter

Spy Hunter is a classic 1983 vehicular combat arcade game where you play as a spy behind the wheels of an armed sports car.

Player control the car. There are normal cars which can be attacked but shouldn't be attacked. There are enemies can be attacked. There are enemies can attack player.

Use sin() function draw road.

Use object pool to decrease the memory used.

Design the structure similar as Unity, in game logically main control function, it will update each object position (GUI) in one loop.

Store points in file, and it can be ranked by score or time in menu.