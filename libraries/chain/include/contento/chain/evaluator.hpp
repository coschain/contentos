#pragma once
#include <contento/protocol/exceptions.hpp>
#include <contento/protocol/operations.hpp>

namespace contento { namespace chain {

class database;
class transaction_context;

template< typename OperationType=contento::protocol::operation >
class evaluator
{
   public:
      virtual void apply(const OperationType& op) = 0;
      virtual void apply(const OperationType& op, std::shared_ptr<transaction_context> trx_ctx) = 0;
      virtual int get_type()const = 0;
};

template< typename EvaluatorType, typename OperationType=contento::protocol::operation >
class evaluator_impl : public evaluator<OperationType>
{
   public:
      typedef OperationType operation_sv_type;
      // typedef typename EvaluatorType::operation_type op_type;

      evaluator_impl( database& d )
         : _db(d) {}

      virtual void apply(const OperationType& o) final override
      {
         auto* eval = static_cast< EvaluatorType* >(this);
         const auto& op = o.template get< typename EvaluatorType::operation_type >();
         eval->do_apply(op);
      }

      virtual void apply(const OperationType& o, std::shared_ptr<transaction_context> trx_ctx) final override
      {
         ctx = trx_ctx;
         apply(o);
      }

      virtual int get_type()const override { return OperationType::template tag< typename EvaluatorType::operation_type >::value; }

      database& db() { return _db; }

   protected:
      database& _db;
      std::shared_ptr<transaction_context> ctx;
};

} }

#define DEFINE_EVALUATOR( X ) \
class X ## _evaluator : public contento::chain::evaluator_impl< X ## _evaluator > \
{                                                                           \
   public:                                                                  \
      typedef X ## _operation operation_type;                               \
                                                                            \
      X ## _evaluator( database& db )                                       \
         : contento::chain::evaluator_impl< X ## _evaluator >( db )          \
      {}                                                                    \
                                                                            \
      void do_apply( const X ## _operation& o );                            \
};
