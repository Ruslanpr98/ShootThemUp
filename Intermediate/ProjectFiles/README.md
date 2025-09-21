# ShootThemUp

ShootThemUp — небольшой шутер на Unreal Engine 5 с C++ логикой. Проект содержит базовый геймплей: оружие, снаряды, враги, простой искуственный интеллект


### Особенности
- Базовый ThirdPerson шутер.

- C++ логика для компонентов оружия, персонажей (игрока и ИИ врагов), виджетов и игрового режима.

- Возможность расширения проекта (можно добавить разрушение, более умных врагов и другой функционал)



# Быстрое руководство

**Клонирование**

```bash
git clone https://github.com/Ruslanpr98/ShootThemUp.git
cd ShootThemUp
```


## Сборка

- Правой кнопкой по ShootThemUp.uproject → Generate Visual Studio project files (если нужно).

- Открыть .sln → выбрать Development Editor | Win64 → Build.

- Запустить через Unreal Editor → Play.

## Требования

- Unreal Engine 5.x 

- Visual Studio с C++ workload или JetBrains Rider

- Git

## Краткое управление

- WASD — движение

- ЛКМ — стрельба

- Пробел — прыжок

- R — перезарядка

## Архитектура

- Source/ — C++ (Projectile, Enemy, Player и т.д.)

- Content/ — ассеты и уровни

- .uproject — настройки проекта