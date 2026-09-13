Import("env")

build_dir = '.pio/build/STC15W408AS/lib'
VariantDir(build_dir, 'src', duplicate=0)

build_lib_task = env.StaticLibrary(f'{build_dir}/stc15', [
    f'{build_dir}/uart.c',
    f'{build_dir}/timer8bit_ticks_to_mcs.c',
    f'{build_dir}/timer_Hz_to_ticks.c',
    f'{build_dir}/timer_Hz_to_ticks_8bit.c',
    f'{build_dir}/timer_ms_to_ticks.c',
    f'{build_dir}/timer_ms_to_ticks_table.c',
    f'{build_dir}/timer_ticks_to_Hz.c',
    f'{build_dir}/timer_ticks_to_ms.c'
])

env.Default(build_lib_task)