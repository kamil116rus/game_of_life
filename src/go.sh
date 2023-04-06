#!/bin/bash

parametr1=$1

parametr2=$2

script_name=$0 #присваиваем переменной script_name значение имени скрипта

echo "Вы запустили скрипт с именем $script_name и параметром $parametr1 и $parametr2"

clang-format -i game_of_life.c

git add . 
git commit -m"$parametr1 $parametr2"
git push origin main