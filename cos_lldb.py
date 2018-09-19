#!/usr/bin/env python
# -*- coding: utf-8 -*-

# This script is lldb data formatter for Contentos C++ project.
# Install it by running it. ~/.lldbinit will be modified so that lldb loads formatters when launching.

import re
import hashlib
from datetime import datetime
import binascii

######## helper ########

class Helper(object):

	# get the std namespace 
	@staticmethod
	def std_namespace(target):
		r = None
		for ns in ["std", "std::__1"]:
			try:
				if target.CreateValueFromExpression("_", "(%s::string*)0" % ns).type:
					r = ns[:]
					break
			except:
				pass
		return r
	
	b58_alphabet = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"

	@staticmethod
	def b58encode(data):
		num = reduce(lambda s, c: (s << 8) + (ord(c) & 0xff), data, 0)
		base_count = len(Helper.b58_alphabet)
		r = []
		while num > 0:
			r.append(Helper.b58_alphabet[num % base_count])
			num /= base_count
		return "".join([c for c in reversed(r)])

	@staticmethod
	def key_to_wif(sha256_checksum):
		data_to_hash = "\x80" + sha256_checksum[:32]
		check = hashlib.sha256(hashlib.sha256(data_to_hash).digest()).digest()[:4]
		return Helper.b58encode(data_to_hash + check)


######## formatter bases ########


# base class for all formatters.
class baseFormatter(object):
	@classmethod
	def apply(clz, debugger, target_clazz_name):
		raise NotImplementedError


# base class for formatters that change summary string only.
class baseSummaryFormatter(baseFormatter):
	@classmethod
	def apply(clz, debugger, target_clazz_name):
		debugger.HandleCommand("type summary add --python-function %s.%s.summary %s" % (clz.__module__, clz.__name__, target_clazz_name))

	# override this and return the summary string based on given value.
	@staticmethod
	def summary(valobj, internal_dict):
		raise NotImplementedError


# base class for formatters that create synthetic children.
class baseSyntheticFormatter(baseFormatter):
	@classmethod
	def apply(clz, debugger, target_clazz_name):
		debugger.HandleCommand("type synthetic add %s --python-class %s.%s" % (target_clazz_name, clz.__module__, clz.__name__))
	
	# deal with special case of index comparasion. "[10]" must be greater than "[2]".
	idx_name_pat = re.compile(r"^\[\d+\]$")
	
	@staticmethod
	def name_cmp(name1, name2):
		idx_pat = baseSyntheticFormatter.idx_name_pat
		if idx_pat.match(name1) and idx_pat.match(name2):
			return cmp(int(name1[1:-1]), int(name2[1:-1]))
		else:
			return cmp(name1, name2)

	def __init__(self, valobj, internal_dict):
		self.valobj = valobj
		self.children_names = list()
		self.children = dict()
		self.ever_parsed = False
	
	# override this and fill in self.children dict.
	def parse(self):
		pass

	def is_valid(self):
		return self.valobj.IsValid() and self.valobj.size > 0
	
	def num_children(self):
		return len(self.children_names)

	def has_children(self):
		return self.num_children() > 0

	def get_child_index(self, name):
		return self.children_names.index(name)

	def get_child_at_index(self, index):
		return self.children.get(self.children_names[index])

	def update(self):
		need_parse = self.valobj.changed or not self.ever_parsed
		if need_parse:
			self.children = dict()
			if self.is_valid():
				self.parse()
			self.children_names = sorted(self.children.keys(), cmp=baseSyntheticFormatter.name_cmp)
			self.ever_parsed = True
		return need_parse


# base class for formatters suitable with std::vector-like value types.
class baseArrayFormatter(baseSyntheticFormatter):
	@classmethod
	def apply(clz, debugger, target_clazz_name):
		super(baseArrayFormatter, clz).apply(debugger, target_clazz_name)
		prefix = clz.summary_prefix()
		debugger.HandleCommand('type summary add --summary-string "%s size=${var%%#}" %s' % (prefix, target_clazz_name))

	# override this and return the prefix of summary string.
	# summary string will be like "${prefix} size=xxx"
	@classmethod
	def summary_prefix(clz):
		return "array"
	
	# override this and return the pointer value of the first element.
	def begin_pointer(self):
		return None

	# override this and return the pointer value of the last+1 element.
	def end_pointer(self):
		return None

	def parse(self):
		try:
			begin, end = self.begin_pointer(), self.end_pointer()
			element_type = begin.type.GetPointeeType()
			element_size = element_type.GetByteSize()
			if begin.IsValid() and end.IsValid() and element_size > 0:
				count = self.valobj.CreateValueFromExpression("_count_", "(%s-%s)/%d" % (end.value, begin.value, element_size)).signed
				if count > 0:
					for i in xrange(count):
						val_name = "[%d]" % i
						self.children[val_name] = begin.CreateChildAtOffset(val_name, i * element_size, element_type)
		except:
			pass


######## formatters ########

class fc__variant(baseSyntheticFormatter):
	@classmethod
	def apply(clz, debugger, target_clazz_name):
		super(fc__variant, clz).apply(debugger, target_clazz_name)
		debugger.HandleCommand('type summary add --summary-string "${var.value}" %s' % target_clazz_name)

	def __init__(self, valobj, internal_dict):
		super(fc__variant, self).__init__(valobj, internal_dict)
		std = Helper.std_namespace(valobj.target)
		self.sub_types = [
			"void*",
			"long long",
			"unsigned long long",
			"double",
			"bool",
			std + "::string*",
			"fc::variants*",
			"fc::variant_object*",
			"fc::blob*",
		]

	def parse(self):
		typeid = self.valobj.GetChildMemberWithName("_type").data.sint8s[-1]
		val = self.valobj.GetChildMemberWithName("_data")
		if 0 <= typeid < len(self.sub_types):
			subtype = self.sub_types[typeid]
			if typeid > 0:
				real_type = self.valobj.CreateValueFromExpression("_tmp_", "(%s)0" % subtype).type
				real_val = self.valobj.CreateValueFromData("_tmp_val_", val.data, real_type)
				while real_val.TypeIsPointerType():
					real_val = real_val.deref
				self.children["value"] = self.valobj.CreateValueFromData("value", real_val.data, real_val.type)
			else:
				self.children["value"] = self.valobj.CreateValueFromExpression("value", "nullptr")


# fc::variants is just a typedef of std::vector<fc::variant>.
# it should be supported by built-in formatters for std::vector, but lldb sometimes can't handle fc::variants properly.
# so that we have to add an explicit formatter here.
class fc__variants(baseArrayFormatter):
	def begin_pointer(self):
		return self.valobj.GetChildMemberWithName("__begin_")

	def end_pointer(self):
		return self.valobj.GetChildMemberWithName("__end_")


# fc::variant_object's _key_value is an std::shared_ptr<std::vector<fc::variant_object::entry>>
class fc__variant_object(baseArrayFormatter):
	@classmethod
	def summary_prefix(clz):
		return "object"

	def begin_pointer(self):
		return self.valobj.GetChildMemberWithName("_key_value").GetChildMemberWithName("__ptr_").GetChildMemberWithName("__begin_")

	def end_pointer(self):
		return self.valobj.GetChildMemberWithName("_key_value").GetChildMemberWithName("__ptr_").GetChildMemberWithName("__end_")


class fc__variant_object__entry(baseFormatter):
	@classmethod
	def apply(clz, debugger, target_clazz_name):
		debugger.HandleCommand('type summary add --inline-children %s' % target_clazz_name)


# fc::blob { std::vector<char> data; }
class fc__blob(baseFormatter):
	@classmethod
	def apply(clz, debugger, target_clazz_name):
		debugger.HandleCommand('type summary add --summary-string "blob ${var.data}" %s' % target_clazz_name)


class contento__protocol__asset(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			amount = valobj.GetChildMemberWithName("amount").GetChildMemberWithName("value").data.sint64s[0]
			symbol = valobj.GetChildMemberWithName("symbol").data.uint64s[0]
			symbol_name, digits = [], symbol & 0xff
			symbol >>= 8
			while symbol != 0:
				symbol_name.append(chr(symbol & 0xff))
				symbol >>= 8
			divider = 10 ** digits
			if divider > 1:
				fmts = "%%d.%%0%dd %s" % (digits, "".join(symbol_name))
				r = fmts % (amount / divider, amount % divider)
			else:
				fmts = "%%d %s" % "".join(symbol_name)
				r = fmts % (amount / divider)
		except:
			pass
		return r


class contento__protocol__name(baseSummaryFormatter):
	charmap = ".12345abcdefghijklmnopqrstuvwxyz"

	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			value = valobj.GetChildMemberWithName("value").data.uint64s[0]
			r = ["."] * 13
			for i in xrange(13):
				r[12 - i] = contento__protocol__name.charmap[value & (0x0f if i == 0 else 0x1f)]
				value >>= 4 if i == 0 else 5
		except:
			pass
		return 'name "%s"' % "".join(r).rstrip(".")


class contento__protocol__namex(baseSummaryFormatter):
	@staticmethod
	def uint64_to_string(ui64):
		return "".join(map(chr, [(ui64 >> i) & 0xff for i in xrange(0, 64, 8)])).rstrip("\0")

	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			lo = valobj.GetChildMemberWithName("value").GetChildMemberWithName("lo").data.uint64s[0]
			hi = valobj.GetChildMemberWithName("value").GetChildMemberWithName("hi").data.uint64s[0]
			r = ""
			if lo > 0:
				r += contento__protocol__namex.uint64_to_string(lo) + contento__protocol__namex.uint64_to_string(hi)
		except:
			pass
		return 'name "%s"' % r


class fc__ecc__private_key(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			s = "".join(map(chr, valobj.data.uint8s))
			r = Helper.key_to_wif(s)
		except:
			pass
		return r


class fc__ecc__public_key(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			data = "".join(map(chr, valobj.data.uint8s))[:33]
			r = Helper.b58encode(data + hashlib.sha256(data).digest()[:4])
		except:
			pass
		return r


class contento__protocol__public_key_type(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			data = "".join(map(chr, valobj.data.uint8s))[:33]
			h = hashlib.new("ripemd160")
			h.update(data)
			r = "COS" + Helper.b58encode(data + h.digest()[:4])
		except:
			pass
		return r


class fc__time_point_sec(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			r = "UTC " + datetime.utcfromtimestamp(valobj.data.uint32s[0]).isoformat(" ")
		except:
			pass
		return r


class fc__time_point(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			r = "UTC " + datetime.utcfromtimestamp(valobj.data.sint64s[0] / 1000000.0).isoformat(" ")
		except:
			pass
		return r


class contento__chain__shared_string(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			size = 0
			d = valobj.GetChildMemberWithName("members_").GetChildMemberWithName("m_repr")
			short_hdr = d.GetChildMemberWithName("s").GetChildMemberWithName("h").data.uint8s[0]
			if short_hdr & 1:
				size = (short_hdr >> 1)
			else:
				long_hdr = d.GetChildMemberWithName("r").GetChildMemberWithName("data").data.uint64s[0]
				size = (long_hdr >> 1)
			r = "shared_string size=%d" % size
		except:
			pass
		return r


# fc crypto hash classes hold their digests in the '_hash' member, which is an integer array.
# it applies for fc::ripemd160/sha1/sha224/sha256/sha512 and their typedefs.
class fc_hash_formatter(baseSummaryFormatter):
	@staticmethod
	def summary(valobj, internal_dict):
		r = "[invalid]"
		try:
			r = binascii.hexlify("".join(map(chr,valobj.GetChildMemberWithName("_hash").data.uint8s)))
		except:
			pass
		return r


######## module entry point ########

def __lldb_init_module(debugger, dictionary):
	handlers = dict()
	handlers["fc::variant"] = fc__variant
	handlers["fc::variants"] = fc__variants
	handlers["fc::variant_object"] = fc__variant_object
	handlers["fc::variant_object::entry"] = fc__variant_object__entry
	handlers["fc::blob"] = fc__blob
	handlers["contento::protocol::asset"] = contento__protocol__asset
	handlers["contento::protocol::name"] = contento__protocol__name
	handlers["contento::protocol::namex"] = contento__protocol__namex
	handlers["fc::ecc::private_key"] = fc__ecc__private_key
	handlers["fc::ecc::public_key"] = fc__ecc__public_key
	handlers["contento::protocol::public_key_type"] = contento__protocol__public_key_type
	handlers["contento::protocol::private_key_type"] = fc__ecc__private_key
	handlers["fc::time_point_sec"] = fc__time_point_sec
	handlers["fc::time_point"] = fc__time_point
	handlers["contento::chain::shared_string"] = contento__chain__shared_string
	handlers["chainbase::shared_string"] = contento__chain__shared_string
	handlers["fc::ripemd160"] = fc_hash_formatter
	handlers["fc::sha1"] = fc_hash_formatter
	handlers["fc::sha224"] = fc_hash_formatter
	handlers["fc::sha256"] = fc_hash_formatter
	handlers["fc::sha512"] = fc_hash_formatter

	for clazz_name, clazz in handlers.iteritems():
		clazz.apply(debugger, clazz_name)


######## installer ########

if __name__ == "__main__":
	from os import path

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
