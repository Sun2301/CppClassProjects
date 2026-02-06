# EPAC - Gestion Scolaire (wxWidgets / C++)

Application de gestion scolaire (EPAC) en C++ avec wxWidgets.

## Prérequis
- Linux
- `g++` (C++11)
- `make`
- `wxWidgets` installé et `wx-config` accessible

Sur Debian/Ubuntu, par exemple:
```
sudo apt-get install g++ make libwxgtk3.0-gtk3-dev
```

## Compilation
À la racine du projet:
```
make
```

## Exécution
```
make run
```

## Nettoyage
```
make clean
```

## Structure du projet
- `src/` : code source
- `include/` : headers
- `src/frames/` : UI (frames)
- `src/dialogs/` : UI (dialogs)
- `src/models/` : logique métier
- `src/database/` : couche données simulée
- `bin/` : binaires et objets

