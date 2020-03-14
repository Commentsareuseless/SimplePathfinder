WX_Libs = `wx-config --cxxflags --libs`
objs = Launcher.o MainWindow.o GridCoord.o  PathFinder.o


AstPathFinder: ${objs}
	g++ -g ${objs} ${WX_Libs} -o AstPathFinder.out

GridCoord.o: GridCoord.h
	g++ -g GridCoord.cpp ${WX_Libs} -c

Launcher.o: Launcher.h MainWindow.h
	g++ -g Launcher.cpp ${WX_Libs} -c

MainWindow.o: MainWindow.h GridCoord.h
	g++ -g MainWindow.cpp ${WX_Libs} -c

PathFinder.o: PathFinder.h MainWindow.h GridCoord.h
	g++ -g PathFinder.cpp ${WX_Libs} -c

.PHONY : clean
clean:
	rm ${objs}