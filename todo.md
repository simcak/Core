# TODO steps

 -[X] make channel class
 -[ ] handle JOIN
    -[ ] validate input
    -[ ]  
    -[ ] 
    -[ ] 
    -[ ] 

# TODO Qs
 - How are we handling if two users have the same Nickname (on joining the server?

# TODO capablites

 - User commands
     -[X] NICK
     -[ ] USER
     -[ ] JOIN
     -[ ] PART
     -[ ] PRIVMSG
     -[ ] NOTICE
     -[ ] PING
     -[X] PONG
     -[ ] QUIT
     -[ ] OPER (Added by R to make user a chanel operator)
 - Channel modes: 
     -[ ] +i
     -[ ] +t
     -[ ] +k
     -[ ] +o
     -[ ] +l

- Operator commands
     -[ ] KICK
     -[ ] INVITE
     -[ ] TOPIC
     -[ ] MODE

---

# Notes
 - I chose the `sic` IRC client as refference for it's super simplicity and ease of install on school PCs (it's just 200 lines of C)
   - I reccomend cloning and  `sudo make install` on your own machine

## Standrads and whatevs
 - Since we can use macros now I created 3 for sending messages to the terminal in a uniform way [ERROR(), INFO(), DEBG()] they are just streams so work with them like that way eg. `ERROR(msg << another_msg)`
 - There is also a `NumReply.hpp` that defines all num replyes

---
# Command Reference

## USER commands

### OPER
4.1.5 Oper

      Command: OPER
   Parameters: <user> <password>

   OPER message is used by a normal user to obtain operator privileges.
   The combination of <user> and <password> are required to gain
   Operator privileges.

   If the client sending the OPER command supplies the correct password
   for the given user, the server then informs the rest of the network
   of the new operator by issuing a "MODE +o" for the clients nickname.

   The OPER message is client-server only.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              RPL_YOUREOPER
           ERR_NOOPERHOST                  ERR_PASSWDMISMATCH

   Example:

   OPER foo bar                    ; Attempt to register as an operator
                                   using a username
                            
### QUIT

4.1.6 Quit

      Command: QUIT
   Parameters: [<Quit message>]

   A client session is ended with a quit message.  The server must close
   the connection to a client which sends a QUIT message. If a "Quit
   Message" is given, this will be sent instead of the default message,
   the nickname.

   When netsplits (disconnecting of two servers) occur, the quit message is composed of the names of two servers involved, separated by a
   space.  The first name is that of the server which is still connected
   and the second name is that of the server that has become
   disconnected.

   If, for some other reason, a client connection is closed without  the
   client  issuing  a  QUIT  command  (e.g.  client  dies and EOF occurs
   on socket), the server is required to fill in the quit  message  with
   some sort  of  message  reflecting the nature of the event which
   caused it to happen.

   Numeric Replies:

           None.

   Examples:

   QUIT :Gone to have lunch        ; Preferred message format.

### JOIN

Command: JOIN
   Parameters: <channel>{,<channel>} [<key>{,<key>}]

   The JOIN command is used by client to start listening a specific
   channel. Whether or not a client is allowed to join a channel is
   checked only by the server the client is connected to; all other
   servers automatically add the user to the channel when it is received
   from other servers.  The conditions which affect this are as follows:

           1.  the user must be invited if the channel is invite-only;

           2.  the user's nick/username/hostname must not match any
               active bans;

           3.  the correct key (password) must be given if it is set.

   These are discussed in more detail under the MODE command (see
   section 4.2.3 for more details).

   Once a user has joined a channel, they receive notice about all
   commands their server receives which affect the channel.  This
   includes MODE, KICK, PART, QUIT and of course PRIVMSG/NOTICE.  The
   JOIN command needs to be broadcast to all servers so that each server
   knows where to find the users who are on the channel.  This allows
   optimal delivery of PRIVMSG/NOTICE messages to the channel.

   If a JOIN is successful, the user is then sent the channel's topic
   (using RPL_TOPIC) and the list of users who are on the channel (using
   RPL_NAMREPLY), which must include the user joining.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_BANNEDFROMCHAN
           ERR_INVITEONLYCHAN              ERR_BADCHANNELKEY
           ERR_CHANNELISFULL               ERR_BADCHANMASK
           ERR_NOSUCHCHANNEL               ERR_TOOMANYCHANNELS
           RPL_TOPIC

   Examples:

   JOIN #foobar                    ; join channel #foobar.

   JOIN &foo fubar                 ; join channel &foo using key "fubar".

   JOIN #foo,&bar fubar            ; join channel #foo using key "fubar"
                                   and &bar using no key.

   JOIN #foo,#bar fubar,foobar     ; join channel #foo using key "fubar".
                                   and channel #bar using key "foobar".

   JOIN #foo,#bar                  ; join channels #foo and #bar.

   :WiZ JOIN #Twilight_zone        ; JOIN message from WiZ

### PART

4.2.2 Part message

      Command: PART
   Parameters: <channel>{,<channel>}

   The PART message causes the client sending the message to be removed
   from the list of active users for all given channels listed in the
   parameter string.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_NOTONCHANNEL

   Examples:

   PART #twilight_zone             ; leave channel "#twilight_zone"

   PART #oz-ops,&group5            ; leave both channels "&group5" and
                                   "#oz-ops".

### PRIVMSG
4.4.1 Private messages

      Command: PRIVMSG
   Parameters: <receiver>{,<receiver>} <text to be sent>

   PRIVMSG is used to send private messages between users.  <receiver>
   is the nickname of the receiver of the message.  <receiver> can also
   be a list of names or channels separated with commas.

   The <receiver> parameter may also me a host mask  (#mask)  or  server
   mask  ($mask).   In  both cases the server will only send the PRIVMSG
   to those who have a server or host matching the mask.  The mask  must
   have at  least  1  (one)  "."  in it and no wildcards following the
   last ".".  This requirement exists to prevent people sending messages
   to  "#*"  or "$*",  which  would  broadcast  to  all  users; from
   experience, this is abused more than used responsibly and properly.
   Wildcards are  the  '*' and  '?'   characters.   This  extension  to
   the PRIVMSG command is only available to Operators.

   Numeric Replies:

           ERR_NORECIPIENT                 ERR_NOTEXTTOSEND
           ERR_CANNOTSENDTOCHAN            ERR_NOTOPLEVEL
           ERR_WILDTOPLEVEL                ERR_TOOMANYTARGETS
           ERR_NOSUCHNICK
           RPL_AWAY

   Examples:

:Angel PRIVMSG Wiz :Hello are you receiving this message ?
                                ; Message from Angel to Wiz.

PRIVMSG Angel :yes I'm receiving it !receiving it !'u>(768u+1n) .br ;
                                Message to Angel.

PRIVMSG jto@tolsun.oulu.fi :Hello !
                                ; Message to a client on server
                                tolsun.oulu.fi with username of "jto".

PRIVMSG $*.fi :Server tolsun.oulu.fi rebooting.
                                ; Message to everyone on a server which
                                has a name matching *.fi.

PRIVMSG #*.edu :NSFNet is undergoing work, expect interruptions
                                ; Message to all users who come from a
                                host which has a name matching *.edu.

### NOTICE

4.4.2 Notice

      Command: NOTICE
   Parameters: <nickname> <text>

   The NOTICE message is used similarly to PRIVMSG.  The difference
   between NOTICE and PRIVMSG is that automatic replies must never be
   sent in response to a NOTICE message.  This rule applies to servers
   too - they must not send any error reply back to the client on
   receipt of a notice.  The object of this rule is to avoid loops
   between a client automatically sending something in response to
   something it received.  This is typically used by automatons (clients
   with either an AI or other interactive program controlling their
   actions) which are always seen to be replying lest they end up in a
   loop with another automaton.

   See PRIVMSG for more details on replies and examples.

### PING

4.6.2 Ping message

      Command: PING
   Parameters: <server1> [<server2>]

   The PING message is used to test the presence of an active client at
   the other end of the connection.  A PING message is sent at regular
   intervals if no other activity detected coming from a connection.  If
   a connection fails to respond to a PING command within a set amount
   of time, that connection is closed.

   Any client which receives a PING message must respond to <server1>
   (server which sent the PING message out) as quickly as possible with
   an appropriate PONG message to indicate it is still there and alive.
   Servers should not respond to PING commands but rely on PINGs from
   the other end of the connection to indicate the connection is alive.
   If the <server2> parameter is specified, the PING message gets
   forwarded there.

   Numeric Replies:

           ERR_NOORIGIN                    ERR_NOSUCHSERVER

   Examples:

   PING tolsun.oulu.fi             ; server sending a PING message to
                                   another server to indicate it is still
                                   alive.

   PING WiZ                        ; PING message being sent to nick WiZ

### PONG


4.6.3 Pong message

      Command: PONG
   Parameters: <daemon> [<daemon2>]

   PONG message is a reply to ping message.  If parameter <daemon2> is
   given this message must be forwarded to given daemon.  The <daemon>
   parameter is the name of the daemon who has responded to PING message
   and generated this message.

   Numeric Replies:

           ERR_NOORIGIN                    ERR_NOSUCHSERVER

   Examples:

   PONG csd.bu.edu tolsun.oulu.fi  ; PONG message from csd.bu.edu to
                                   tolsun.oulu.fi

## Operator commands

### MODE command

4.2.3 Mode message

      Command: MODE

   The MODE command is a dual-purpose command in IRC.  It allows both
   usernames and channels to have their mode changed.  The rationale for
   this choice is that one day nicknames will be obsolete and the
   equivalent property will be the channel.

   When parsing MODE messages, it is recommended that the entire message
   be parsed first and then the changes which resulted then passed on.

#### MODE options

4.2.3.1 Channel modes

   Parameters: <channel> {[+|-]|o|p|s|i|t|n|b|v} [<limit>] [<user>]
               [<ban mask>]

   The MODE command is provided so that channel operators may change the
   characteristics of `their' channel.  It is also required that servers
   be able to change channel modes so that channel operators may be
   created.

   The various modes available for channels are as follows:

           o - give/take channel operator privileges;
           p - private channel flag;
           s - secret channel flag;
           i - invite-only channel flag;
           t - topic settable by channel operator only flag;
           n - no messages to channel from clients on the outside;
           m - moderated channel;
           l - set the user limit to channel;

(we are supposed to do +i +t +k +o +l)

### TOPIC

4.2.4 Topic message

      Command: TOPIC
   Parameters: <channel> [<topic>]

   The TOPIC message is used to change or view the topic of a channel.
   The topic for channel <channel> is returned if there is no <topic>
   given.  If the <topic> parameter is present, the topic for that
   channel will be changed, if the channel modes permit this action.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOTONCHANNEL
           RPL_NOTOPIC                     RPL_TOPIC
           ERR_CHANOPRIVSNEEDED

   Examples:

   :Wiz TOPIC #test :New topic     ;User Wiz setting the topic.

   TOPIC #test :another topic      ;set the topic on #test to "another
                                   topic".

   TOPIC #test                     ; check the topic for #test.

### INVITE

4.2.7 Invite message

      Command: INVITE
   Parameters: <nickname> <channel>

   The INVITE message is used to invite users to a channel.  The
   parameter <nickname> is the nickname of the person to be invited to
   the target channel <channel>.  There is no requirement that the
   channel the target user is being invited to must exist or be a valid
   channel.  To invite a user to a channel which is invite only (MODE
   +i), the client sending the invite must be recognised as being a
   channel operator on the given channel.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHNICK
           ERR_NOTONCHANNEL                ERR_USERONCHANNEL
           ERR_CHANOPRIVSNEEDED
           RPL_INVITING                    RPL_AWAY

   Examples:

   :Angel INVITE Wiz #Dust         ; User Angel inviting WiZ to channel
                                   #Dust

   INVITE Wiz #Twilight_Zone       ; Command to invite WiZ to
                                   #Twilight_zone

### KICK

4.2.8 Kick command

      Command: KICK
   Parameters: <channel> <user> [<comment>]

   The KICK command can be  used  to  forcibly  remove  a  user  from  a
   channel.   It  'kicks  them  out'  of the channel (forced PART)
   Only a channel operator may kick another user out of a  channel.
   Each  server that  receives  a KICK message checks that it is valid
   (ie the sender is actually a  channel  operator)  before  removing
   the  victim  from  the channel.

   Numeric Replies:

           ERR_NEEDMOREPARAMS              ERR_NOSUCHCHANNEL
           ERR_BADCHANMASK                 ERR_CHANOPRIVSNEEDED
           ERR_NOTONCHANNEL

   Examples:

KICK &Melbourne Matthew         ; Kick Matthew from &Melbourne

KICK #Finnish John :Speaking English
                                ; Kick John from #Finnish using
                                "Speaking English" as the reason
                                (comment).

:WiZ KICK #Finnish John         ; KICK message from WiZ to remove John
                                from channel #Finnish

NOTE:
     It is possible to extend the KICK command parameters to the
following:

<channel>{,<channel>} <user>{,<user>} [<comment>]
