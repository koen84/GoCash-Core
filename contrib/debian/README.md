
Debian
====================
This directory contains files used to package gcashd/gcash-qt
for Debian-based Linux systems. If you compile gcashd/gcash-qt yourself, there are some useful files here.

## gcash: URI support ##


gcash-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install gcash-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your gcashqt binary to `/usr/bin`
and the `../../share/pixmaps/gcash128.png` to `/usr/share/pixmaps`

gcash-qt.protocol (KDE)

