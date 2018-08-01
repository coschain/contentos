#include <fc/exception/exception.hpp>
#include <fc/io/json.hpp>
#include <contento/rpc_api_generator/rpc_api_generator.hpp>
#include <fc/variant_object.hpp>

using namespace contento;
using namespace contento::rpc_api;

using mvo = fc::mutable_variant_object;

std::unique_ptr<FrontendActionFactory> create_factory(bool verbose, bool opt_sfs, string abi_context, abi_def& output, const string& contract, const rpc_api_macro_def_result& actions) {

  struct rpc_api_frontend_action_factory : public FrontendActionFactory {

    bool                             verbose;
    bool                             opt_sfs;
    string                           abi_context;
    abi_def&                         output;
    const string&                    contract;
    const rpc_api_macro_def_result&  actions;

    rpc_api_frontend_action_factory(bool verbose, bool opt_sfs, string abi_context,
      abi_def& output, const string& contract, const rpc_api_macro_def_result& actions) : verbose(verbose),
      abi_context(abi_context), output(output), contract(contract), actions(actions) {}

    clang::FrontendAction *create() override {
      return new generate_rpc_api_action(verbose, opt_sfs, abi_context, output, contract, actions);
    }

  };

  return std::unique_ptr<FrontendActionFactory>(
      new rpc_api_frontend_action_factory(verbose, opt_sfs, abi_context, output, contract, actions)
  );
}

std::unique_ptr<FrontendActionFactory> create_find_macro_factory(string& contract, rpc_api_macro_def_result& actions, string abi_context) {

  struct rpc_api_frontend_macro_action_factory : public FrontendActionFactory {

    string&                      contract;
    rpc_api_macro_def_result&    actions;
    string                       abi_context;

    rpc_api_frontend_macro_action_factory (string& contract, rpc_api_macro_def_result& actions,
      string abi_context ) : contract(contract), actions(actions), abi_context(abi_context) {}

    clang::FrontendAction *create() override {
      return new find_contento_rpc_api_macro_action(contract, actions, abi_context);
    }

  };

  return std::unique_ptr<FrontendActionFactory>(
    new rpc_api_frontend_macro_action_factory(contract, actions, abi_context)
  );
}

static cl::OptionCategory rpc_api_generator_category("ABI generator options");

static cl::opt<std::string> abi_context(
    "context",
    cl::desc("ABI context"),
    cl::cat(rpc_api_generator_category));

static cl::opt<std::string> abi_destination(
    "destination-file",
    cl::desc("destination json file"),
    cl::cat(rpc_api_generator_category));

static cl::opt<bool> abi_verbose(
    "verbose",
    cl::desc("show debug info"),
    cl::cat(rpc_api_generator_category));

static cl::opt<bool> abi_opt_sfs(
    "optimize-sfs",
    cl::desc("Optimize single field struct"),
    cl::cat(rpc_api_generator_category));

int main(int argc, const char **argv) {
   abi_def output;

   try {
   CommonOptionsParser op(argc, argv, rpc_api_generator_category);
   ClangTool Tool(op.getCompilations(), op.getSourcePathList());

   string contract;
   rpc_api_macro_def_result actions;
   int result = Tool.run(create_find_macro_factory(contract, actions, abi_context).get());
   if(!result) {
      result = Tool.run(create_factory(abi_verbose, abi_opt_sfs, abi_context, output, contract, actions).get());
      if(!result) {
         rpc_api_serializer(output).validate();
         fc::variant vabi;
         to_variant(output, vabi);

         auto comment = fc::format_string(
           "This file was generated by rpc-apigen. DO NOT EDIT - ${ts}",
           mvo("ts",fc::time_point_sec(fc::time_point::now()).to_iso_string()));

         auto abi_with_comment = mvo("____comment", comment)(mvo(vabi));

         fc::json::save_to_file(abi_with_comment, abi_destination, true);
      }
   }
   return result;
} FC_CAPTURE_AND_LOG((output)); return -1; }
