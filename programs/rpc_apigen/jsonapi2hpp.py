#!/usr/bin/python
import json


def type2cxx(typename):
    if typename.endswith('[]'):
        return 'vector<' + type2cxx(typename[0:-2]) + '>'
    elif typename.startswith('{') and typename.endswith('}'):
        key_value   = typename[1:-1]
        key_str     = type2cxx(key_value.split(',')[0])
        value_str     = type2cxx(key_value.split(',')[1])

        return 'map<' + key_str + ',' + value_str + '>'
    else:
        return typename

def print_struct_fields( struct_fields_info ):
    return '\n'.join( map( lambda info: '\t{0}\t\t{1};'.format(type2cxx(info['type']),info['name']), struct_fields_info) )

def print_struct_serial( struct_fields_info ):
    return ''.join( map( lambda info: '({0})'.format(info['name']), struct_fields_info) )

def join_func_params( params_info ):
    params_list = ','.join( map( lambda arg: ' const {0}& {1}'.format( type2cxx(arg['type']), arg['name']), params_info ) )
    return '({})'.format(params_list)

def join_func_params_serial( params_info ):
    return ''.join( map( lambda info:' << {0}'.format(info['name']), params_info) )

def print_structs( structs_info ):
    result2 = ''
    for info in structs_info:
        serial = ''
        if info['base'] != '':
            result = 'struct {0} : public {1} {{\n'.format(info['name'],info['base'])
            serial = '\n\tEOSLIB_SERIALIZE_DERIVED( {0}, {1},'.format(info['name'], info['base'] )
        else:
            result = 'struct {0} {{\n'.format(info['name'] )
            serial = '\n\tEOSLIB_SERIALIZE( {0}, '.format(info['name'])


        serial += print_struct_serial(info['fields']) + ' );'
        result = '{0}{1} \n {2} \n}};\n'.format(result, print_struct_fields(info['fields']),  serial )
        result2 += result + '\n'
    return result2

def print_functions( className, funcs_info ):

    result = 'class {0} {{\n\n\tstd::string get_name()const{{ return std::string("{0}"); }}\n\n'.format(className)

    for info in funcs_info:
        retstr = type2cxx(info['ret']['type'])
        params = join_func_params(info['fields'])
        func_name = info['name']
        
        func_define = '\t{0} {1}{2} {{\n\t\tSTUB_API({0},{3});\n\t}}\n'.format(retstr,func_name,params,join_func_params_serial(info['fields']))
        result += func_define + '\n'

    result += '};'
    return result

def print_classes( clss_info ):
    result = ""
    for info in clss_info :
        result += print_functions( info['name'], info['functions']) + '\n\n'
    return result

def print_typedef(typedef_infos):
    result = ''.join( map( lambda info: 'using {0}\t = {1};\n'.format(type2cxx(info['new_type_name']), type2cxx(info['type'])), typedef_infos ) )
    return result
    
if __name__ == "__main__":
    f = open('/Users/yykingking/apixx.abi')
    contents = f.read()
    f.close()

    api_array = json.loads(contents)

    result  = '#include <iostream>\n'
    result += '#include <map>\n'
    result += '#include <vector>\n'
    result += '#include <eosiolib/eosiolib.hpp>\n'

    result += '\n\n'
    result += 'namespace eosio { \n\n'
    result += 'using std::vector;\nusing std::string;\nusing std::map;\n\n\n'

    result += print_typedef(api_array['types']) + '\n'
    result += print_structs(api_array['structs']) + '\n'
    result += print_classes(api_array['classes']) + '\n'

    result += '}  }\n\n'
    print result
    #print(api_array['types'])
