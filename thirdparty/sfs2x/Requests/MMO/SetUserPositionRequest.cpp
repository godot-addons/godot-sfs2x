// ===================================================================
//
// Description		
//		Contains the implementation of SetUserPositionRequest
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "SetUserPositionRequest.h"

namespace Sfs2X {
namespace Requests {
namespace MMO {

boost::shared_ptr<string> SetUserPositionRequest::KEY_ROOM (new string("r"));
boost::shared_ptr<string> SetUserPositionRequest::KEY_VEC3D (new string("v"));
boost::shared_ptr<string> SetUserPositionRequest::KEY_PLUS_USER_LIST (new string("p"));
boost::shared_ptr<string> SetUserPositionRequest::KEY_MINUS_USER_LIST (new string("m"));
boost::shared_ptr<string> SetUserPositionRequest::KEY_PLUS_ITEM_LIST (new string("q"));
boost::shared_ptr<string> SetUserPositionRequest::KEY_MINUS_ITEM_LIST (new string("n"));

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SetUserPositionRequest::SetUserPositionRequest (boost::shared_ptr<Vec3D> position, boost::shared_ptr<Room> room)
	: BaseRequest (RequestType_SetUserPosition)
{
	this->room = room;
	this->pos = position;
}

SetUserPositionRequest::SetUserPositionRequest (boost::shared_ptr<Vec3D> position)
	: BaseRequest (RequestType_SetUserPosition)
{
	this->room = boost::shared_ptr<Room>();
	this->pos = position;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SetUserPositionRequest::~SetUserPositionRequest()
{
}

// -------------------------------------------------------------------
// Validate
// -------------------------------------------------------------------
void SetUserPositionRequest::Validate(boost::shared_ptr<SmartFox> sfs)
{
	boost::shared_ptr<list<string> > errors (new list<string>());

	if (pos == NULL)
		errors->push_back("Position must be a valid Vec3D ");

	if (room == NULL)
		room = sfs->LastJoinedRoom();

	if (room == NULL)
		errors->push_back("You are not joined in any room");

	if (dynamic_cast<MMORoom*>(room.get()) == NULL)
		errors->push_back("Selected Room is not an MMORoom");

	if (errors->size() > 0)
	{
		boost::shared_ptr<string> message (new string("SetUserVariables request error"));
		boost::shared_ptr<SFSValidationError> exception(new SFSValidationError(message, errors));
		throw exception;
	}
}

// -------------------------------------------------------------------
// Execute
// -------------------------------------------------------------------
void SetUserPositionRequest::Execute(boost::shared_ptr<SmartFox> sfs)
{
	sfso->PutInt(KEY_ROOM, room->Id());
			
	if (pos->IsFloat())
	{
		boost::shared_ptr<vector<float> > vectors3D = pos->ToFloatArray();
		sfso->PutFloatArray(KEY_VEC3D, vectors3D);
	}
	else 
	{
		boost::shared_ptr<vector<long int> > vectors3D = pos->ToIntArray();
		sfso->PutIntArray(KEY_VEC3D, vectors3D);
	}
}

}	// namespace MMO
}	// namespace Requests
}	// namespace Sfs2X
