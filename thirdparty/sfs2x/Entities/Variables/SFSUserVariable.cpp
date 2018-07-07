// ===================================================================
//
// Description		
//		Contains the implementation of SFSUserVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSUserVariable.h"
#include <typeinfo>

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<UserVariable> SFSUserVariable::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	boost::shared_ptr<UserVariable> variable(new SFSUserVariable(
									 *(sfsa->GetUtfString(0)), 	// name
									 sfsa->GetElementAt(2),		// typed value
									 sfsa->GetByte(1)			// type id
									 ));

	// Since SFS v2.12.0 we're getting a new element at position #3
	if (sfsa->Size() > 3)
		variable->IsPrivate(sfsa->GetBool(3));	// 'private' flag

	return variable;
}

// -------------------------------------------------------------------
// newPrivateVariable
// -------------------------------------------------------------------
boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<long int> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<unsigned long int> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<int> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<unsigned int> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<bool> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<double> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<string> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<SFSObject> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

boost::shared_ptr<SFSUserVariable> SFSUserVariable::newPrivateVariable(string name, boost::shared_ptr<SFSArray> val)
{
	boost::shared_ptr<SFSUserVariable> uv(new SFSUserVariable(name, val));
	uv->IsPrivate(true);

	return uv;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<long int> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<unsigned long int> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<int> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<unsigned int> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<bool> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<double> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<string> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<SFSObject> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}

SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<SFSArray> val)
	: BaseVariable(name, val)
{
	isPrivate = false;
}


// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserVariable::SFSUserVariable(string name, boost::shared_ptr<void> val, long int type)
	: BaseVariable(name, val, type)
{
	isPrivate = false;
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSUserVariable::~SFSUserVariable()
{
	this->Name() = boost::shared_ptr<string>();
	this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
bool SFSUserVariable::IsPrivate()
{
	return isPrivate;
}

// -------------------------------------------------------------------
// IsPrivate
// -------------------------------------------------------------------
void SFSUserVariable::IsPrivate(bool value)
{
	isPrivate = value;
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSUserVariable::Name()
{
	return BaseVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType SFSUserVariable::Type()
{
	return BaseVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSUserVariable::Value()
{
	return BaseVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSUserVariable::GetBoolValue()
{
	return BaseVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<long int> SFSUserVariable::GetIntValue()
{
	return BaseVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSUserVariable::GetDoubleValue()
{
	return BaseVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSUserVariable::GetStringValue()
{
	return BaseVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSUserVariable::GetSFSObjectValue()
{
	return BaseVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSUserVariable::GetSFSArrayValue()
{
	return BaseVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSUserVariable::IsNull()
{
	return BaseVariable::IsNull();
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSUserVariable::ToSFSArray()
{
	boost::shared_ptr<ISFSArray> sfsa = BaseVariable::ToSFSArray();

	// private flag (3)
	sfsa->AddBool(isPrivate);
				
	return sfsa;
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSUserVariable::ToString()
{
	boost::shared_ptr<string> returned(new string());
	returned->append("[UserVar: ");
	returned->append(Name()->c_str());
	returned->append(", type: ");
	returned->append(TypeAsString()->c_str());
	returned->append(", value: ");
	returned->append(ValueAsString()->c_str());
	returned->append("]");

	return returned;
}

}	// namespace Variables
}	// namespace Entities
}	// namespace Sfs2X
