#!/usr/bin/python
import json

g_output = ''
g_stucts_depend = ''
g_depend_exist  = {}
api_array = {}

def type2cxx(typename):
    if typename.endswith('[]'):
        add_depend_typeinfo( type2cxx(typename[0:-2]) )
        return 'vector<' + type2cxx(typename[0:-2]) + '>'
    elif typename.startswith('{') and typename.endswith('}'):
        key_value   = typename[1:-1]
        key_str     = type2cxx(key_value.split(',')[0])
        value_str     = type2cxx(key_value.split(',')[1])

        add_depend_typeinfo(key_str)
        add_depend_typeinfo(value_str)

        return 'map<' + key_str + ',' + value_str + '>'
    else:
        return typename

def print_struct_fields( struct_fields_info ):
    for field in struct_fields_info:
        add_depend_typeinfo(field['type'])

    return '\n'.join( map( lambda info: '\t{0}\t\t{1};'.format(type2cxx(info['type']),info['name']), struct_fields_info) )

def print_struct_serial( struct_fields_info ):
    return ''.join( map( lambda info: '({0})'.format(info['name']), struct_fields_info) )

def join_func_params( params_info ):
    params_list = ','.join( map( lambda arg: ' const {0}& {1}'.format( type2cxx(arg['type']), arg['name']), params_info ) )
    return '({})'.format(params_list)

def join_func_params_serial( params_info ):
    return ''.join( map( lambda info:' << {0}'.format(info['name']), params_info) )

def print_ops_define():
    global g_stucts_depend
    ops = ','.join( api_array['operations'] )
    g_stucts_depend += '\n\ntypedef static_variant<{0}> \n\toperation;\n\n'.format(ops)

def add_depend_typeinfo( type_name ):
    global g_depend_exist
    global g_stucts_depend
    if type_name in g_depend_exist:
        return

    g_depend_exist[type_name] = type_name
    for struct in api_array['structs'] :
        if struct['name'] == type_name:
            g_stucts_depend += '\n//  Found depend for {0}\n'.format(type_name)
            print_struct( struct )

    if type_name == 'operation':
        print_ops_define()

def check_struct_define_in_json( typename ):
    if typename.endswith('[]'):
        return check_struct_define_in_json(typename[0:-2])
    elif typename.startswith('{') and typename.endswith('}'):
        key_value   = typename[1:-1]
        key_str     = type2cxx(key_value.split(',')[0])
        value_str     = type2cxx(key_value.split(',')[1])

        if check_struct_define_in_json( key_str ):
            return True
        
        return check_struct_define_in_json(value_str)
    for struct in api_array['structs'] :
        if struct['name'] == typename:
            return True    
    return False

def check_typedef_define_in_json( typename ):
    if typename.endswith('[]'):
        return check_typedef_define_in_json(typename[0:-2])
    elif typename.startswith('{') and typename.endswith('}'):
        key_value   = typename[1:-1]
        key_str     = type2cxx(key_value.split(',')[0])
        value_str     = type2cxx(key_value.split(',')[1])

        if check_typedef_define_in_json( key_str ):
            return True
        
        return check_typedef_define_in_json(value_str)

    for struct in api_array['types'] :
        if struct['type'] == typename:
            return True    
    return False

def print_struct( info ):
    global g_stucts_depend
    global g_depend_exist

    serial = ''
    result = ''
    if info['base'] != '':
        add_depend_typeinfo(info['base'])
        result = 'struct {0} : public {1} {{\n'.format(info['name'],info['base'])
        serial = '\n\tEOSLIB_SERIALIZE_DERIVED( {0}, {1},'.format(info['name'], info['base'] )
    else:
        result = 'struct {0} {{\n'.format(info['name'] )
        serial = '\n\tEOSLIB_SERIALIZE( {0}, '.format(info['name'])


    serial += print_struct_serial(info['fields']) + ' );'
    result = '{0}{1} \n {2} \n}};\n\n'.format(result, print_struct_fields(info['fields']),  serial )
    result += print_typedef( info['name'] ) + '\n'
    #if check_typedef_define_in_json( info['name'] ) :


    g_stucts_depend += result
    g_depend_exist[info['name']] = info['name']


def print_structs( structs_info ):
    for info in structs_info:
        print_struct(info)

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

def print_typedefs(typedef_infos):
    result = ''
    for info in typedef_infos:
        if check_struct_define_in_json( info['type'] ) == False:
            result += 'using {0}\t = {1};\n'.format(type2cxx(info['new_type_name']), type2cxx(info['type']))
    return result

def print_typedef( type):
    result = ''
    for info in api_array['types']:
        if info['type'] == type:
            result += 'using {0}\t = {1};\n'.format(type2cxx(info['new_type_name']), type2cxx(info['type']))
    return result    
    
if __name__ == "__main__":
    f = open('/Users/yykingking/apixx.abi')
    contents = f.read()
    f.close()

    api_array = json.loads(contents)

    g_output  = '#include <iostream>\n'
    g_output += '#include <map>\n'
    g_output += '#include <vector>\n'
    g_output += '#include <eosiolib/eosiolib.hpp>\n'

    g_output += '\n\n'
    g_output += 'namespace eosio { \n\n'
    g_output += 'using std::vector;\nusing std::string;\nusing std::map;\n\n\n'

    g_output += print_typedefs(api_array['types']) + '\n'

    print_structs(api_array['structs'])
    g_output += g_stucts_depend
    #g_output += print_structs(api_array['structs']) + '\n'
    g_output += print_classes(api_array['classes']) + '\n'

    g_output += '}\n\n'
    print g_output
    #print(api_array['types'])
