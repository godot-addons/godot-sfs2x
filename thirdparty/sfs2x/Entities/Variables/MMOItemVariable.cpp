// ===================================================================
//
// Description		
//		Contains the implementation of MMOItemVariable
//
// Revision history
//		Date			Description
//		30-Nov-2013		First version
//
// ===================================================================
#include "MMOItemVariable.h"

namespace Sfs2X {
namespace Entities {
namespace Variables {

// -------------------------------------------------------------------
// FromSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<IMMOItemVariable> MMOItemVariable::FromSFSArray(boost::shared_ptr<ISFSArray> sfsa)
{
	boost::shared_ptr<IMMOItemVariable> variable (new MMOItemVariable (
		*(sfsa->GetUtfString(0)), 	// name
		sfsa->GetElementAt(2),		// typed value
		sfsa->GetByte(1)			// type id
	));
	
	return variable;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<void> val, long int type)
	: BaseVariable(name, val, type)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<long int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<unsigned long int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<unsigned int> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<bool> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<double> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<string> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<SFSObject> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

MMOItemVariable::MMOItemVariable(string name, boost::shared_ptr<SFSArray> val)
	: BaseVariable(name, val)
{
	// Nothing else to do
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
MMOItemVariable::~MMOItemVariable()
{
	this->Name() = boost::shared_ptr<string>();
	this->Value() = boost::shared_ptr<void>();
}

// -------------------------------------------------------------------
// Name
// -------------------------------------------------------------------
boost::shared_ptr<string> MMOItemVariable::Name()
{
	return BaseVariable::Name();
}

// -------------------------------------------------------------------
// Type
// -------------------------------------------------------------------
VariableType MMOItemVariable::Type()
{
	return BaseVariable::Type();
}

// -------------------------------------------------------------------
// Value
// -------------------------------------------------------------------
boost::shared_ptr<void> MMOItemVariable::Value()
{
	return BaseVariable::Value();
}

// -------------------------------------------------------------------
// GetBoolValue
// -------------------------------------------------------------------
boost::shared_ptr<bool> MMOItemVariable::GetBoolValue()
{
	return BaseVariable::GetBoolValue();
}

// -------------------------------------------------------------------
// GetIntValue
// -------------------------------------------------------------------
boost::shared_ptr<long int> MMOItemVariable::GetIntValue()
{
	return BaseVariable::GetIntValue();
}

// -------------------------------------------------------------------
// GetDoubleValue
// -------------------------------------------------------------------
boost::shared_ptr<double> MMOItemVariable::GetDoubleValue()
{
	return BaseVariable::GetDoubleValue();
}

// -------------------------------------------------------------------
// GetStringValue
// -------------------------------------------------------------------
boost::shared_ptr<string> MMOItemVariable::GetStringValue()
{
	return BaseVariable::GetStringValue();
}

// -------------------------------------------------------------------
// GetSFSObjectValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSObject> MMOItemVariable::GetSFSObjectValue()
{
	return BaseVariable::GetSFSObjectValue();
}

// -------------------------------------------------------------------
// GetSFSArrayValue
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MMOItemVariable::GetSFSArrayValue()
{
	return BaseVariable::GetSFSArrayValue();
}

// -------------------------------------------------------------------
// IsNull
// -------------------------------------------------------------------
bool MMOItemVariable::IsNull()
{
	return BaseVariable::IsNull();
}

// -------------------------------------------------------------------
// ToSFSArray
// -------------------------------------------------------------------
boost::shared_ptr<ISFSArray> MMOItemVariable::ToSFSArray()
{
	return BaseVariable::ToSFSArray();
}

// -------------------------------------------------------------------
// ToString
// -------------------------------------------------------------------
boost::shared_ptr<string> MMOItemVariable::ToString()
{
	boost::shared_ptr<string> returned(new string());
	returned->append("[MMOItemVar: ");
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
		
		
