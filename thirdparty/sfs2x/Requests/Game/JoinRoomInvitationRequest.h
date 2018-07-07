// ===================================================================
//
// Description		
//		Contains the definition of JoinRoomInvitationRequest
//
// Revision history
//		Date			Description
//		30-Nov-2016		First version
//
// ===================================================================
#ifndef __JoinRoomInvitationRequest__
#define __JoinRoomInvitationRequest__

#include "../../Util/Common.h"
#include "../BaseRequest.h"
#include "../../Entities/Data/ISFSObject.h"
#include "../../Entities/Room.h"

#include <boost/shared_ptr.hpp>				// Boost Asio shared pointer

#if defined(_MSC_VER)
#pragma warning(disable:4786)			// STL library: disable warning 4786; this warning is generated due to a Microsoft bug
#endif
#include <list>							// STL library: list object
#include <string>						// STL library: string object
using namespace std;					// STL library: declare the STL namespace

using namespace Sfs2X::Entities::Data;

namespace Sfs2X {
namespace Requests {
namespace Game {

	/// <summary>
	/// Sends an invitation to other users/players to join a specific Room.
	/// </summary>
	/// 
	/// <remarks>
	/// Invited users receive the invitation as an <see cref="Sfs2X.Core.SFSEvent.INVITATION"/> event dispatched to their clients: they can accept or refuse it
	/// by means of the InvitationReplyRequest request, which must be sent within the specified amount of time.
	/// <para/>
	/// Depending on the Room's settings this invitation can be sent by the Room's owner only or by any other user.
	/// This behavior can be set via the RoomSettings.AllowOwnerOnlyInvitation parameter.
	/// <para/>
	/// <b>NOTE:</b> spectators in a Game Room are not allowed to invite other users; only players are.
	/// <para/>
	/// An invitation can also specify the amount of time given to each invitee to reply. Default is 30 seconds.
	/// A positive answer will attempt to join the user in the designated Room. For Game Rooms the <em>asSpectator</em> flag can be toggled to join the invitee as player or spectator (default = player).
	/// <para/>
	/// There aren't any specific notifications sent back to the inviter after the invitee's response. Users that have accepted the invitation will join the Room while those who didn't reply or turned down the invitation won't generate any event.
	/// In order to send specific messages (e.g. chat), just send a private message back to the inviter.
	/// </remarks>
	/// 
	/// <example>
	/// The following example invites two more users in the current game:
	///		\code{.cpp}
	///		void SomeMethod() 
	///		{
	///			ptrSmartFox->AddEventListener(SFSEvent::USER_ENTER_ROOM, boost::shared_ptr<EventListenerDelegate> (new EventListenerDelegate(CMyClass::onUserJoin, (unsigned long long)this)));
	///
	///			boost::shared_ptr<list<string> > invitedUsers(new list<string>());
	///			invitedUsers->push_back("Fozzie");
	///			invitedUsers->push_back("Piggy");
	/// 	
	///			boost::shared_ptr<Room> room = ptrSmartFox->GetRoomByName("The Garden");
	///		
	/// 		// Add message to be shown to the invited users
	/// 		boost::shared_ptr<ISFSObject> params= SFSObject.NewInstance();
	/// 		params.PutUtfString("msg", "You are invited in this Room: " + room->Name());
	///
	/// 		// Send the request
	///			boost::shared_ptr<IRequest> request (new JoinRoomInvitationRequest(room, invitedUsers, params));
	///			ptrSmartFox->Send(request);
	///		}
	///
	///		static void onUserJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent);
	///
	///		void CMyClass::onUserJoin(unsigned long long ptrContext, boost::shared_ptr<BaseEvent> ptrEvent) 
	///		{
	///			// Get the pointer to my class
	///			CMyClass* instance = (CMyClass*)ptrContext;
	///
	///			boost::shared_ptr<void> ptrEventParamValueUser = (*ptrEventParams)["user"];
	///			boost::shared_ptr<User> ptrUser = ((boost::static_pointer_cast<User>))(ptrEventParamValueUser);
	///
	/// 		System.Diagnostics.Debug.WriteLine("Room joined by: " + user->Name());		// for win8 and win phone
	///		}
	/// 	\endcode
	/// </example>
	/// 
	/// <seealso cref="Sfs2X.Requests.RoomSettings"/>
	class DLLImportExport JoinRoomInvitationRequest : public BaseRequest
	{
	public:

		// -------------------------------------------------------------------
		// Public methods
		// -------------------------------------------------------------------

		/// <summary>
		/// Creates a new JoinRoomInvitationRequest instance.
		/// </summary>
		/// 
		/// <remarks>
		/// The instance must be passed to the <see cref="Sfs2X.SmartFox.Send">SmartFox.Send</see> method for the request to be performed.
		/// </remarks>
		/// 
		/// <param name="targetRoom">The Room to join (must have free user/player slots).</param>
		/// <param name="invitedUserNames">A list of user names to invite.</param>
		/// <param name="parameters">An instance of <see cref="Sfs2X.Entities.Data.SFSObject"/> containing any relevant parameter or message to be sent to the invited users (for example an invitation message). Default is <c>null</c>.</param>
		/// <param name="expirySeconds">The time given to the invitee to reply to the invitation. Default is 30.</param>
		/// <param name="asSpectator">In Game Rooms only, indicates if the invited user(s) should join as spectator(s) instead of player(s). Default is <c>false</c>.</param>
		JoinRoomInvitationRequest(boost::shared_ptr<Room> targetRoom, boost::shared_ptr<list<string> > invitedUserNames, boost::shared_ptr<ISFSObject> parameters, long int expirySeconds, bool asSpectator);

		/// <summary>
		/// See <em>JoinRoomInvitationRequest(boost::shared_ptr&lt;Room&gt;, boost::shared_ptr&lt;list&lt;string&gt; &gt;, boost::shared_ptr&lt;ISFSObject&gt;, long int, bool)</em> constructor.
		/// </summary>
		JoinRoomInvitationRequest(boost::shared_ptr<Room> targetRoom, boost::shared_ptr<list<string> > invitedUserNames, boost::shared_ptr<ISFSObject> parameters, long int expirySeconds);

		/// <summary>
		/// See <em>JoinRoomInvitationRequest(boost::shared_ptr&lt;Room&gt;, boost::shared_ptr&lt;list&lt;string&gt; &gt;, boost::shared_ptr&lt;ISFSObject&gt;, long int, bool)</em> constructor.
		/// </summary>
		JoinRoomInvitationRequest(boost::shared_ptr<Room> targetRoom, boost::shared_ptr<list<string> > invitedUserNames, boost::shared_ptr<ISFSObject> parameters);

		/// <summary>
		/// See <em>JoinRoomInvitationRequest(boost::shared_ptr&lt;Room&gt;, boost::shared_ptr&lt;list&lt;string&gt; &gt;, boost::shared_ptr&lt;ISFSObject&gt;, long int, bool)</em> constructor.
		/// </summary>
		JoinRoomInvitationRequest(boost::shared_ptr<Room> targetRoom, boost::shared_ptr<list<string> > invitedUserNames);

		virtual ~JoinRoomInvitationRequest();

		void Validate(boost::shared_ptr<SmartFox> sfs);

		void Execute (boost::shared_ptr<SmartFox> sfs);

		// -------------------------------------------------------------------
		// Public members
		// -------------------------------------------------------------------
	
		/// <exclude/>
		static boost::shared_ptr<string> KEY_ROOM_ID;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_EXPIRY_SECONDS;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_INVITED_NAMES;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_AS_SPECT;

		/// <exclude/>
		static boost::shared_ptr<string> KEY_OPTIONAL_PARAMS;

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
		void Init(boost::shared_ptr<Room> targetRoom, boost::shared_ptr<list<string> > invitedUserNames, boost::shared_ptr<ISFSObject> parameters, long int expirySeconds, bool asSpectator);

		// -------------------------------------------------------------------
		// Private members
		// -------------------------------------------------------------------
		boost::shared_ptr<Room> targetRoom;
		boost::shared_ptr<list<string> > invitedUserNames;
		long int expirySeconds;
		bool asSpectator;
		boost::shared_ptr<ISFSObject> parameters;
	};

}	// namespace Game
}	// namespace Requests
}	// namespace Sfs2X

#endif
