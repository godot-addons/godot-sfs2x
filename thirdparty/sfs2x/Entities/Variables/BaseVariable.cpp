// ===================================================================
//
// Description		
//		Contains the implementation of BaseVariable
//
// Revision history
//		Date			Description
//		30-Nov-2016		First version
//
// ===================================================================
#include "BaseVariable.h"

namespace Sfs2X {
	namespace Entities {
		namespace Variables {

			// -------------------------------------------------------------------
			// Constructor
			// -------------------------------------------------------------------
			BaseVariable::BaseVariable(string name, boost::shared_ptr<void> val, long int type)
			{
				this->name = boost::shared_ptr<string>(new string(name));

				// If type is specfied let's use it
				if (type > -1)
				{
					this->val = val;
					this->type = (VariableType)type;
				}
				// Otherwise let's autodetect the type
				else
				{
					//SetValue(val);
				}
			}

			BaseVariable::BaseVariable(string name, boost::shared_ptr<long int> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}
			
			BaseVariable::BaseVariable(string name, boost::shared_ptr<unsigned long int> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}
			
			BaseVariable::BaseVariable(string name, boost::shared_ptr<int> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}
			
			BaseVariable::BaseVariable(string name, boost::shared_ptr<unsigned int> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}
			
			BaseVariable::BaseVariable(string name, boost::shared_ptr<bool> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}
			
			BaseVariable::BaseVariable(string name, boost::shared_ptr<double> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}
			
			BaseVariable::BaseVariable(string name, boost::shared_ptr<string> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}

			BaseVariable::BaseVariable(string name, boost::shared_ptr<SFSObject> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}
			
			BaseVariable::BaseVariable(string name, boost::shared_ptr<SFSArray> val)
			{
				this->name = boost::shared_ptr<string>(new string(name));
				SetValue(val);
			}

			// -------------------------------------------------------------------
			// Destructor
			// -------------------------------------------------------------------
			BaseVariable::~BaseVariable()
			{
				this->name = boost::shared_ptr<string>();
				this->val = boost::shared_ptr<void>();
			}

			// -------------------------------------------------------------------
			// Name
			// -------------------------------------------------------------------
			boost::shared_ptr<string> BaseVariable::Name()
			{
				return name;
			}

			// -------------------------------------------------------------------
			// Type
			// -------------------------------------------------------------------
			VariableType BaseVariable::Type()
			{
				return type;
			}

			// -------------------------------------------------------------------
			// Value
			// -------------------------------------------------------------------
			boost::shared_ptr<void> BaseVariable::Value()
			{
				return val;
			}

			// -------------------------------------------------------------------
			// GetBoolValue
			// -------------------------------------------------------------------
			boost::shared_ptr<bool> BaseVariable::GetBoolValue()
			{
				return (boost::static_pointer_cast<bool>)(val);
			}

			// -------------------------------------------------------------------
			// GetIntValue
			// -------------------------------------------------------------------
			boost::shared_ptr<long int> BaseVariable::GetIntValue()
			{
				return (boost::static_pointer_cast<long int>)(val);
			}

			// -------------------------------------------------------------------
			// GetDoubleValue
			// -------------------------------------------------------------------
			boost::shared_ptr<double> BaseVariable::GetDoubleValue()
			{
				return (boost::static_pointer_cast<double>)(val);
			}

			// -------------------------------------------------------------------
			// GetStringValue
			// -------------------------------------------------------------------
			boost::shared_ptr<string> BaseVariable::GetStringValue()
			{
				return (boost::static_pointer_cast<string>)(val);
			}

			// -------------------------------------------------------------------
			// GetSFSObjectValue
			// -------------------------------------------------------------------
			boost::shared_ptr<ISFSObject> BaseVariable::GetSFSObjectValue()
			{
				return (boost::static_pointer_cast<ISFSObject>)(val);
			}

			// -------------------------------------------------------------------
			// GetSFSArrayValue
			// -------------------------------------------------------------------
			boost::shared_ptr<ISFSArray> BaseVariable::GetSFSArrayValue()
			{
				return (boost::static_pointer_cast<ISFSArray>)(val);
			}

			// -------------------------------------------------------------------
			// IsNull
			// -------------------------------------------------------------------
			bool BaseVariable::IsNull()
			{
				return type == VARIABLETYPE_NULL;
			}

			// -------------------------------------------------------------------
			// ToSFSArray
			// -------------------------------------------------------------------
			boost::shared_ptr<ISFSArray> BaseVariable::ToSFSArray()
			{
				boost::shared_ptr<ISFSArray> sfsa = SFSArray::NewInstance();

				// var name (0)
				sfsa->AddUtfString(name);

				// var type (1)
				boost::shared_ptr<unsigned char> ptrType(new unsigned char());
				*ptrType = type;
				sfsa->AddByte(ptrType);

				// var value (2)
				PopulateArrayWithValue(sfsa);

				return sfsa;
			}

			// -------------------------------------------------------------------
			// PopulateArrayWithValue
			// -------------------------------------------------------------------
			void BaseVariable::PopulateArrayWithValue(boost::shared_ptr<ISFSArray> arr)
			{
				switch (type)
				{
				case VARIABLETYPE_UNKNOWN:
					break;

				case VARIABLETYPE_NULL:
					arr->AddNull();
					break;

				case VARIABLETYPE_BOOL:
					arr->AddBool(GetBoolValue());
					break;

				case VARIABLETYPE_INT:
					arr->AddInt(GetIntValue());
					break;

				case VARIABLETYPE_DOUBLE:
					arr->AddDouble(GetDoubleValue());
					break;

				case VARIABLETYPE_STRING:
					arr->AddUtfString(GetStringValue());
					break;

				case VARIABLETYPE_OBJECT:
					arr->AddSFSObject(GetSFSObjectValue());
					break;

				case VARIABLETYPE_ARRAY:
					arr->AddSFSArray(GetSFSArrayValue());
					break;
				}
			}

			// -------------------------------------------------------------------
			// SetValue
			// -------------------------------------------------------------------
			void BaseVariable::SetValue(boost::shared_ptr<long int> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_INT;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<unsigned long int> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_INT;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<int> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_INT;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<unsigned int> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_INT;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<bool> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_BOOL;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<double> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_DOUBLE;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<string> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_STRING;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<SFSObject> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_OBJECT;
				}
			}

			void BaseVariable::SetValue(boost::shared_ptr<SFSArray> val)
			{
				this->val = val;

				if (val == NULL)
				{
					type = VARIABLETYPE_NULL;
				}
				else
				{
					type = VARIABLETYPE_ARRAY;
				}
			}

			// -------------------------------------------------------------------
			// TypeAsString
			// -------------------------------------------------------------------
			boost::shared_ptr<string> BaseVariable::TypeAsString()
			{
				switch (type)
				{
				case VARIABLETYPE_UNKNOWN:
					return boost::shared_ptr<string>(new string("UNKNOWN"));

				case VARIABLETYPE_NULL:
					return boost::shared_ptr<string>(new string("NULL"));

				case VARIABLETYPE_BOOL:
					return boost::shared_ptr<string>(new string("BOOL"));

				case VARIABLETYPE_INT:
					return boost::shared_ptr<string>(new string("INT"));

				case VARIABLETYPE_DOUBLE:
					return boost::shared_ptr<string>(new string("DOUBLE"));

				case VARIABLETYPE_STRING:
					return boost::shared_ptr<string>(new string("STRING"));

				case VARIABLETYPE_OBJECT:
					return boost::shared_ptr<string>(new string("OBJECT"));

				case VARIABLETYPE_ARRAY:
					return boost::shared_ptr<string>(new string("ARRAY"));
				}

				return boost::shared_ptr<string>();
			}

			// -------------------------------------------------------------------
			// ValueAsString
			// -------------------------------------------------------------------
			boost::shared_ptr<string> BaseVariable::ValueAsString()
			{
				boost::shared_ptr<string> valueReturned;
				boost::shared_ptr<string> valueFormat;

				switch (type)
				{
				case VARIABLETYPE_UNKNOWN:
					valueReturned = boost::shared_ptr<string>(new string());
					break;

				case VARIABLETYPE_NULL:
					valueReturned = boost::shared_ptr<string>(new string());
					break;

				case VARIABLETYPE_BOOL:
					if (*GetBoolValue() == true)
					{
						valueReturned = boost::shared_ptr<string>(new string("true"));
					}
					else
					{
						valueReturned = boost::shared_ptr<string>(new string("false"));
					}
					break;

				case VARIABLETYPE_INT:
					valueReturned = boost::shared_ptr<string>(new string());
					valueFormat = boost::shared_ptr<string>(new string("%ld"));
					StringFormatter<long int>(valueReturned, valueFormat, *GetIntValue());
					break;

				case VARIABLETYPE_DOUBLE:
					valueReturned = boost::shared_ptr<string>(new string());
					valueFormat = boost::shared_ptr<string>(new string("%f"));
					StringFormatter<double>(valueReturned, valueFormat, *GetDoubleValue());
					break;

				case VARIABLETYPE_STRING:
					valueReturned = boost::shared_ptr<string>(new string(GetStringValue()->c_str()));
					break;

				case VARIABLETYPE_OBJECT:
					valueReturned = boost::shared_ptr<string>(new string(GetSFSObjectValue()->GetDump()->c_str()));
					break;

				case VARIABLETYPE_ARRAY:
					valueReturned = boost::shared_ptr<string>(new string(GetSFSArrayValue()->GetDump()->c_str()));
					break;
				}

				return valueReturned;
			}

		}	// namespace Variables
	}	// namespace Entities
}	// namespace Sfs2X


