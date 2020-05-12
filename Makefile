all: clean ass5

ass5:
	g++ -g --std=c++11 *.cpp -o ass5
clean:
	rm -rf ass5