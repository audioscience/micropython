# Test that asyncio.open_connection cleans up sockets on error paths:
#   - immediate connect failure (non-EINPROGRESS) closes the raw socket
#   - ssl.wrap_socket() failure closes the raw socket

import sys

if sys.platform != "linux":
    print("SKIP")
    raise SystemExit

try:
    import asyncio
    import gc
    import os
    import socket
except ImportError:
    print("SKIP")
    raise SystemExit


def count_fds():
    return len(os.listdir("/proc/self/fd"))


# -- Test 1: immediate connect error --
# Replace the socket module so connect() raises a non-EINPROGRESS OSError.
# Verify the socket's close() is called exactly once per attempt.

async def test_connect_error():
    real_mod = sys.modules["socket"]
    close_count = [0]

    class MockSock:
        def __init__(self, *a, **kw):
            pass

        def setblocking(self, v):
            pass

        def connect(self, addr):
            raise OSError(111)  # ECONNREFUSED

        def close(self):
            close_count[0] += 1

    class MockSocketMod:
        SOCK_STREAM = 1
        socket = MockSock

        @staticmethod
        def getaddrinfo(host, port, family=0, type=0):
            return [(2, 1, 0, "", (host, port))]

    sys.modules["socket"] = MockSocketMod
    try:
        for _ in range(5):
            try:
                await asyncio.open_connection("127.0.0.1", 1)
            except OSError:
                pass
    finally:
        sys.modules["socket"] = real_mod

    print("connect_error: close_called=%d" % close_count[0])


# -- Test 2: SSL wrap failure --
# Pass a mock SSL context whose wrap_socket() always raises.
# A real listener ensures connect() succeeds (EINPROGRESS), so we
# reach the SSL path.  Disable GC so leaked FDs are not finalised.

class FailingSSLContext:
    def wrap_socket(self, sock, **kw):
        raise OSError("simulated SSL failure")


async def test_ssl_wrap_failure():
    srv_sock = socket.socket()
    srv_sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv_sock.bind(socket.getaddrinfo("127.0.0.1", 48292)[0][-1])
    srv_sock.listen(1)

    gc.collect()
    gc.disable()
    fds_before = count_fds()

    for _ in range(10):
        try:
            await asyncio.open_connection("127.0.0.1", 48292, ssl=FailingSSLContext())
        except OSError:
            pass

    fds_after = count_fds()
    gc.enable()
    srv_sock.close()

    print("ssl_wrap_failure: leak=%d" % (fds_after - fds_before))


asyncio.run(test_connect_error())
asyncio.run(test_ssl_wrap_failure())
