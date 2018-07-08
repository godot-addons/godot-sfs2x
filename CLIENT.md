# SFS2X Client API Examples

## Connectors

### SFSEvent Types

```
HANDSHAKE = "handshake"
UDP_INIT = "udpInit"
CONNECTION = "connection"
PING_PONG = "pingPong"
SOCKET_ERROR = "socketError"
CONNECTION_LOST = "connectionLost"
CONNECTION_RETRY = "connectionRetry"
CONNECTION_RESUME = "connectionResume"
CONNECTION_ATTEMPT_HTTP = "connectionAttemptHttp"
CONFIG_LOAD_SUCCESS = "configLoadSuccess"
CONFIG_LOAD_FAILURE = "configLoadFailure"
LOGIN = "login"
LOGIN_ERROR = "loginError"
LOGOUT = "logout"
ROOM_ADD = "roomAdd"
ROOM_REMOVE = "roomRemove"
ROOM_CREATION_ERROR = "roomCreationError"
ROOM_JOIN = "roomJoin"
ROOM_JOIN_ERROR = "roomJoinError"
USER_ENTER_ROOM = "userEnterRoom"
USER_EXIT_ROOM = "userExitRoom"
USER_COUNT_CHANGE = "userCountChange"
PUBLIC_MESSAGE = "publicMessage"
PRIVATE_MESSAGE = "privateMessage"
MODERATOR_MESSAGE = "moderatorMessage"
ADMIN_MESSAGE = "adminMessage"
OBJECT_MESSAGE = "objectMessage"
EXTENSION_RESPONSE = "extensionResponse"
ROOM_VARIABLES_UPDATE = "roomVariablesUpdate"
USER_VARIABLES_UPDATE = "userVariablesUpdate"
ROOM_GROUP_SUBSCRIBE = "roomGroupSubscribe"
ROOM_GROUP_UNSUBSCRIBE = "roomGroupUnsubscribe"
ROOM_GROUP_SUBSCRIBE_ERROR = "roomGroupSubscribeError"
ROOM_GROUP_UNSUBSCRIBE_ERROR = "roomGroupUnsubscribeError"
SPECTATOR_TO_PLAYER = "spectatorToPlayer"
PLAYER_TO_SPECTATOR = "playerToSpectator"
SPECTATOR_TO_PLAYER_ERROR = "spectatorToPlayerError"
PLAYER_TO_SPECTATOR_ERROR = "playerToSpectatorError"
ROOM_NAME_CHANGE = "roomNameChange"
ROOM_NAME_CHANGE_ERROR = "roomNameChangeError"
ROOM_PASSWORD_STATE_CHANGE = "roomPasswordStateChange"
ROOM_PASSWORD_STATE_CHANGE_ERROR = "roomPasswordStateChangeError"
ROOM_CAPACITY_CHANGE = "roomCapacityChange"
ROOM_CAPACITY_CHANGE_ERROR = "roomCapacityChangeError"
ROOM_FIND_RESULT = "roomFindResult"
USER_FIND_RESULT = "userFindResult"
INVITATION = "invitation"
INVITATION_REPLY = "invitationReply"
INVITATION_REPLY_ERROR = "invitationReplyError"
PROXIMITY_LIST_UPDATE = "proximityListUpdate"
MMOITEM_VARIABLES_UPDATE = "mmoItemVariablesUpdate"
CRYPTO_INIT = "cryptoInit"
```

### Java

```kotlin
class Example {
  private val sfs = SmartFox()
  private val cfg = ConfigData()

  init {
    // Method 1
    sfs.addEventListener(SFSEvent.CONNECTION, this)
    sfs.addEventListener(SFSEvent.CONNECTION_LOST, this)
    sfs.addEventListener(SFSEvent.LOGIN, this)
    sfs.addEventListener(SFSEvent.LOGIN_ERROR, this)

    // Method 2
    sfs.addEventListener(SFSEvent.CONNECTION, onConnection)
    sfs.addEventListener(SFSEvent.CONNECTION, onConnectionLost)

    // Method 3
    sfs.addEventListener(SFSEvent.CONNECTION) { sfs.send(LoginRequest("", "", sfs.currentZone)) }

    // Method 1
    sfs.connect() // defaults to localhost:9933

    // Method 2
    sfs.connect("localhost", 9933)

    // Method 3
    cfg.host = "localhost"
    cfg.port = 9933
    cfg.zone = "ExampleZone"
    sfs.connect(cfg)
  }

  // Method 1, single method which will switch on the event type
  fun dispatch(evt: BaseEvent) {
    when (evt.type) {
      SFSEvent.CONNECTION -> sfs.send(LoginRequest("", "", sfs.currentZone))
      SFSEvent.CONNECTION_LOST) -> log.info("Connection was closed")
      SFSEvent.LOGIN -> log.info("Logged in as: " + sfs.mySelf.name)
      SFSEvent.LOGIN_ERROR -> log.warn("Login error:  " + evt.arguments.get("errorMessage"))
    }
  }

  // Method 2, individual methods to handle an event
  fun onConnection(evt: BaseEvent) {
    sfs.send(LoginRequest("username", "password", sfs.currentZone))
  }

  // Method 2, individual methods to handle an event
  fun onConnectionLost(evt: BaseEvent) {
    log.info("Connection was closed")
  }
}
```

```csharp
public class Example
{
  private SmartFox sfs = new SmartFox();
  private ConfigData cfg = new ConfigData();

  public void Start()
  {
    sfs.ThreadSafeMode = false;

    sfs.AddEventListener(SFSEvent.CONNECTION, OnConnection);
    sfs.AddEventListener(SFSEvent.CONNECTION_LOST, OnConnectionLost);
    sfs.addEventListener(SFSEvent.LOGIN, OnLogin);
    sfs.addEventListener(SFSEvent.LOGIN_ERROR, OnLoginError);

    sfs.AddLogListener(LogLevel.INFO, OnInfoMessage);
    sfs.AddLogListener(LogLevel.WARN, OnWarnMessage);
    sfs.AddLogListener(LogLevel.ERROR, OnErrorMessage);

    // Method 1
    sfs.connect(); // defaults to localhost:9933

    // Method 2
    sfs.connect("localhost", 9933);

    // Method 3
    cfg.Host = "localhost";
    cfg.Port = 9933;
    cfg.Zone = "ExampleZone";
    sfs.Connect(cfg);
  }

  public void OnConnection(BaseEvent evt)
  {
    sfs.Send(new LoginRequest("username", "password", sfs.currentZone));
  }
}
```

```gdscript
class Example:
  var sfs
  var cfg

  func _init():
    sfs = SmartFox.new()
    cfg = ConfigData.new()

    sfs.add_event_listener(SFSEvent.CONNECTION, self, "on_connection")
    sfs.add_event_listener(SFSEvent.CONNECTION_LOST, self, "on_connection_lost")
    sfs.add_event_listener(SFSEvent.LOGIN, self, "on_login")
    sfs.add_event_listener(SFSEvent.LOGIN_ERROR, self, "on_login_error")

  func on_connection(evt):
    sfs.send(LoginRequest.new("username", "password", sfs.current_zone))

  func on_connection_lost(evt):
    log.info("Connection was closed")

  func on_login(evt):
    log.info("Logged in as: " + sfs.myself.name)

  func on_login_error(evt):
    log.warn("Login error:  " + evt.arguments.get("errorMessage"))
```
