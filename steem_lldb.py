#!/usr/bin/env python
# -*- coding: utf-8 -*-

class Helper:
	handlers = {}

	@staticmethod
	def add_handler(clazz_name, handler_clazz):
		Helper.handlers[clazz_name] = handler_clazz

	@staticmethod
	def apply(debugger):
		for t, c in Helper.handlers.iteritems():
			c.apply(debugger, t)

	@staticmethod
	def get_std_namespace(target):
		result = None
		for ns in ["std", "std::__1"]:
			try:
				t = target.CreateValueFromExpression("_", "(%s::string*)0" % ns).type
			except:
				t = None
			if t:
				result = ns[:]
				break
		return result


######## type formatters ########


class fc__variant:

	@classmethod
	def apply(clz, debugger, target_class_name):
		debugger.HandleCommand("type synthetic add %s --python-class %s.%s" % (target_class_name, clz.__module__, clz.__name__))
		debugger.HandleCommand('type summary add --summary-string "${var.value}" %s' % target_class_name)

	def __init__(self, valobj, internal_dict):
		self.valobj = valobj
		self.val = None
		std_ns = Helper.get_std_namespace(valobj.target)
		self.types = ["long long", "unsigned long long", "double", "bool", 
			"%s::string*" % std_ns, 
			"fc::variants*", 
			"fc::variant_object*",
			"fc::blob*"
			]
		self.parse()

	def parse(self):
		typeid = 0
		try:
			typeid = self.valobj.GetChildMemberWithName("_type").data.sint8s[-1]
			val = self.valobj.GetChildMemberWithName("_data")
		except:
			typeid = 0
		if 0 < typeid < 9:
			real_type = self.valobj.CreateValueFromExpression("_tmp_ptr_", "(%s)0" % self.types[typeid - 1]).type
			real_val = self.valobj.CreateValueFromData("_tmp_val_", val.data, real_type)
			while real_val.TypeIsPointerType():
				real_val = real_val.deref
			self.val = self.valobj.target.CreateValueFromData("value", real_val.data, real_val.type)
		elif typeid == 0:
			self.val = self.valobj.target.CreateValueFromExpression("value", "(void*)0")

	def get_value(self):
		return self.val

	def num_children(self):
		return 1 if self.val else 0

	def has_children(self):
		return self.num_children() > 0

	def get_child_index(self, name):
		return 0 if name == "value" else None

	def get_child_at_index(self, index):
		return self.val if index == 0 else None

	def update(self):
		if self.valobj.changed:
			self.parse()


class fc__variant_object:
	@classmethod
	def apply(clz, debugger, target_class_name):
		debugger.HandleCommand("type synthetic add %s --python-class %s.%s" % (target_class_name, clz.__module__, clz.__name__))
		debugger.HandleCommand('type summary add --summary-string "size=${var%%#}" %s' % target_class_name)

	def __init__(self, valobj, internal_dict):
		self.valobj = valobj
		self.count = 0
		self.entries = []
		self.parse()
		
	def parse(self):
		self.count, self.entries = 0, []
		if self.valobj.IsValid() and self.valobj.size > 0:
			vec_ptr = self.valobj.GetChildMemberWithName("_key_value").GetChildMemberWithName("__ptr_")
			if vec_ptr.IsValid() and vec_ptr.value:
				entry_type = "fc::variant_object::entry"
				begin = self.valobj.target.CreateValueFromExpression("begin", "*(%s**)%s" % (entry_type, vec_ptr.value))
				end = self.valobj.target.CreateValueFromExpression("end", "*(%s**)(%s + sizeof(void*))" % (entry_type, vec_ptr.value))
				count = self.valobj.target.CreateValueFromExpression("count", "(%s - %s) / sizeof(%s)" % (end.value, begin.value, entry_type)).signed
				self.count = min(max(count, 0), 1024)
				self.entries = map(lambda i: begin.GetValueForExpressionPath("[%d]" % i), range(self.count))

	def num_children(self):
		return self.count

	def has_children(self):
		return self.num_children() > 0

	def get_child_index(self, name):
		r = None
		if name.startswith("[") and name.endswith("]"):
			r = int(name[1:-1])
			if r >= self.count:
				r = None
		return r

	def get_child_at_index(self, index):
		return self.entries[index] if index < self.count else None

	def update(self):
		if self.valobj.changed:
			self.parse()


class fc__variant_object__entry:
	@classmethod
	def apply(clz, debugger, target_class_name):
		debugger.HandleCommand('type summary add --inline-children %s' % target_class_name)


######## module entry point ########

def __lldb_init_module(debugger, dictionary):
	Helper.add_handler("fc::variant", fc__variant)
	Helper.add_handler("fc::variant_object", fc__variant_object)
	Helper.add_handler("fc::variant_object::entry", fc__variant_object__entry)
	Helper.apply(debugger)


######## installer ########

if __name__ == "__main__":
	from os import path
	import sys

	lldbinit = path.expanduser("~/.lldbinit")
	me = path.abspath(__file__)
	lines = []
	try:
		f = open(lldbinit)
		lines = f.readlines()
		f.close()
	except:
		pass
	lines = filter(lambda x: me not in x, lines)

	if "uninstall" not in sys.argv[1:]:
		lines.append("command script import %s" % me)

	try:
		f = open(lldbinit, "w")
		f.write("\n".join(lines))
		f.close()
	except:
		pass
