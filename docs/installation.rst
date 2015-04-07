Installation
=====================================

.. highlight:: bash

**Requirements**

cmake

**Installing from Source**::

    git clone https://github.com/wesbarnett/libgmxcpp.git
    cd libgmxcpp
    mkdir build
    cd build
    cmake ..
    make
    make install

**Installing from AUR**

`libgmxcpp is now in the AUR
repository. <https://aur.archlinux.org/packages/libgmxcpp/>`_ If you're on Arch
you know what to do.

**Testing the build**

To test your build you can run the following in the build directory (see above):::

    make test

Automated tests are performed `via
Travis <https://travis-ci.org/wesbarnett/libgmxcpp>`_ when new commits are pushed.
Tests are in the "tests" directory.
