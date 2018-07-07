// ===================================================================
//
// Description		
//		Contains the implementation of SFSUserManager
//
// Revision history
//		Date			Description
//		30-Nov-2012		First version
//
// ===================================================================
#include "SFSUserManager.h"

namespace Sfs2X {
namespace Entities {
namespace Managers {

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserManager::SFSUserManager(boost::shared_ptr<SmartFox> sfs)
{
	this->sfs = sfs;
	usersByName = boost::shared_ptr<map<string, boost::shared_ptr<User> > >(new map<string, boost::shared_ptr<User> >());
	usersById = boost::shared_ptr<map<long int, boost::shared_ptr<User> > >(new map<long int, boost::shared_ptr<User> >());
	room = boost::shared_ptr<Room>();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
SFSUserManager::SFSUserManager(boost::shared_ptr<Room> room)
{
	this->sfs = boost::shared_ptr<SmartFox>();
	this->room = room;
	usersByName = boost::shared_ptr<map<string, boost::shared_ptr<User> > >(new map<string, boost::shared_ptr<User> >());
	usersById = boost::shared_ptr<map<long int, boost::shared_ptr<User> > >(new map<long int, boost::shared_ptr<User> >());
	room = boost::shared_ptr<Room>();
}

// -------------------------------------------------------------------
// Dispose
// -------------------------------------------------------------------
void SFSUserManager::Dispose()
{
	this->sfs = boost::shared_ptr<SmartFox>();

	if (usersByName != NULL)
	{
		map<string, boost::shared_ptr<User> >::iterator iteratorByName;
		for (iteratorByName = usersByName->begin(); iteratorByName != usersByName->end(); iteratorByName++)
		{
			iteratorByName->second = boost::shared_ptr<User>();
		}
		usersByName->clear();
		usersByName = boost::shared_ptr<map<string, boost::shared_ptr<User> > >();
	}

	if (usersById != NULL)
	{
		map<long int, boost::shared_ptr<User> >::iterator iteratorById;
		for (iteratorById = usersById->begin(); iteratorById != usersById->end(); iteratorById++)
		{
			iteratorById->second = boost::shared_ptr<User>();
		}
		usersById->clear();
		usersById = boost::shared_ptr<map<long int, boost::shared_ptr<User> > >();
	}
}

// -------------------------------------------------------------------
// Destructor
// -------------------------------------------------------------------
SFSUserManager::~SFSUserManager()
{
}

// -------------------------------------------------------------------
// ContainsUserName
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUserName(string userName)
{
	lockUsersByName.lock();

	map<string, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersByName->find(userName);
	bool returned = iterator == usersByName->end() ? false : true;

	lockUsersByName.unlock();

	return returned;
}

// -------------------------------------------------------------------
// ContainsUserId
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUserId(long int userId)
{
	lockUsersById.lock();

	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersById->find(userId);
	bool returned = iterator == usersById->end() ? false : true;

	lockUsersById.unlock();

	return returned;
}

// -------------------------------------------------------------------
// ContainsUser
// -------------------------------------------------------------------
bool SFSUserManager::ContainsUser(boost::shared_ptr<User> user)
{
	lockUsersByName.lock();

	map<string, boost::shared_ptr<User> >::iterator iterator; 
	for (iterator = usersByName->begin(); iterator != usersByName->end(); iterator++)
	{
		if (iterator->second == user)
		{
			lockUsersByName.unlock();
			return true;
		}
	}

	lockUsersByName.unlock();

	return false;
}

// -------------------------------------------------------------------
// GetUserByName
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSUserManager::GetUserByName(string userName)
{
	if (usersByName == NULL)
		return boost::shared_ptr<User>();

	lockUsersByName.lock();

	map<string, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersByName->find(userName);
	boost::shared_ptr<User> user = iterator == usersByName->end() ? boost::shared_ptr<User>() : iterator->second;

	lockUsersByName.unlock();

	return user;
}

// -------------------------------------------------------------------
// GetUserById
// -------------------------------------------------------------------
boost::shared_ptr<User> SFSUserManager::GetUserById(long int userId)
{
	if (usersById == NULL)
		return boost::shared_ptr<User>();

	lockUsersById.lock();

	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersById->find(userId);
	boost::shared_ptr<User> user = iterator == usersById->end() ? boost::shared_ptr<User>() : iterator->second;

	lockUsersById.unlock();

	return user;
}

// -------------------------------------------------------------------
// AddUser
// -------------------------------------------------------------------
void SFSUserManager::AddUser(boost::shared_ptr<User> user)
{
	lockUsersById.lock();

	// Very defensive, no need to fire exception, however we keep it for debugging
	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	iterator = usersById->find(user->Id());

	if (iterator != usersById->end()) 
	{
		boost::shared_ptr<string> message (new string("Unexpected: duplicate user in UserManager: " + (*user->Name())));
		LogWarn(message);
	}
	
	lockUsersById.unlock();

	AddUserInternal(user);
}

// -------------------------------------------------------------------
// RemoveUser
// -------------------------------------------------------------------
void SFSUserManager::RemoveUser(boost::shared_ptr<User> user)
{
	lockUsersById.lock();

	map<long int, boost::shared_ptr<User> >::iterator iteratorById; 
	iteratorById = usersById->find(user->Id());
	if (iteratorById != usersById->end())
	{
		usersById->erase(iteratorById);
	}

	lockUsersById.unlock();

	lockUsersByName.lock();

	map<string, boost::shared_ptr<User> >::iterator iteratorByName; 
	iteratorByName = usersByName->find(*user->Name());
	if (iteratorByName != usersByName->end())
	{
		usersByName->erase(iteratorByName);
	}

	lockUsersByName.unlock();
}

// -------------------------------------------------------------------
// RemoveUserById
// -------------------------------------------------------------------
void SFSUserManager::RemoveUserById(long int id)
{
	lockUsersById.lock();

	map<long int, boost::shared_ptr<User> >::iterator iterator;
	iterator = usersById->find(id);
	if (iterator != usersById->end())
	{
		RemoveUser(iterator->second);
	}

	lockUsersById.unlock();
}

// -------------------------------------------------------------------
// UserCount
// -------------------------------------------------------------------
long int SFSUserManager::UserCount()
{
	return (long int)usersById->size();
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
boost::shared_ptr<SmartFox> SFSUserManager::SmartFoxClient()
{
	return sfs;
}

// -------------------------------------------------------------------
// GetUserList
// -------------------------------------------------------------------
boost::shared_ptr<vector<boost::shared_ptr<User> > > SFSUserManager::GetUserList()
{
	boost::shared_ptr<vector<boost::shared_ptr<User> > > result (new vector<boost::shared_ptr<User> >());
		
	lockUsersById.lock();

	map<long int, boost::shared_ptr<User> >::iterator iterator; 
	for (iterator = usersById->begin(); iterator != usersById->end(); iterator++)
	{
		result->push_back(iterator->second);
	}

	lockUsersById.unlock();

	return result;
}

// -------------------------------------------------------------------
// Constructor
// -------------------------------------------------------------------
void SFSUserManager::ClearAll()
{
	usersById->clear();
	usersByName->clear();
}

// -------------------------------------------------------------------
// LogWarn
// -------------------------------------------------------------------
void SFSUserManager::LogWarn(boost::shared_ptr<string> msg)
{
	if (sfs != NULL) 
	{
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back(*msg);

		sfs->Log()->Warn(messages);
		return;
	}
			
	if (room != NULL && room->RoomManager() != NULL) 
	{
		boost::shared_ptr<vector<string> > messages (new vector<string>());
		messages->push_back(*msg);

		room->RoomManager()->SmartFoxClient()->Log()->Warn(messages);
		return;
	}
}

// -------------------------------------------------------------------
// AddUserInternal
// -------------------------------------------------------------------
void SFSUserManager::AddUserInternal(boost::shared_ptr<User> user)
{
	lockUsersById.lock();
	usersById->insert(pair<long int, boost::shared_ptr<User> >(user->Id(), user));
	lockUsersById.unlock();

	lockUsersByName.lock();
	usersByName->insert(pair<string, boost::shared_ptr<User> >(*user->Name(), user));
	lockUsersByName.unlock();
}

}	// namespace Managers
}	// namespace Entities
}	// namespace Sfs2X
