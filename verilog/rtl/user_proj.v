// SPDX-FileCopyrightText: 2020 Efabless Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
// SPDX-License-Identifier: Apache-2.0

`default_nettype none

module user_proj #(
    parameter BITS = 32
)(
`ifdef USE_POWER_PINS
    inout vccd1,	// User area 1 1.8V supply
    inout vssd1,	// User area 1 digital ground
`endif

    // Wishbone Slave ports (WB MI A)
    input wire wb_clk_i,
    input wire wb_rst_i,
    input wire wbs_stb_i,
    input wire wbs_cyc_i,
    input wire wbs_we_i,
    input wire [3:0] wbs_sel_i,
    input wire [31:0] wbs_dat_i,
    input wire [31:0] wbs_adr_i,
    output wire wbs_ack_o,
    output wire [31:0] wbs_dat_o,

    // Logic Analyzer Signals
    input wire [127:0] la_data_in,
    output wire [127:0] la_data_out,
    input wire [127:0] la_oenb,

    // IOs
    input wire [37:0] io_in,
    output wire [37:0] io_out,
    output wire [37:0] io_oeb,

    // IRQ
    output wire [2:0] irq
);

    assign wbs_ack_o = 0;
    assign wbs_dat_o = 0;

    assign io_oeb = {{12{1'b0}},  // [37:26] = outputs
                     {12{1'b1}},  // [25:14] = inputs
                     {6{1'b1}},   // [13:8] = des select
                     {1{1'b1}},   // [7:7] = hold reset
                     {1{1'b1}},   // [6:6] = sync inputs
                     {1{1'b1}},   // [5:5] = reset
                     {5{1'b1}}};  // [4:0] = unused inputs

    assign io_out[25:0] = 0;

    reg [4:0] reset_sync;
    wire des_reset = reset_sync[4];
    always @(posedge wb_clk_i) begin
        reset_sync <= {reset_sync, io_in[5]};
    end

    CoreTop risc240_core (
        .clock(wb_clk_i),
        .reset(des_reset),
        .io_la_data_in(la_data_in),
        .io_la_data_out(la_data_out),
        .io_la_oenb(la_oenb)
    );

    design_instantiations designs (
        .io_in(io_in[25:14]),
        .io_out(io_out[37:26]),
        .clock(wb_clk_i),
        .reset(des_reset),
        .des_sel(io_in[13:8]),
        .hold_if_not_sel(io_in[7]),
        .sync_inputs(io_in[6])
    );

endmodule

`default_nettype wire
