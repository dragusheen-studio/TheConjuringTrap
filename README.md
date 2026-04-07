# 🕯️ The Conjuring Trap

[![C++ Version](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://en.cppreference.com/w/cpp/17)
[![Library](https://img.shields.io/badge/Library-SDL2-green.svg)](https://www.libsdl.org/)
[![Tests](https://img.shields.io/badge/Tests-GoogleTest-red.svg)](https://github.com/google/googletest)

**The Conjuring Trap** est un jeu d'horreur à la première personne propulsé par un moteur de rendu 3D (**Raycasting**) développé entièrement *from scratch* en C++17.

---

## 🕹️ Le Jeu
Le joueur se retrouve piégé dans un environnement hostile et oppressant. Pour s'échapper, il devra :
* **Survivre** : Gérer sa santé mentale, son endurance et ses ressources face aux événements paranormaux.
* **Explorer** : Fouiller les coffres pour trouver des items critiques comme des pilules de soin ou des clés.
* **Interagir** : Utiliser un inventaire dynamique et des mécaniques de gameplay pour progresser dans le labyrinthe.

## 🛠️ Spécifications Techniques
Ce projet n'utilise aucun moteur commercial (Unity, Unreal). Tout a été conçu manuellement pour démontrer une maîtrise avancée de la POO :

* **Moteur de Raycasting** : Rendu 3D temps réel avec correction de l'effet "Fish-Eye" par calculs trigonométriques.
* **Architecture Data-Driven** : Utilisation d'un **parseur YAML sur mesure** pour configurer les entités et les cartes sans recompiler le code source.
* **Gestions de la Mémoire** : Utilisation exclusive de *Smart Pointers* (`std::unique_ptr`, `std::shared_ptr`) pour garantir la robustesse et l'absence de fuites mémoire.
* **Programmation Générique** : Classe `Vector<T>` templatisée avec sécurité à la compilation via `std::enable_if` (métaprogrammation).
* **Système d'Interactions** : Utilisation intensive du polymorphisme (`dynamic_cast`) et d'interfaces pures pour gérer les objets interactifs de manière modulaire.

## 🚀 Installation & Compilation

### Dépendances
* **CMake** (v3.10+)
* **SDL2** (SDL2, SDL2_image, SDL2_mixer, SDL2_ttf)
* **Google Test** (téléchargé et lié automatiquement via CMake)

### Build
```bash
# Cloner le dépôt
git clone [https://github.com/ton-username/The-Conjuring-Trap.git](https://github.com/ton-username/The-Conjuring-Trap.git)
cd The-Conjuring-Trap

# Créer le dossier de build
mkdir build && cd build

# Configurer et compiler le projet
cmake .. -DBUILD_GAME=ON -DBUILD_TESTS=ON
make
```

## 🧪 Tests Unitaires
La stabilité du moteur est assurée par une suite de **plus de 120 tests unitaires** automatisés via le framework Google Test.

Pour lancer la suite de validation :
```bash
./bin/tests
```
Les tests couvrent le noyau mathématique (`Vector`), le parseur YAML, et la logique métier du joueur (inventaire, santé, collisions).

## 🎹 Contrôles
* **ZQSD / Flèches** : Déplacement et rotation de la vue.
* **E** : Interagir avec l'environnement (ouvrir les coffres, etc.).
* **Shift** : Courir (consomme de l'endurance).
* **A** : Utiliser une pilule de santé mentale.

---

**Développé par Nathan TIROLF**
*Projet de fin de session - UQAC 2026*
