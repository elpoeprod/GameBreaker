# Maintainer: Arvedui <arvedui@posteo.de>
# Contributor: Jakub Kądziołka <kuba@kadziolka.net>

pkgname=gb
pkgdesc="Simple graphics engine for C++"
pkgver=0.0.5
pkgrel=2
arch=(x86_64)
url="https://github.com/elpoeprod/GameBreaker"
license=(BSD-3)
depends=(sdl2 sdl2_image sdl2_ttf sdl2_net)
conflicts=()
# Upstream suggests using clang, but gcc is supported on Linux: https://github.com/LIJI32/SameBoy/issues/164#issuecomment-486464194
makedepends=(make)
source=("GameBreaker-${pkgver}.tar.gz::https://github.com/elpoeprod/GameBreaker/archive/v${pkgver}.tar.gz")
md5sums=('0442ec751aa4c227be2589bfdfd0f9a6')

build(){
	cd "${srcdir}/GameBreaker-${pkgver}"
	make
}

package(){
	cd "${srcdir}/GameBreaker-${pkgver}"

	make install
	install -D "${pkgdir}/usr/share/licenses/gb/LICENSE"

}
