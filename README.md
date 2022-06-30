# My build of dwm

### original from [Luke Smith](https://github.com/LukeSmithxyz/dwm)

## Patches and features

- clickable statusbar with Lukes build of [dwmblocks](https://github.com/lukesmithxyz/dwmblocks)
- scratchpad terminals: calculator, open a temp note in neovim, terminal, file manager (lf) and email (neomutt).
- layouts: tiled, bstack, monocle, deck, centered master, centered floating master, spiral, dwindle and floating.
- true fullscreen (`super+f`) and prevents focus shifting.
- xmenu incorporation to open an apps menu, close windows and change layouts.
- dmenu incorporation for various programs.
- windows can be made sticky (`super+s`).
- stacker: move windows up the stack manually (`super-K/J`).
- vanitygaps: gaps allowed across all layouts.
- systray: system tray in in the statur bar after dwmblocks
- winicon: display window icons on the status bar.
- swallow: if a program run from a terminal would make it inoperable, it temporarily takes its place to save space.
- and a few other small patches to make dwm more useable.

```
git clone https://github.com/mattkel/dwm
cd dwm
sudo make clean install - initally, then
sudo make install - thereafter
```

## Please install `libxft-bgra`!

This build of dwm does not block color emoji in the statusbar, so you must install [libxft-bgra](https://aur.archlinux.org/packages/libxft-bgra/) from the AUR, which fixes a libxft color emoji rendering problem, otherwise dwm will crash upon trying to render one. Hopefully this fix will be in all libxft soon enough.
