#include "ConstexprString.h"

#include <iostream>
#include <memory>
#include <vector>

struct Service
{
  // Service class definition?
  virtual void DoWork() = 0;
};

template<xelous::ConstExpr::TemplateString Name>
struct NamedService : public Service
{
    constexpr static auto sServiceName { Name.mText };     
    
    virtual void DoWork() = 0;
};

struct MyService : public NamedService<"ExampleService">
{
  void DoWork() { std::cout << sServiceName << " is working" << std::endl; };
};

struct OtherService : public NamedService<"OtherService">
{
  void DoWork() { std::cout << sServiceName << " is working, but does something different" << std::endl; };
};

int main()
{      
  static_assert(xelous::ConstExpr::Compare(MyService::sServiceName, "ExampleService"));
  static_assert(xelous::ConstExpr::Compare(OtherService::sServiceName, "OtherService"));
  
  std::cout << "Service Name: " << MyService::sServiceName << std::endl;
  std::cout << "Service Name: " << OtherService::sServiceName << std::endl;
  
  MyService ms;  
  ms.DoWork();
  
  OtherService os;
  os.DoWork();
  
  // Owning pointers
  std::unique_ptr<MyService> myServicePtr = std::make_unique<MyService>();
  std::unique_ptr<OtherService> otherServicePtr = std::make_unique<OtherService>();
  
  // Non-owning pointers or base type in use to do generic work
  std::vector<Service*> services;
  services.push_back(reinterpret_cast<Service*>(myServicePtr.get()));
  services.push_back(reinterpret_cast<Service*>(otherServicePtr.get()));
  
  for(auto& service : services)
  {
    service->DoWork();
  }
  
  // clear up non-owning pointers
  services.clear();

  // Allow everything to go out of scope
}
