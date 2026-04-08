# Test split namespace packages: sub-modules of the same namespace package
# located in different directories on sys.path.
# Requires MICROPY_MODULE_SPLIT_NAMESPACE_PACKAGES to be enabled.

import sys

_f = __file__.replace("\\", "/")
test_dir = _f[:_f.rfind("/")] if "/" in _f else "."

sys.path.insert(0, test_dir + "/split_ns_dir1")
sys.path.insert(1, test_dir + "/split_ns_dir2")

# Detect feature by checking if __path__ is a list (split ns) vs string.
import nspkg
if not isinstance(nspkg.__path__, list):
    print("SKIP")
    raise SystemExit

import nspkg.mod_a
import nspkg.mod_b
print("split namespace package OK")
