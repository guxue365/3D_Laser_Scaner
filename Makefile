CFLAGS =
LDFLAGS =
LIBS = -lm 

all: scaner_test rotator_test write_pcd single_line_test read_config_test

scaner_test:
	g++ $(CFLAGS) $(LDFLAGS) $(LIBS) src/scaner.cpp src/extract.cpp src/rotator.cpp src/pcd_file.cpp src/scaner_test.cpp src/read_config.cpp -o bin/scaner_test `pkg-config opencv --cflags --libs`

rotator_test:
	g++ src/rotator.cpp src/rotator_test.cpp -o ./bin/rotator_test

write_pcd:
	g++ $(CFLAGS) $(LDFLAGS) $(LIBS) src/pcd_file.cpp src/write_pcd_test.cpp -o bin/write_pcd_test `pkg-config opencv --cflags --libs`
	
single_line_test:
	g++ $(CFLAGS) $(LDFLAGS) $(LIBS) src/single_line_test.cpp src/extract.cpp src/pcd_file.cpp src/scaner.cpp src/read_config.cpp -o bin/single_line_test `pkg-config opencv --cflags --libs`
	
read_config_test:
	g++ $(CFLAGS) $(LDFLAGS) $(LIBS) src/read_config.cpp src/read_config_test.cpp -o bin/read_config_test
	
.PHONY: clean
clean:
	rm ./bin/*
