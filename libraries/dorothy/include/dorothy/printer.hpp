#include <iostream>

namespace dorothy {

    class AccountPrinter{
        public:
            template<typename Iterator>
            void print(TablePrinter& tp, Iterator current)
            {
                tp << current -> id._id << std::string(current -> name) << current -> balance.to_string()
                    << current -> vesting_shares.to_string() << current -> next_vesting_withdrawal.sec_since_epoch()
                    << std::string(current -> to_withdraw) << std::string(current -> withdrawn);
            }
    };

    class CommentPrinter {
        public:
            template<typename Iterator>
            void print(TablePrinter& tp, Iterator current)
            {
                tp << (current->id._id);
                (current -> root_comment == current -> id) ? tp << "Yes":tp << "No";
                tp << std::string(current -> parent_author) << current -> parent_permlink << 
                std::string(current -> author) << current -> permlink << current -> title 
                << std::string(current -> net_rshares)
                << current -> created.sec_since_epoch() << current -> cashout_time.sec_since_epoch();
            }
    };

    class DynamicGlobalPropertyPrinter {
        public:
            template<typename Iterator>
            void print(TablePrinter& tp, Iterator current)
            {
                tp << (current->id._id) << (current -> head_block_number) << (current -> time.sec_since_epoch()) << 
                (std::string(current -> current_witness)) << (current -> virtual_supply.to_string()) << 
                (current ->current_supply.to_string()) << (current -> total_vesting_shares.to_string()) << 
                (current -> last_irreversible_block_num);
            }
    };
}