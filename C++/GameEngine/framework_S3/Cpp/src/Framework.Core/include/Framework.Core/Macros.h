#pragma once

// ****************************************************************************
// FRAMEWORK MACROS
// ****************************************************************************

#define min(a,b) (((a) < (b)) ? (a) : (b))

#define max(a,b) (((a) > (b)) ? (a) : (b))

#define SAFE_RELEASE(x) if(x != nullptr){x->Release();}

#define SAFE_DELETE(x) if(x != nullptr){delete x; x = nullptr;}