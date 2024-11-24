
//silver_chain_scope_start
//mannaged by silver chain
#include "../../../imports/imports.dec.h"
//silver_chain_scope_end


#if defined(_WIN32)


extern char *Universal_GetLastError(){
  
  static char errorBuffer[256];

  DWORD dwError = WSAGetLastError();
  if (dwError == 0) {
      return "Nenhum erro";
  }

  FormatMessage(
      FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
      NULL,
      dwError,
      0,
      errorBuffer,
      sizeof(errorBuffer),
      NULL
  );

  return errorBuffer;
}



#endif



