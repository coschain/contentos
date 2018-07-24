#include <fc/api.hpp>
#include <fc/log/logger.hpp>
#include <fc/rpc/api_connection.hpp>
#include <fc/rpc/binary_api_connection.hpp>

#include <fc/rpc/websocket_api.hpp>
#include <vector>


using namespace fc;
using std::string;
using std::vector;

struct binary_pack_object {
   binary_pack_object() {};
   
   int             idx;
   vector<string>  str_array;
};
FC_REFLECT(binary_pack_object, (idx)(str_array));

class binary_calculator
{
public:
   int32_t add( int32_t a, int32_t b ) {
      wlog(".");
      return a+b;
   }

   string addstr(string str1, string str2){
      wlog(".");
      return str1+str2;
   }

   vector<string> pack_string(string str1, string str2){
      wlog(".");
      vector<string> vec;

      vec.push_back(str1);
      vec.push_back(str2);
      return vec;
   }

   binary_pack_object calc_pack_object(int value, binary_pack_object obj_in){
      binary_pack_object obj_out;

      obj_out.idx = obj_in.idx + value;
      obj_out.str_array = obj_in.str_array;
      obj_out.str_array.push_back("call success");
      return obj_out;
   }

};
FC_API( binary_calculator, (add)(addstr)(pack_string)(calc_pack_object) )


using namespace fc::http;
using namespace fc::rpc;

int call_binary_api_test(){
   fc::api<binary_calculator> calc_api( std::make_shared<binary_calculator>() );

   std::shared_ptr<fc::bapi::local_binary_api_connection> api_server = std::make_shared<fc::bapi::local_binary_api_connection>();

   api_id_type idx = api_server->register_api(calc_api);


   {
      std::vector<char> vec(1024);
      datastream<char*>  ds( vec.data(), size_t(vec.size()) );
      fc::raw::pack(ds,101);
      fc::raw::pack(ds,99);

      std::vector<char> result_packed = api_server->receive_call(idx,
                                                "add",
                                                 vec);

      int32_t result = fc::raw::unpack<int32_t>(result_packed);
      std::cout << "add result: " << result << std::endl;
   }

   {
      std::vector<char> vec(1024);
      datastream<char*>  ds( vec.data(), size_t(vec.size()) );
      fc::raw::pack(ds,string("123"));
      fc::raw::pack(ds,string("456"));

      std::vector<char> result_packed = api_server->receive_call(idx,
                                                                 "addstr",
                                                                 vec);

      string result = fc::raw::unpack<string>(result_packed);
      std::cout << "addstr result: " << result << std::endl;
   }

   {
      std::vector<char> vec(1024);
      datastream<char*> ds( vec.data(), size_t(vec.size()) );
      fc::raw::pack(ds,string("123"));
      fc::raw::pack(ds,string("456"));

      std::vector<char> result_packed = api_server->receive_call(idx,
                                                                 "pack_string",
                                                                 vec);

      vector<string> result = fc::raw::unpack< vector<string> >(result_packed);
      std::cout << "addstr result: " << result[0] << "  -  " << result[1] << std::endl;
   }

   {
      std::vector<char> vec(1024);
      datastream<char*> ds( vec.data(), size_t(vec.size()) );
      binary_pack_object obj_in;

      obj_in.idx = 3;
      obj_in.str_array.push_back("start call");

      fc::raw::pack(ds,10);
      fc::raw::pack(ds,obj_in);

      std::vector<char> result_packed = api_server->receive_call(idx,
                                                                 "calc_pack_object",
                                                                 vec);

      binary_pack_object result = fc::raw::unpack<binary_pack_object>(result_packed);
      std::cout << "calc_pack_object result: " << result.idx << std::endl;
      std::cout << "calc_pack_object result str: " << result.str_array[0] << "  -  " << result.str_array[1] << std::endl;

   }



   return 0;
}
