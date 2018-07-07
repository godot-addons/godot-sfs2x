// ===================================================================
//
// Description		
//		Contains the definition of ISFSObject interface
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#ifndef __ISFSObject__
#define __ISFSObject__

// Forward class declaration
namespace Sfs2X {
namespace Entities {
namespace Data {
	class ISFSObject;
}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#include "../../Util/ByteArray.h"
#include "SFSDataWrapper.h"
#include "ISFSArray.h"

#include <boost/shared_ptr.hpp>					// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <string>						// STL library: string object
#include <vector>						// STL library: vector object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Util;

namespace Sfs2X {
namespace Entities {
namespace Data {

	/// <summary>
	/// SFSObject interface
	/// </summary>
	class DLLImportExport ISFSObject
	{
	public:
		/// <summary>
		/// Indicates if the value mapped by the specified key is <c>null</c>.
		/// </summary>
		/// 
		/// <param name="key">The key to be checked.</param>
		/// 
		/// <returns><c>true</c> if the value mapped by the passed key is <c>null</c> or the mapping doesn't exist for that key.</returns>
		virtual bool IsNull(string key) = 0;

		/// <summary>
		/// Indicates if the value mapped by the specified key is <c>null</c>.
		/// </summary>
		/// 
		/// <param name="key">The key to be checked.</param>
		/// 
		/// <returns><c>true</c> if the value mapped by the passed key is <c>null</c> or the mapping doesn't exist for that key.</returns>
		virtual bool IsNull(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Indicates whether this object contains a mapping for the specified key or not.
		/// </summary>
		/// 
		/// <param name="key">The key whose presence in this object is to be tested.</param>
		/// 
		/// <returns><c>true</c> if this object contains a mapping for the specified key.</returns>
		virtual bool ContainsKey(string key) = 0;

		/// <summary>
		/// Indicates whether this object contains a mapping for the specified key or not.
		/// </summary>
		/// 
		/// <param name="key">The key whose presence in this object is to be tested.</param>
		/// 
		/// <returns><c>true</c> if this object contains a mapping for the specified key.</returns>
		virtual bool ContainsKey(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Removes the element corresponding to the passed key from this object.
		/// </summary>
		/// 
		/// <param name="key">The key of the element to be removed.</param>
		virtual void RemoveElement(string key) = 0;

		/// <summary>
		/// Removes the element corresponding to the passed key from this object.
		/// </summary>
		/// 
		/// <param name="key">The key of the element to be removed.</param>
		virtual void RemoveElement(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Retrieves a list of all the keys contained in this object.
		/// </summary>
		/// 
		/// <returns>The list of all the keys in this object.</returns>
		virtual boost::shared_ptr<vector<string> > GetKeys() = 0;
		
		/// <summary>
		/// Indicates the number of elements in this object.
		/// </summary>
		/// 
		/// <returns>The number of elements in this object.</returns>
		virtual long int Size() = 0;
		
		/// <summary>
		/// Provides the binary form of this object.
		/// </summary>
		/// 
		/// <returns>The binary data representing this object.</returns>
		virtual boost::shared_ptr<ByteArray> ToBinary() = 0;
		
		/// <summary>
		/// Provides a formatted string representing this object.
		/// </summary>
		/// 
		/// <remarks>
		/// The returned string can be logged or traced in the console for debugging purposes.
		/// </remarks>
		/// 
		/// <param name="format">If <c>true</c>, the output is formatted in a human-readable way.</param>
		/// 
		/// <returns>The string representation of this object.</returns>
		virtual boost::shared_ptr<string> GetDump(bool format) = 0; 
		
		/// <summary>
		/// See <see cref="GetDump(bool)"/>.
		/// </summary>
		virtual boost::shared_ptr<string> GetDump() = 0;  // default to true

		/// <summary>
		/// Provides a detailed hexadecimal representation of this object.
		/// </summary>
		/// 
		/// <remarks>
		/// The returned string can be logged or traced in the console for debugging purposes.
		/// </remarks>
		/// 
		/// <returns>The hexadecimal string representation of this object.</returns>
		virtual boost::shared_ptr<string> GetHexDump() = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type getters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <exclude />
		virtual boost::shared_ptr<SFSDataWrapper> GetData(string key) = 0;
		virtual boost::shared_ptr<SFSDataWrapper> GetData(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a boolean.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>false</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<bool> GetBool(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a boolean.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>false</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<bool> GetBool(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a signed byte (8 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<unsigned char> GetByte(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a signed byte (8 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<unsigned char> GetByte(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a short integer (16 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<short int> GetShort(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a short integer (16 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<short int> GetShort(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an integer (32 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<long int> GetInt(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an integer (32 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<long int> GetInt(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a long integer (64 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<long long> GetLong(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a long integer (64 bits).
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<long long> GetLong(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a floating point number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<float> GetFloat(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a floating point number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<float> GetFloat(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a double precision number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<double> GetDouble(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a double precision number.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>0</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<double> GetDouble(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 32 KBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<string> GetUtfString(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 32 KBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<string> GetUtfString(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 2 GBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<string> GetText(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an UTF-8 string, with max length of 2 GBytes.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object associated with the specified key; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<string> GetText(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of booleans.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of booleans; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<bool> > GetBoolArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of booleans.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of booleans; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<bool> > GetBoolArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a ByteArray object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as a ByteArray object; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<ByteArray> GetByteArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as a ByteArray object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as a ByteArray object; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<ByteArray> GetByteArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of shorts.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of shorts; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<short int> > GetShortArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of shorts.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of shorts; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<short int> > GetShortArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of integers.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of integers; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<long int> > GetIntArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of integers.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of integers; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<long int> > GetIntArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of longs.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of longs; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<long long> > GetLongArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of longs.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of longs; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<long long> > GetLongArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of floats.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of floats; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<float> > GetFloatArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of floats.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of floats; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<float> > GetFloatArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of doubles.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of doubles; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<double> > GetDoubleArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of doubles.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of doubles; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<double> > GetDoubleArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of UTF-8 strings.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of UTF-8 strings; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<string> > GetUtfStringArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an array of UTF-8 strings.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an array of UTF-8 strings; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		virtual boost::shared_ptr<vector<string> > GetUtfStringArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSArray object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSArray interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSArray"/>
		virtual boost::shared_ptr<ISFSArray> GetSFSArray(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSArray object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSArray interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSArray"/>
		virtual boost::shared_ptr<ISFSArray> GetSFSArray(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSObject object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSObject interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSObject"/>
		virtual boost::shared_ptr<ISFSObject> GetSFSObject(string key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an ISFSObject object.
		/// </summary>
		/// 
		/// <param name="key">The key whose associated value is to be returned.</param>
		/// 
		/// <returns>The element of this object as an object implementing the ISFSObject interface; <c>null</c> if a mapping for the passed key doesn't exist.</returns>
		/// 
		/// <seealso cref="SFSObject"/>
		virtual boost::shared_ptr<ISFSObject> GetSFSObject(boost::shared_ptr<string> key) = 0;

		/// <summary>
		/// Returns the element corresponding to the specified key as an instance of a custom class.
		/// </summary>
		/// <remarks>
		/// This advanced feature allows the transmission of specific object instances between client-side C++ and server-side Java provided that:<br/>
		/// - the respective class definitions on both sides have the same package name<br/>
		/// - the following code is executed right after creating the SmartFox object: <c>DefaultSFSDataSerializer.RunningAssembly = Assembly.GetExecutingAssembly();</c> (requires <c>System.Reflection</c> and <c>Sfs2X.Protocol.Serialization</c>)
		/// </remarks>
		/// <example>
		/// This is an example of the same class on the server and client side:
		/// 
		/// <b>Server Java code:</b>
		///			\code{.cpp}
		/// 			package my.game.spacecombat
		/// 
		/// 			public class SpaceShip
		/// 			{
		/// 				private String type;
		/// 				private String name;
		/// 				private int firePower;
		/// 				private int maxSpeed;
		/// 				private List<String> weapons;
		/// 
		/// 				public SpaceShip(String name, String type)
		/// 				{
		/// 					this.name = name;
		/// 					this.type = type;
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		\endcode
		/// 
		/// <b>Client AS3 code:</b>
		///			\code{.cpp}
		/// 		package my.game.spacecombat
		/// 		{
		/// 			public class SpaceShip
		/// 			{
		/// 				private var _type:String
		/// 				private var _name:String
		/// 				private var _firePower:int;
		/// 				private var _maxSpeed:int;
		/// 				private var _weapons:Array;
		/// 
		/// 				public SpaceShip(name:String, type:Strig)
		/// 				{
		/// 					_name = name
		/// 					_type = type
		/// 				}
		/// 
		/// 				// ... Getters / Setters ...
		/// 			}
		/// 		}	
		/// 			
		/// 		\endcode
		/// 
		/// 	A SpaceShip instance from server side is sent to the client. This is how you get it: 
		///		\code{.cpp}
		///			boost::shared_ptr<string> name (new string("spaceShip"));
		///			boost::shared_ptr<SpaceShip> mySpaceShip = (boost::static_pointer_cast<SpaceShip>)sfsObject->getClass(name) 
		/// 	\endcode
		/// </example>
		/// <param name="key">
		/// A string pointer
		/// </param>
		/// <returns>
		/// A void pointer
		/// </returns>
		virtual boost::shared_ptr<void> GetClass(string key) = 0;
		virtual boost::shared_ptr<void> GetClass(boost::shared_ptr<string> key) = 0;

		/*
		* :::::::::::::::::::::::::::::::::::::::::
		* Type setters
		* :::::::::::::::::::::::::::::::::::::::::	
		*/

		/// <exclude />
		virtual void PutNull(string key) = 0;
		virtual void PutNull(boost::shared_ptr<string> key) = 0;
		
		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(string key, boost::shared_ptr<bool> val) = 0;

		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(boost::shared_ptr<string> key, boost::shared_ptr<bool> val) = 0;

		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(string key, bool val) = 0;

		/// <summary>
		/// Associates the passed boolean value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutBool(boost::shared_ptr<string> key, bool val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(string key, boost::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(boost::shared_ptr<string> key, boost::shared_ptr<unsigned char> val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(string key, unsigned char val) = 0;

		/// <summary>
		/// Associates the passed byte value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutByte(boost::shared_ptr<string> key, unsigned char val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(string key, boost::shared_ptr<short int> val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(boost::shared_ptr<string> key, boost::shared_ptr<short int> val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(string key, short int val) = 0;

		/// <summary>
		/// Associates the passed short value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutShort(boost::shared_ptr<string> key, short int val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(string key, boost::shared_ptr<long int> val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(boost::shared_ptr<string> key, boost::shared_ptr<long int> val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(string key, long int val) = 0;

		/// <summary>
		/// Associates the passed integer value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutInt(boost::shared_ptr<string> key, long int val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(string key, boost::shared_ptr<long long> val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(boost::shared_ptr<string> key, boost::shared_ptr<long long> val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(string key, long long val) = 0;

		/// <summary>
		/// Associates the passed long value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutLong(boost::shared_ptr<string> key, long long val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(string key, boost::shared_ptr<float> val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(boost::shared_ptr<string> key, boost::shared_ptr<float> val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(string key, float val) = 0;

		/// <summary>
		/// Associates the passed float value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutFloat(boost::shared_ptr<string> key, float val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(string key, boost::shared_ptr<double> val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(boost::shared_ptr<string> key, boost::shared_ptr<double> val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(string key, double val) = 0;

		/// <summary>
		/// Associates the passed double value with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutDouble(boost::shared_ptr<string> key, double val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(string key, boost::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(boost::shared_ptr<string> key, boost::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(string key, string val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 32 KBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutUtfString(boost::shared_ptr<string> key, string val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(string key, boost::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(boost::shared_ptr<string> key, boost::shared_ptr<string> val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(string key, string val) = 0;

		/// <summary>
		/// Associates the passed UTF-8 string value (max length: 2 GBytes) with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified value is to be associated.</param>
		/// <param name="val">The value to be associated with the specified key.</param>
		virtual void PutText(boost::shared_ptr<string> key, string val) = 0;

		/// <summary>
		/// Associates the passed array of booleans with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of booleans to be associated with the specified key.</param>
		virtual void PutBoolArray(string key, boost::shared_ptr<vector<bool> > val) = 0;

		/// <summary>
		/// Associates the passed array of booleans with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of booleans to be associated with the specified key.</param>
		virtual void PutBoolArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<bool> > val) = 0;

		/// <summary>
		/// Associates the passed ByteArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutByteArray(string key, boost::shared_ptr<ByteArray> val) = 0;

		/// <summary>
		/// Associates the passed ByteArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// <b>IMPORTANT</b>: ByteArrays transmission is not supported in Unity WebGL.
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutByteArray(boost::shared_ptr<string> key, boost::shared_ptr<ByteArray> val) = 0;

		/// <summary>
		/// Associates the passed array of shorts with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of shorts to be associated with the specified key.</param>
		virtual void PutShortArray(string key, boost::shared_ptr<vector<short int> > val) = 0;

		/// <summary>
		/// Associates the passed array of shorts with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of shorts to be associated with the specified key.</param>
		virtual void PutShortArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<short int> > val) = 0;

		/// <summary>
		/// Associates the passed array of integers with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of integers to be associated with the specified key.</param>
		virtual void PutIntArray(string key, boost::shared_ptr<vector<long int> > val) = 0;

		/// <summary>
		/// Associates the passed array of integers with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of integers to be associated with the specified key.</param>
		virtual void PutIntArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<long int> > val) = 0;

		/// <summary>
		/// Associates the passed array of longs with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of longs to be associated with the specified key.</param>
		virtual void PutLongArray(string key, boost::shared_ptr<vector<long long> > val) = 0;

		/// <summary>
		/// Associates the passed array of longs with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of longs to be associated with the specified key.</param>
		virtual void PutLongArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<long long> > val) = 0;

		/// <summary>
		/// Associates the passed array of floats with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of floats to be associated with the specified key.</param>
		virtual void PutFloatArray(string key, boost::shared_ptr<vector<float> > val) = 0;

		/// <summary>
		/// Associates the passed array of floats with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of floats to be associated with the specified key.</param>
		virtual void PutFloatArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<float> > val) = 0;

		/// <summary>
		/// Associates the passed array of doubles with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of doubles to be associated with the specified key.</param>
		virtual void PutDoubleArray(string key, boost::shared_ptr<vector<double> > val) = 0;

		/// <summary>
		/// Associates the passed array of doubles with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of doubles to be associated with the specified key.</param>
		virtual void PutDoubleArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<double> > val) = 0;

		/// <summary>
		/// Associates the passed array of UTF-8 strings with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of UTF-8 strings to be associated with the specified key.</param>
		virtual void PutUtfStringArray(string key, boost::shared_ptr<vector<string> > val) = 0;

		/// <summary>
		/// Associates the passed array of UTF-8 strings with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified array is to be associated.</param>
		/// <param name="val">The array of UTF-8 strings to be associated with the specified key.</param>
		virtual void PutUtfStringArray(boost::shared_ptr<string> key, boost::shared_ptr<vector<string> > val) = 0;

		/// <summary>
		/// Associates the passed ISFSArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSArray(string key, boost::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// Associates the passed ISFSArray object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSArray(boost::shared_ptr<string> key, boost::shared_ptr<ISFSArray> val) = 0;

		/// <summary>
		/// Associates the passed ISFSObject object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSObject(string key, boost::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// Associates the passed ISFSObject object with the specified key in this object.
		/// </summary>
		/// 
		/// <param name="key">The key with which the specified object is to be associated.</param>
		/// <param name="val">The object to be associated with the specified key.</param>
		virtual void PutSFSObject(boost::shared_ptr<string> key, boost::shared_ptr<ISFSObject> val) = 0;

		/// <summary>
		/// Associates the passed custom class instance with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// Read the <see cref="GetClass"/> method description for more informations.
		/// <para/>
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified custom class instance is to be associated.</param>
		/// <param name="val">The custom class instance to be associated with the specified key.</param>
		/// 
		/// <seealso cref="GetClass"/>
		virtual void PutClass(string key, boost::shared_ptr<void> val) = 0;

		/// <summary>
		/// Associates the passed custom class instance with the specified key in this object.
		/// </summary>
		/// 
		/// <remarks>
		/// Read the <see cref="GetClass"/> method description for more informations.
		/// <para/>
		/// </remarks>
		/// 
		/// <param name="key">The key with which the specified custom class instance is to be associated.</param>
		/// <param name="val">The custom class instance to be associated with the specified key.</param>
		/// 
		/// <seealso cref="GetClass"/>
		virtual void PutClass(boost::shared_ptr<string> key, boost::shared_ptr<void> val) = 0;

		/// <exclude/>
		virtual void Put(string key, boost::shared_ptr<SFSDataWrapper> val) = 0;

		/// <exclude/>
		virtual void Put(boost::shared_ptr<string> key, boost::shared_ptr<SFSDataWrapper> val) = 0;
	};

}	// namespace Data
}	// namespace Entities
}	// namespace Sfs2X

#endif
