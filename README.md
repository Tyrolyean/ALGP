# ALGP
## IN DEVELOPMENT! NOT STABLE YET! PLEASE DON'T USE!
The ALGP is a protocol intended to ease plaintext data transfer
from client to server and unify it. If anybody intends to use it,
please aknowledge that the protocol's ONLY server-sided operation
is to validate the client's output. No other calculation tasks
are performed on the server side. The server, however is
responsible for data exchange, though this is limited to text.

##  BUILD

As per usual there is a Makefile in the root directory.
Please make sure the following dependencys are installed:

* Libsodium
* GPGME

They should be in your library paths.

## INSTALL 

The include directory probably should be self-explaining,
as it inhabits the header files you program should include.
The make command should produce build/ALGP.so which your
program should link against.

## Rest

I don't want to be blamed for unusable code so I don't know
why I put this up here in this kinda early stage…
If you, for whatever reason want to help me bringing this
to a readable format, please don't hasitate to message me.
Thank you for your attention and please don't intend to use this.

