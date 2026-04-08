# Test that split namespace package support does not break existing imports:
# 1. Regular packages (with __init__.py) still work
# 2. Single-directory namespace packages (without __init__.py) still work
# This test must pass regardless of MICROPY_MODULE_SPLIT_NAMESPACE_PACKAGES.

import pkg.mod
print("regular package:", pkg.mod.foo())

import pkg8.mod
print("single-dir ns package OK")
