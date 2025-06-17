#ifndef ESTATUS_CODE_H
#define ESTATUS_CODE_H

enum class EStatusCode {
    Success,
    InvalidParameters,
    SocketClosed,
    SocketCreationError,
    NullPointer
};

#endif // ESTATUS_CODE_H