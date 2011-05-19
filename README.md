Introduction
============

GNURadio-Scilab contains the setup files for installing SBHS Scilab block in GNURadio. This block calls Scilab which in turns is interfaced with SBHS. SBHS Scilab block reads the temperature of SBHS through Scilab, which can then be plotted using Plot Sink block.  Plot Sink block can be found by installing either of the two modules;

	1. GNURadio-SBHS-Cpp    Module [https://github.com/a-w-s/GNURadio-SBHS-Cpp]
	2. GNURadio-SBHS-Python Module [https://github.com/a-w-s/GNURadio-SBHS-Python]


Pre-Requisites
==============

This package requires that gnuradio-core and scilab is already installed on your machine.  It also depends on some GNU Radio pre-requisites, such as Boost, Python2.6-dev and Cppunit.

For a complete list of Pre-requisites visit: http://gnuradio.org/redmine/wiki/gnuradio/BuildGuide

It is also required that Scilab header files such as stack-c.h, call_scilab.h and api_scilab.h are is installed under /usr/include/scilab directory.

Building & Compiling
====================

To build and compile do the following inside the directory:

	$ sudo autoconf
	$ sudo ./bootstrap
	$ sudo ./configure
	$ cd swig
	$ sudo make generate-makefile-swig
	$ cd ..
	$ sudo make
	$ sudo make install
	$ sudo ldconfig

You can also use the shell script provided as follows;
	
	$ sh ./gr_shell.sh

After successfully installing the block you need to make some changes in the .bashrc file.  Open the file scilab_shell.sh present in this directory and copy the commands to the end of your .bashrc file. To open the .bashrc file do as follows;
	
	$ gedit ~/.bashrc

Files required by Scilab to interface with SBHS is provided in the sub-directory [Scilab StepTest]. The block requires the path to any of these files in the [Scilab File] parameter present on the block. The device terminal has been hard coded as /dev/ttyUSB0 in the file [ser_init.sce]. Necessary changes can be made in case communication fails. 
	



