#pragma once

#include <stdexcept>
#include <sstream>

#define ExAssertInfo(code, info) \
  if(!(code)) throw AssertException{#code, info, __FILE__, __LINE__}

#define ExAssert(code) \
  ExAssertInfo(code, "")

namespace MyTracer
{
  class AssertException: public std::exception
  {
  public:
    AssertException(std::string const &assertStr, std::string const &addInfo, std::string const &file, int line)
      : mAssertStr(assertStr), mFile(file), mLine(line)
    {
      std::stringstream ss;
      ss << "Assertion '" << mAssertStr << "' in file " << mFile << " on line " << mLine << " failed!\n";
      ss << "Additional info: " << addInfo;
      mWhat = ss.str();
    }

    AssertException(AssertException const &other) = default;
    virtual ~AssertException() = default;

    const char *what() const override
    {
      return mWhat.c_str();
    }
  protected:
    std::string mAssertStr;
    std::string mFile;
    int mLine;
    std::string mWhat;
  };
}