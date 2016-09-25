#define FREESPACE_ENABLED 1

#include "Windows/ScopedSetCurrentDir.h"
#include "PluginData.h"
#include "PluginLog.h"

#if UNITY_IPHONE
#	include <OpenGLES/ES2/gl.h>
#elif UNITY_ANDROID
#	include <GLES2/gl2.h>
#else
#	include "../GLEW/glew.h"
#endif

#if FREESPACE_ENABLED
#include "freespace2/freespace.h"
#include "graphics/2d.h"
#endif

void Plugin_FSInit()
{
	ScopedSetCurrentDir scoped(GetData_AssetPath().c_str());

#if FREESPACE_ENABLED
	try
	{
		game_init("-uplugin");// -window -no_glsl -nomovies");
	}
	catch (const std::exception& e)
	{
		DebugLog(e.what());
	}
	catch (...)
	{
		DebugLog("Unknown exception");
	}
#endif
}

void Plugin_FSDeinit()
{
	ScopedSetCurrentDir scoped(GetData_AssetPath().c_str());

#if FREESPACE_ENABLED
	game_deinit();
#endif
}

void Plugin_Render()
{
#if FREESPACE_ENABLED
	glDisable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
	//glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	gr_clear_states();
	gr_set_buffer(-1);
	game_process();
#endif
}
