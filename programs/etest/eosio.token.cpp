/**
 *  @file
 *  @copyright defined in eos/LICENSE.txt
 */

#include "eosio.token.hpp"
#include <eosiolib/compiler_builtins.h>
#include <eosiolib/chain.h>
#include <math.h>
#include <eosiolib/crypto.h>

namespace eosio {

int test_switch(uint64_t foo) {
	int x = (int)(foo & 0xff);
	int r = 100;
	switch(x) {
		case 0: r = 1; break;
		case 1: r = 12; break;
		case 5: r = 14; break;
		case 10: r = 41; break;
		case 32: r = 31; break;
		case 64: r = 71; break;
		case 99: r = 62; break;			
	}
	return r;
}

void token::create( account_name issuer,
                    asset        maximum_supply )
{
    require_auth( _self );

    auto sym = maximum_supply.symbol;
    eosio_assert( sym.is_valid(), "invalid symbol name" );
    eosio_assert( maximum_supply.is_valid(), "invalid supply");
    eosio_assert( maximum_supply.amount > 0, "max-supply must be positive");

    stats statstable( _self, sym.name() );
    auto existing = statstable.find( sym.name() );
    eosio_assert( existing == statstable.end(), "token with symbol already exists" );

    statstable.emplace( _self, [&]( auto& s ) {
       s.supply.symbol = maximum_supply.symbol;
       s.max_supply    = maximum_supply;
       s.issuer        = issuer;
    });
    
    eosio_assert( test_switch(issuer), "oops!");
}


void token::issue( account_name to, asset quantity, string memo )
{
    auto sym = quantity.symbol;
    eosio_assert( sym.is_valid(), "invalid symbol name" );
    eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );
    eosio_assert( test_switch(to), "oops!");

    auto sym_name = sym.name();
    stats statstable( _self, sym_name );
    auto existing = statstable.find( sym_name );
    eosio_assert( existing != statstable.end(), "token with symbol does not exist, create token before issue" );
    const auto& st = *existing;

    require_auth( st.issuer );
    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must issue positive quantity" );

    eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    eosio_assert( quantity.amount <= st.max_supply.amount - st.supply.amount, "quantity exceeds available supply");

    statstable.modify( st, 0, [&]( auto& s ) {
       s.supply += quantity;
    });

    add_balance( st.issuer, quantity, st.issuer );

    if( to != st.issuer ) {
       SEND_INLINE_ACTION( *this, transfer, {st.issuer,N(active)}, {st.issuer, to, quantity, memo} );
    }
}

void token::transfer( account_name from,
                      account_name to,
                      asset        quantity,
                      string       memo )
{
    eosio_assert( from != to, "cannot transfer to self" );
    require_auth( from );
    eosio_assert( is_account( to ), "to account does not exist");
    eosio_assert( test_switch(from), "oops!");
    eosio_assert( test_switch(to), "oops!");
    
    auto sym = quantity.symbol.name();
    stats statstable( _self, sym );
    const auto& st = statstable.get( sym );

    require_recipient( from );
    require_recipient( to );

    eosio_assert( quantity.is_valid(), "invalid quantity" );
    eosio_assert( quantity.amount > 0, "must transfer positive quantity" );
    eosio_assert( quantity.symbol == st.supply.symbol, "symbol precision mismatch" );
    eosio_assert( memo.size() <= 256, "memo has more than 256 bytes" );


    sub_balance( from, quantity );
    add_balance( to, quantity, from );
}

void token::sub_balance( account_name owner, asset value ) {
   accounts from_acnts( _self, owner );

   const auto& from = from_acnts.get( value.symbol.name(), "no balance object found" );
   eosio_assert( from.balance.amount >= value.amount, "overdrawn balance" );


   if( from.balance.amount == value.amount ) {
      from_acnts.erase( from );
   } else {
      from_acnts.modify( from, owner, [&]( auto& a ) {
          a.balance -= value;
      });
   }
}

void token::add_balance( account_name owner, asset value, account_name ram_payer )
{
   accounts to_acnts( _self, owner );
   auto to = to_acnts.find( value.symbol.name() );
   if( to == to_acnts.end() ) {
      to_acnts.emplace( ram_payer, [&]( auto& a ){
        a.balance = value;
      });
   } else {
      to_acnts.modify( to, 0, [&]( auto& a ) {
        a.balance += value;
      });
   }
}

// <eosiolib/compiler_builtins.h> missed the following declarations.
extern "C" {
      void __negtf2( long double& ret, uint64_t la, uint64_t ha );
      void __fixtfti( __int128& ret, uint64_t l, uint64_t h );
      void __fixunstfti( unsigned __int128& ret, uint64_t l, uint64_t h );
      void __fixsfti( __int128& ret, float a );
      void __fixdfti( __int128& ret, double a );
      void __fixunssfti( unsigned __int128& ret, float a );
      void __fixunsdfti( unsigned __int128& ret, double a );
      
      double __floatsidf( int32_t i );
      void __floatsitf( long double& ret, int32_t i );
      void __floatditf( long double& ret, uint64_t a );
      void __floatunsitf( long double& ret, uint32_t i );
      void __floatunditf( long double& ret, uint64_t a );
      double __floattidf( uint64_t l, uint64_t h );
      double __floatuntidf( uint64_t l, uint64_t h );
}

void token::testcb( account_name name )
{
	__int128 r = 0;
	unsigned __int128 u = 0;
	long double ld = 0;

	for (int i=0; i<100; i++) {
		__ashlti3(r, 12, 34, 56);
		__ashrti3(r, 12, 34, 56);
		__lshlti3(r, 12, 34, 56);
		__lshrti3(r, 12, 34, 56);
		__divti3(r, 12, 34, 56, 78);
		__udivti3(u, 12, 34, 56, 78);
		__modti3(r, 12, 34, 56, 78);
		__umodti3(u, 12, 34, 56, 78);
		__multi3(r, 12, 34, 56, 78);
		__addtf3(ld, 12, 34, 56, 78);
		__subtf3(ld, 12, 34, 56, 78);
		__multf3(ld, 12, 34, 56, 78);
		__divtf3(ld, 12, 34, 56, 78);
		__eqtf2(12, 34, 56, 78);
		__netf2(12, 34, 56, 78);
		__getf2(12, 34, 56, 78);
		__gttf2(12, 34, 56, 78);
		__lttf2(12, 34, 56, 78);
		__letf2(12, 34, 56, 78);
		__cmptf2(12, 34, 56, 78);
		__unordtf2(12, 34, 56, 78);
		
		__negtf2(ld, 12, 34);
		__floatsitf(ld, 12);
		__floatunsitf(ld, 12);
		__floatditf(ld, 12);
		__floatunditf(ld, 12);
		__floattidf(12, 34);
		__floatuntidf(12, 34);
		__floatsidf(12);
		
		__extendsftf2(ld, 12);
		__extenddftf2(ld, 12);
		
		__fixtfti(r, 12, 34);
		
		__fixtfdi(12, 34);
		__fixtfsi(12, 34);
		
		__fixunstfti(u, 12, 34);
		
		__fixunstfdi(12, 34);
		__fixunstfsi(12, 34);
		
		__fixsfti(r, 12);
		__fixdfti(r, 12);
		__fixunssfti(u, 12);
		__fixunsdfti(u, 12);
		
		__trunctfdf2(12, 34);
		__trunctfsf2(12, 34);
	}
}

void token::testchain( account_name name )
{
	account_name active_producers[21];
	for (int i=0; i<100; i++) {
  	auto active_prod_size = get_active_producers( active_producers, sizeof(active_producers) );
  }
}

void token::testfloat( account_name name )
{
	float a = (float)name;
	double b = a;
	int32_t i32 = 0;
	uint32_t u32 = 0;
	int64_t i64 = 0;
	uint64_t u64 = 0;
	
	for (int i=0; i<100; i++) {
  	float f = i + 1;
  	a += f;
  	a *= f;
  	a -= f;
  	a /= f;
  	a += (a < 1.0);
  	a += (a <= 1.0);
  	a += (a > 0.0);
  	a += (a >= 0.0);
  	a += (a != 1.0);
  	a += (a == 1.0);
  	
  	double d = f;
  	b += d;
  	b *= d;
  	b -= d;
  	b /= d;
  	b += (b < 1.0);
  	b += (b <= 1.0);
  	b += (b > 0.0);
  	b += (b >= 0.0);
  	b += (b != 1.0);
  	b += (b == 1.0);
  	
  	i32 += (int32_t)f;
  	i32 += (int32_t)d;
  	u32 += (uint32_t)f;
  	u32 += (uint32_t)d;
  	i64 += (int64_t)f;
  	i64 += (int64_t)d;
  	u64 += (uint64_t)f;
  	u64 += (uint64_t)d;
  	
  	f = d;
  }
  eosio_assert( a != 0, "oops!" );
  eosio_assert( b != 0, "oops!" );
  eosio_assert( i32 != 0, "oops!" );
  eosio_assert( u32 != 0, "oops!" );
  eosio_assert( i64 != 0, "oops!" );
  eosio_assert( u64 != 0, "oops!" );
}

void token::testcrypto( account_name name )
{
	checksum160 h_sha1;
	checksum160 h_ripemd;
	checksum256 h_sha256;
	checksum512 h_sha512;
	
	char data[4096];
	
	for (int i=0; i<100; i++) {
		sha1(data, 0, &h_sha1);
		ripemd160(data, 0, &h_ripemd);
		sha256(data, 0, &h_sha256);
		sha512(data, 0, &h_sha512);
		
		assert_sha1(data, 0, &h_sha1);
		assert_ripemd160(data, 0, &h_ripemd);
		assert_sha256(data, 0, &h_sha256);
		assert_sha512(data, 0, &h_sha512);
		
		char sig[65];
		sig[0] = 31;
		char pk[33];
		memcpy(sig + 1, &h_sha512, 64);
   	recover_key( &h_sha256, sig, 65, pk, sizeof(pk) );
		assert_recover_key( &h_sha256, sig, 65, pk, sizeof(pk) );
	}
}

} /// namespace eosio

EOSIO_ABI( eosio::token, (create)(issue)(transfer)(testcb)(testchain)(testfloat)(testcrypto) )
