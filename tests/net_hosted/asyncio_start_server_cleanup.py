# Test that asyncio.start_server cleans up socket on bind/listen failure.
# Binding to an already-occupied port should raise EADDRINUSE and not
# leak the newly-created socket FD.

import sys

if sys.platform != "linux":
    print("SKIP")
    raise SystemExit

try:
    import asyncio
    import gc
    import os
except ImportError:
    print("SKIP")
    raise SystemExit


def count_fds():
    return len(os.listdir("/proc/self/fd"))


async def test():
    server = await asyncio.start_server(None, "0.0.0.0", 48291)

    gc.collect()
    gc.disable()
    fds_before = count_fds()

    for _ in range(10):
        try:
            await asyncio.start_server(None, "0.0.0.0", 48291)
        except OSError:
            pass

    fds_after = count_fds()
    gc.enable()

    server.close()
    await server.wait_closed()

    print("bind_failure: leak=%d" % (fds_after - fds_before))


asyncio.run(test())
