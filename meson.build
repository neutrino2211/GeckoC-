project('Gecko', 'cpp',
          version: '0.0.1',
    meson_version: '>= 0.57.0',
  default_options: [ 'warning_level=2',
                     'cpp_std=c++17',
                   ],
)

add_project_arguments([
    '-I' + meson.current_source_dir()
], language: 'cpp')

gecko_sources = [
    'ast.cpp',
    'colors.cpp',
    'commander.cpp',
    'errors.cpp',
    'Gecko.cpp',
    'keyword.cpp',
    'keywords.cpp',
    'lexer.cpp',
    'parser.cpp',
    'readfile.cpp',
    'utils.cpp'
]

subdir('golang')

executable('gecko', gecko_sources, link_with: go_parser_lib, install: true)