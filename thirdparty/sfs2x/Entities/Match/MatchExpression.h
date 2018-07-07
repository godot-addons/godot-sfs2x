// ===================================================================
//
// Description		
//		Contains the definition of MatchExpression
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __MatchExpression__
#define __MatchExpression__

#include "IMatcher.h"
#include "../../Util/Common.h"
#include "../Data/ISFSArray.h"
#include "../Data/SFSArray.h"

#include "LogicOperator.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer
#include <boost/enable_shared_from_this.hpp>	// Boost shared_ptr for this

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

namespace Sfs2X {
namespace Entities {
namespace Match {

	/// <summary>
	/// <b>Match Expressions</b> are built like "if" conditions in any common programming language.
	/// </summary>
	/// <remarks>
	/// <h2>Overview</h2>
	/// <b>Match Expressions</b> are built like "if" conditions in any common programming language. 
	/// They work like queries in a database and can be used to search for Rooms or Users using custom criteria. 
	/// These expressions are extremely easy to create and concatenate and they can be used for many different filtering operations within the SFS2X framework.
	///
	///  This is a quick example:
	/// <pre>
	/// boost::shared_ptr<int> value(new int());
	/// *value = 5;
	/// boost::shared_ptr<MatchExpression> exp(new MatchExpression("rank", NumberMatch::GREATER_THAN, value));
	/// boost::shared_ptr<string> country(new string("Italy"));
	/// exp->And("country", StringMatch::EQUALS, country);
	/// </pre>
	///
	///  Expressions are made of three elements: 
	///	<ul> 
	///		<li>Variable name</li> 
	///		<li>Match operator</li> 
	///		<li>Value</li> 
	///	</ul>
	/// Additionally any number of expressions can be linked together with a logical <b>AND</b> / <b>OR</b> operator, just like in regular code. 
	/// In the above example we have created an expression that will check for a rank value > 5 and a country value == "Italy".
	///  
	/// The search options are not just limited to User/Room Variables name. In fact the Matching engine provides two extra classes, <b>RoomProperties</b> and <b>UserProperties</b>, 
	/// where you can access many specific attributes of the Room and User class.
	/// 
	/// This is an example of matching specific Room properties and Variables:
	/// <pre>
	/// // Prepare match expression
	/// boost::shared_ptr<bool> value(new bool());
	/// *value = true;
	/// boost::shared_ptr<MatchExpression> exp(new MatchExpression(RoomProperties::IS_GAME, BoolMatch::EQUALS, value));
	/// 
	/// boost::shared_ptr<bool> value1(new bool());
	/// *value1 = true;
	/// exp->And(RoomProperties::HAS_FREE_PLAYER_SLOTS, BoolMatch::EQUALS, value1);
	/// 
	/// // Search Rooms
	/// boost::shared_ptr<IRequest> requestFindRoomsRequest(new FindRoomsRequest(exp));
	/// m_ptrSmartFox->Send(requestFindRoomsRequest);
	/// </pre>
	/// 
	/// <h3>Advanced features</h3>
	/// 	the Match expression offer advanced capabilities of searching through nested data structures such as <strong>SFSObject</strong> and <strong>SFSArray</strong>. 
	/// 	This is done via a very simple <strong>dot-syntax</strong>. Here's an example of how it works:
	/// <pre>
	/// boost::shared_ptr<string> value(new string("Rome"));
	/// boost::shared_ptr<MatchExpression> exp(new MatchExpression("europe.italy.capital", StringMatch::EQUALS, value));
	/// </pre>
	/// 
	/// 	The above example goes down deep into an SFSObject called <em>europe</em>, taking the <em>italy</em> object (another SFSObject) and finally reading its String field <em>capital</em> and matching it with another String.
	/// 	Here is one more examples using SFSObject and SFSArray:
	/// 
	/// <pre>
	/// boost::shared_ptr<string> value(new string("Milan"));
	/// boost::shared_ptr<MatchExpression> exp(new MatchExpression("europe.italy.majorCities.3.name", StringMatch::EQUALS, value));
	/// </pre>	
	/// 
	/// From the <em>italy</em> object we obtain a <em>majorCities</em> SFSArray and we grab the third item in it (the <strong>.3</strong> expression means &#x27;give me the element at index == 3&#x27;). 
	/// The item is again an SFSObject whose <em>name</em> property we finally compare to a String.
	/// 
	/// 	The power of <b>Match Expression</b> doesn't end here. You can run multiple passes of matching if you need complex searches to be performed. For example you can run a first match and obtain a list of filtered Rooms and then use it to apply another expression to further refine your search, and so on and so forth. 
	/// 	<para/>
	/// The power of <b>Match Expression</b> doesn't end here. You can run multiple passes of matching if you need complex searches to be performed. For example you can run a first match and obtain a list of filtered Rooms and then use it to apply another expression to further refine your search, and so on and so forth. 
	/// </remarks>
	/// 
	/// <seealso cref="RoomProperties"/>
	/// <seealso cref="UserProperties"/>
	class DLLImportExport MatchExpression : public boost::enable_shared_from_this<MatchExpression>
	{
	public:

		enum MatchExpressionValueType
		{
			MatchExpression_ValueString,
			MatchExpression_ValueOther
		};

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned char> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<short int> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned short int> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<int> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned int> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long int> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long int> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long long> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long long> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<float> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<double> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<bool> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);
		static boost::shared_ptr<MatchExpression> ChainedMatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<string> value, boost::shared_ptr<LogicOperator> logicOp, boost::shared_ptr<MatchExpression> parent);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="varName">
		/// name of the variable/property to match
		/// </param>
		/// <param name="condition">
		/// the match condition
		/// </param>
		/// <param name="varValue">
		/// the value to match against
		/// </param>
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned char> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<short int> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned short int> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<int> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned int> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long int> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long int> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long long> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long long> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<float> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<double> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<bool> varValue);
		MatchExpression(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<string> varValue);

		/// <summary>
		/// Constructor
		/// </summary>
		/// <param name="varName">
		/// name of the variable/property to match
		/// </param>
		/// <param name="condition">
		/// the match condition
		/// </param>
		/// <param name="varValue">
		/// the value to match against
		/// </param>
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned char> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<short int> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned short int> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<int> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned int> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long int> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long int> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long long> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long long> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<float> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<double> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<bool> varValue);
		MatchExpression(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<string> varValue);

		/// <summary>
		/// Concatenate the current expression with a new one using the logical AND operator
		/// </summary>
		/// <param name="varName">
		/// name of the variable/property to match
		/// </param>
		/// <param name="condition">
		/// the match condition
		/// </param>
		/// <param name="varValue">
		/// the value to match against
		/// </param>
		/// <returns>
		/// a new MatchExpression 
		/// </returns>
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned char> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<short int> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned short int> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<int> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned int> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long int> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long int> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long long> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long long> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<float> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<double> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<bool> varValue);
		boost::shared_ptr<MatchExpression> And(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<string> varValue);

		/// <summary>
		/// Concatenate the current expression with a new one using the logical AND operator
		/// </summary>
		/// <param name="varName">
		/// name of the variable/property to match
		/// </param>
		/// <param name="condition">
		/// the match condition
		/// </param>
		/// <param name="varValue">
		/// the value to match against
		/// </param>
		/// <returns>
		/// a new MatchExpression 
		/// </returns>
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned char> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<short int> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned short int> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<int> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned int> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long int> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long int> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long long> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long long> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<float> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<double> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<bool> varValue);
		boost::shared_ptr<MatchExpression> And(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<string> varValue);

		/// <summary>
		/// Concatenate the current expression with a new one using the logical OR operator
		/// </summary>
		/// <param name="varName">
		/// name of the variable/property to match
		/// </param>
		/// <param name="condition">
		/// the match condition
		/// </param>
		/// <param name="varValue">
		/// the value to match against
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="MatchExpression"/> instance
		/// </returns>
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned char> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<short int> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned short int> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<int> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned int> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long int> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long int> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long long> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long long> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<float> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<double> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<bool> varValue);
		boost::shared_ptr<MatchExpression> Or(boost::shared_ptr<string> varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<string> varValue);

		/// <summary>
		/// Concatenate the current expression with a new one using the logical OR operator
		/// </summary>
		/// <param name="varName">
		/// name of the variable/property to match
		/// </param>
		/// <param name="condition">
		/// the match condition
		/// </param>
		/// <param name="varValue">
		/// the value to match against
		/// </param>
		/// <returns>
		/// Pointer to a <see cref="MatchExpression"/> instance
		/// </returns>
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned char> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<short int> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned short int> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<int> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned int> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long int> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long int> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<long long> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<unsigned long long> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<float> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<double> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<bool> varValue);
		boost::shared_ptr<MatchExpression> Or(string varName, boost::shared_ptr<IMatcher> condition, boost::shared_ptr<string> varValue);

		/// <summary>
		/// Get the name of the variable or property that is being matched.
		/// </summary>
		/// <remarks>
		/// This can be the name of a User/Room variable or a property from the classes listed below.
		/// </remarks>
		/// <seealso cref="RoomProperties"/>
		/// <seealso cref="UserProperties"/>
		boost::shared_ptr<string> VarName();

		/// <summary>
		/// Get the condition used for matching
		/// </summary>
		/// <seealso cref="BoolMatch"/>
		/// <seealso cref="NumberMatch"/>
		/// <seealso cref="StringMatch"/>
		boost::shared_ptr<IMatcher> Condition();

		/// <summary>
		/// The value used to test the condition in the expression
		/// </summary>
		boost::shared_ptr<void> VarValue();

		/// <summary>
		/// Get the current logic operator, could be null if the expression has no other concatenated expressions
		/// </summary>
		/// <seealso cref="LogicOperator"/>
		boost::shared_ptr<LogicOperator> LogicOp();

		/// <summary>
		/// Check if the current expression is concatenated to another one via a logic operator
		/// </summary>
		/// <returns>
		/// A boolean
		/// </returns>
		/// <seealso cref="LogicOperator"/>
		bool HasNext();

		/// <summary>
		/// Get the next expression chained to the current one.
		/// </summary>
		/// <returns>
		/// the next expression chained to the current one.
		/// </returns>
		boost::shared_ptr<MatchExpression> Next();

		/// <summary>
		/// Rewinds the cursor to the first expression in the chain and return the MatchExpression at the top of the chain of expressions
		/// </summary>
		/// <returns>
		/// Pointer to a <see cref="MatchExpression"/> instance
		/// </returns>
		boost::shared_ptr<MatchExpression> Rewind();

		boost::shared_ptr<string> AsString();

		boost::shared_ptr<string> ToString();

		boost::shared_ptr<ISFSArray> ToSFSArray();

		boost::shared_ptr<ISFSArray> ExpressionAsSFSArray();

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
		boost::shared_ptr<LogicOperator> logicOp;
		boost::shared_ptr<MatchExpression> parent;
		boost::shared_ptr<MatchExpression> next;
		
	protected:

		// -------------------------------------------------------------------
		// Protected methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Protected members
		// -------------------------------------------------------------------

	private:

		// -------------------------------------------------------------------
		// Private methods
		// -------------------------------------------------------------------

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------

		// Defines types for varValue
		enum ValueTypes
		{
			ValueTypeUnsignedChar = 0,
			ValueTypeShortInt,
			ValueTypeUnsignedShortInt,
			ValueTypeInt,
			ValueTypeUnsignedInt,
			ValueTypeLongInt,
			ValueTypeUnsignedLongInt,
			ValueTypeLongLong,
			ValueTypeUnsignedLongLong,
			ValueTypeFloat,
			ValueTypeDouble,
			ValueTypeBool,
			ValueTypeString,
		};

		boost::shared_ptr<string> varName;
		boost::shared_ptr<IMatcher> condition;
		boost::shared_ptr<void> varValue;
		ValueTypes varValueDataType;
	};

}	// namespace Match
}	// namespace Entities
}	// namespace Sfs2X

#endif
