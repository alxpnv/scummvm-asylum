/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef ASYLUM_ACTOR_H_
#define ASYLUM_ACTOR_H_

#include "asylum/respack.h"
#include "asylum/graphics.h"

namespace Asylum {

class Scene;
class Screen;
struct ActionArea;

// TODO investigate other actor resources (from other
// scenes) to see if the unused blocks in the actor
// definition are in fact used elsewhere
enum ActorResources {
	kSound1 = 0,
	kSound2 = 1,
	kSound3 = 2,
	kSound4 = 3,
	//kUnused = 4,	// 0
	kFlags  = 5,

	kWalkN  = 6,
	kWalkNW = 7,
	kWalkW  = 8,
	kWalkSW = 9,
	kWalkS  = 10,

	kFaceN  = 11,
	kFaceNW = 12,
	kFaceW  = 13,
	kFaceSW = 14,
	kFaceS  = 15,

	kFaceAndShakeN  = 16,
	kFaceAndShakeNW = 17,
	kFaceAndShakeW  = 18,
	kFaceAndShakeSW = 19,
	kFaceAndShakeS  = 20,

	kStretchN  = 21,
	kStretchNW = 22,
	kStretchW  = 23,
	kStretchSW = 24,
	kStretchS  = 25,

	kFidgetN  = 26,
	kFidgetNW = 27,
	kFidgetW  = 28,
	kFidgetSW = 29,
	kFidgetS  = 30,

	// These are 0
	/*
	kUnknown1 = 31,
	kUnknown2 = 32,
	kUnknown3 = 33,
	kUnknown4 = 34,
	kUnknown5 = 35,
	*/

	kPickupN  = 36,
	kPickupNW = 37,
	kPickupW  = 38,
	kPickupSW = 39,
	kPickupS  = 40,

	kOperateN  = 41,
	kOperateNW = 42,
	kOperateW  = 43,
	kOperateSW = 44,
	kOperateS  = 45,

	kOperate2N  = 46,
	kOperate2NW = 47,
	kOperate2W  = 48,
	kOperate2SW = 49,
	kOperate2S  = 50,

	// These are 0
	/*
	kUnknown6  = 51,
	kUnknown7  = 52,
	kUnknown8  = 53,
	kUnknown9  = 54,
	kUnknown10 = 55,
	kUnknown11 = 56,
	kUnknown12 = 57,
	kUnknown13 = 58,
	kUnknown14 = 59
	*/

	// Horizontally flipped animations (100 + regular anim Id)
	kWalkNE = 107,
	kWalkE  = 108,
	kWalkSE = 109,

	kFaceNE = 112,
	kFaceE  = 113,
	kFaceSE = 114
	// TODO: finish these
};

class Actor {
public:
	Actor();
	virtual ~Actor();

	/**
	 * Initialize the 500 byte resource index from the scene
	 * file (at offset 0xA73B6).
	 *
	 * TODO remove this or add it in the right place
	 */
	void setRawResources(uint8* data);

	bool visible() {
		return flags & 0x01;
	}

	void visible(bool value);

	void setPosition(uint32 targetX, uint32 targetY);

	/**
	 * Initialize the x1/y1 values of the actor, update the active animation frame
	 * and, if the current direction isn't 8, update the actor's direction
	 */
	void setPosition_40A260(uint32 newX, uint32 newY, int newDirection, int frame);

	/**
	 * Change the direction the actor's facing based
	 * on the supplied parament.
	 *
	 * Note that the parameter doesn't directly update the
	 * actor's direction, but it used as a lookup
	 * to determine the value
	 */
	void changeOrientation(int param);

	void faceTarget(int targetId, int targetType);

	// FIXME
	// I don't really like how this is used in the scene constructor
	void setResourcePack(ResourcePack *res) {
		_resPack = res;
	}

	// XXX Hack to get a reference to the parent scene
	// into the actor instance
	void setScene(Scene *scene) {
		_scene = scene;
	}

	// OLD METHODS
	// TODO ALL of these need to be depreciated in favour
	// of the proper functions from the original
	void setWalkArea(ActionArea *target);
	void setAction(int action);
	void setActionByIndex(int index);
	void drawActorAt(uint32 curX, uint32 curY);
	void drawActor();
	void walkTo(uint32 curX, uint32 curY);


	int currentAction; // TODO depreciate

	int32		 x;
	int32		 y;
	uint32		 grResId;
	uint32		 field_C; // BarrierIndex? Mask index?
	uint32		 frameNum;
	uint32		 frameCount;
	int32		 x1;
	int32		 y1;
	int32		 x2;
	int32		 y2;
	Common::Rect boundingRect;
	uint32		 direction;
	uint32		 field_3C;
	uint32		 updateType;
	uint32		 field_44;
	uint32		 priority;
	uint32		 flags;
	uint32		 field_50;
	uint32		 field_54;
	uint32		 field_58;
	uint32		 field_5C;
	uint32		 field_60;
	uint32		 actionIdx3;
	// TODO field_68 till field_617
	uint32		 reaction[8];
	uint32		 field_638;
	uint32		 walkingSound1;
	uint32		 walkingSound2;
	uint32		 walkingSound3;
	uint32		 walkingSound4;
	uint32		 field_64C;
	uint32		 field_650;
	uint32		 grResTable[55];
	char		 name[256];
	uint32		 field_830[20];
	uint32		 field_880[20];
	uint32		 field_8D0[20];
	uint32		 actionIdx2;
	uint32		 field_924;
	uint32		 tickValue1;
	uint32		 field_92C;
	uint32		 flags2;
	uint32		 field_934;
	uint32		 field_938;
	uint32		 soundResId; // field_93C
	uint32       field_940;
	uint32       field_944;
	uint32       field_948;
	uint32       field_94C;
	uint32       field_950;
	uint32       field_954;
	uint32       field_958;
	uint32       field_95C;
	uint32       field_960;
	uint32       field_964;
	uint32       field_968;
	uint32       field_96C;
	uint32       field_970;
	uint32       field_974;
	uint32       field_978;
	uint32		 actionIdx1;
	// TODO field_980 till field_9A0

private:
	Scene			*_scene;
	ResourcePack    *_resPack;
	GraphicResource *_graphic;
	uint32          _resources[61];
	ActionArea 	    *_currentWalkArea;

	GraphicFrame *getFrame();
	int getAngle(int ax1, int ay1, int ax2, int ay2);

}; // end of class MainActor

// Angle Tables used by getAngle()
const uint8 angleTable01[256] = {
	0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x02, 0x02, 0x03, 0x03, 0x03, 0x03,
	0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07,
	0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x09, 0x09, 0x09, 0x09, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
	0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0C, 0x0C, 0x0C, 0x0C, 0x0D, 0x0D, 0x0D, 0x0D, 0x0D, 0x0E, 0x0E,
	0x0E, 0x0E, 0x0E, 0x0F, 0x0F, 0x0F, 0x0F, 0x10, 0x10, 0x10, 0x10, 0x10, 0x11, 0x11, 0x11, 0x11,
	0x11, 0x12, 0x12, 0x12, 0x12, 0x12, 0x13, 0x13, 0x13, 0x13, 0x13, 0x14, 0x14, 0x14, 0x14, 0x14,
	0x15, 0x15, 0x15, 0x15, 0x15, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x17, 0x17, 0x17, 0x17, 0x17,
	0x18, 0x18, 0x18, 0x18, 0x18, 0x19, 0x19, 0x19, 0x19, 0x19, 0x19, 0x1A, 0x1A, 0x1A, 0x1A, 0x1A,
	0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1B, 0x1C, 0x1C, 0x1C, 0x1C, 0x1C, 0x1D, 0x1D, 0x1D, 0x1D, 0x1D,
	0x1D, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1E, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x1F, 0x20, 0x20, 0x20,
	0x20, 0x20, 0x20, 0x20, 0x21, 0x21, 0x21, 0x21, 0x21, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
	0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x23, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x24, 0x25, 0x25,
	0x25, 0x25, 0x25, 0x25, 0x25, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x27, 0x27, 0x27, 0x27,
	0x27, 0x27, 0x27, 0x27, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x28, 0x29, 0x29, 0x29, 0x29, 0x29,
	0x29, 0x29, 0x29, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2A, 0x2B, 0x2B, 0x2B, 0x2B, 0x2B,
	0x2B, 0x2B, 0x2B, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2C, 0x2D, 0x2D, 0x2D, 0x2D
};

const uint8 angleTable02[256] = {
	0x00, 0x04, 0x07, 0x0B, 0x0E, 0x11, 0x15, 0x18, 0x1B, 0x1D, 0x20, 0x23, 0x25, 0x27, 0x29, 0x2B,
	0x2D, 0x2F, 0x30, 0x32, 0x33, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
	0x3F, 0x40, 0x41, 0x41, 0x42, 0x43, 0x43, 0x44, 0x44, 0x45, 0x45, 0x46, 0x46, 0x46, 0x47, 0x47,
	0x48, 0x48, 0x48, 0x49, 0x49, 0x49, 0x49, 0x4A, 0x4A, 0x4A, 0x4B, 0x4B, 0x4B, 0x4B, 0x4C, 0x4C,
	0x4C, 0x4C, 0x4C, 0x4D, 0x4D, 0x4D, 0x4D, 0x4D, 0x4D, 0x4E, 0x4E, 0x4E, 0x4E, 0x4E, 0x4E, 0x4F,
	0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x4F, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50, 0x50,
	0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x51, 0x52, 0x52, 0x52, 0x52,
	0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x52, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53,
	0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x53, 0x54, 0x54, 0x54,
	0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54,
	0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x54, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55,
	0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x56, 0x56, 0x56, 0x56,
	0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56,
	0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56,
	0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56, 0x56
};

const uint8 angleTable03[256] = {
	0x00, 0x45, 0x63, 0x72, 0x76, 0x79, 0x81, 0x82, 0x83, 0x84, 0x84, 0x85, 0x85, 0x86, 0x86, 0x86,
	0x86, 0x87, 0x87, 0x87, 0x87, 0x87, 0x87, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88,
	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89,
	0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89,
	0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89,
	0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89,
	0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89, 0x89,
	0x89, 0x89, 0x89, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90,
	0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90
};

} // end of namespace Asylum

#endif
