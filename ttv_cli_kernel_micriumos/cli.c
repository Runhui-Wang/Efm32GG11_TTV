#include "cli.h"
#include "sl_iostream.h"
#include "sl_iostream_init_instances.h"
#include "sl_iostream_handles.h"

#include "task.h"
#include "user_spi_interface.h"
#include "em_gpio.h"
#include "em_cmu.h"
//Public Variables
bool status;
uint64_t time_off;

static const sl_cli_command_info_t cmd__echoint =
SL_CLI_COMMAND(set_time,
    "Set the time",
    "?",
      { SL_CLI_ARG_INT32, SL_CLI_ARG_END,});

static sl_cli_command_entry_t a_table[] =
  {
    { "set_time", &cmd__echoint, false },

    { NULL, NULL, false }, };

static sl_cli_command_group_t a_group =
  {
    { NULL },
  false, a_table };
sl_cli_command_group_t *command_group = &a_group;



void cli_init(){

  printf("CLI_Initialized! Enter set_time var () to start. \n");
  status = sl_cli_command_add_command_group (sl_cli_inst_handle, command_group);
  EFM_ASSERT(status);

}

void set_time (sl_cli_command_arg_t *arguments)
{
  uint64_t argument_value;
  RTOS_ERR err;
  // Read all the arguments provided as integers and print them back

  argument_value = (uint64_t) sl_cli_get_argument_int32(arguments, 0);

  time_off = argument_value;

  task_init();

}
void uart_init(){

}
void spi_init(){

}

