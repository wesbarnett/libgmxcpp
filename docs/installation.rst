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

Classes for use with AVX Instructions
-------------------------------------

Some classes are provided for use with SIMD intrinsics, specifically the AVX
set. To compile with these classes available, add ``-DAVX=ON`` to your cmake
call when installing. This is experimental, since tests have not been implemented
for these classes yet.

Unfortunately I don't have time to cover all instruction
sets, so I'm focusing on those most useful to myself. If you're interested in
adding more, please file a pull request.

A good example of this in practice, is my test particle insertion code found
`here <http://github.com/wesbarnett/tpi>`_. Specifically look at the CalcPE
function in Atomtype.cpp.

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
