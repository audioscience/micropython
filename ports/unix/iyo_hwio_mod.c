
#include <hwio/hwioc.h>
#include "extmod/misc.h"

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>


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

STATIC mp_obj_t mod_iyo_hwio_set_gpo(mp_obj_t index, mp_obj_t bits) {
    int r = hwioc_set_gpo(mp_obj_get_int(index), mp_obj_get_int(bits));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_gpo_obj, mod_iyo_hwio_set_gpo);

STATIC mp_obj_t mod_iyo_hwio_set_input_mute(mp_obj_t index, mp_obj_t enable) {
    int r = hwioc_set_input_mute(mp_obj_get_int(index), !!mp_obj_get_int(enable));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_input_mute_obj, mod_iyo_hwio_set_input_mute);

STATIC mp_obj_t mod_iyo_hwio_set_output_mute(mp_obj_t index, mp_obj_t enable) {
    int r = hwioc_set_output_mute(mp_obj_get_int(index), !!mp_obj_get_int(enable));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_output_mute_obj, mod_iyo_hwio_set_output_mute);

STATIC mp_obj_t mod_iyo_hwio_set_led_diagnostic(mp_obj_t enable, mp_obj_t rgb_pwm) {
    int r = hwioc_set_led_diagnostic(!!mp_obj_get_int(enable), mp_obj_get_int(rgb_pwm));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_set_led_diagnostic_obj, mod_iyo_hwio_set_led_diagnostic);

STATIC mp_obj_t mod_iyo_hwio_add_aes67_transmit_flow(mp_obj_t ip, mp_obj_t base_ch_idx, mp_obj_t channel_count) {
    int r = hwioc_add_aes67_transmit_flow(mp_obj_str_get_str(ip), mp_obj_get_int(base_ch_idx), mp_obj_get_int(channel_count));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(mod_iyo_hwio_add_aes67_transmit_flow_obj, mod_iyo_hwio_add_aes67_transmit_flow);

STATIC mp_obj_t mod_iyo_hwio_delete_aes67_transmit_flow(mp_obj_t base_ch_idx, mp_obj_t channel_count) {
    int r = hwioc_delete_aes67_transmit_flow(mp_obj_get_int(base_ch_idx), mp_obj_get_int(channel_count));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_delete_aes67_transmit_flow_obj, mod_iyo_hwio_delete_aes67_transmit_flow);

STATIC mp_obj_t mod_iyo_hwio_add_aes67_receive_flow(mp_obj_t rx_sub_ip, mp_obj_t base_ch_idx, mp_obj_t channel_count) {
    int r = hwioc_add_aes67_receive_flow(mp_obj_str_get_str(rx_sub_ip), mp_obj_get_int(base_ch_idx), mp_obj_get_int(channel_count));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(mod_iyo_hwio_add_aes67_receive_flow_obj, mod_iyo_hwio_add_aes67_receive_flow);

STATIC mp_obj_t mod_iyo_hwio_delete_aes67_receive_flow(mp_obj_t rx_sub_ip) {
    int r = hwioc_delete_aes67_receive_flow(mp_obj_str_get_str(rx_sub_ip));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_delete_aes67_receive_flow_obj, mod_iyo_hwio_delete_aes67_receive_flow);

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

STATIC mp_obj_t mod_iyo_hwio_signal_objects_restore_done(void) {
    int r = hwioc_signal_objects_restore_done();

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_signal_objects_restore_done_obj, mod_iyo_hwio_signal_objects_restore_done);

STATIC mp_obj_t mod_iyo_hwio_send_identify_cmd(mp_obj_t enable) {
    int r = hwioc_send_device_identify_cmd(!!mp_obj_get_int(enable));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_send_identify_cmd_obj, mod_iyo_hwio_send_identify_cmd);

STATIC mp_obj_t mod_iyo_hwio_set_user_data_label(mp_obj_t label) {
    int r = hwioc_set_dante_device_name(mp_obj_str_get_str(label));

    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_set_user_data_label_obj, mod_iyo_hwio_set_user_data_label);

STATIC mp_obj_t mod_iyo_hwio_get_fds(void) {
    int m_fd = hwioc_meter_update_fd();
    int c_fd = hwioc_conmon_to_py_fd();
    int a_fd = hwioc_conmon_aes67_to_py_fd();
    int cs_fd = hwioc_conmon_str_to_py_fd();
    int x_fd = hwioc_xmos_to_py_fd();
    int xs_fd = hwioc_xmos_str_to_py_fd();

    mp_obj_tuple_t *t = MP_OBJ_TO_PTR(mp_obj_new_tuple(6, NULL));
    t->items[0] = mp_obj_new_int(m_fd);
    t->items[1] = mp_obj_new_int(c_fd);
    t->items[2] = mp_obj_new_int(a_fd);
    t->items[3] = mp_obj_new_int(cs_fd);
    t->items[4] = mp_obj_new_int(x_fd);
    t->items[5] = mp_obj_new_int(xs_fd);

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

STATIC mp_obj_t mod_iyo_hwio_set_front_panel_phantom_power_indication(mp_obj_t enable) {
    int r = hwioc_set_front_panel_phantom_power_indication(!!mp_obj_get_int(enable));
    if (r < 0) {
        mp_raise_OSError(-r);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(mod_iyo_hwio_set_front_panel_phantom_power_indication_obj, mod_iyo_hwio_set_front_panel_phantom_power_indication);

static int i2c_file = 0;

STATIC mp_obj_t mod_iyo_hwio_i2c_io_open(void) {
    char *filename = "/dev/i2c-0";
    i2c_file = open(filename, O_RDWR);
    if (i2c_file < 0) {
        mp_raise_OSError(i2c_file);
    }
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_i2c_io_open_obj, mod_iyo_hwio_i2c_io_open);

STATIC mp_obj_t mod_iyo_hwio_i2c_io_close(void) {
    close(i2c_file);
    i2c_file = 0;
    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_0(mod_iyo_hwio_i2c_io_close_obj, mod_iyo_hwio_i2c_io_close);

STATIC mp_obj_t mod_iyo_hwio_i2c_read_reg(mp_obj_t i2c_addr_param, mp_obj_t reg_addr_param) {
    int i2c_addr = mp_obj_get_int(i2c_addr_param);
    int reg_addr = mp_obj_get_int(reg_addr_param);
    uint8_t inbuf, outbuf;
    struct i2c_rdwr_ioctl_data packets;
    struct i2c_msg messages[2];
    int ioctl_rslt;

    outbuf = reg_addr;
    messages[0].addr  = i2c_addr;
    messages[0].flags = 0;
    messages[0].len   = 1;
    messages[0].buf   = &outbuf;

    messages[1].addr  = i2c_addr;
    messages[1].flags = I2C_M_RD;
    messages[1].len   = 1;
    messages[1].buf   = &inbuf;

    packets.msgs      = messages;
    packets.nmsgs     = 2;
    
    ioctl_rslt = ioctl(i2c_file, I2C_RDWR, &packets);
    if (ioctl_rslt < 0) {
        mp_raise_OSError(ioctl_rslt);
    }

    return mp_obj_new_int((mp_int_t)inbuf);
}
STATIC MP_DEFINE_CONST_FUN_OBJ_2(mod_iyo_hwio_i2c_read_reg_obj, mod_iyo_hwio_i2c_read_reg);

STATIC mp_obj_t mod_iyo_hwio_i2c_write_reg(mp_obj_t i2c_addr_param, mp_obj_t reg_addr_param, mp_obj_t value_param) {
    int i2c_addr = mp_obj_get_int(i2c_addr_param);
    int reg_addr = mp_obj_get_int(reg_addr_param);
    int reg_value = mp_obj_get_int(value_param);
	struct i2c_rdwr_ioctl_data msgset;
	struct i2c_msg msg_details[1];
	uint8_t buf[2];
    int ioctl_rslt;
	
	buf[0] = reg_addr;
	buf[1] = reg_value;
	msg_details[0].addr = i2c_addr;
	msg_details[0].len = 2;
	msg_details[0].flags = 0;
	msg_details[0].buf = buf;

	msgset.nmsgs = 1;
	msgset.msgs = msg_details;

    ioctl_rslt = ioctl(i2c_file, I2C_RDWR, (unsigned long int)&msgset);
    if (ioctl_rslt < 0) {
        mp_raise_OSError(ioctl_rslt);
    }

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(mod_iyo_hwio_i2c_write_reg_obj, mod_iyo_hwio_i2c_write_reg);


STATIC const mp_rom_map_elem_t mp_module_iyo_hwio_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_iyo_hwio) },
    { MP_ROM_QSTR(MP_QSTR_init), MP_ROM_PTR(&mod_iyo_hwio_init_obj) },
    { MP_ROM_QSTR(MP_QSTR_shutdown), MP_ROM_PTR(&mod_iyo_hwio_shutdown_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_trim_level), MP_ROM_PTR(&mod_iyo_hwio_set_trim_level_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_input_phantom_power), MP_ROM_PTR(&mod_iyo_hwio_set_input_phantom_power_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_gpo), MP_ROM_PTR(&mod_iyo_hwio_set_gpo_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_input_mute), MP_ROM_PTR(&mod_iyo_hwio_set_input_mute_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_output_mute), MP_ROM_PTR(&mod_iyo_hwio_set_output_mute_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_led_diagnostic), MP_ROM_PTR(&mod_iyo_hwio_set_led_diagnostic_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_save_pending_flag), MP_ROM_PTR(&mod_iyo_hwio_set_save_pending_flag_obj) },

    { MP_ROM_QSTR(MP_QSTR_send_reboot_cmd), MP_ROM_PTR(&mod_iyo_hwio_send_reboot_cmd_obj) },

    { MP_ROM_QSTR(MP_QSTR_signal_objects_restore_done), MP_ROM_PTR(&mod_iyo_hwio_signal_objects_restore_done_obj) },

    { MP_ROM_QSTR(MP_QSTR_send_identify_cmd), MP_ROM_PTR(&mod_iyo_hwio_send_identify_cmd_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_user_data_label), MP_ROM_PTR(&mod_iyo_hwio_set_user_data_label_obj) },

    { MP_ROM_QSTR(MP_QSTR_get_fds), MP_ROM_PTR(&mod_iyo_hwio_get_fds_obj) },

    { MP_ROM_QSTR(MP_QSTR_add_aes67_transmit_flow), MP_ROM_PTR(&mod_iyo_hwio_add_aes67_transmit_flow_obj) },

    { MP_ROM_QSTR(MP_QSTR_delete_aes67_transmit_flow), MP_ROM_PTR(&mod_iyo_hwio_delete_aes67_transmit_flow_obj) },

    { MP_ROM_QSTR(MP_QSTR_add_aes67_receive_flow), MP_ROM_PTR(&mod_iyo_hwio_add_aes67_receive_flow_obj) },

    { MP_ROM_QSTR(MP_QSTR_delete_aes67_receive_flow), MP_ROM_PTR(&mod_iyo_hwio_delete_aes67_receive_flow_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_front_panel_brightness), MP_ROM_PTR(&mod_iyo_hwio_set_front_panel_brightness_obj) },

    { MP_ROM_QSTR(MP_QSTR_set_front_panel_phantom_power_indication), MP_ROM_PTR(&mod_iyo_hwio_set_front_panel_phantom_power_indication_obj) },

    { MP_ROM_QSTR(MP_QSTR_i2c_io_open), MP_ROM_PTR(&mod_iyo_hwio_i2c_io_open_obj) },

    { MP_ROM_QSTR(MP_QSTR_i2c_io_close), MP_ROM_PTR(&mod_iyo_hwio_i2c_io_close_obj) },

    { MP_ROM_QSTR(MP_QSTR_i2c_read_reg), MP_ROM_PTR(&mod_iyo_hwio_i2c_read_reg_obj) },

    { MP_ROM_QSTR(MP_QSTR_i2c_write_reg), MP_ROM_PTR(&mod_iyo_hwio_i2c_write_reg_obj) },

};
STATIC MP_DEFINE_CONST_DICT(mp_module_iyo_hwio_globals, mp_module_iyo_hwio_globals_table);

const mp_obj_module_t mp_module_iyo_hwio = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_iyo_hwio_globals,
};
