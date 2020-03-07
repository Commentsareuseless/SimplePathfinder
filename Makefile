WX_Libs = `wx-config --cxxflags --libs`
objs = Launcher.o MainWindow.o GridCoord.o  PathFinder.o


AstPathFinder: ${objs}
	g++ ${objs} ${WX_Libs} -o AstPathFinder

GridCoord.o: GridCoord.h
	g++ GridCoord.cpp ${WX_Libs} -c

Launcher.o: Launcher.h MainWindow.h
	g++ Launcher.cpp ${WX_Libs} -c

MainWindow.o: MainWindow.h GridCoord.h
	g++ MainWindow.cpp ${WX_Libs} -c

PathFinder.o: PathFinder.h MainWindow.h GridCoord.h
	g++ PathFinder.cpp ${WX_Libs} -c

.PHONY : clean
clean:
	rm ${objs}