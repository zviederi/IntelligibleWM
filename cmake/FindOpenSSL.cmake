# Set OpenSSL inlude path
set(OPENSSL_INCLUDE_DIR "C:/OpenSSL-Win64/include")

set(OPENSSL_LIBRARIES "C:/OpenSSL-Win64/lib")

set(OPENSSL_ROOT_DIR  "C:/OpenSSL-Win64")


# Add imported target ssl (ssleay32)
add_library(ssl SHARED IMPORTED)

# Add imported target for crypto (libeay32)
add_library(crypto SHARED IMPORTED)