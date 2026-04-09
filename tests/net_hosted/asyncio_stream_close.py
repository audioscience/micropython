# Test that Stream.close() and wait_closed() match CPython semantics:
#   - close() actually closes the underlying socket
#   - wait_closed() is a no-op (socket already closed by close())
#   - aclose() closes the socket (calls close() internally)
#   - double close is safe (no exception)

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


async def test():
    # Test 1: close() alone must close the underlying socket
    reader, writer = await asyncio.open_connection("127.0.0.1", port)
    fd = writer.s.fileno()
    assert fd >= 0, "socket should be open"
    writer.close()
    print("close: fd=%d" % writer.s.fileno())

    await asyncio.sleep(0)

    # Test 2: close() + wait_closed() — idiomatic CPython pattern
    reader, writer = await asyncio.open_connection("127.0.0.1", port)
    writer.close()
    await writer.wait_closed()
    print("close+wait_closed: fd=%d" % writer.s.fileno())

    await asyncio.sleep(0)

    # Test 3: aclose() alone
    reader, writer = await asyncio.open_connection("127.0.0.1", port)
    await writer.aclose()
    print("aclose: fd=%d" % writer.s.fileno())

    await asyncio.sleep(0)

    # Test 4: double close — must not raise
    reader, writer = await asyncio.open_connection("127.0.0.1", port)
    writer.close()
    writer.close()
    print("double_close: fd=%d" % writer.s.fileno())

    await asyncio.sleep(0)

    # Test 5: FD leak check — close() without wait_closed() must not leak
    gc.collect()
    gc.disable()
    fds_before = count_fds()
    for _ in range(10):
        reader, writer = await asyncio.open_connection("127.0.0.1", port)
        writer.close()
        await asyncio.sleep(0)
    fds_after = count_fds()
    gc.enable()
    print("close_only_leak: %d" % (fds_after - fds_before))

    server.close()
    await server.wait_closed()


async def dummy_handler(r, w):
    await r.read(-1)
    w.close()


server = None
port = 48293


async def main():
    global server
    server = await asyncio.start_server(dummy_handler, "0.0.0.0", port)
    await test()


asyncio.run(main())
