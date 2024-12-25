project(
  'my_project',
  ['c', 'cpp'],
  version: '0.1',
  default_options: ['cpp_std=c++20'],
)
incdir = include_directories('./include', '/usr/include/boost')

executable(
  'my_executable',
  'src/my_executable.cpp',
  sources: [
    'src/duktape.cpp',
    'src/mqtt.cpp',
    'src/components/component.cpp',
    'src/components/io.cpp',
    'src/components/javascript.cpp',
    'src/components/math.cpp',
    'src/components/setter.cpp',
    'src/components/string.cpp',
    'src/components/mqtt_component.cpp',
    'src/components/ble_component.cpp',
  ],
  include_directories: incdir,
)
executable('webserver', 'src/webserver.cpp', sources: ['src/duktape.cpp', 'src/mqtt.cpp'], include_directories : incdir)
