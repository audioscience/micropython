"""
categories: Core,import
description: MicroPython doesn't support namespace packages split across filesystem by default.
cause: MicroPython's import system is highly optimized for simplicity, minimal memory usage, and minimal filesystem search overhead.
workaround: Enable MICROPY_MODULE_SPLIT_NAMESPACE_PACKAGES in the build configuration, or don't install modules belonging to the same namespace package in different directories.
"""

import sys

sys.path.append(sys.path[1] + "/modules")
sys.path.append(sys.path[1] + "/modules2")

import subpkg.foo
import subpkg.bar

print("Two modules of a split namespace package imported")
