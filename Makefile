
all: crackP

crackP:
	g++ -o crack.x crack.cpp

clean:
	rm -rf crack.x
