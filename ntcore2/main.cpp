#include <iostream>
#include <chrono>
#include <cstdio>
#include <thread>
#include "ntcore.h"

#include "networktables/NetworkTable.h"

using namespace std;
using namespace nt;
int main() {

  NetworkTable::SetClientMode();
  NetworkTable::SetIPAddress("10.58.27.2");
  
  auto nt = NetworkTable::GetTable("foo");
  
  
  //nt->Initialize();
  std::this_thread::sleep_for(std::chrono::seconds(3));

  cout << "Starting loop.\n";

  while (true) { 
    int i = rand() % 1000 + 1;
    cout << "Number: " << nt->GetNumber("value", 1.0) << '\n';
    //nt->PutNumber("randomvalue", i);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }

}
