#include "register_types.h"

#include "gdexample.h"

#include "fabrik/AKIK_chain.h"
#include "fabrik/AKIK_joint.h"
#include "dampedtransform/AKIK_Procedural_Rig.h"
#include "environment-targeting/ground-targeter.h"
#include "custom-position-interpolation/follower.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

void initialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_CLASS(GDExample);
	GDREGISTER_CLASS(AKIK_chain);
	GDREGISTER_CLASS(AKIK_joint);
	GDREGISTER_CLASS(AKIK_ground_targeter);
	GDREGISTER_CLASS(AKIK_Procedural_Rig);
	GDREGISTER_CLASS(AKIK_follower);
}

void uninitialize_example_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
} 
 
extern "C" {
// Initialization.
GDExtensionBool GDE_EXPORT example_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
	godot::GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

	init_obj.register_initializer(initialize_example_module);
	init_obj.register_terminator(uninitialize_example_module);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}