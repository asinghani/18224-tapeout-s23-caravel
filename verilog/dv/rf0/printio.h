
void shift_char(char c) {
    uint32_t x = c;
    reg_mprj_datal = (x<<24)|(x<<16)|(x<<8)|(x);

    reg_gpio_oe = 1;
    reg_gpio_out = 1;
    reg_gpio_out = 1;
    // should be enough delay to detect output
    reg_gpio_out = 0;
}

void setup_out() {
    reg_mprj_io_15 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_14 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_13 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_12 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_11 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_10 = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_9  = GPIO_MODE_MGMT_STD_OUTPUT;
    reg_mprj_io_8  = GPIO_MODE_MGMT_STD_OUTPUT;

    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void write_char(char c) {
    uint32_t tmp7 = reg_mprj_io_15;
    uint32_t tmp6 = reg_mprj_io_14;
    uint32_t tmp5 = reg_mprj_io_13;
    uint32_t tmp4 = reg_mprj_io_12;
    uint32_t tmp3 = reg_mprj_io_11;
    uint32_t tmp2 = reg_mprj_io_10;
    uint32_t tmp1 = reg_mprj_io_9;
    uint32_t tmp0 = reg_mprj_io_8;

    setup_out();

    shift_char(c);

    reg_mprj_io_15 = tmp7;
    reg_mprj_io_14 = tmp6;
    reg_mprj_io_13 = tmp5;
    reg_mprj_io_12 = tmp4;
    reg_mprj_io_11 = tmp3;
    reg_mprj_io_10 = tmp2;
    reg_mprj_io_9  = tmp1;
    reg_mprj_io_8  = tmp0;

    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void printhex(uint32_t x, bool newline) {
    uint32_t tmp7 = reg_mprj_io_15;
    uint32_t tmp6 = reg_mprj_io_14;
    uint32_t tmp5 = reg_mprj_io_13;
    uint32_t tmp4 = reg_mprj_io_12;
    uint32_t tmp3 = reg_mprj_io_11;
    uint32_t tmp2 = reg_mprj_io_10;
    uint32_t tmp1 = reg_mprj_io_9;
    uint32_t tmp0 = reg_mprj_io_8;

    setup_out();

    char *s = "0123456789abcdef";

    for (int i = 0; i < 8; i++) {
        shift_char(s[(x & 0xF0000000) >> 28]);
        x = x << 4;
    }
    if(newline) shift_char('\n');

    reg_mprj_io_15 = tmp7;
    reg_mprj_io_14 = tmp6;
    reg_mprj_io_13 = tmp5;
    reg_mprj_io_12 = tmp4;
    reg_mprj_io_11 = tmp3;
    reg_mprj_io_10 = tmp2;
    reg_mprj_io_9  = tmp1;
    reg_mprj_io_8  = tmp0;

    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void printstr(char *str) {
    uint32_t tmp7 = reg_mprj_io_15;
    uint32_t tmp6 = reg_mprj_io_14;
    uint32_t tmp5 = reg_mprj_io_13;
    uint32_t tmp4 = reg_mprj_io_12;
    uint32_t tmp3 = reg_mprj_io_11;
    uint32_t tmp2 = reg_mprj_io_10;
    uint32_t tmp1 = reg_mprj_io_9;
    uint32_t tmp0 = reg_mprj_io_8;

    setup_out();

    char c;
    while (*str) shift_char(*str++);

    reg_mprj_io_15 = tmp7;
    reg_mprj_io_14 = tmp6;
    reg_mprj_io_13 = tmp5;
    reg_mprj_io_12 = tmp4;
    reg_mprj_io_11 = tmp3;
    reg_mprj_io_10 = tmp2;
    reg_mprj_io_9  = tmp1;
    reg_mprj_io_8  = tmp0;

    reg_mprj_xfer = 1;
    while (reg_mprj_xfer == 1);
}

void endtest() {
    printstr("\x04");
}

