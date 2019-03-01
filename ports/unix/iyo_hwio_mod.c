
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

STATIC mp_obj_t mod_iyo_hwio_set_input_mute(mp_obj_t index, mp_obj_t enable) {
    int r = hwioc_set_input_mute(mp_obj_get_int(index), !!mp_obj_get_int(enable));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_input_mute_obj, mod_iyo_hwio_set_input_mute);

STATIC mp_obj_t mod_iyo_hwio_set_led_diagnostic(mp_obj_t enable, mp_obj_t rgb_pwm) {
    int r = hwioc_set_led_diagnostic(!!mp_obj_get_int(enable), mp_obj_get_int(rgb_pwm));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_led_diagnostic_obj, mod_iyo_hwio_set_led_diagnostic);

STATIC mp_obj_t mod_iyo_hwio_toggle_aes67_transmitter(mp_obj_t index, mp_obj_t enable) {
    int r = hwioc_toggle_aes67_transmitter(mp_obj_get_int(index), !!mp_obj_get_int(enable));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_toggle_aes67_transmitter_obj, mod_iyo_hwio_toggle_aes67_transmitter);

STATIC mp_obj_t mod_iyo_hwio_subscribe_rx_ch_to_aes67_transmitter(mp_obj_t rx_ch_idx, mp_obj_t tx_flow_ip, mp_obj_t tx_flow_idx) {
    int r = hwioc_subscribe_rx_ch_to_aes67_transmitter(mp_obj_get_int(rx_ch_idx), mp_obj_str_get_str(tx_flow_ip), mp_obj_get_int(tx_flow_idx));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(mod_iyo_hwio_subscribe_rx_ch_to_aes67_transmitter_obj, mod_iyo_hwio_subscribe_rx_ch_to_aes67_transmitter);

STATIC mp_obj_t mod_iyo_hwio_set_save_pending_flag(mp_obj_t pending) {
    int r = hwioc_set_save_pending_flag(!!mp_obj_get_int(pending));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_set_save_pending_flag_obj, mod_iyo_hwio_set_save_pending_flag);

STATIC mp_obj_t mod_iyo_hwio_get_dante_device_name(void) {
    char * name = hwioc_get_dante_device_name();
    if (!name) {
        mp_raise_OSError(-1);
    }

    return MP_OBJ_FROM_PTR(MP_OBJ_NEW_QSTR(qstr_from_str(name)));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_dante_device_name_obj, mod_iyo_hwio_get_dante_device_name);

STATIC mp_obj_t mod_iyo_hwio_send_reboot_cmd(void) {
    int r = hwioc_send_device_reboot_cmd();

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_send_reboot_cmd_obj, mod_iyo_hwio_send_reboot_cmd);

STATIC mp_obj_t mod_iyo_hwio_send_identify_cmd(mp_obj_t enable) {
    int r = hwioc_send_device_identify_cmd(!!mp_obj_get_int(enable));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_send_identify_cmd_obj, mod_iyo_hwio_send_identify_cmd);

STATIC mp_obj_t mod_iyo_hwio_get_fds(void) {
    int m_fd = hwioc_meter_update_fd();
    int e_fd = hwioc_error_notification_fd();
    int a_fd = hwioc_aes67_tx_discovery_fd();

    mp_obj_tuple_t *t = MP_OBJ_TO_PTR(mp_obj_new_tuple(3, NULL));
    t->items[0] = mp_obj_new_int(m_fd);
    t->items[1] = mp_obj_new_int(e_fd);
    t->items[2] = mp_obj_new_int(a_fd);

    return MP_OBJ_FROM_PTR(t);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_fds_obj, mod_iyo_hwio_get_fds);

STATIC mp_obj_t mod_iyo_hwio_set_front_panel_brightness(mp_obj_t brightness) {
    int r = hwioc_set_front_panel_brightness(mp_obj_get_int(brightness));
    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_set_front_panel_brightness_obj, mod_iyo_hwio_set_front_panel_brightness);

STATIC mp_obj_t mod_iyo_hwio_get_dev_status(void) {
    char * dev_sync_status = hwioc_get_device_sync_status();
    char * dev_sys_status = hwioc_get_device_sys_status();

    mp_obj_tuple_t *t = MP_OBJ_TO_PTR(mp_obj_new_tuple(2, NULL));
    t->items[0] = MP_OBJ_NEW_QSTR(qstr_from_str(dev_sync_status));
    t->items[1] = MP_OBJ_NEW_QSTR(qstr_from_str(dev_sys_status));

    return MP_OBJ_FROM_PTR(t);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_dev_status_obj, mod_iyo_hwio_get_dev_status);

STATIC mp_obj_t mod_iyo_hwio_get_dev_temp(void) {
    int dev_temp = hwioc_get_device_temp();

    return MP_OBJ_FROM_PTR(mp_obj_new_int(dev_temp));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_dev_temp_obj, mod_iyo_hwio_get_dev_temp);

STATIC mp_obj_t mod_iyo_hwio_get_mac_address(void) {
    uint8_t * mac = hwioc_get_mac_address();
    if (!mac) {
        mp_raise_OSError(-1);
    }

    return MP_OBJ_FROM_PTR(mp_obj_new_bytearray(6, mac));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_get_mac_address_obj, mod_iyo_hwio_get_mac_address);

STATIC mp_obj_t mod_iyo_hwio_get_tx_ch_aes67_transport_ip(mp_obj_t index) {
    uint8_t * ip = hwioc_get_tx_ch_aes67_transport_ip(mp_obj_get_int(index));
    if (!ip) {
        mp_raise_OSError(-1);
    }

    return MP_OBJ_FROM_PTR(mp_obj_new_bytearray(4, ip));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_get_tx_ch_aes67_transport_ip_obj, mod_iyo_hwio_get_tx_ch_aes67_transport_ip);

STATIC mp_obj_t mod_iyo_hwio_get_rx_ch_aes67_sub_transport_ip(mp_obj_t index) {
    uint8_t * ip = hwioc_get_rx_ch_aes67_sub_transport_ip(mp_obj_get_int(index));
    if (!ip) {
        mp_raise_OSError(-1);
    }

    return MP_OBJ_FROM_PTR(mp_obj_new_bytearray(4, ip));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_get_rx_ch_aes67_sub_transport_ip_obj, mod_iyo_hwio_get_rx_ch_aes67_sub_transport_ip);

STATIC mp_obj_t mod_iyo_hwio_get_rx_ch_aes67_sub_channel_index(mp_obj_t index) {
    int ch_idx = hwioc_get_rx_ch_aes67_sub_channel_index(mp_obj_get_int(index));
    if (ch_idx < 0) {
        mp_raise_OSError(-1);
    }

    return MP_OBJ_FROM_PTR(mp_obj_new_int(ch_idx));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_get_rx_ch_aes67_sub_channel_index_obj, mod_iyo_hwio_get_rx_ch_aes67_sub_channel_index);

STATIC mp_obj_t mod_iyo_hwio_get_rx_ch_aes67_sub_connections_active(mp_obj_t index) {
    int connections_active = hwioc_get_rx_ch_aes67_sub_connections_active(mp_obj_get_int(index));
    if (connections_active < 0) {
        mp_raise_OSError(-1);
    }

    return MP_OBJ_FROM_PTR(mp_obj_new_int(connections_active));
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_get_rx_ch_aes67_sub_connections_active_obj, mod_iyo_hwio_get_rx_ch_aes67_sub_connections_active);

STATIC const mp_rom_map_elem_t mp_module_iyo_hwio_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_iyo_hwio) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mod_iyo_hwio_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_shutdown), MP_ROM_PTR(&mod_iyo_hwio_shutdown_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_trim_level), MP_ROM_PTR(&mod_iyo_hwio_set_trim_level_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_input_phantom_power), MP_ROM_PTR(&mod_iyo_hwio_set_input_phantom_power_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_input_mute), MP_ROM_PTR(&mod_iyo_hwio_set_input_mute_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_led_diagnostic), MP_ROM_PTR(&mod_iyo_hwio_set_led_diagnostic_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_save_pending_flag), MP_ROM_PTR(&mod_iyo_hwio_set_save_pending_flag_obj) },

    { MP_ROM_QSTR(MP_QSTR_send_reboot_cmd), MP_ROM_PTR(&mod_iyo_hwio_send_reboot_cmd_obj) },

    { MP_ROM_QSTR(MP_QSTR_send_identify_cmd), MP_ROM_PTR(&mod_iyo_hwio_send_identify_cmd_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_fds), MP_ROM_PTR(&mod_iyo_hwio_get_fds_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_dev_status), MP_ROM_PTR(&mod_iyo_hwio_get_dev_status_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_dev_temp), MP_ROM_PTR(&mod_iyo_hwio_get_dev_temp_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_mac_address), MP_ROM_PTR(&mod_iyo_hwio_get_mac_address_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_dante_device_name), MP_ROM_PTR(&mod_iyo_hwio_get_dante_device_name_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_tx_ch_aes67_transport_ip), MP_ROM_PTR(&mod_iyo_hwio_get_tx_ch_aes67_transport_ip_obj) },

    { MP_ROM_QSTR(MP_QSTR_toggle_aes67_transmitter), MP_ROM_PTR(&mod_iyo_hwio_toggle_aes67_transmitter_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_rx_ch_aes67_sub_transport_ip), MP_ROM_PTR(&mod_iyo_hwio_get_rx_ch_aes67_sub_transport_ip_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_rx_ch_aes67_sub_channel_index), MP_ROM_PTR(&mod_iyo_hwio_get_rx_ch_aes67_sub_channel_index_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_rx_ch_aes67_sub_connections_active), MP_ROM_PTR(&mod_iyo_hwio_get_rx_ch_aes67_sub_connections_active_obj) },

    { MP_ROM_QSTR(MP_QSTR_subscribe_rx_ch_to_aes67_transmitter), MP_ROM_PTR(&mod_iyo_hwio_subscribe_rx_ch_to_aes67_transmitter_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_front_panel_brightness), MP_ROM_PTR(&mod_iyo_hwio_set_front_panel_brightness_obj) },
};
STATIC MP_DEFINE_CONST_DICT(mp_module_iyo_hwio_globals, mp_module_iyo_hwio_globals_table);

const mp_obj_module_t mp_module_iyo_hwio = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_iyo_hwio_globals,
};
