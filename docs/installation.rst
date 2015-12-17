Installation
=====================================

.. highlight:: bash

Requirements
------------

``cmake`` is required for building the library. `Gromacs
<http://www.gromacs.org/>`_ 5.1+ is required, since the library links to some of it's
functions.

Installing
-----------

A typical install consists of `downloading the most recent
tarball <https://github.com/wesbarnett/libgmxcpp/releases>`_ and extracting it.
Enter the source directory. Then do::

    mkdir build
    cd build
    cmake ..
    make
    make install

You may need superuser privileges for the last step, or you may need to specify
a different installation directory (like your home folder) with the `cmake`
option ``-DCMAKE_INSTALL_PREFIX`` above.

Alternatively if you are running `Arch <https://www.archlinux.org/>`_ you can
`install it from the AUR <https://aur.archlinux.org/packages/libgmxcpp/>`_.

Location
--------

Header files will be installed within a folder named ``gmxcpp``.

Testing the build
-----------------

To test your build you can run ``make test`` in the build directory (see
above).

Automated tests were performed `via
Travis <https://travis-ci.org/wesbarnett/libgmxcpp>`_ when new commits were
pushed, but a newer compiler is required than available.  Specifically, "<random>" 
is used in some utilities. 

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
