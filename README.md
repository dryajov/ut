# Utube - Elegant Youtube player/downloader for Linux Desktop

being developed in BANKUBAD LABS by [@keshavbhatt](https://github.com/keshavbhatt)

[![Snap Status](https://build.snapcraft.io/badge/keshavbhatt/ut.svg)](https://build.snapcraft.io/user/keshavbhatt/olivia) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) [![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/keshavbhatt/ut.svg)](http://isitmaintained.com/project/keshavbhatt/olivia "Average time to resolve an issue") [![Percentage of issues still open](http://isitmaintained.com/badge/open/keshavbhatt/ut.svg)](http://isitmaintained.com/project/keshavbhatt/olivia "Percentage of issues still open") 

﻿**Nightly Build on any [snapd](https://docs.snapcraft.io/installing-snapd) enabled Linux Distribution can be installed using:**

[![Get it from the Snap Store](https://snapcraft.io/static/images/badges/en/snap-store-black.svg)](https://snapcraft.io/utube)

﻿**Consider Donating if you want this music player grow further**

[**PayPal Me**](https://paypal.me/keshavnrj/10)

﻿**Build requirement**

    Qt >=5.5.1 with these modules
        - libqt5sql5-sqlite
        - libqt5webkit5 (must)
        - libqt5x11extras5
        
    mpv >= 0.29.1
    coreutils >=8.25
    socat >=1.7.3.1-1
    python >=2.7
    wget >=1.17.1
    
**Build instructions**
With all build requirements in place go to project root and execute:

Build:

    qmake (or qmake-qt5, depending on your distro)
    make
    
Execute :

    ./utube
     
﻿
﻿**Or build a snap package**
Copy snap directory from project root and paste it somewhere else (so the build will not mess with source code)
Run :

    snapcraft
Try snap with :

    snap try
Install snap with

    snap install --dangerous name_of_snap_file

**ScreenShots:**
![Olivia](https://res.cloudinary.com/canonical/image/fetch/q_auto,f_auto,w_860/https://dashboard.snapcraft.io/site_media/appmedia/2019/09/Screenshot_from_2019-09-13_16-45-41.png)
![Utube watch and download with lyrics option widgets](https://res.cloudinary.com/canonical/image/fetch/q_auto,f_auto,w_860/https://dashboard.snapcraft.io/site_media/appmedia/2019/09/Screenshot_from_2019-09-13_16-46-58.png)
![Utube setting widget](https://res.cloudinary.com/canonical/image/fetch/q_auto,f_auto,w_860/https://dashboard.snapcraft.io/site_media/appmedia/2019/09/Screenshot_from_2019-09-13_16-48-14.png)

