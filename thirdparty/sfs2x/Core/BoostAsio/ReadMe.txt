Boost version is 1.55.0

Folder "Unix" contains Boost sources for Linux
	We need of follow boost libraries:

		cygboost_chrono.dll
		cygboost_date_time.dll
		cygboost_regex.dll
		cygboost_system.dll
		cygboost_thread.dll

	To build these libraries we must:
		- Go to directory \cygwin\bin. Copy g++-3.exe as g++.exe overriding already exist file
		- Add cygwin\bin to system path
		- Run cygwin terminal (see in start\programs menu of Windows)
		- From cygwin terminal shell, move into the folder that contains boost  
	
			cd /cygdrive/c/..../trunk_api/Core/BoostAsio/Unix

		  Then type the command

			./bootstrap.sh –prefix=boost/

		  Wait the command execution is completed, than type

			./b2

		output libraries will be created into stage\lib folder


Folder "Windows" contains Boost sources for Visual Studio 2010/2012/2013
	We need of follow boost libraries:

		libboost_chrono-vc100-mt-1_55.lib		
		libboost_chrono-vc100-mt-gd-1_55.lib
		libboost_chrono-vc110-mt-1_55.lib		
		libboost_chrono-vc110-mt-gd-1_55.lib
		libboost_chrono-vc120-mt-1_55.lib		
		libboost_chrono-vc120-mt-gd-1_55.lib

		libboost_date_time-vc100-mt-1_55.lib
		libboost_date_time-vc100-mt-gd-1_55.lib
		libboost_date_time-vc110-mt-1_55.lib
		libboost_date_time-vc110-mt-gd-1_55.lib
		libboost_date_time-vc120-mt-1_55.lib
		libboost_date_time-vc120-mt-gd-1_55.lib

		libboost_regex-vc100-mt-1_55.lib
		libboost_regex-vc100-mt-gd-1_55.lib
		libboost_regex-vc110-mt-1_55.lib
		libboost_regex-vc110-mt-gd-1_55.lib
		libboost_regex-vc120-mt-1_55.lib
		libboost_regex-vc120-mt-gd-1_55.lib

		libboost_system-vc100-mt-1_55.lib
		libboost_system-vc100-mt-gd-1_55.lib
		libboost_system-vc110-mt-1_55.lib
		libboost_system-vc110-mt-gd-1_55.lib
		libboost_system-vc120-mt-1_55.lib
		libboost_system-vc120-mt-gd-1_55.lib
	
		libboost_thread-vc100-mt-1_55.lib
		libboost_thread-vc100-mt-gd-1_55.lib
		libboost_thread-vc110-mt-1_55.lib
		libboost_thread-vc110-mt-gd-1_55.lib
		libboost_thread-vc120-mt-1_55.lib
		libboost_thread-vc120-mt-gd-1_55.lib

	To build these libraries we must:
		- Open a DOS shell. Go to \Core\BoostAsio\Windows
		- From a DOS shell type the command

			bootstrap

		- When bootstrap command is completed, type these commands

			b2 -a toolset=msvc-10.0 threading=multi link=static runtime-link=shared --with-system stage
			b2 -a toolset=msvc-11.0 threading=multi link=static runtime-link=shared --with-system stage
			b2 -a toolset=msvc-12.0 threading=multi link=static runtime-link=shared --with-system stage

			b2 -a toolset=msvc-10.0 threading=multi link=static runtime-link=shared --with-date_time stage
			b2 -a toolset=msvc-11.0 threading=multi link=static runtime-link=shared --with-date_time stage
			b2 -a toolset=msvc-12.0 threading=multi link=static runtime-link=shared --with-date_time stage

			b2 -a toolset=msvc-10.0 threading=multi link=static runtime-link=shared --with-chrono stage
			b2 -a toolset=msvc-11.0 threading=multi link=static runtime-link=shared --with-chrono stage
			b2 -a toolset=msvc-12.0 threading=multi link=static runtime-link=shared --with-chrono stage

			b2 -a toolset=msvc-10.0 threading=multi link=static runtime-link=shared --with-regex stage
			b2 -a toolset=msvc-11.0 threading=multi link=static runtime-link=shared --with-regex stage
			b2 -a toolset=msvc-12.0 threading=multi link=static runtime-link=shared --with-regex stage

			b2 -a toolset=msvc-10.0 threading=multi link=static runtime-link=shared --with-thread stage
			b2 -a toolset=msvc-11.0 threading=multi link=static runtime-link=shared --with-thread stage
			b2 -a toolset=msvc-12.0 threading=multi link=static runtime-link=shared --with-thread stage

		output libraries will be created into stage\lib folder
		
	
