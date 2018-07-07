// ===================================================================
//
// Description		
//		Contains the implementation of SFSRoomVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSRoomVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<RoomVariable> SFSRoomVariable::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	boost::shared_ptr<RoomVariable> variable (new SFSRoomVariable (
		*(sfsa->GetUtfString(0)), 	// name
		sfsa->GetElementAt(2),		// typed value
		sfsa->GetByte(1)			// type id
	));
	
	variable->IsPrivate(sfsa->GetBool(3)); // "Private" flag
	variable->IsPersistent(sfsa->GetBool(4)); // "Persistent" flag					
			
	return variable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<long int> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<unsigned long int> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<int> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<unsigned int> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<bool> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<double> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<string> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<SFSObject> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<SFSArray> val)
	: BaseVariable(name, val)
{
	isPersistent = false;
	isPrivate = false;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSRoomVariable::SFSRoomVariable(string name, boost::shared_ptr<void> val, long int type)
	: BaseVariable(name, val, type)
{
	isPersistent = false;
	isPrivate = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSRoomVariable::~SFSRoomVariable()
{
	this->Name() = boost::shared_ptr<string>();
	this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
bool SFSRoomVariable::IsPrivate()
{
	return isPrivate;
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
void SFSRoomVariable::IsPrivate(bool value)
{
	isPrivate = value;
}

// -------------------------------------------------------------------
// IsPersistent
// -------------------------------------------------------------------
bool SFSRoomVariable::IsPersistent()
{
	return isPersistent;
}

// -------------------------------------------------------------------
// IsPersistent
// -------------------------------------------------------------------
void SFSRoomVariable::IsPersistent(bool value)
{
	isPersistent = value;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoomVariable::ToString()
{
	boost::shared_ptr<string> returned(new string());
	returned->append("[RoomVar: ");
	returned->append(Name()->c_str());
	returned->append(", type: ");
	returned->append(TypeAsString()->c_str());
	returned->append(", value: ");
	returned->append(ValueAsString()->c_str());
	returned->append("]");

	return returned;
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSRoomVariable::ToSFSArray()
{
	boost::shared_ptr<ISFSArray> arr = BaseVariable::ToSFSArray();
			
	// isPrivate (3)
	boost::shared_ptr<bool> valueIsPrivate (new bool());
	*valueIsPrivate = isPrivate;
	arr->AddBool(valueIsPrivate);
			
	// isPersistent (4)
	boost::shared_ptr<bool> valueIsPersistent (new bool());
	*valueIsPersistent = isPersistent;
	arr->AddBool(valueIsPersistent);
			
	return arr;
}

// -----
// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoomVariable::Name()
{
	return BaseVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType SFSRoomVariable::Type()
{
	return BaseVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSRoomVariable::Value()
{
	return BaseVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSRoomVariable::GetBoolValue()
{
	return BaseVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<long int> SFSRoomVariable::GetIntValue()
{
	return BaseVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSRoomVariable::GetDoubleValue()
{
	return BaseVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSRoomVariable::GetStringValue()
{
	return BaseVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSRoomVariable::GetSFSObjectValue()
{
	return BaseVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSRoomVariable::GetSFSArrayValue()
{
	return BaseVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSRoomVariable::IsNull()
{
	return BaseVariable::IsNull();
}

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X

