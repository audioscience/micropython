# Test that __path__ of a split namespace package is a list containing
# all contributing directories.
# Requires MICROPY_MODULE_SPLIT_NAMESPACE_PACKAGES to be enabled.

import sys

_f = __file__.replace("\\", "/")
test_dir = _f[:_f.rfind("/")] if "/" in _f else "."

sys.path.insert(0, test_dir + "/split_ns_dir1")
sys.path.insert(1, test_dir + "/split_ns_dir2")

import nspkg

p = nspkg.__path__
if not isinstance(p, list):
    print("SKIP")
    raise SystemExit

print("type:", type(p).__name__)
print("len:", len(p))

# Verify both directories are present (check basenames of parent dirs).
dirs = []
for d in p:
    d = d.replace("\\", "/")
    parent = d[:d.rfind("/")] if "/" in d else d
    name = parent[parent.rfind("/") + 1:] if "/" in parent else parent
    dirs.append(name)
dirs.sort()
print("dirs:", dirs)
