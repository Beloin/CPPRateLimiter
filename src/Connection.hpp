////////////////////////////////////////////////////////////////////////////////
// File:        Connection.hpp
// Author:      Beloin Rodrigues
////////////////////////////////////////////////////////////////////////////////
#ifndef SRC_CONNECTION_H
#define SRC_CONNECTION_H
////////////////////////////////////////////////////////////////////////////////

#include <memory>
#include <string>

class Connection {

public:
  /**
   * @brief Async proceed
   */
  virtual void proceed() = 0;

  /**
   * @brief Async abort
   */
  virtual void abort() = 0;
  virtual std::string getAddr() = 0;
};

using SharedConnection = std::shared_ptr<Connection>;

#endif /* SRC_CONNECTION_H */
