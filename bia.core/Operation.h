#ifndef _EOPERATION_TYPE_
#define _EOPERATION_TYPE_

namespace BIA
{
   class Operation
   {
   public:
      static const char* READ;
      static const char* WRITE;
   };
}

const char* BIA::Operation::READ = "r";
const char* BIA::Operation::WRITE = "w";

#endif
