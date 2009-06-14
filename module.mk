MODULE := engines/asylum

MODULE_OBJS := \
	asylum.o \
	bundle.o \
	detection.o \
	graphicbundle.o \
	video.o \
	resman.o \
	resourcepack.o \
	scene.o \
	screen.o \
	sound.o \
	state.o \
	text.o

# This module can be built as a plugin
ifeq ($(ENABLE_ASYLUM), DYNAMIC_PLUGIN)
PLUGIN := 1
endif

# Include common rules
include $(srcdir)/rules.mk
