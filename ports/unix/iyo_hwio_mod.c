
#include <hwio/hwioc.h>
#include "extmod/misc.h"


STATIC mp_obj_t mod_iyo_hwio_init(mp_obj_t loglevel) {
    int r = hwioc_init(mp_obj_get_int(loglevel));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_init_obj, mod_iyo_hwio_init);


STATIC mp_obj_t mod_iyo_hwio_shutdown(void) {
    hwioc_shutdown();

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_shutdown_obj, mod_iyo_hwio_shutdown);


STATIC mp_obj_t mod_iyo_hwio_set_trim_level(mp_obj_t index, mp_obj_t is_input, mp_obj_t level) {
    int r = hwioc_set_trim_level(mp_obj_get_int(index), !!mp_obj_get_int(is_input), mp_obj_get_int(level));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(mod_iyo_hwio_set_trim_level_obj, mod_iyo_hwio_set_trim_level);


STATIC mp_obj_t mod_iyo_hwio_set_input_phantom_power(mp_obj_t index, mp_obj_t enable) {
    int r = hwioc_set_input_phantom_power(mp_obj_get_int(index), !!mp_obj_get_int(enable));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_input_phantom_power_obj, mod_iyo_hwio_set_input_phantom_power);

STATIC mp_obj_t mod_iyo_hwio_set_led_diagnostic(mp_obj_t enable, mp_obj_t rgb_pwm) {
    int r = hwioc_set_led_diagnostic(!!mp_obj_get_int(enable), mp_obj_get_int(rgb_pwm));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_led_diagnostic_obj, mod_iyo_hwio_set_led_diagnostic);

STATIC mp_obj_t mod_iyo_hwio_set_save_pending_flag(mp_obj_t pending) {
    int r = hwioc_set_save_pending_flag(!!mp_obj_get_int(pending));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_set_save_pending_flag_obj, mod_iyo_hwio_set_save_pending_flag);

STATIC mp_obj_t mod_iyo_hwio_send_reboot_cmd(void) {
    int r = hwioc_send_device_reboot_cmd();

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_send_reboot_cmd_obj, mod_iyo_hwio_send_reboot_cmd);

STATIC mp_obj_t mod_iyo_hwio_send_identify_cmd(void) {
    int r = hwioc_send_device_identify_cmd();

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_send_identify_cmd_obj, mod_iyo_hwio_send_identify_cmd);

STATIC mp_obj_t mod_iyo_hwio_get_fds(void) {
    int m_fd = hwioc_meter_update_fd();
    int e_fd = hwioc_error_notification_fd();

    mp_obj_tuple_t *t = MP_OBJ_TO_PTR(mp_obj_new_tuple(2, NULL));
    t->items[0] = mp_obj_new_int(m_fd);
    t->items[1] = mp_obj_new_int(e_fd);

    return MP_OBJ_FROM_PTR(t);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_fds_obj, mod_iyo_hwio_get_fds);

STATIC mp_obj_t mod_iyo_hwio_get_dev_status(void) {
    int dev_sync_status = hwioc_get_device_sync_status();
    int dev_sys_status = hwioc_get_device_sys_status();

    mp_obj_tuple_t *t = MP_OBJ_TO_PTR(mp_obj_new_tuple(2, NULL));
    t->items[0] = mp_obj_new_int(dev_sync_status);
    t->items[1] = mp_obj_new_int(dev_sys_status);

    return MP_OBJ_FROM_PTR(t);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_dev_status_obj, mod_iyo_hwio_get_dev_status);

STATIC mp_obj_t mod_iyo_hwio_get_mac_address(void) {
    int i;
    mp_obj_tuple_t *t = MP_OBJ_TO_PTR(mp_obj_new_tuple(6, NULL));
    for (i = 0; i < 6; i++) {
        t->items[i] = mp_obj_new_int(hwioc_get_mac_address_byte(i));
    }

    return MP_OBJ_FROM_PTR(t);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_mac_address_obj, mod_iyo_hwio_get_mac_address);

STATIC const mp_rom_map_elem_t mp_module_iyo_hwio_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_iyo_hwio) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mod_iyo_hwio_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_shutdown), MP_ROM_PTR(&mod_iyo_hwio_shutdown_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_trim_level), MP_ROM_PTR(&mod_iyo_hwio_set_trim_level_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_input_phantom_power), MP_ROM_PTR(&mod_iyo_hwio_set_input_phantom_power_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_led_diagnostic), MP_ROM_PTR(&mod_iyo_hwio_set_led_diagnostic_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_save_pending_flag), MP_ROM_PTR(&mod_iyo_hwio_set_save_pending_flag_obj) },

    { MP_ROM_QSTR(MP_QSTR_send_reboot_cmd), MP_ROM_PTR(&mod_iyo_hwio_send_reboot_cmd_obj) },

    { MP_ROM_QSTR(MP_QSTR_send_identify_cmd), MP_ROM_PTR(&mod_iyo_hwio_send_identify_cmd_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_fds), MP_ROM_PTR(&mod_iyo_hwio_get_fds_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_dev_status), MP_ROM_PTR(&mod_iyo_hwio_get_dev_status_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_mac_address), MP_ROM_PTR(&mod_iyo_hwio_get_mac_address_obj) },    
};
STATIC MP_DEFINE_CONST_DICT(mp_module_iyo_hwio_globals, mp_module_iyo_hwio_globals_table);

const mp_obj_module_t mp_module_iyo_hwio = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_iyo_hwio_globals,
};
