---
title: 全栈项目KeyChcker密钥访问
date: 2023-02-28 00:33:53
tags:
 - vue
 - qt
 - C++
 - springboot
 - mysql
 - python
categories:
 - 全栈
description: Prepare a "coat" for other programs which user can use a time-limited key to log in. User's machine is bound. Supervisor have has his own interface. Use SHA-256 encrytion, http request, Multi-processes communication(Shared Memory, Message Pipe), Multithread, WinAPI.
---


## Intro

[Github link](https://github.com/DuGuYifei/KeyChecker)

![](全栈项目KeyChcker密钥访问/2023-02-27-20-49-51.png)

![](全栈项目KeyChcker密钥访问/2023-02-27-21-04-32.png)

Prepare a "coat" for other programs which user can use a time-limited key to log in. Their machines are bound.

The wrapper framework use `mysql` and contains back-end (`Springboot`), back-end supervise interface (`vue`) and user client (`Qt c++`).

Also display a wrappee example by `pyhon` to use the shared memory or message pipe.

## Tech stack
1. <img src="https://user-images.githubusercontent.com/25181517/183891303-41f257f8-6b3d-487c-aa56-c497b880d0fb.png"  width="20" height="20"> Springboot - java
2. <img src="https://user-images.githubusercontent.com/25181517/117448124-a2da9800-af3e-11eb-85d2-bd1b69b65603.png"  width="20" height="20"> Vue.js - javascript, html, css
3. <img src="./qt.png"  width="20" height="20"> Qt desktop - C++
4. <img src="https://user-images.githubusercontent.com/25181517/183423507-c056a6f9-1ba8-4312-a350-19bcbc5a8697.png"  width="20" height="20"> Python script
5. <img src="https://user-images.githubusercontent.com/25181517/183896128-ec99105a-ec1a-4d85-b08b-1aa1620b2046.png"  width="20" height="20"> Database - MySQL


* <img src="https://user-images.githubusercontent.com/25181517/192107854-765620d7-f909-4953-a6da-36e1ef69eea6.png"  width="20" height="20"> Http request
* <img src="https://user-images.githubusercontent.com/25181517/186884150-05e9ff6d-340e-4802-9533-2c3f02363ee3.png"  width="20" height="20"> WinAPI - C++, python
* <img src="./multiprocess.png"  width="20" height="20"> Multi-processes communication - Shared Memory, Message Pipe
* <img src="./multithread.png"  width="20" height="20"> Multithread in Qt C++
* <img src="https://user-images.githubusercontent.com/25181517/117207330-263ba280-adf4-11eb-9b97-0ac5b40bc3be.png"  width="20" height="20"> Test by Docker

## TODO
1. Give log-in func in back-end supervise interface
2. Use JWT token in no.1 of todo list
