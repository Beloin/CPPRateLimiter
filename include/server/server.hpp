////////////////////////////////////////////////////////////////////////////////
// File:        server.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef INCLUDE_SERVER_SERVER_H
#define INCLUDE_SERVER_SERVER_H
////////////////////////////////////////////////////////////////////////////////

#include <string>
namespace Server {

//------------------------------------------------------------------------------

class Server
{

public:
    Server() = default;
    ~Server() = default; 

  void serve(std::string &host, std::string& port);

private:

};

//------------------------------------------------------------------------------

}
#endif /* INCLUDE_SERVER_SERVER_H */
