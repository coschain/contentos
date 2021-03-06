#include <fc/compress/zlib.hpp>

#include "miniz.c"

namespace fc
{
    string zlib_compress(const string& in)
    {
    size_t compressed_message_length;
        char* compressed_message = (char*)tdefl_compress_mem_to_heap(in.c_str(), in.size(), &compressed_message_length,  TDEFL_WRITE_ZLIB_HEADER | TDEFL_DEFAULT_MAX_PROBES);
        string result(compressed_message, compressed_message_length);
        free(compressed_message);
        return result;
    }
    
     std::string zlib_decompress( const string& in)
    {
        size_t decompressed_message_length;
        char* decompressed_message = (char*)tinfl_decompress_mem_to_heap( in.c_str(), in.length(), &decompressed_message_length, TINFL_FLAG_PARSE_ZLIB_HEADER );
        std::string result( decompressed_message, decompressed_message_length );
        free( decompressed_message );
        return result;
    }
}
