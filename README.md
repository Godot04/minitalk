# minitalk - Inter-Process Communication using UNIX Signals

![42 school](https://img.shields.io/badge/42-School-000000?style=flat-square&logo=42&logoColor=white)
![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![Norminette](https://img.shields.io/badge/Norminette-passing-success?style=flat-square)

## 📖 About

**minitalk** is a project that implements a simple data exchange program using UNIX signals. It consists of a client and a server that communicate through `SIGUSR1` and `SIGUSR2` signals. The server displays its PID and receives strings sent by the client, which are transmitted bit by bit using only these two signals.

Through this project, I got knowledge of:
- UNIX signal handling and inter-process communication (IPC)
- Bitwise operations and binary data transmission
- Process IDs and signal-based communication protocols
- Real-time data encoding and decoding

## 🎯 Project Goals

- Implement reliable client-server communication using only UNIX signals
- Develop efficient bit-level data transmission
- Handle signal reception and processing in real-time
- Understand low-level inter-process communication mechanisms
- Work with process IDs and signal handlers

## 📚 How It Works

### Signal-Based Communication

The program uses two UNIX signals for binary communication:

- **SIGUSR1** - Represents binary `0`
- **SIGUSR2** - Represents binary `1`

### Transmission Protocol

1. **Server Initialization**: The server starts and displays its PID
2. **Character Encoding**: Each character is sent as 8 bits (1 byte)
3. **Bit Transmission**: Each bit is sent as either SIGUSR1 (0) or SIGUSR2 (1)
4. **Character Assembly**: Server receives 8 signals and reconstructs the character
5. **String Termination**: A null character (8 zero bits) signals the end of transmission

### Data Flow

```
Client                              Server
  |                                    |
  |  1. Get Server PID                 |
  |                                    |
  |  2. Convert char to bits           |
  |     'A' = 01000001                 |
  |                                    |
  |  3. Send bit by bit:               |
  |     SIGUSR1 (0) ---------------->  |
  |     SIGUSR2 (1) ---------------->  |
  |     SIGUSR1 (0) ---------------->  |  4. Receive signals
  |     SIGUSR1 (0) ---------------->  |     and reconstruct
  |     SIGUSR1 (0) ---------------->  |     the character
  |     SIGUSR1 (0) ---------------->  |
  |     SIGUSR1 (0) ---------------->  |
  |     SIGUSR2 (1) ---------------->  |
  |                                    |
  |                                    |  5. Display 'A'
  |                                    |
```

## 🧠 Implementation Strategy

### Server

The server uses `sigaction()` with `SA_SIGINFO` flag to:
- Receive signals from the client
- Track the sender's PID to prevent signal mixing from multiple clients
- Accumulate bits to reconstruct characters
- Display received characters in real-time
- Reset state after receiving null terminator

### Client

The client:
- Takes server PID and message as arguments
- Converts each character to binary representation
- Sends each bit using `kill()` function with appropriate signal
- Uses `usleep()` to ensure reliable signal delivery
- Sends null terminator to signal end of transmission

### Key Features

- **Error Handling**: Validates input arguments and handles signal errors
- **Multi-client Protection**: Server detects and prevents simultaneous transmissions
- **Bit-by-bit Transmission**: Efficient binary encoding using bitwise operations
- **Reliable Delivery**: Small delays ensure signals are not lost
- **Clean Termination**: Proper null character handling

## 🛠️ Compilation

### Building the Program

To compile both client and server, simply run:

```bash
make
```

This creates two executables: `server` and `client`.

### Available Commands

- `make` - Compile both server and client
- `make clean` - Remove object files
- `make fclean` - Remove object files and executables
- `make re` - Recompile everything from scratch

## 🚀 Usage

### Starting the Server

First, start the server:

```bash
./server
```

The server will display its PID:

```
PID: 12345
```

### Sending Messages from Client

In another terminal, use the client to send messages:

```bash
./client [SERVER_PID] [MESSAGE]
```

### Examples

```bash
# Terminal 1: Start server
./server
PID: 12345

# Terminal 2: Send a simple message
./client 12345 "Hello, World!"

# Terminal 1 (server output):
Hello, World!

# Terminal 2: Send another message
./client 12345 "Hey from 42Wolfsburg!"

# Terminal 1 (server output):
Hello, World!Hey from 42Wolfsburg!
```

### Complex Messages

The program supports:
- Special characters: `./client 12345 "Hello! @#$%"`
- Spaces and punctuation: `./client 12345 "Test 123, works?"`
- Unicode characters: `./client 12345 "Hello 世界"`

### Error Handling

The client outputs "Error: invalid input.\n" to standard error for:

- Missing or incorrect number of arguments
- Invalid PID (non-positive or non-numeric)
- Empty message string

The server outputs error messages for:

- Signal handling setup failures
- Simultaneous transmissions from multiple clients

## 📊 Implementation Structure

### Files

- **server.c** - Server implementation with signal handlers
- **client.c** - Client implementation with bit transmission
- **Makefile** - Build configuration for both programs
- **Libft/** - Custom C library for utility functions

## ⚙️ Technical Details

- **Language**: C
- **Compiler**: gcc
- **Flags**: `-Wall -Wextra -Werror`
- **Norm**: 42 Norminette
- **Signals Used**: SIGUSR1, SIGUSR2
- **Dependencies**: libft
- **System Calls**: `signal()`, `sigaction()`, `kill()`, `getpid()`, `pause()`

## 🎮 Testing

You can test the program with various inputs:

```bash
# Test 1: Start server
./server
# Note the PID (e.g., 12345)

# Test 2: Simple message
./client 12345 "Hello"

# Test 3: Numbers and symbols
./client 12345 "Test 123 !@#"

# Test 4: Long message
./client 12345 "The quick brown fox jumps over the lazy dog. Pack my box with five dozen liquor jugs."

# Test 5: Empty message (should error)
./client 12345 ""

# Test 6: Invalid PID (should error)
./client -1 "Test"

# Test 7: Multiple messages in succession
./client 12345 "First"
./client 12345 "Second"
./client 12345 "Third"
```

### Expected Behavior

- ✅ Server displays each complete message
- ✅ Messages appear without corruption
- ✅ Server continues running after each message
- ✅ Client validates input before sending
- ✅ No memory leaks or crashes

## 📝 Notes

- All functions follow the 42 Norminette coding standards
- Memory is properly managed with no leaks
- The implementation uses `SA_SIGINFO` for enhanced signal handling
- Small delays (`usleep(200)`) ensure reliable signal delivery
- Server can only handle one client at a time to prevent signal mixing
- The bitwise transmission is MSB (Most Significant Bit) first
- Null terminator ensures clean message boundaries

## 🔧 Possible Improvements

For bonus features, consider:
- **Acknowledgment System**: Server confirms receipt of each character
- **Unicode Support**: Extended character set handling
- **Multiple Clients**: Queue system for handling concurrent transmissions
- **Optimization**: Reduce transmission delays while maintaining reliability

## 👤 Author

**opopov** - 42 School Student

## 📄 License

This project is part of the 42 School curriculum.
