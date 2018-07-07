// ===================================================================
//
// Description		
//		Contains the implementation of SFSBuddyVariable
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSBuddyVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

boost::shared_ptr<string> SFSBuddyVariable::OFFLINE_PREFIX (new string("$")); 

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<BuddyVariable> SFSBuddyVariable::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	boost::shared_ptr<SFSBuddyVariable> variable (new SFSBuddyVariable(sfsa->GetUtfString(0), 	// name
													  sfsa->GetElementAt(2),	// typed value
													  sfsa->GetByte(1)			// type id
													  ));

	return variable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<void> val, long int type)
	: BaseVariable(name, val, type)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(boost::shared_ptr<string> name, boost::shared_ptr<void> val, long int type)
	: BaseVariable(*name, val, type)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<long int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<unsigned long int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<unsigned int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<bool> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<double> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<string> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<SFSObject> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

SFSBuddyVariable::SFSBuddyVariable(string name, boost::shared_ptr<SFSArray> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSBuddyVariable::~SFSBuddyVariable()
{
	this->Name() = boost::shared_ptr<string>();
	this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// IsOffline
// -------------------------------------------------------------------
bool SFSBuddyVariable::IsOffline()
{
	return (Name()->find("$") == 0);
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyVariable::Name()
{
	return BaseVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType SFSBuddyVariable::Type()
{
	return BaseVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> SFSBuddyVariable::Value()
{
	return BaseVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> SFSBuddyVariable::GetBoolValue()
{
	return BaseVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<long int> SFSBuddyVariable::GetIntValue()
{
	return BaseVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> SFSBuddyVariable::GetDoubleValue()
{
	return BaseVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyVariable::GetStringValue()
{
	return BaseVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> SFSBuddyVariable::GetSFSObjectValue()
{
	return BaseVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSBuddyVariable::GetSFSArrayValue()
{
	return BaseVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool SFSBuddyVariable::IsNull()
{
	return BaseVariable::IsNull();
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> SFSBuddyVariable::ToSFSArray()
{
	return BaseVariable::ToSFSArray();
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> SFSBuddyVariable::ToString()
{
	boost::shared_ptr<string> returned(new string());
	returned->append("[BuddyVar: ");
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

