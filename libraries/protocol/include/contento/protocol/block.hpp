#pragma once
#include <contento/protocol/block_header.hpp>
#include <contento/protocol/transaction.hpp>

namespace contento { namespace protocol {

   struct signed_block : public signed_block_header
   {
      checksum_type calculate_merkle_root()const;
      vector<signed_transaction> transactions;
   };

} } // contento::protocol

FC_REFLECT_DERIVED( contento::protocol::signed_block, (contento::protocol::signed_block_header), (transactions) )
