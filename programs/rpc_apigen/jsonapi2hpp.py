#!/usr/bin/python
import json
import sys

api_array = {}

g_defined_struct = {}
g_defined_typedef = {}

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
    global g_defined_struct
    result2 = ''
    for info in structs_info:
        serial = ''
        if info['isunion'] == False:
            if info['base'] != '':
                result = 'struct {0} : public {1} {{\n'.format(info['name'],info['base'])
                serial = '\n\tCOSLIB_SERIALIZE_DERIVED( {0}, {1},'.format(info['name'], info['base'] )
            else:
                result = 'struct {0} {{\n'.format(info['name'] )
                serial = '\n\tCOSLIB_SERIALIZE( {0}, '.format(info['name'])


            serial += print_struct_serial(info['fields']) + ' )'
            result = '{0}{1} \n {2} \n}};\n'.format(result, print_struct_fields(info['fields']),  serial )
            result2 += result + '\n'
        else:
            #result2 = 'uuuu'
            unions = ','.join( map( lambda field:'{0}'.format(field['type']), info['fields']) )
            result2 += 'typedef static_variant<{0}>\n\t{1};\n\n\n'.format( unions, info['name'])

        g_defined_struct[ info['name'] ] = info['name']

        result2 += print_new_defined_typedef( api_array['types'] )

    return result2

def print_functions( className, funcs_info ):

    result = 'class {0} {{\npublic:\n\n\tstd::string api_name()const{{ return std::string("{0}"); }}\n\n'.format(className)

    for info in funcs_info:
        retstr = type2cxx(info['ret']['type'])
        params = join_func_params(info['fields'])
        func_name = info['name']
        
        func_define = '\t{0} {1}{2} {{\n\t\tSTUB_API( RET_TYPE({4}::{1}),{3});\n\t}}\n'.format(retstr,func_name,params,join_func_params_serial(info['fields']), className)
        result += func_define + '\n'

    result += '};'
    return result

def print_classes( clss_info ):
    result = ""
    for info in clss_info :
        result += print_functions( info['name'], info['functions']) + '\n\n'
    return result

def print_typedef(typedef_infos):
    global g_defined_typedef
    result = ''
    for info in typedef_infos:
        if check_typedef_is_struct( info['type'] ) == False:
            result += 'using {0}\t = {1};\n'.format(type2cxx(info['new_type_name']), type2cxx(info['type']))
            g_defined_typedef[ info['new_type_name'] ] = info['new_type_name']
    return result

def print_new_defined_typedef(typedef_infos):
    global g_defined_typedef
    result = ''
    for info in typedef_infos:
        if info['new_type_name'] in g_defined_typedef:
            continue

        if check_typedef_is_all_defined( info['type'] ) == True:
            result += 'using {0}\t = {1};\n\n'.format(type2cxx(info['new_type_name']), type2cxx(info['type']))
            g_defined_typedef[ info['new_type_name'] ] = info['new_type_name']
    return result


def get_all_relation_types( typename ):
    list_info = []
    list_info.append( typename )
    if typename.endswith('[]'):
        list_info += get_all_relation_types(typename[0:-2])
    elif typename.startswith('{') and typename.endswith('}'):
        key_value   = typename[1:-1]
        key_str     = key_value.split(',')[0]
        value_str     = key_value.split(',')[1]

        list_info +=  get_all_relation_types(key_str)
        list_info +=  get_all_relation_types(value_str)

    return list_info

def check_typedef_is_all_defined( new_type ):
    typelists = get_all_relation_types( new_type )

    for type_found in typelists:
        if check_single_type_is_struct( type_found ):
            if type_found not in g_defined_struct:
                return False

    return True

def check_single_type_is_struct( single_type ):
    for types in api_array['structs']:
        if types['name'] == single_type:
            return True
    return False

def check_typedef_is_struct( old_type ):
    typelists = get_all_relation_types( old_type )

    for type_found in typelists:
        for types in api_array['structs']:
            if types['name'] == type_found:
                return True

    return False

if __name__ == "__main__":
    f = open(sys.argv[1])
    contents = f.read()
    f.close()

    api_array = json.loads(contents)

    result  = "\n";

    result += '#pragma once\n\n'
    result += '#include <iostream>\n'
    result += '#include <map>\n'
    result += '#include <vector>\n'
    result += '#include <cosiolib/cosio.hpp>\n'
    result += '#include <cosiolib/static_variant.hpp>\n'
    result += '#include <cosiolib/content_util.hpp>\n'

    result += '\n\n'
    result += 'namespace cosio { \n\n'
    result += 'using std::vector;\nusing std::string;\nusing std::map;\n\n\n'

    result += print_typedef(api_array['types']) + '\n'
    result += print_structs(api_array['structs']) + '\n'
    result += print_classes(api_array['classes']) + '\n'

    result += '}\n\n'
    #print result

    fo = open(sys.argv[2], "w")
    fo.write( result )
    fo.close()

    #print(api_array['types'])
