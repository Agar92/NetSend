#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>

#include <filesystem>

using boost::asio::ip::tcp;

enum { max_length = 1000000 };

uint8_t buffer[1000000];

int main(int argc, char* argv[])
{
  try
  {
    /*
    if (argc != 3)
    {
      std::cerr << "Usage: blocking_tcp_echo_client <host> <port>\n";
      return 1;
    }
    */

    boost::asio::io_context io_context;

    tcp::socket s(io_context);
    tcp::resolver resolver(io_context);
    boost::asio::connect(s, resolver.resolve("localhost", "10001"));//argv[1], argv[2]));

    std::cout << "Enter message: ";
    //char request[max_length];
    //std::cin.getline(request, max_length);
    //size_t request_length = std::strlen(request);
  //boost::asio::write(s, boost::asio::buffer(request, request_length));



    std::filesystem::path example = "s.jpg";
    std::filesystem::path p = std::filesystem::current_path() / example;
    std::cout<<"STEP #0"<<std::endl;
    std::cout<<"STEP #1 "<<p.string()<<std::endl;
    auto size=std::filesystem::file_size(p);
    std::cout<<"STEP #2 size="<<size<<std::endl;
    std::ifstream in("land.png", std::ios::in | std::ios::binary);
    in.read((char*)&buffer[0], size);
    ///std::cout<<"buffer="<<buffer<<"   "<<in.gcount()<<std::endl;
    //std::cout<<"CHECK:"<<std::endl;
    //for(int i=0; i<1000; ++i) std::cout<<(char)buffer[i];
    in.close();
    /*
    std::ofstream out("out.png");
    out.write(&buffer[0], size);
    out.close();
    */

    boost::asio::write(s, boost::asio::buffer(buffer, size));
    //exit(0);

    uint8_t reply[max_length];
    size_t reply_length = boost::asio::read(s,
        boost::asio::buffer(reply, size));
    std::cout << "Reply is: reply_length="<<reply_length<<std::endl;;
    std::cout.write((const char*)reply, reply_length);
    std::cout << reply;
    //
    std::ofstream ou("out.png");
    ou.write((const char*)&reply[0], reply_length);
    ou.close();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}