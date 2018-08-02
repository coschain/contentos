#pragma once

#include <set>
#include <regex>
#include <algorithm>
#include <memory>
#include <map>
#include <fstream>
#include <sstream>

#include <contento/rpc_api_generator/rpc_api_serializer.hpp>
#include <fc/io/json.hpp>

//clashes with something deep in the AST includes in clang 6 and possibly other versions of clang
#pragma push_macro("N")
#undef N

#include "clang/Driver/Options.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"

#include "clang/Frontend/FrontendPluginRegistry.h"
#include "clang/AST/AST.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendActions.h"
#include "clang/Sema/Sema.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Lex/MacroArgs.h"
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CommonOptionsParser.h"
#include "clang/Tooling/Core/QualTypeNames.h"
#include "llvm/Support/raw_ostream.h"
#include <boost/algorithm/string.hpp>
#include <boost/range/algorithm_ext/erase.hpp>

using namespace clang;
using namespace std;
using namespace clang::tooling;
namespace cl = llvm::cl;

namespace contento {
   using namespace contento::rpc_api;

   FC_DECLARE_EXCEPTION( abi_generation_exception, 999999, "Unable to generate abi" );

   #define ABI_ASSERT( TEST, ... ) \
      FC_EXPAND_MACRO( \
       FC_MULTILINE_MACRO_BEGIN \
         if( UNLIKELY(!(TEST)) ) \
         {                                                                      \
           if( fc::enable_record_assert_trip )                                  \
              fc::record_assert_trip( __FILE__, __LINE__, #TEST );              \
           FC_THROW_EXCEPTION( contento::abi_generation_exception, #TEST ": "  __VA_ARGS__ ); \
         }                                                                      \
       FC_MULTILINE_MACRO_END \
      )

   struct rpc_api_macro_def_structs {
      string            base_struct;
      vector<string>    members;
   };

   struct rpc_api_macro_def_result {
      map<string, vector<string> > functions_map;
      map<string, rpc_api_macro_def_structs > structs_map;

      vector<string> filter_classes;
      vector<string> filter_functions;
   };

   /**
     * @brief Generates contento::abi_def struct handling events from ASTConsumer
     */
   class rpc_api_generator {
      private:
         static constexpr size_t max_recursion_depth = 25; // arbitrary depth to prevent infinite recursion
         bool                   verbose;
         int                    optimizations;
         abi_def*               output;
         CompilerInstance*      compiler_instance;
         map<string, uint64_t>  type_size;
         map<string, string>    full_types;
         string                 abi_context;
         clang::ASTContext*     ast_context;   
         string                 target_contract;
         rpc_api_macro_def_result  target_actions;

      public:

         enum optimization {
            OPT_SINGLE_FIELD_STRUCT
         };

         rpc_api_generator()
         : verbose(false)
         , optimizations(0)
         , output(nullptr)
         , compiler_instance(nullptr)
         , ast_context(nullptr)
         {}

         ~rpc_api_generator() {}

         /**
           * @brief Enable optimization when generating ABI
           * @param o optimization to enable
           */
         void enable_optimizaton(optimization o);

         /**
           * @brief Check if an optimization is enabled
           * @param o optimization to check
           */
         bool is_opt_enabled(optimization o);

         /**
          * @brief Set the destination ABI struct to write
          * @param output ABI destination
          */
         void set_output(abi_def& output);

         /**
          * @brief Enable/Disable verbose status messages
          * @param verbose enable/disable flag
          */
         void set_verbose(bool verbose);

         /**
          * @brief Set the root folder that limits where types will be imported. Types declared in header files located in child sub-folders will also be exported
          * @param abi_context folder
          */
         void set_abi_context(const string& abi_context);


         /**
          * @brief Set the single instance of the Clang compiler
          * @param compiler_instance compiler instance
          */
         void set_compiler_instance(CompilerInstance& compiler_instance);

         /**
          * @brief Handle declaration of struct/union/enum
          * @param tag_decl declaration to handle
          */
         void handle_tagdecl_definition(TagDecl* tag_decl);

         void set_target_contract( const rpc_api_macro_def_result& actions);

      private:
         bool inspect_type_methods_for_actions(const Decl* decl);

         string remove_namespace(const string& full_name);

         bool is_builtin_type(const string& type_name);

         string translate_type(const string& type_name);

         void handle_decl(const Decl* decl);

         bool is_64bit(const string& type);

         bool is_128bit(const string& type);

         bool is_string(const string& type);

         void get_all_fields(const struct_def& s, vector<field_def>& fields);

         bool is_i64i64i64_index(const vector<field_def>& fields);

         bool is_i64_index(const vector<field_def>& fields);

         bool is_i128i128_index(const vector<field_def>& fields);

         bool is_str_index(const vector<field_def>& fields);

//         void guess_index_type(table_def& table, const struct_def s);
//
//         void guess_key_names(table_def& table, const struct_def s);
//
//         const table_def* find_table(const table_name& name);

         const type_def* find_type(const type_name& new_type_name);

         const action_def* find_action(const action_name& name);

         const struct_def* find_struct(const type_name& name);

         type_name resolve_type(const type_name& type);

         bool is_one_filed_no_base(const string& type_name);

         string decl_to_string(clang::Decl* d);

         bool is_typedef(const clang::QualType& qt);
         QualType add_typedef(const clang::QualType& qt, size_t recursion_depth);

         bool is_vector(const clang::QualType& qt);
         bool is_vector(const string& type_name);
         string add_vector(const clang::QualType& qt, size_t recursion_depth);

         bool is_map(const clang::QualType& qt);
         bool is_map(const string& type_name);
         string add_map(const clang::QualType& qt, size_t recursion_depth);

      bool check_container_support(string type_name, size_t recursion_depth = 0);

         bool is_struct(const clang::QualType& qt);
         string add_struct(const clang::QualType& qt, string full_type_name, size_t recursion_depth);

         string get_type_name(const clang::QualType& qt, bool no_namespace);
         string add_type(const clang::QualType& tqt, size_t recursion_depth);

         bool is_elaborated(const clang::QualType& qt);
         bool is_struct_specialization(const clang::QualType& qt);

         QualType get_vector_element_type(const clang::QualType& qt);
         string get_vector_element_type(const string& type_name);
         string get_map_element_type(const string& type_name, bool key);

         QualType get_map_key_element_type(const clang::QualType& qt);
         QualType get_map_value_element_type(const clang::QualType& qt);


         clang::QualType get_named_type_if_elaborated(const clang::QualType& qt);

         const clang::RecordDecl::field_range get_struct_fields(const clang::QualType& qt);
         clang::CXXRecordDecl::base_class_range get_struct_bases(const clang::QualType& qt);
   };

   struct rpc_api_generator_astconsumer : public ASTConsumer {
      rpc_api_generator& abi_gen;

      rpc_api_generator_astconsumer(CompilerInstance& compiler_instance, rpc_api_generator& abi_gen)
      :abi_gen(abi_gen)
      {
         abi_gen.set_compiler_instance(compiler_instance);
      }

      void HandleTagDeclDefinition(TagDecl* tag_decl) override {
         abi_gen.handle_tagdecl_definition(tag_decl);
      }
   };


   struct find_contento_rpc_api_macro_action : public PreprocessOnlyAction {

         string&                    contract;
         rpc_api_macro_def_result&  actions;
         const string&              abi_context;

         find_contento_rpc_api_macro_action(string& contract, rpc_api_macro_def_result& actions, const string& abi_context
            ): contract(contract),
            actions(actions), abi_context(abi_context) {
         }

         struct callback_handler : public PPCallbacks {

            CompilerInstance& compiler_instance;
            find_contento_rpc_api_macro_action& act;

            callback_handler(CompilerInstance& compiler_instance, find_contento_rpc_api_macro_action& act)
            : compiler_instance(compiler_instance), act(act) {}

            string remove_namespace(const string& full_name) {
               int i = full_name.size();
               int on_spec = 0;
               int colons = 0;
               while( --i >= 0 ) {
                  if( full_name[i] == '>' ) {
                     ++on_spec; colons=0;
                  } else if( full_name[i] == '<' ) {
                     --on_spec; colons=0;
                  } else if( full_name[i] == ':' && !on_spec) {
                     if (++colons == 2)
                        return full_name.substr(i+2);
                  } else {
                     colons = 0;
                  }
               }
               return full_name;
            }

            void MacroExpands (const Token &token, const MacroDefinition &md, SourceRange range, const MacroArgs *args) override {

               auto* id = token.getIdentifierInfo();
               if( id == nullptr ) return;

               bool is_derived_struct = id->getName() == "FC_REFLECT_DERIVED";

               if( !is_derived_struct &&
                   id->getName() != "FC_API" &&
                   id->getName() != "FC_REFLECT"
                    ) return;


               const auto& sm = compiler_instance.getSourceManager();
               auto file_name = sm.getFilename(range.getBegin());
               if ( !act.abi_context.empty() && !file_name.startswith(act.abi_context) ) {
                  return;
               }

               ABI_ASSERT( md.getMacroInfo()->getNumArgs() == 2 || md.getMacroInfo()->getNumArgs() == 3 );

               clang::SourceLocation b(range.getBegin()), _e(range.getEnd());
               clang::SourceLocation e(clang::Lexer::getLocForEndOfToken(_e, 0, sm, compiler_instance.getLangOpts()));
               auto macrostr = string(sm.getCharacterData(b), sm.getCharacterData(e)-sm.getCharacterData(b));

               // trim all comments
               regex r_multi_line_comment(R"(/\*[\s\S]*?\*/)");
               regex r_single_line_comment(R"(//.*)");

               macrostr = regex_replace(macrostr, r_multi_line_comment, "");
               macrostr = regex_replace(macrostr, r_single_line_comment, "");

               regex r_new_line(R"(\s)");
               macrostr = regex_replace(macrostr, r_new_line, "");
               std::cout << "parser: " << macrostr << std::endl;

               string regx_str;
               if ( !is_derived_struct )
                  regx_str = string(id->getName()) + R"(\s*\(\s*(.+?)\s*,((?:.+?)*)\s*\))" ;
               else
                  regx_str = string(id->getName()) + R"(\s*\(\s*(.+?)\s*,\s*(.+?)\s*,((?:.+?)*)\s*\))" ;

               regex r(regx_str);
               smatch smatch;
               auto res = regex_search(macrostr, smatch, r);
               ABI_ASSERT( res );

               act.contract = remove_namespace(smatch[1].str());

               auto actions_str = smatch[is_derived_struct ? 3 : 2].str();
               boost::trim(actions_str);

               vector<string> split_result;
               if ( actions_str.size() > 0 ){
                  actions_str = actions_str.substr(1);
                  actions_str.pop_back();
                  boost::remove_erase_if(actions_str, boost::is_any_of(" ("));
                  boost::split(split_result, actions_str, boost::is_any_of(")"));
               }

               if ( is_derived_struct ){
                  rpc_api_macro_def_structs def_structs;
                  string base_name = smatch[2].str();
                  boost::remove_erase_if(base_name, boost::is_any_of(" ()"));

                  def_structs.members     = split_result;
                  def_structs.base_struct = remove_namespace(base_name);

                  act.actions.structs_map[act.contract] = def_structs;
               } else if ( id->getName() == "FC_API" ) {
                  ABI_ASSERT(split_result.size() > 0);
                  act.actions.functions_map[act.contract] = split_result;
               } else {
                  rpc_api_macro_def_structs def_structs;
                  def_structs.members     = split_result;

                  act.actions.structs_map[act.contract] = def_structs;
               }
            }
         };

         void ExecuteAction() override {
            getCompilerInstance().getPreprocessor().addPPCallbacks(
               llvm::make_unique<callback_handler>(getCompilerInstance(), *this)
            );
            PreprocessOnlyAction::ExecuteAction();
         };

   };

  
   class generate_rpc_api_action : public ASTFrontendAction {

      private:
         set<string> parsed_templates;
         rpc_api_generator abi_gen;

      public:

         generate_rpc_api_action(bool verbose, bool opt_sfs, string abi_context,
                             abi_def& output, const string& contract, const rpc_api_macro_def_result& actions) {
            
            abi_gen.set_output(output);
            abi_gen.set_verbose(verbose);
            abi_gen.set_abi_context(abi_context);
            abi_gen.set_target_contract(actions);

            if(opt_sfs)
               abi_gen.enable_optimizaton(rpc_api_generator::OPT_SINGLE_FIELD_STRUCT);
         }

      protected:
         std::unique_ptr<ASTConsumer> CreateASTConsumer(CompilerInstance& compiler_instance,
                                                        llvm::StringRef) override {
            return llvm::make_unique<rpc_api_generator_astconsumer>(compiler_instance, abi_gen);
         }
   };

} //ns contento

#pragma pop_macro("N")
