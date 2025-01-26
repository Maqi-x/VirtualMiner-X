# VirtualMiner-X

## EN:
VirtualMIner-X is a simple clicker game, so far in Beta phase

### How to build?
1. install dependencies, you can do it using your package manager:
> **[TIP]:** You will probably have to use sudo/pkexec to install packages
- Fedora/Redhat and derivatives: `dnf install qt5-qtbase-devel qt5-qtdeclarative-devel qt5-qtmultimedia-devel qt5-qttools-devel qt5-qtbase qt5-linguist`
- Debian/ubuntu and derivatives: `sudo apt install qtbase5-dev qtchooser qt5-qmake qttools5-dev-tools`
- Arch/Manjaro and derivatives: `sudo pacman -S qt5-base qt5-tools`
- windows: install Fedora, your system is shit

2. run compilations:
```bash
qmake && make
```

3. ready! The binary should be in the bin/ folder


# PL:
VirtualMIner-X to prosta gra clicker, narazie w fazie Beta

## Jak zbudować?
1. zainstaluj zależności, możesz to zrobić używając swojego menażera pakietów:
> **[TIP]:** Zapewne będziesz musiał użyć sudo/pkexec by instalować pakiety
- Fedora/Redhat i pochodne: `dnf install qt5-qtbase-devel qt5-qtdeclarative-devel qt5-qtmultimedia-devel qt5-qttools-devel qt5-qtbase qt5-linguist`
- Debian/Ubuntu i pochodne: `sudo apt install qtbase5-dev qtchooser qt5-qmake qttools5-dev-tools`
- Arch/Manjaro i pochodne: `sudo pacman -S qt5-base qt5-tools`
- Windows: zainstaluj Fedore, twój system jest śmieciem

2. uruchom kompilacje:
```bash
qmake && make
```

3. Gotowe! binarka powinna się znaleźć w folderze bin/
