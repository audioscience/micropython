freeze_as_mpy('$(MPY_DIR)/tools', 'upip.py')
freeze_as_mpy('$(MPY_DIR)/tools', 'upip_utarfile.py', opt=3)
include("$(MPY_DIR)/extmod/uasyncio/manifest.py")
