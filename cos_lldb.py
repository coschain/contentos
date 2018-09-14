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


class contento__protocol__operation:
	@classmethod
	def apply(clz, debugger, target_class_name):
		debugger.HandleCommand("type synthetic add %s --python-class %s.%s" % (target_class_name, clz.__module__, clz.__name__))
		debugger.HandleCommand("type synthetic add --python-class %s.%s -x \"^fc::static_variant<.+>$\"" % (clz.__module__, clz.__name__))
		debugger.HandleCommand("type synthetic add --python-class %s.%s -x \"^const fc::static_variant<.+>$\"" % (clz.__module__, clz.__name__))

	def __init__(self, valobj, internal_dict):
		self.valobj = valobj
		self.val = None
		self.parse()
		
	def parse(self):
		if self.valobj.IsValid() and self.valobj.size > 0:
			t = self.valobj.type
			self.real_parse(t.GetTypedefedType() if t.IsTypedefType() else t)

	def real_parse(self, t):
		self.val = None
		idx = self.valobj.GetChildMemberWithName("_tag").signed
		sv_typename = t.name
		pos = sv_typename.find("fc::static_variant<")
		if pos >= 0 and sv_typename.endswith(">"):
			types = map(str.strip, sv_typename[pos + 19:-1].split(","))
			if 0 <= idx < len(types):
				op_type = self.valobj.CreateValueFromExpression("_tmp_ptr_", "(%s*)0" % types[idx]).type.GetPointeeType()
				self.val = self.valobj.CreateValueFromData("value", self.valobj.data, op_type)

	def get_value(self):
		return self.val

	def num_children(self):
		return 1 if self.get_value() else 0

	def has_children(self):
		return self.num_children() > 0

	def get_child_index(self, name):
		return 0 if name == "value" else None

	def get_child_at_index(self, index):
		return self.val if index == 0 else None

	def update(self):
		if self.valobj.changed:
			self.parse()


class contento__protocol__asset:
	@classmethod
	def apply(clz, debugger, target_class_name):
		debugger.HandleCommand('type summary add --python-function %s.%s.asset_summary %s' % (clz.__module__, clz.__name__, target_class_name))

	@staticmethod
	def asset_summary(valobj, internal_dict):
		r = ""
		if valobj.IsValid() and valobj.size > 0:
			amount = valobj.GetChildMemberWithName("amount").GetChildMemberWithName("value").data.sint64s[0]
			symbol = valobj.GetChildMemberWithName("symbol").data.uint64s[0]
			symbol_name, digits = "", symbol & 0xff
			divider = 10 ** digits
			symbol >>= 8
			while symbol != 0:
				symbol_name += chr(symbol & 0xff)
				symbol >>= 8
			fmts = "%%d.%%0%dd %s" % (digits, symbol_name)
			r = fmts % (amount / divider, amount % divider)
		return r


class contento__protocol__name:
	@classmethod
	def apply(clz, debugger, target_class_name):
		debugger.HandleCommand('type summary add --python-function %s.%s.asset_summary %s' % (clz.__module__, clz.__name__, target_class_name))

	@staticmethod
	def asset_summary(valobj, internal_dict):
		charmap = ".12345abcdefghijklmnopqrstuvwxyz"
		r = ["."] * 13
		if valobj.IsValid() and valobj.size > 0:
			value = valobj.GetChildMemberWithName("value").data.uint64s[0]
			for i in xrange(13):
				r[12 - i] = charmap[value & (0x0f if i == 0 else 0x1f)]
				value >>= 4 if i == 0 else 5
		return '"%s"' % "".join(r).rstrip(".")


class contento__protocol__namex:
	@classmethod
	def apply(clz, debugger, target_class_name):
		debugger.HandleCommand('type summary add --python-function %s.%s.asset_summary %s' % (clz.__module__, clz.__name__, target_class_name))

	@staticmethod
	def uint64_to_string(ui64):
		r = list()
		while ui64 > 0:
			r.append(chr(ui64 & 0xff))
			ui64 >>= 8
		return "".join(r)

	@staticmethod
	def asset_summary(valobj, internal_dict):
		r = ""
		if valobj.IsValid() and valobj.size > 0:
			lo = valobj.GetChildMemberWithName("value").GetChildMemberWithName("lo").data.uint64s[0]
			hi = valobj.GetChildMemberWithName("value").GetChildMemberWithName("hi").data.uint64s[0]
			if lo > 0:
				r += contento__protocol__namex.uint64_to_string(lo) + contento__protocol__namex.uint64_to_string(hi)
		return '"%s"' % r

######## module entry point ########

def __lldb_init_module(debugger, dictionary):
	Helper.add_handler("fc::variant", fc__variant)
	Helper.add_handler("fc::variant_object", fc__variant_object)
	Helper.add_handler("fc::variant_object::entry", fc__variant_object__entry)
	Helper.add_handler("contento::protocol::operation", contento__protocol__operation)
	Helper.add_handler("contento::protocol::asset", contento__protocol__asset)
	Helper.add_handler("contento::protocol::name", contento__protocol__name)
	Helper.add_handler("contento::protocol::namex", contento__protocol__namex)
	Helper.apply(debugger)


######## installer ########

if __name__ == "__main__":
	from os import path
	import sys

	lldbinit = path.expanduser("~/.lldbinit")
	me = "command script import %s\n" % path.abspath(__file__)
	lines = []
	try:
		f = open(lldbinit)
		lines = f.readlines()
		f.close()
	except:
		pass
	if me in lines:
		print "already installed."
		pass
	else:
		if len(lines) > 0:
			try:
				f = open(lldbinit + ".bak", "w")
				f.write("".join(lines))
				f.close()
				print "old .lldbinit backed up as %s" % (lldbinit + ".bak")
			except:
				pass
		try:
			f = open(lldbinit, "w")
			f.write(me)
			f.close()
			print "installed to %s" % lldbinit
		except:
			pass
