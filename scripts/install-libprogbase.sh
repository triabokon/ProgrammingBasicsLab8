#!/bin/sh

wget -O libprogbase.zip https://github.com/PublicHadyniak/libprogbase/archive/master.zip
unzip libprogbase.zip -d libprogbase
cd libprogbase/libprogbase-master ; sudo make install
cd ../../ ; rm libprogbase/ libprogbase.zip -rf
