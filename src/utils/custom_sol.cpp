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
#include "custom_sol.hpp"

#include "convert_godot_lua.hpp"
#include "convert_godot_std.hpp"

#include <godot_cpp/variant/packed_byte_array.hpp>

using namespace luagdextension;

String sol_lua_get(sol::types<String>, lua_State* L, int index, sol::stack::record& tracking) {
	auto sv = sol::stack::get<std::string_view>(L, index);
	return String::utf8(sv.data(), sv.size());
}

int sol_lua_push(lua_State* L, const String& str) {
	PackedByteArray bytes = str.to_utf8_buffer();
	return sol::stack::push(L, to_string_view(bytes));
}

StringName sol_lua_get(sol::types<StringName>, lua_State* L, int index, sol::stack::record& tracking) {
	const char *str = sol::stack::get<const char *>(L, index);
	return StringName(str);
}

int sol_lua_push(lua_State* L, const StringName& str) {
	PackedByteArray bytes = str.to_utf8_buffer();
	return sol::stack::push(L, to_string_view(bytes));
}

int sol_lua_push(lua_State* L, const Vector2 &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Vector2i &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Rect2 &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Rect2i &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Vector3 &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Vector3i &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Transform2D &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Vector4 &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Vector4i &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Plane &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Quaternion &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const AABB &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Basis &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Transform3D &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Projection &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Color &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const NodePath &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const RID &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const ObjectID &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, Object *v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Callable &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Signal &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Dictionary &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const Array &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedByteArray &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedInt32Array &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedInt64Array &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedFloat32Array &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedFloat64Array &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedStringArray &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedVector2Array &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedVector3Array &v) { to_lua(L, Variant(v)); return 1; }
int sol_lua_push(lua_State* L, const PackedColorArray &v) { to_lua(L, Variant(v)); return 1; }

#if LUA_VERSION_NUM < 504
int lua_resume(lua_State *L, lua_State *from, int nargs, int *nresults) {
	int status = lua_resume(L, from, nargs);
	if (nresults) {
		nresults = lua_gettop(L);
	}
	return status;
}
#endif
