Prerequisites
=============

**There will be a lot of errors and I resolve them in some way,so I revise the README.md,and  sorry  for my poor English,I hope you can understand the file.**

Custom version of NS-3 and specified version of ndnSIM needs to be installed.

The code should also work with the latest version of ndnSIM, but it is not guaranteed.

    mkdir ndnSIM
    cd ndnSIM

    git clone https://github.com/named-data-ndnSIM/ns-3-dev.git ns-3
    git clone https://github.com/named-data-ndnSIM/pybindgen.git pybindgen
    git clone -b ndnSIM-2.3 --recursive https://github.com/named-data-ndnSIM/ndnSIM ns-3/src/ndnSIM

    # compile your pybindgen There will be some errors,never mind
    # In my env,xml is too old and gtk id not found
    # specially,the version is uncorrect,you should modify version.py
     sudo ./waf configure --boost-includes=/opt/boost_1_64_0 --boost-libs=/opt/boost_1_64_0/stage/lib --enable-examples

    # Build and install NS-3 and ndnSIM,There will be some errors,never mind
    # In my env,brite,click,openflow is not built
    cd ns-3
    ./waf configure -d optimized
    ./waf
    sudo ./waf install

    # When using Linux, run
    # sudo ldconfig

    # When using Freebsd, run
    # sudo ldconfig -a

    cd ..
    git clone https://github.com/named-data-ndnSIM/scenario-template.git my-simulations
    cd my-simulations

    ./waf configure
    ./waf --run scenario

After which you can proceed to compile and run the code

For more information how to install NS-3 and ndnSIM, please refer to http://ndnsim.net website.

Compiling
=========

**Not only do as below,if you didn't configure global variables you should add boost parameter as me such as**

     sudo ./waf configure --boost-includes=/opt/boost_1_64_0 --boost-libs=/opt/boost_1_64_0/stage/lib --enable-examples
     
**and if you do this,don't forget other thing such as -d optimized**

To configure in optimized mode without logging **(default)**:

    ./waf configure

To configure in optimized mode with scenario logging enabled (logging in NS-3 and ndnSIM modules will still be disabled,
but you can see output from NS_LOG* calls from your scenarios and extensions):

    ./waf configure --logging

To configure in debug mode with all logging enabled

    ./waf configure --debug

If you have installed NS-3 in a non-standard location, you may need to set up ``PKG_CONFIG_PATH`` variable.

Running
=======
**you should find your path at first,In my env,it is located at /usr/local/lib64 and if you can't loading your scanario as error while loading shared libraries,please modify the file: /etc/ls.so.conf,and add your lib of boost.after this,ldconfig.**

Normally, you can run scenarios either directly

    ./build/<scenario_name>

or using waf

    ./waf --run <scenario_name>

If NS-3 is installed in a non-standard location, on some platforms (e.g., Linux) you need to specify ``LD_LIBRARY_PATH`` variable:

    LD_LIBRARY_PATH=/usr/local/lib ./build/<scenario_name>

or

    LD_LIBRARY_PATH=/usr/local/lib ./waf --run <scenario_name>

To run scenario using debugger, use the following command:

    gdb --args ./build/<scenario_name>


Running with visualizer
-----------------------

There are several tricks to run scenarios in visualizer.  Before you can do it, you need to set up environment variables for python to find visualizer module.  The easiest way to do it using the following commands:

    cd ns-dev/ns-3
    ./waf shell

After these command, you will have complete environment to run the vizualizer.

The following will run scenario with visualizer:

    ./waf --run <scenario_name> --vis

or

    PKG_LIBRARY_PATH=/usr/local/lib ./waf --run <scenario_name> --vis

If you want to request automatic node placement, set up additional environment variable:

    NS_VIS_ASSIGN=1 ./waf --run <scenario_name> --vis

or

    PKG_LIBRARY_PATH=/usr/local/lib NS_VIS_ASSIGN=1 ./waf --run <scenario_name> --vis

Available simulations
=====================

<Scenario Name>
---------------

Description
