# Maintainer: Aline Ferraz <freya.df@gmail.com>

pkgname=manaplus-git
pkgver=1.1.6.12
pkgrel=1
pkgdesc="ManaPlus (aka The Mana World 4144 patch)"
arch=('i686' 'x86_64')
url="http://manaplus.evolonline.org"
depends=('guichan' 'libxml2' 'physfs' 'sdl_image' 'sdl_mixer' 'sdl_net' 'sdl_ttf' 'sdl_gfx' 'enet')
license=('GPL2')

build() {
cd ${startdir}/
git clone git://gitorious.org/~alineferraz/manaplus/alineferraz-manaplus.git
cd alineferraz-manaplus
autoreconf -i
./configure --prefix=/usr
make clean
make || return 1
make DESTDIR=$startdir/pkg install
} 
