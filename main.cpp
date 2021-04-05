#include <thread>
#include "buffered_channel.h"
#include <string>
#include <chrono>
#include <iostream>

template<class T>
void f1(BufferedChannel<T>& chanel) {
	std::string words[] = { "Hello\n","world\n","!\n"};
	for (int i = 0; i < 3; i++) {
		chanel.Send(words[i]);
		std::this_thread::sleep_for(std::chrono::milliseconds(200));
	}
}
template<class T>
void f2(BufferedChannel<T>& chanel) {
	for (int i = 0; i < 3; i++) {
		std::cout << chanel.Recv().first;
	}
}

int main() {
	BufferedChannel<std::string> chanel(2);
	std::thread t1(f1<std::string>, std::ref(chanel));
	std::thread t2(f2<std::string>, std::ref(chanel));
	t1.join();
	t2.join();
}