__start__: obj interp __plugin__
	export LD_LIBRARY_PATH="./libs"; ./interp

obj:
	mkdir obj

__plugin__:
	cd plugin; make

CPPFLAGS=-Wall -g -pedantic -std=c++11 -Iinc
LDFLAGS=-Wall

interp: obj/main.o obj/xmlparser4scene.o obj/lacze_do_gnuplota.o obj/GnuplotVisualizer.o obj/Wektor3D.o obj/Manager4Plugins.o obj/Scene.o obj/Colision.o
	g++ ${LDFLAGS} -o interp   obj/main.o obj/xmlparser4scene.o obj/lacze_do_gnuplota.o obj/GnuplotVisualizer.o obj/Wektor3D.o obj/Manager4Plugins.o  obj/Scene.o obj/Colision.o -ldl -lxerces-c -lreadline

obj/xmlparser4scene.o: src/xmlparser4scene.cpp inc/xmlparser4scene.hh
	g++ -c ${CPPFLAGS} -o obj/xmlparser4scene.o src/xmlparser4scene.cpp

obj/Colision.o: src/Colision.cpp inc/Colision.hh
	g++ -c ${CPPFLAGS} -o obj/Colision.o src/Colision.cpp

obj/lacze_do_gnuplota.o: src/lacze_do_gnuplota.cpp inc/lacze_do_gnuplota.hh
	g++  -c ${CPPFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/GnuplotVisualizer.o: src/GnuplotVisualizer.cpp inc/GnuplotVisualizer.hh\
                         inc/GnuplotVisualizer.hh inc/Wektor3D.hh
	g++  -c ${CPPFLAGS} -o obj/GnuplotVisualizer.o src/GnuplotVisualizer.cpp

obj/Wektor3D.o: src/Wektor3D.cpp inc/Wektor3D.hh
	g++ -c ${CPPFLAGS} -o obj/Wektor3D.o src/Wektor3D.cpp

obj/Manager4Plugins.o: src/Manager4Plugins.cpp inc/Manager4Plugins.hh inc/DronPose.hh
	g++ -c ${CPPFLAGS} -o obj/Manager4Plugins.o src/Manager4Plugins.cpp

obj/Scene.o: src/Scene.cpp inc/Scene.hh inc/Cuboid.hh 
	g++ -c ${CPPFLAGS} -o obj/Scene.o src/Scene.cpp

obj/main.o: src/main.cpp inc/Interp4Command.hh inc/DronPose.hh
	g++ -c ${CPPFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -f obj/* interp core*


clean_plugin:
	cd plugin; make clean

cleanall: clean
	cd plugin; make cleanall
	cd dox; make cleanall
	rm -f libs/*
	find . -name \*~ -print -exec rm {} \;

help:
	@echo
	@echo "  Lista podcelow dla polecenia make"
	@echo 
	@echo "        - (wywolanie bez specyfikacji celu) wymusza"
	@echo "          kompilacje i uruchomienie programu."
	@echo "  clean    - usuwa produkty kompilacji oraz program"
	@echo "  clean_plugin - usuwa plugin"
	@echo "  cleanall - wykonuje wszystkie operacje dla podcelu clean oraz clean_plugin"
	@echo "             oprocz tego usuwa wszystkie kopie (pliki, ktorych nazwa "
	@echo "             konczy sie znakiem ~)."
	@echo "  help  - wyswietla niniejszy komunikat"
	@echo
	@echo " Przykladowe wywolania dla poszczegolnych wariantow. "
	@echo "  make           # kompilacja i uruchomienie programu."
	@echo "  make clean     # usuwa produkty kompilacji."
	@echo
 
