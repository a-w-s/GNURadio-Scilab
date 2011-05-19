#!/bin/sh

sudo autoconf
sudo ./bootstrap
sudo ./configure
cd swig
sudo make generate-makefile-swig
cd ..
sudo make
sudo make install
sudo ldconfig
