g++ -fPIC libSource.cpp -shared -o libTest.so
g++ main.cpp -lTest -o tester