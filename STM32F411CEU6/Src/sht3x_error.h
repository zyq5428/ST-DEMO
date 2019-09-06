
#ifndef SHT3X_ERROR_H
#define SHT3X_ERROR_H

//-- Includes -----------------------------------------------------------------
#include "typedefs.h"              // type definitions

//-- Enumerations -------------------------------------------------------------
// Error codes
typedef enum{
  NO_ERROR       = 0x00, // no error
  ACK_ERROR      = 0x01, // no acknowledgment error
  CHECKSUM_ERROR = 0x02, // checksum mismatch error
  TIMEOUT_ERROR  = 0x04, // timeout error
  PARM_ERROR     = 0x80, // parameter out of range error
}etError;

#endif
