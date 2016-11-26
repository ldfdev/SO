#include <iostream>
#include <string>
#include <thread>
#include <future>

void get_string(std::promise<std::string> &prm){
	std::string s("Hi W223drt3\n");
	prm.set_value(s);
}
int main()
{
	std::promise<std::string> promiss;
	std::future<std::string> ftr=promiss.get_future();
	std::thread threaddy(&get_string,std::ref(promiss));
	std::cout<<"Hello from main!\n";
	std::string ss=ftr.get();
	std::cout<<ss<<std::endl;
	threaddy.join();
	return 0;
}
