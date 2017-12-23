#!/bin/bash
echo Please ensure your encoding is right! default is GB2312. 
echo rename 's/.cpp/.c/' ./\*
rename 's/.cpp/.c/' ./*
echo echo \#pragma once \> targetver.h
echo \#pragma once > targetver.h
echo gcc *.c -o fruit_market -lm -Wno-format-security
gcc *.c -o fruit_market -lm -Wno-format-security