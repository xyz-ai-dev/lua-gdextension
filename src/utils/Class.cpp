/**
 * Copyright (C) 2023 Gil Barbosa Reis.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the “Software”), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "Class.hpp"

#include "convert_godot_lua.hpp"

#include <godot_cpp/classes/class_db_singleton.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/godot.hpp>

namespace luagdextension {

Class::Class(const StringName& class_name) : class_name(class_name) {}

const StringName& Class::get_name() const {
	return class_name;
}

sol::optional<int64_t> Class::get_constant(const StringName& name) const {
	ClassDBSingleton *class_db = ClassDBSingleton::get_singleton();
	if (class_db->class_has_integer_constant(class_name, name)) {
		return class_db->class_get_integer_constant(class_name, name);
	}
	else {
		return {};
	}
}

Variant Class::construct(const sol::variadic_args& args) const {
	GDExtensionObjectPtr obj_ptr = godot::internal::gdextension_interface_classdb_construct_object(class_name._native_ptr());
	Object *obj = godot::internal::get_object_instance_binding(obj_ptr);
	if (obj->has_method("_init")) {
		obj->callv("_init", to_array(args));
	}
	return obj;
}

bool Class::operator==(const Class& other) const {
	return class_name == other.class_name;
}

static sol::optional<int64_t> __index(sol::this_state state, const Class& cls, sol::stack_object key) {
	if (key.get_type() == sol::type::string) {
		StringName name = key.as<StringName>();
		return cls.get_constant(name);
	}
	else {
		return {};
	}
}
void Class::register_usertype(sol::state_view& state) {
	state.new_usertype<Class>(
		"Class",
		"new", &Class::construct,
		sol::meta_function::index, &__index,
		sol::meta_function::to_string, &Class::get_name
	);
}

}
