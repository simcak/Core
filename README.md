*This project has been created as part of the 42 curriculum by **psimcak**, **cberneri**, **rludvik**.*

## Description

**ft_irc** is a minimal IRC server written in **C++98**.  
It accepts multiple TCP clients using **non-blocking sockets** and a single **poll()** loop, parses IRC lines, performs user registration (PASS/NICK/USER), and supports basic channel and messaging features required for the 42 *ft_irc* project.

Core goals:
- implement a small, correct subset of the IRC protocol
- manage many clients concurrently without threads
- maintain consistent server/channel/user state (join/part/quit cleanup)

## Instructions

### Compilation

```bash
make
```

### Execution

```bash
./ircserv <port> <password>
```

### Quick usage (raw test with netcat)

```bash
nc 127.0.0.1 6667
PASS password
NICK alice
USER alice 0 * :Alice Example
JOIN #42
PRIVMSG #42 :hello everyone
```

Notes:
- Registration is considered complete only after **PASS + NICK + USER**.
- Input is handled as IRC lines terminated by `\r\n` (or `\n` with optional `\r`).

## Supported commands

### Registration / connection
- `NICK <nickname>` (allowed chars: alnum + `_ - [ ]`)
- `USER <username> <ip> <servername> :<realname>`
- `PASS <password>`
- `QUIT [:reason]`

### Channels / queries
- `JOIN #channel [key]`
- `PART #channel [:message]`
- `TOPIC #channel [topic]`
- `NAMES [#chan1,#chan2,...]`
- `LIST [#chan1,#chan2,...]`
- `WHO <#channel|nick|*>`

### Messaging
- `PRIVMSG <nick>/<channel> :<text>`

### Operator / moderation
- `KICK #channel <nick> [:reason]`
- `INVITE <nick> #channel`
- `MODE #channel [modes [params...]]`

Examples for `MODE` command:
- `MODE #channel`                  <- queries current modes
- `MODE #channel +/-i`             <- sets/unsets invite-only
- `MODE #channel +/-t`             <- sets/unsets topic-protected
- `MODE #channel +/-k secretkey`   <- sets/removes key
- `MODE #channel +/-o usernick`    <- gives/removes operator status
- `MODE #channel +l 10`            <- sets user limit to 10

Behavior:
- The first user to join a new channel becomes an operator.
- If operators leave, no new operators are assigned automatically.
- When `+i` is enabled, invitations are consumed on successful JOIN.
- Empty channels are deleted.

## Technical overview

- **Concurrency:** one thread, `poll()` + non-blocking sockets (`O_NONBLOCK`)
- **Buffers per client:**
  - input buffer accumulates bytes until a full line arrives
  - output buffer queues server replies and flushes on writable events
- **Parsing:** `parseIrcLine()` supports `:prefix`, command, parameters, and `:trailing` (spaces)
- **Dispatch:** command string → member-function pointer lookup (`std::map`)
- **Numerics:** helper for IRC numeric replies (`001/002/003/004`, `3xx`, `4xx`, ...)

## Repository layout (key files)

- `main.cpp` — argument validation and server start
- `headers/Server.hpp`, `srcs/Server.cpp` — socket setup, poll loop, dispatch, shutdown
- `headers/User.hpp`, `srcs/User.cpp` — per-client state (buffers, nick/user/realname)
- `headers/Channel.hpp`, `srcs/Channel.cpp` — channel state (members, ops, bans, invites, modes)
- `headers/Message.hpp`, `srcs/Message.cpp` — IRC line parsing
- `headers/NumReply.hpp` — numeric reply codes
- `srcs/cmds/*` — individual command handlers

## Resources

Classic references:
- [ircgod](https://ircgod.com/)
- [Medium article: Small IRC Server](https://medium.com/@afatir.ahmedfatir/small-irc-server-ft-irc-42-network-7cee848de6f9)
- IRC message format and numerics: **[RFC 2812](https://datatracker.ietf.org/doc/html/rfc2812)**

How AI was used:
- Used ChatGPT to **draft and iterate** this README (structure, wording, and command summary).
- Used ChatGPT during development to **explain protocol details**, **review parsing/dispatch ideas**, and **spot edge cases** in command handling.
- All final code decisions and implementation were made by the project team and validated by compiling/running locally.