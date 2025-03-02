import json
from os import path

SRC_DIR = path.dirname(__file__)
DEST_DIR = path.join(SRC_DIR, "generated")
API_JSON_PATH = path.join(SRC_DIR, "..", "lib", "godot-cpp", "gdextension", "extension_api.json")
PRIMITIVE_VARIANTS = [
    "bool",
    "int",
    "float",
]
UTILITY_FUNCTION_MAP = {
    "typeof": "type_of",
    "is_instance_valid": None,
}


def generate_utility_functions(utility_functions):
    lines = [
        "#undef register_utility_functions\n#define register_utility_functions(state)"
    ]
    for f in utility_functions:
        name = f["name"]
        funcname = UTILITY_FUNCTION_MAP.get(name, name)
        if funcname is None:
            continue
        if f.get("is_vararg", False):
            lines.append(f'\tstate.set("{name}", wrap_function(&UtilityFunctions::{funcname}_internal));')
        elif (
            f.get("return_type") not in PRIMITIVE_VARIANTS
            or any(arg["type"] not in PRIMITIVE_VARIANTS for arg in f.get("arguments", []))
        ):
            lines.append(f'\tstate.set("{name}", wrap_function(&UtilityFunctions::{funcname}));')
        else:
            lines.append(f'\tstate.set("{name}", &UtilityFunctions::{funcname});')
    return " \\\n".join(lines) + "\n"


def generate_enums(global_enums):
    lines = [
        "#undef register_global_enums\n#define register_global_enums(state)"
    ]
    for enum in global_enums:
        lines.append(f"\t/* {enum['name']} */")
        for value in enum["values"]:
            lines.append(f'\tstate.set("{value["name"]}", {value["value"]});')
    return " \\\n".join(lines) + "\n"


def main():
    with open(API_JSON_PATH) as f:
        api = json.load(f)

    with open(path.join(DEST_DIR, "utility_functions.hpp"), "w") as f:
        code = generate_utility_functions(api["utility_functions"])
        f.write(code)

    with open(path.join(DEST_DIR, "global_enums.hpp"), "w") as f:
        code = generate_enums(api["global_enums"])
        f.write(code)


if __name__ == "__main__":
    main()
