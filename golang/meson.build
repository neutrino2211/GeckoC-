system = host_machine.system()

golang = find_program('go')

extension = '.dll'
builddir = 'build'

if system == 'darwin'
    extension = '.dylib'
elif system == 'linux'
    extension = '.so'
endif

output = 'go-parser.a'
src = meson.current_source_dir()

lib_files = [
    src + '/main.go',
    src + '/tokens.go'
]

message(lib_files)

go_parser_lib = custom_target(
    'go-parser',
    input: lib_files,
    output: output,
    command: ['zsh', src + '/scripts/build.sh', src, golang.full_path(), 'build/' + output, meson.current_build_dir()]
)