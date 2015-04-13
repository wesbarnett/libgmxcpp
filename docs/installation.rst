Installation
=====================================

.. highlight:: bash

Requirements
------------

``cmake`` is required for building the library. `Gromacs
<http://www.gromacs.org/>`_ is required, since
the library links to some of it's functions.

Installing
-----------

**From Source**::

    git clone https://github.com/wesbarnett/libgmxcpp.git
    cd libgmxcpp
    mkdir build
    cd build
    cmake ..
    make
    make install

**From AUR**

`libgmxcpp is now in the AUR
repository. <https://aur.archlinux.org/packages/libgmxcpp/>`_ If you're on Arch
you know what to do.

Location
--------

Header files will be installed within a folder named ``gmxcpp``.

Testing the build
-----------------

To test your build you can run ``make test`` in the build directory (see above).

Automated tests are performed `via
Travis <https://travis-ci.org/wesbarnett/libgmxcpp>`_ when new commits are pushed.
Tests are in the ``tests`` directory.

Documentation
-------------

If you want to have a local copy of the documentation, do ``make docs`` in the
build directory. The html files will be placed in ``docs/html`` in your build
directory. ``sphinx``, ``breathe``, and ``doxygen`` are required to build the
documentation. Install ``doxygen`` with your package manager (*e.g.,* ``sudo
apt-get install doxygen``). Install ``sphinx`` and ``breathe`` with::

    sudo pip install sphinx
    sudo pip install breathe

Additionally the source code is well-documented, containing more detail than the
generated documentation.
