
#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <cosiolib/cosio.hpp>
#include <cosiolib/content.hpp>
#include <cosiolib/content.h>


namespace eosio { 


	template <typename OperationType>
	bool send_inline_operation( OperationType & op){
		operation optype(op);
		datastream<size_t> dss;
        dss << optype;
        std::vector<char>  vec_in(dss.tellp());
        datastream<const char*> ds(vec_in.data(), vec_in.size());
        ds << optype;

		return excute_operation( vec_in.data(), vec_in.size() );
	}

}


