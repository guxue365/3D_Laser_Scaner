CFLAGS =
LDFLAGS =
LIBS = -lm 

test:
	g++ $(CFLAGS) $(LDFLAGS) $(LIBS) src/scaner.cpp src/extract.cpp src/rotator.cpp src/pcd_file.cpp src/utils.cpp -o bin/scaner `pkg-config opencv --cflags --libs`
	g++ src/rotator.cpp src/rotator_test.cpp -o ./bin/rotator_test
	g++ $(CFLAGS) $(LDFLAGS) $(LIBS) src/pcd_file.cpp src/write_pcd.cpp -o bin/write_pcd `pkg-config opencv --cflags --libs`
	
	
.PHONY: clean
clean:
	rm ./bin/*
