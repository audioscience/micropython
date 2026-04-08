"""
categories: Core,import
description: __path__ attribute of a regular package has a different type (single string instead of list of strings) in MicroPython
cause: MicroPython's import system is highly optimized for minimal memory usage. With MICROPY_MODULE_SPLIT_NAMESPACE_PACKAGES enabled, namespace packages (without __init__.py) get a list __path__, but regular packages still use a string.
workaround: Details of import handling is inherently implementation dependent. Don't rely on such details in portable applications.
"""

import modules

print(modules.__path__)
